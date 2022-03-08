#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>



struct threadData{
 int curr,max;
 int long *path; 
};

void *threadFunc(void * arg){
 int i;
 pthread_t t[2];
 struct threadData *new=(struct threadData *)arg;
 if(new->curr==new->max){
	for(i=0;i<new->max;i++)
		printf("%ld",new->path[i]);
	 printf("\n");
	 pthread_exit(NULL);
 	}
 struct threadData *next=malloc(sizeof(struct threadData *));

  next->path=malloc(sizeof(long int)*new->max);
  next->path[new->curr]=pthread_self();
  next->curr=new->curr+1;
  next->max=new->max;

  pthread_create (&t[0], NULL,threadFunc ,(void *) next);
  pthread_create (&t[1], NULL,threadFunc ,(void *) next);
  pthread_join (t[0], NULL);
  pthread_join (t[1], NULL);		
  return (NULL);
}


int main (int argc,char **argv) {
  int n=atoi(argv[1]);
  pthread_t tid[2];	 
  struct threadData *start=malloc(sizeof(struct threadData *));
  start->curr=1;
  start->max=n;
  start->path=malloc(sizeof(long int)*n);
  start->path[0]=pthread_self();
  pthread_create (&tid[0], NULL,threadFunc ,(void *) start);
  pthread_create (&tid[1], NULL,threadFunc ,(void *) start);
  pthread_join (tid[0], NULL);
  pthread_join (tid[1], NULL);		
  return (1);
}

/* EX 6
int sig1=0;
int sig2=0;
void  manager(int signal);
int main () {

signal (SIGUSR1, manager);
signal (SIGUSR2, manager);

while(1);

}

void  manager(int signal)
{
    if(signal==SIGUSR1){
	if (sig1==1)
		printf("error! 2 sig1 in a row \n");
	if (sig1==2)
		exit(0);
	if (sig2==1)
		printf("Success! 2 diff sigs received");
	sig1++;
	sig2=0;
	}
    if(signal==SIGUSR2){
	if (sig2==1)
		printf("error! 2 sig2 in a row \n");
	if (sig2==2)
		exit(0);
	if (sig1==1)
		printf("Success! 2 diff sigs received");
	sig2++;
	sig1=0;
	}
}*/


/* EX 5
int main (int argc,char **argv) {
  int n=atoi(argv[1]);
  int i,j; 
  int *vet; 
  pid_t pid;

  vet = (int *)malloc(n * sizeof(int));
  if (vet == NULL) {
    printf("Allocatin Error.\n");
    exit(1);
  }
	
  printf("Binary Numbers:\n");
  for(i=0;i<n;i++)  {
    pid=fork();
    if(pid) vet[i]=0;
    else vet[i]=1;
    
    if(i==n-1) {
		for (j=0; j<n; j++) {
		      printf("%d", vet[j]);
		    }
		printf("\n"); }
  }
  free(vet);	
  return (1);
}
*/


/* EX 4
int main (int argc,char **argv) {
  int n=atoi(argv[1]);
  int h=atoi(argv[2]);
  int i,j;  
  pid_t pid;

  for(i=0;i<=n;i++){
    for(j=0;j<h;j++)
	{
		pid=fork();
		if(!pid){
			if(i==n)
			 fprintf (stdout, "End PID=%d\n", getpid());
			break;
		}
	}
    if(pid) break;	
 }
  return (1);
} */