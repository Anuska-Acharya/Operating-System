#include <stdio.h>

struct process
{
    int pid;
    int bt;
    int wt;
    int tt;
} p[10], temp;

int main()
{
    int i, j, n;
    int totwt = 0, tottt = 0;
    float avg1, avg2;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("Enter the burst time of Process %d: ", p[i].pid);
        scanf("%d", &p[i].bt);
    }

    // Sort by Burst Time (SJF)
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (p[i].bt > p[j].bt)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    p[0].wt = 0;
    p[0].tt = p[0].bt;

    for (i = 1; i < n; i++)
    {
        p[i].wt = p[i - 1].wt + p[i - 1].bt;
        p[i].tt = p[i].wt + p[i].bt;
    }

    printf("\nProcess\tBT\tWT\tTT\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].bt,
               p[i].wt,
               p[i].tt);

        totwt += p[i].wt;
        tottt += p[i].tt;
    }

    avg1 = (float)totwt / n;
    avg2 = (float)tottt / n;

    printf("\nAverage Waiting Time = %.2f\n", avg1);
    printf("Average Turnaround Time = %.2f\n", avg2);

    return 0;
}