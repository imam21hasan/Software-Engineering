#include <stdio.h>

#define MAX 100

void printTable(int n, int pid[], int at[], int bt[], int ct[], int tat[], int wt[], int rt[])
{
    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }
}

// -------- FCFS --------
void fcfs(int n, int at[], int bt[])
{
    int ct[MAX], tat[MAX], wt[MAX], rt[MAX], pid[MAX];

    for (int i = 0; i < n; i++)
        pid[i] = i + 1;

    // Sorting by arrival time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (at[j] > at[j + 1])
            {
                int temp;

                temp = at[j];   at[j] = at[j + 1];  at[j + 1] = temp;
                temp = bt[j];   bt[j] = bt[j + 1];  bt[j + 1] = temp;
                temp = pid[j];  pid[j] = pid[j + 1];    pid[j + 1] = temp;
            }
        }
    }

    int time = 0;
    int timeline[MAX], t_index = 0;

    // Gantt Chart (Process part)
    printf("\n|");

    for (int i = 0; i < n; i++)
    {
        if (time < at[i])
        {
            printf(" Idle |");
            time = at[i];
            timeline[t_index++] = time;
        }

        printf(" P%d |", pid[i]);

        rt[i] = time - at[i];
        time += bt[i];
        ct[i] = time;

        timeline[t_index++] = time;
    }

    // Gantt Chart (Time part)
    printf("\n0");
    for (int i = 0; i < t_index; i++)
    {
        printf("    %d", timeline[i]);
    }

    for (int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    printTable(n, pid, at, bt, ct, tat, wt, rt);
}

// -------- SJF --------
void sjf(int n, int at[], int bt[])
{
    int ct[MAX], tat[MAX], wt[MAX], rt[MAX], completed[MAX] = {0}, pid[MAX];

    for (int i = 0; i < n; i++)
        pid[i] = i + 1;

    int time = 0, done = 0;
    int timeline[MAX], t_index = 0;

    printf("\n|");

    while (done < n)
    {
        int idx = -1, min_bt = 100000;

        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time && !completed[i])
            {
                if (bt[i] < min_bt)
                {
                    min_bt = bt[i];
                    idx = i;
                }
            }
        }

        if (idx == -1)
        {
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
    for (int i = 0; i < t_index; i++)
    {
        printf("    %d", timeline[i]);
    }

    for (int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    printTable(n, pid, at, bt, ct, tat, wt, rt);
}

// -------- Round Robin --------
void rr(int n, int at[], int bt[])
{
    int tq;
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int rem_bt[MAX], ct[MAX], tat[MAX], wt[MAX], rt[MAX], visited[MAX] = {0}, pid[MAX];

    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        rem_bt[i] = bt[i];
    }

    int time = 0, completed = 0;
    int timeline[MAX], t_index = 0;

    printf("\n|");

    while (completed < n)
    {
        int executed = 0;

        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time && rem_bt[i] > 0)
            {

                if (!visited[i])
                {
                    rt[i] = time - at[i];
                    visited[i] = 1;
                }

                printf(" P%d |", pid[i]);

                if (rem_bt[i] > tq)
                {
                    time += tq;
                    rem_bt[i] -= tq;
                }
                else
                {
                    time += rem_bt[i];
                    rem_bt[i] = 0;
                    ct[i] = time;
                    completed++;
                }

                timeline[t_index++] = time;
                executed = 1;
            }
        }

        if (!executed)
        {
            printf(" Idle |");
            time++;
            timeline[t_index++] = time;
        }
    }

    printf("\n0");
    for (int i = 0; i < t_index; i++)
    {
        printf("    %d", timeline[i]);
    }

    for (int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    printTable(n, pid, at, bt, ct, tat, wt, rt);
}

int main()
{
    int n, choice;

    printf("Enter number of processes : ");
    scanf("%d", &n);

    int at[MAX], bt[MAX];

    printf("Enter Arrival Time : ");
    for (int i = 0; i < n; i++)
        scanf("%d", &at[i]);

    printf("Enter Burst Time : ");
    for (int i = 0; i < n; i++)
        scanf("%d", &bt[i]);

    printf("\nSelect Scheduling Algorithm :\n1.FCFS\n2.SJF\n3.Round Robin\n");
    printf("Enter choice : ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        fcfs(n, at, bt);
        break;
    case 2:
        sjf(n, at, bt);
        break;
    case 3:
        rr(n, at, bt);
        break;
    default:
        printf("Invalid choice\n");
    }

    return 0;
}