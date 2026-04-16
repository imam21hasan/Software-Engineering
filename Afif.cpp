#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>
using namespace std;

struct Process{
    int id;
    int at;
    int bt;
    int ct=0;
    int wt=0;
    int tt=0;

};

void ganttChart(vector<int>order, vector<int>time)
{
    cout<<"\nGantt Chart: \n";
    for (int i=0; i<order.size(); i++)
    {
        cout<<"--------";
    }
    cout<<"-\n";

    for(int i=0;i<order.size(); i++)
    {
        if(order[i]==0)
        {
            cout<<"---IDLE|";
        }
        else
        {
            cout<<"   P"<<order[i]<<"   |";
        }
    }
    cout<<"\n";

    for(int i=0; i<order.size(); i++)
    {
        cout<<"--------";

    }
    cout<<"-\n";

    for(int i=0; i<time.size(); i++)
    {
        cout<<time[i]<<setw(8);
    }
    cout<<"\n";

}

void fcfs(vector<Process> p, int num)
{

    sort(p.begin(), p.end(), [](Process a, Process b)
         {
             return a.at<b.at;
         });

    vector <int>order, time;
    int currentTime =0;

    for (int i=0; i<num; i++)
    {
        if(currentTime<p[i].at)
        {
            order.push_back(0);
            time.push_back(currentTime);
            currentTime =p[i].at;

        }
        order.push_back(p[i].id);
        time.push_back(currentTime);
        p[i].wt=currentTime-p[i].at;
        currentTime +=p[i].bt;
        p[i].ct=currentTime;
        p[i].tt=p[i].ct-p[i].at;

    }
    time.push_back(currentTime);
    ganttChart(order, time);

    float avgwt=0;
    float avgtt=0;

    cout<<"\nP\tAt\tBt\tWt\tTT\n";

    for(auto pr:p)
    {
        cout<<"P "<<pr.id<<"\t"<<pr.at<<"\t"<<pr.bt<<"\t"<<pr.wt<<"\t"<<pr.tt<<endl;
        avgwt += pr.wt;
        avgtt += pr.tt;

    }

    cout<<"Avg wt"<<avgwt/num<<"\n";
    cout<<"Avg tt"<<avgtt/num;



}


void sjf(vector<Process> p, int num)
{
    vector <int>order ,time;
    vector<bool>done(num, false);
    int completed=0, currentTime=0;

    while(completed<num)
    {
       int idx=-1;
       int mn=1e9;

       for (int i=0; i<num; i++)
       {
           if(!done[i] && p[i].at <=currentTime &&  p[i].bt<mn )
           {
               idx=i;
               mn=p[i].bt;
           }
       }

       if(idx ==-1)
       {
         order.push_back(0);
         order.push_back(currentTime);
         currentTime ++;
         continue;

       }
       order.push_back(p[idx].id);
       time.push_back(currentTime);

       p[idx].wt=currentTime-p[idx].at;
       currentTime +=p[idx].bt;
       p[idx].ct=currentTime;
       p[idx].tt=p[idx].ct-p[idx].at;

       done[idx]=true;
       completed ++;


    }

    time.push_back(currentTime);
    ganttChart(order, time);

    float avgwt=0;
    float avgtt=0;

    cout<<"\nP\tAt\tBt\tWt\tTT\n";

    for(auto pr:p)
    {
        cout<<"P "<<pr.id<<"\t"<<pr.at<<"\t"<<pr.bt<<"\t"<<pr.wt<<"\t"<<pr.tt<<endl;
        avgwt += pr.wt;
        avgtt += pr.tt;

    }

    cout<<"Avg wt"<<avgwt/num<<"\n";
    cout<<"Avg tt"<<avgtt/num;


}
void roundRobin(vector<Process>p,int num,int q)
{
    vector<int>order, time;
    vector<int>rem(num);
    int completed=0;
    int currentTime=0;

    for (int i=0; i<num; i++)
    {
        rem[i]=p[i].bt;
    }

    while(completed<num)
    {
        bool progress=false;
        for (int i=0; i<num; i++)
        {
            if(p[i].at<=currentTime && rem[i] >0)

            {
                progress=true;
                order.push_back(p[i].id);
                time.push_back(currentTime);
                if(rem[i]>q)
                {
                    currentTime +=q;
                    rem[i] -=q;

                }
                else
                {
                    currentTime += rem[i];

                    p[i].ct = currentTime;
                    p[i].tt = p[i].ct - p[i].at;
                    p[i].wt = p[i].tt - p[i].bt;

                    rem[i]=0;
                    completed ++;

                }

            }

        }
        if (!progress)
        {
            order.push_back(0);
            time.push_back(currentTime);
            currentTime ++;
        }

    }


    time.push_back(currentTime);
    ganttChart(order, time);

    float avgwt=0;
    float avgtt=0;

    cout<<"\nP\tAt\tBt\tWt\tTT\n";

    for(auto pr:p)
    {
        cout<<"P "<<pr.id<<"\t"<<pr.at<<"\t"<<pr.bt<<"\t"<<pr.wt<<"\t"<<pr.tt<<endl;
        avgwt += pr.wt;
        avgtt += pr.tt;

    }

    cout<<"Avg wt"<<avgwt/num<<"\n";
    cout<<"Avg tt"<<avgtt/num;


}




int main()
{
    int num;
    cout<<"Enter number of process:";
    cin>>num;
    vector<Process>p(num);

    for(int i=0; i<num; i++)
    {
        p[i].id=i+1;
        cout<<"Process " <<i+1 <<"Arrival Time: ";
        cin>>p[i].at;
        cout<<"Process "<<i+1<<"Bust Time: ";
        cin>>p[i].bt;
    }


    int choice;
    cout<<"\n1.FCFS\n2.SJF\n3.RoundRobin\n";
    cout<<"Choice Algorithm: \n";
    cin>>choice;


    if(choice==1)
    {
        fcfs(p, num);

    }
    else if(choice==2)
    {
        sjf(p,num);

    }
    else if (choice==3)
    {
        int q;
        cout<<"Enter quantum Time: ";
        cin>>q;
        roundRobin(p, num, q);

    }
    else
    {
        cout<<"Invalid Choice \n";
    }

    return 0;

}
