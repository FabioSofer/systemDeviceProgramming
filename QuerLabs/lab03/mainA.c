
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define WAIT_TIME_1 1
#define WAIT_TIME_2 1
#define STR_NUM 3
#define STR_SIZE 5

int writeDataToPipe(int pipe[]);

int main(){

    int p1[2],p2[2];
    pid_t pid1,pid2;
    int i=0,r,writeCounter=0,readCounter=0;
    char c,buf[STR_SIZE];
    if(pipe (p1)==0){
        pid1 = fork ();
                if (pid1 == -1) {
                    fprintf(stderr, "Fork failure");
                    exit(EXIT_FAILURE);
                }
        if (pid1==0){  // C1
            srand(1);
            printf("C1 started\n");
            close(p1[0]);
            while(writeCounter!=STR_NUM)
            {

                sleep(WAIT_TIME_1);
                i=writeDataToPipe(p1);
                printf("C1 wrote %d bytes \n",i);
                writeCounter++;
            }
            exit(1);
        }
    } 

    if(pipe (p2)==0){
        pid2 = fork ();
                if (pid2 == -1) {
                    fprintf(stderr, "Fork failure");
                    exit(EXIT_FAILURE);
                }
        if (pid2==0){  // C2
            srand(2);
            printf("C2 started \n");
            close(p2[0]);
            while(writeCounter!=STR_NUM)
            {
                sleep(WAIT_TIME_1);
                i=writeDataToPipe(p2);
                printf("C2 wrote %d bytes\n",i);
                writeCounter++;
            }
            exit(2);
        }
    }

    while(readCounter<STR_NUM){
        read(p1[0],&i,1);
        i=read(p1[0],buf,i);
        printf("Read %d bytes from C1\n",i);
        read(p2[0],&i,1);
        i=read(p2[0],buf,i);
        printf("Read %d bytes from C2\n",i);
        readCounter++;
    }
        
}

int writeDataToPipe(int pipe[])
{
    int r=rand()%STR_SIZE+1;
    char buf[STR_SIZE],i;
    for (i=0;i<r;i++)
            buf[i]=(rand()%26)+'a';

    write(pipe[1],&i,1);
    i=write(pipe[1],buf,i);
    return i;
}