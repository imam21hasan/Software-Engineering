#include <stdio.h>
#define MAX 100

void printTable(int n, int pid[], int at[], int bt[], int ct[], int tat[], int wt[], int rt[]) {
    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }
}

// -------- SJF PREEMPTIVE --------
void sjf_preemptive(int n, int at[], int bt[]) {
    int rem_bt[MAX], ct[MAX], tat[MAX], wt[MAX], rt[MAX], visited[MAX] = {0}, pid[MAX];

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        rem_bt[i] = bt[i];
    }

    int time = 0, completed = 0;
    int timeline[MAX], t_index = 0;

    printf("\n|");

    while (completed < n) {
        int idx = -1, min_bt = 100000;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rem_bt[i] > 0) {
                if (rem_bt[i] < min_bt) {
                    min_bt = rem_bt[i];
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            printf(" Idle |");
            time++;
            timeline[t_index++] = time;
            continue;
        }

        if (!visited[idx]) {
            rt[idx] = time - at[idx];
            visited[idx] = 1;
        }

        printf(" P%d |", pid[idx]);

        rem_bt[idx]--;
        time++;

        if (rem_bt[idx] == 0) {
            ct[idx] = time;
            completed++;
        }

        timeline[t_index++] = time;
    }

    printf("\n0");
    for (int i = 0; i < t_index; i++) printf("    %d", timeline[i]);

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    printTable(n, pid, at, bt, ct, tat, wt, rt);
}

// -------- PRIORITY NON PREEMPTIVE --------
void priority_non_preemptive(int n, int at[], int bt[], int pr[]) {
    int ct[MAX], tat[MAX], wt[MAX], rt[MAX], completed[MAX] = {0}, pid[MAX];

    for (int i = 0; i < n; i++)
        pid[i] = i + 1;

    int time = 0, done = 0;
    int timeline[MAX], t_index = 0;

    printf("\n|");

    while (done < n) {
        int idx = -1, highest = 100000;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && !completed[i]) {
                if (pr[i] < highest) {
                    highest = pr[i];
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            printf(" Idle |");
            time++;
            timeline[t_index++] = time;
            continue;
        }

        printf(" P%d |", pid[idx]);

        rt[idx] = time - at[idx];
        time += bt[idx];
        ct[idx] = time;

        timeline[t_index++] = time;

        completed[idx] = 1;
        done++;
    }

    printf("\n0");
    for (int i = 0; i < t_index; i++) printf("    %d", timeline[i]);

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    printTable(n, pid, at, bt, ct, tat, wt, rt);
}

// PRIORITY PREEMPTIVE
void priority_preemptive(int n, int at[], int bt[], int pr[]) {
    int rem_bt[MAX], ct[MAX], tat[MAX], wt[MAX], rt[MAX], visited[MAX] = {0}, pid[MAX];

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        rem_bt[i] = bt[i];
    }

    int time = 0, completed = 0;
    int timeline[MAX], t_index = 0;

    printf("\n|");

    while (completed < n) {
        int idx = -1, highest = 100000;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rem_bt[i] > 0) {
                if (pr[i] < highest) {
                    highest = pr[i];
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            printf(" Idle |");
            time++;
            timeline[t_index++] = time;
            continue;
        }

        if (!visited[idx]) {
            rt[idx] = time - at[idx];
            visited[idx] = 1;
        }

        printf(" P%d |", pid[idx]);

        rem_bt[idx]--;
        time++;

        if (rem_bt[idx] == 0) {
            ct[idx] = time;
            completed++;
        }

        timeline[t_index++] = time;
    }

    printf("\n0");
    for (int i = 0; i < t_index; i++) printf("    %d", timeline[i]);

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    printTable(n, pid, at, bt, ct, tat, wt, rt);
}

int main() {
    int n, choice;

    printf("Enter number of processes : ");
    scanf("%d", &n);

    int at[MAX], bt[MAX], pr[MAX];

    printf("Enter Arrival Time : ");
    for (int i = 0; i < n; i++) scanf("%d", &at[i]);

    printf("Enter Burst Time : ");
    for (int i = 0; i < n; i++) scanf("%d", &bt[i]);

    printf("Enter Priority : ");
    for (int i = 0; i < n; i++) scanf("%d", &pr[i]);

    printf("\n1.SJF(Preemptive)\n2.Priority(Non Preemptive)\n3.Priority(Preemptive)\n");
    printf("Enter choice : ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        sjf_preemptive(n, at, bt);
        break;
    case 2:
        priority_non_preemptive(n, at, bt, pr);
        break;
    case 3:
        priority_preemptive(n, at, bt, pr);
        break;
    default:
        printf("Invalid choice\n");
    }

    return 0;
}
