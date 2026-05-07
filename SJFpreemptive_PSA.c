#include <stdio.h>

#define MAX 100

void printTable(int n, int pid[], int at[], int bt[],
                int ct[], int tat[], int wt[], int rt[])
{
    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }
}

//              SRTF

void srtf(int n, int at[], int bt[])
{
    int pid[MAX], rt[MAX], wt[MAX], tat[MAX], ct[MAX];
    int rem_bt[MAX], visited[MAX] = {0};

    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        rem_bt[i] = bt[i];
    }

    int completed = 0, time = 0;

    int g_pid[MAX], timeline[MAX];
    int g_index = 0, t_index = 0;

    int prev = -1;

    while (completed < n)
    {
        int idx = -1;
        int min_bt = 100000;

        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time && rem_bt[i] > 0)
            {
                if (rem_bt[i] < min_bt)
                {
                    min_bt = rem_bt[i];
                    idx = i;
                }
            }
        }

        if (idx == -1)
        {
            if (prev != 0)
            {
                g_pid[g_index++] = 0;
                timeline[t_index++] = time;
            }

            prev = 0;
            time++;
            continue;
        }

        if (!visited[idx])
        {
            rt[idx] = time - at[idx];
            visited[idx] = 1;
        }

        if (prev != pid[idx])
        {
            g_pid[g_index++] = pid[idx];
            timeline[t_index++] = time;
        }

        prev = pid[idx];

        rem_bt[idx]--;
        time++;

        if (rem_bt[idx] == 0)
        {
            ct[idx] = time;
            completed++;
        }
    }

    timeline[t_index++] = time;

    printf("\n|");

    for (int i = 0; i < g_index; i++)
    {
        if (g_pid[i] == 0)
            printf(" Idle |");
        else
            printf(" P%d |", g_pid[i]);
    }

    printf("\n0");

    for (int i = 1; i < t_index; i++)
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

//          Priority Scheduling-Preemptive

void priorityScheduling(int n, int at[], int bt[])
{
    int priority[MAX];

    printf("Enter Priority : ");

    for (int i = 0; i < n; i++)
        scanf("%d", &priority[i]);

    int pid[MAX], rt[MAX], wt[MAX], tat[MAX], ct[MAX];
    int rem_bt[MAX], visited[MAX] = {0};

    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        rem_bt[i] = bt[i];
    }

    int completed = 0, time = 0;

    int g_pid[MAX], timeline[MAX];
    int g_index = 0, t_index = 0;

    int prev = -1;

    while (completed < n)
    {
        int idx = -1;
        int best_priority = 100000;

        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time && rem_bt[i] > 0)
            {
                if (priority[i] < best_priority)
                {
                    best_priority = priority[i];
                    idx = i;
                }
            }
        }

        if (idx == -1)
        {
            if (prev != 0)
            {
                g_pid[g_index++] = 0;
                timeline[t_index++] = time;
            }

            prev = 0;
            time++;
            continue;
        }

        if (!visited[idx])
        {
            rt[idx] = time - at[idx];
            visited[idx] = 1;
        }

        if (prev != pid[idx])
        {
            g_pid[g_index++] = pid[idx];
            timeline[t_index++] = time;
        }

        prev = pid[idx];

        rem_bt[idx]--;
        time++;

        if (rem_bt[idx] == 0)
        {
            ct[idx] = time;
            completed++;
        }
    }

    timeline[t_index++] = time;

    printf("\n|");

    for (int i = 0; i < g_index; i++)
    {
        if (g_pid[i] == 0)
            printf(" Idle |");
        else
            printf(" P%d |", g_pid[i]);
    }

    printf("\n0");

    for (int i = 1; i < t_index; i++)
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

    printf("Enter number of process : ");
    scanf("%d", &n);

    int at[MAX], bt[MAX];

    printf("Enter Arrival Time : ");

    for (int i = 0; i < n; i++)
        scanf("%d", &at[i]);

    printf("Enter Burst Time : ");

    for (int i = 0; i < n; i++)
        scanf("%d", &bt[i]);

    printf("\n1.SRTF (Preemptive SJF)\n");
    printf("2.Priority Scheduling\n");

    printf("Enter choice : ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        srtf(n, at, bt);
        break;

    case 2:
        priorityScheduling(n, at, bt);
        break;

    default:
        printf("Invalid Choice");
    }

    return 0;
}