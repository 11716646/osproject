
#include<stdio.h>
#include<conio.h>
#include<windows.h>
struct process
{
	char name;
	int arr_t;
	int bur_t;
	int wait_t;
	int turn_t,rt;
	int comp;
}p[10];

int n;
int q[10];
int front=-1,rear=-1;
void enqueue(int i)
{
    if(rear==10)
        printf("overflow");
    rear++;
    q[rear]=i;
    if(front==-1)
        front=0;

}

int dequeue()
{
    if(front==-1)
        printf("underflow");
    int temp=q[front];
    if(front==rear)
        front=rear=-1;
    else
        front++;
    return temp;
}
int isInQueue(int i)
{
    int k;
    for(k=front;k<=rear;k++)
    {
        if(q[k]==i)
        return 1;
    }
    return 0;
}

void sortByArrival()
{
    struct process temp;
    int i,j;
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(p[i].arr_t>p[j].arr_t)
            {
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
}

void main()
{
    int i,j,time=0,sum_bur_t=0,tq;
    char c;
    float avgwait_t=0;
    
     printf("Round Robin Process Scheduling:- \n\nEnter Number of Processes::- ");
     scanf("%d",&n);
     for(i=0,c='A';i<n;i++,c++)
     {
         p[i].name=c;
         
    
         printf("\nProcess P[%c]:-\n",c);
         printf("\nArrival Time(s) :\t");
         scanf("%d",&p[i].arr_t);
         printf("\nBurst   Time(s) :\t");
         scanf("%d",&p[i].bur_t);
         p[i].rt=p[i].bur_t;
         p[i].comp=0;
         sum_bur_t+=p[i].bur_t;
    }
    printf("\nEnter the Time Quantum(s):");
    scanf("%d",&tq);
    sortByArrival();
    enqueue(0);          // enqueue the first process
    printf("Process execution order: ");
    for(time=p[0].arr_t;time<sum_bur_t;)       // run until the total burst time reached
    {   
        i=dequeue();
        if(p[i].rt<=tq)
        {                          /* for processes having remaining time with less than                                             or  equal  to time quantum  */
                              
            time+=p[i].rt;
            p[i].rt=0;
            p[i].comp=1;         
            printf(" %c ",p[i].name);
            p[i].wait_t=time-p[i].arr_t-p[i].bur_t;
            p[i].turn_t=time-p[i].arr_t;      
            for(j=0;j<n;j++)     /*enqueue the processes which have come while scheduling */
            {
                if(p[j].arr_t<=time && p[j].comp!=1&& isInQueue(j)!=1)
                {
                    enqueue(j);
                }
            }
        }
        else               // more than time quantum
        {
            time+=tq;
            p[i].rt-=tq;
            printf(" %c ",p[i].name);
            for(j=0;j<n;j++)    /*first enqueue the processes which have come while                                             scheduling */
            {
                if(p[j].arr_t<=time && p[j].comp!=1&&i!=j&& isInQueue(j)!=1)
                {
                    enqueue(j);
                }
            }
            enqueue(i);   // then enqueue the uncomp process
        }
    }

	system("cls");
	
    
    printf("\n\nProcess Table:-\nName\tArrival Time\tBurst Time\tResponse Time\tTurnAround Time");
    for(i=0;i<n;i++)
    {
        avgwait_t+=p[i].wait_t;
        printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d",p[i].name,p[i].arr_t,p[i].bur_t,p[i].wait_t,p[i].turn_t);
    }
    printf("\nAverage waiting time:%f\n",avgwait_t/n);
}
