#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Process
{
    int id, at, bt, ct, tat, wt, rt, remaining;
};

void printResult(vector<Process> p)
{
    cout << "\n\nProcess |    AT    |    BT    |    CT    |    TAT    |    WT    |    RT\n";
    for (auto x : p)
    {
        cout << "   P" << x.id << "        "
             << x.at << "          "
             << x.bt << "          "
             << x.ct << "          "
             << x.tat << "          "
             << x.wt << "          "
             << x.rt << endl;
    }
}

// ================= FCFS =================
void fcfs(vector<Process> p)
{
    sort(p.begin(), p.end(), [](Process a, Process b)
         { return a.at < b.at; });

    int time = 0;
    cout << "\nGantt Chart:\n|";

    for (auto &x : p)
    {
        if (time < x.at)
        {
            cout << " Idle |";
            time = x.at;
        }

        cout << " P" << x.id << " |";

        x.rt = time - x.at;
        time += x.bt;
        x.ct = time;
        x.tat = x.ct - x.at;
        x.wt = x.tat - x.bt;
    }

    cout << "\n0";
    time = 0;

    for (auto x : p)
    {
        if (time < x.at)
        {
            time = x.at;
            cout << "    " << time;
        }
        time += x.bt;
        cout << "    " << time;
    }

    printResult(p);
}

// ================= SJF (Non-preemptive) =================
void sjf(vector<Process> p)
{
    int n = p.size(), time = 0, completed = 0;
    vector<bool> done(n, false);

    cout << "\nGantt Chart:\n|";

    while (completed < n)
    {
        int idx = -1, mn = 1e9;

        for (int i = 0; i < n; i++)
        {
            if (!done[i] && p[i].at <= time && p[i].bt < mn)
            {
                mn = p[i].bt;
                idx = i;
            }
        }

        if (idx == -1)
        {
            cout << " Idle |";
            time++;
            continue;
        }

        cout << " P" << p[idx].id << " |";

        p[idx].rt = time - p[idx].at;
        time += p[idx].bt;

        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        done[idx] = true;
        completed++;
    }

    printResult(p);
}

// ================= Round Robin =================
void rr(vector<Process> p, int tq)
{
    int n = p.size();
    queue<int> q;
    int time = 0;
    vector<bool> inQ(n, false);

    cout << "\nGantt Chart :\n|";

    while (true)
    {
        bool done = true;

        for (int i = 0; i < n; i++)
        {
            if (p[i].remaining > 0)
            {
                done = false;
                if (!inQ[i] && p[i].at <= time)
                {
                    q.push(i);
                    inQ[i] = true;
                }
            }
        }

        if (done)
            break;

        if (q.empty())
        {
            cout << " Idle |";
            time++;
            continue;
        }

        int i = q.front();
        q.pop();

        cout << " P" << p[i].id << " |";

        if (p[i].remaining == p[i].bt)
            p[i].rt = time - p[i].at;

        if (p[i].remaining > tq)
        {
            time += tq;
            p[i].remaining -= tq;
        }
        else
        {
            time += p[i].remaining;
            p[i].remaining = 0;
            p[i].ct = time;
            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
        }

        for (int j = 0; j < n; j++)
        {
            if (!inQ[j] && p[j].at <= time && p[j].remaining > 0)
            {
                q.push(j);
                inQ[j] = true;
            }
        }

        if (p[i].remaining > 0)
            q.push(i);
    }

    printResult(p);
}

// ================= MAIN =================
int main()
{
    int n;
    cout << "Enter number of process: ";
    cin >> n;

    vector<Process> p(n);

    cout << "Enter Arrival Time:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> p[i].at;
        p[i].id = i + 1;
    }

    cout << "Enter Burst Time:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> p[i].bt;
        p[i].remaining = p[i].bt;
    }

    int choice;
    cout << "\nChoose Algorithm:\n1.FCFS\n2.SJF\n3.Round Robin\nChoice: ";
    cin >> choice;

    if (choice == 1)
        fcfs(p);
    else if (choice == 2)
        sjf(p);
    else if (choice == 3)
    {
        int tq;
        cout << "Enter Time Quantum: ";
        cin >> tq;
        rr(p, tq);
    }

    return 0;
}