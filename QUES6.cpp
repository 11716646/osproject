#include<stdio.h> 
 
int main() 
{ 
 
  int counter,j,n,time,remain,flag=0,time_quantum; 
  int wait_time=0,turnaround_time=0,arr[10],burst[10],respo[10]; 
  printf("Enter Total Process:\t "); 
  scanf("%d",&n); 
  remain=n; 
  for(counter=0;counter<n;counter++) 
  { 
   printf("\nProcess P[%d]:-\n",counter+1);
   printf("\nArrival Time(s) :\t");
    scanf("%d",&arr[counter]); 
    printf("\nBurst   Time(s) :\t");
    scanf("%d",&burst[counter]); 
    respo[counter]=burst[counter]; 
  } 
  time_quantum=10; 
  printf("The Time Quantum is :%d\t",time_quantum); 
  printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n"); 
  for(time=3,counter=0;remain!=0;) 
  { 
    if(respo[counter]<=time_quantum && respo[counter]>0) 
    { 
      time+=respo[counter]; 
      respo[counter]=0; 
      flag=1; 
    } 
    else if(respo[counter]>0) 
    { 
      respo[counter]-=time_quantum; 
      time+=time_quantum; 
    } 
    if(respo[counter]==0 && flag==1) 
    { 
      remain--; 
      printf("P[%d]\t|\t%d\t|\t%d\n",counter+1,time-arr[counter],time-arr[counter]-burst[counter]); 
      wait_time+=time-arr[counter]-burst[counter]; 
      turnaround_time+=time-arr[counter]; 
      flag=0; 
    } 
    if(counter==n-1) 
      counter=0; 
    else if(arr[counter+1]<=time) 
      counter++; 
    else 
      counter=0; 
  } 
  printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n); 
  printf("Avg Turnaround Time = %f",turnaround_time*1.0/n); 
  
  return 0; 
}




