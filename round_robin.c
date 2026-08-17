#include <stdio.h>

struct process
{
    int pid, bt, tt, wt;
};

int main()
{
    struct process x[10], p[50];

    int i, j, k, tot = 0, m, n;
    float wttime = 0.0, tottime = 0.0, a1, a2;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        x[i].pid = i + 1;
        printf("Enter Burst Time of Process %d: ", x[i].pid);
        scanf("%d", &x[i].bt);
        tot += x[i].bt;
    }

    printf("\nTotal Burst Time = %d\n", tot);

    p[0].tt = 0;
    k = 1;

    printf("Enter Time Slice: ");
    scanf("%d", &m);

    for (j = 0; j < tot; j++)
    {
        for (i = 0; i < n; i++)
        {
            if (x[i].bt > 0)
            {
                p[k].pid = x[i].pid;

                if (x[i].bt <= m)
                {
                    p[k].wt = p[k - 1].tt;
                    p[k].bt = x[i].bt;
                    p[k].tt = p[k].wt + x[i].bt;
                    x[i].bt = 0;
                }
                else
                {
                    p[k].wt = p[k - 1].tt;
                    p[k].bt = m;
                    p[k].tt = p[k].wt + m;
                    x[i].bt -= m;
                }

                k++;
            }
        }
    }

    printf("\nProcess ID\tWT\tTT\n");

    for (i = 1; i < k; i++)
    {
        printf("%d\t\t%d\t%d\n",
               p[i].pid,
               p[i].wt,
               p[i].tt);

        wttime += p[i].wt;
        tottime += p[i].tt;
    }

    a1 = wttime / (k - 1);
    a2 = tottime / (k - 1);

    printf("\nAverage Waiting Time = %.2f\n", a1);
    printf("Average Turnaround Time = %.2f\n", a2);

    return 0;
}