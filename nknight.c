#include<stdio.h>
#include<string.h>
#include<mpi.h>

struct node
{
int in;
int name;
int inname[100];
int visited;
};

struct paths
{
unsigned int p[40];
unsigned int pa[40];
}p;

struct graph
{
int start;
int size;
struct node nd[100];
};



int traverse(struct graph *t,int nnum,int d)
{
int i;
if(t->nd[nnum].visited==1)
{
if(nnum==t->start && d+1>=t->size)
 {
/*
 printf("Success");
 printf("Path:\n");
 for(i=0;i<t->size-1;i++)
 {
 printf("%d->",p.p[i]);
 }
 printf("%d\n",nnum);
 getch();
*/
 p.pa[nnum]=p.pa[nnum]+1;
 }
return 0;
}

if(d+1>=t->size)
{
               /*
        printf("Success");
        

               printf("Path:\n");
        for(i=0;i<t->size-1;i++)
        {
        printf("%d->",p.p[i]);
        }
        printf("%d\n",nnum);
        getch();
        */
                     p.pa[nnum]=p.pa[nnum]+1;
//        printf("%d : %d\n",nnum,p.pa[nnum]);
return 1;
}
if(t->nd[nnum].visited==0)
{
    t->nd[nnum].visited=1;
    p.p[d]=t->nd[nnum].name;
/*
    printf("\n");
    for(i=0;i<=d;i++)
    {
    printf("%d->",p.p[i]);
    }
    getch();
*/


    


    for(i=1;i<=t->nd[nnum].in;i++)
    {
    //p.p[p.pa][d]=t->nd[nnum].name;
    if(traverse(t,t->nd[nnum].inname[i],d+1)==1)
    {
    if(i==t->nd[nnum].in)
    {
    t->nd[nnum].visited=0;
    return 1;
    }
    }
    }
    t->nd[nnum].visited=0;
}
//t->nd[nnum].visited=0;
return 0;
}

int main(int argc, char **argv)
{
          int n,a,b,t,i,j,k,np=0;
          int s,r,nc[50],ncc=0;
    int start,end;
    int send,receive,task,send_ok,flag;
    int max,cur;
    int size,length;     
     int my_rank;
    struct graph g,c;
    FILE *fp;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
     MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
          fp=fopen("knight6","r");

//reading from the file making the graph
    fscanf(fp,"%d\n",&n);
//    printf("%d\n",n);
    g.size=n;
    
    //in
    for(i=1;i<=n;i++)
    {
    fscanf(fp,"%d ",&a);
    g.nd[i].name=a;
    fscanf(fp,"%d ",&a);
    g.nd[i].in=a;
    for(j=1;j<=a;j++)
    {
    fscanf(fp,"%d ",&t);
    g.nd[i].inname[j]=t;
    }
    }
     for(i=1;i<=n;i++)
    {
    p.pa[i]=0;
    }
    for(i=1;i<=n;i++)
    {
    g.nd[i].visited=0;
    }
      fclose(fp);
      if(my_rank==0)
           {
    for(i=1;i<=n;i++)
    {
    for(j=1;j<=g.nd[i].in;j++)
    {
    printf("(%d,%d) ",g.nd[i].name,g.nd[i].inname[j]);
    }
    printf("\n");
    }
     for(j=1;j<=n;j++)
     {
      send=j;
send_ok=1;
flag=0;
     while(send_ok)
     {



for(i=1;i<size;i++)
{
MPI_Iprobe(i,1,MPI_COMM_WORLD,&flag,&stat);
if(flag)
{
MPI_Recv(&receive,1,MPI_INT,i,1,MPI_COMM_WORLD,&stat);
MPI_Ssend(&send,1,MPI_INT,i,1,MPI_COMM_WORLD);
send_ok=0;
break;
}
}
}
}
for(i=1;i<size;i++)
{
send=0;
MPI_Recv(&receive,1,MPI_INT,i,1,MPI_COMM_WORLD,&stat);
MPI_Ssend(&send,1,MPI_INT,i,1,MPI_COMM_WORLD);
}

/*    
if(MPI_Iprobe(i,1,MPI_COMM_WORLD,&flag,&stat)==1)
{
    MPI_Recv(&receive,1,MPI_INT,i,1,MPI_COMM_WORLD,&stat);
          printf("Success %d\n",receive);
    
}
    

}
    
/*
      for(i=1;i<size;i++)
     {
    send=i;
          MPI_Send(&send,1,MPI_INT,i,1,MPI_COMM_WORLD);
}
         i=0;
 for(j=size;j<=n;j++)
     {
        send_ok=0;
   while(send_ok==0)
   {
      i=i+1;
            if(i>=size)
           {
             i=1;    
    }
    send=j;
    printf("\nSending %d to %d\n",j,i);
           MPI_Send(&send,1,MPI_INT,i,1,MPI_COMM_WORLD);
           MPI_Recv(&receive,1,MPI_INT,i,1,MPI_COMM_WORLD,&stat);
           received=receive;
    
if(send==received)
     {
          printf("\nNode %d send successfully to %d\n",send,i);
    send_ok=1;
}
}    
}
     for(i=1;i<size;i++)
{
    send=0;
    MPI_Ssend(&send,1,MPI_INT,i,1,MPI_COMM_WORLD);
}
*/
}
else
{
while(1)
     {
    send=my_rank;
          MPI_Ssend(&send,1,MPI_INT,0,1,MPI_COMM_WORLD);
    MPI_Recv(&receive,1,MPI_INT,0,1,MPI_COMM_WORLD,&stat);
          if(receive==0)
         {
    break;
   }
    



printf("\nReceived:%d by:%d\n",receive,my_rank);
     g.start=receive;
for(i=1;i<=n;i++)
{
     p.pa[i]=0;
}
     c=g;
    t=traverse(&c,g.start,0);
    printf("\nTotal Number of paths:%d\n",g.start);
          for(t=1;t<=n;t++)
    {
    printf("%2d:%6d\t",t,p.pa[t]);
    if(t%6==0)
    {
    printf("\n");
    }
    }
    }

}

  MPI_Finalize();
return 0;
}


