/*#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
 
pthread_t tid1;
pthread_t tid2;
int status;

void* prima1(void *arg)
{
    status = 0;
 
    int prima;
    for (int i=1;i<=100/2;i++)
    {
        prima=0;
        if (i==2)
        prima=1;
        else
        {
            for (int j=2;j<i;j++)
            {
                if (i % j==0)
                {
                    prima=0;
                    break; // keluar dari looping
                }
                else prima=1;
            }
        }
        if (prima) printf("%d\n",i);
    }
 
    status = 1;
 
    return NULL;
}


void* prima2(void *arg)
{
    while(status != 1)
    {

    }

    int prima;
    for (int i=1+(100/2);i<=100;i++)
    {
        prima=0;
        if (i==2)
        prima=1;
        else
        {
            for (int j=2;j<i;j++)
            {
                if (i % j==0)
                {
                    prima=0;
                    break; // keluar dari looping
                }
                else prima=1;
            }
        }
        if (prima) printf("%d\n",i);
    }
}
 
int main(void)
{
    //const int *bilangan = 100;
    pthread_create(&(tid1), NULL, &prima1, NULL);
    pthread_create(&(tid2), NULL, &prima2, NULL);
 
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
 
    return 0;
}
*/
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
/*******************************************************
*compile dengan cara gcc -pthread -o [output] input.c *
*******************************************************/

pthread_t tid[100];

typedef struct number
{
    int atas,bawah;
}number;

void* prima(void *ptr)
{
    //status = 0;
    int prima;
    number * data=(number*) ptr;
    //printf("\n%d\n",data->atas);
    for (int i=data->bawah;i<=data->atas;i++)
    {
        prima=0;
        if (i==2)
        prima=1;
        else
        {
            for (int j=2;j<i;j++)
            {
                if (i % j==0)
                {
                    prima=0;
                    break; // keluar dari looping
                }
                else prima=1;
            }
        }
        if (prima) printf("%d\n",i);
    }
 
    //status = 1;
 
    return NULL;
}
int main(void)
{
    
    int i=0,T,N;
    printf("masukkan jumlah maksimal bilangan : \n");
    scanf("%d",&N);
    printf("masukkan jumlah thread\n");
    scanf("%d",&T);
    int err;
    number n[T];
        n[0].bawah=1;
        n[0].atas=N*(1/T);
    for(int j=1;j<T;j++){
        n[j].bawah=n[j-1].atas+1;
        n[j].atas=N*((j+1)/T);
    }
    
    while(i<T)//looping membuat thread
    {
        err=pthread_create(&(tid[i]),NULL,&prima,(void *) &n[i]);//membuat thread
        if(err!=0)//cek error
        {
            printf("\n can't create thread : [%s]",strerror(err));
        }
        else
        {
            //printf("\n create thread success");
        }
        i++;
    }
    i=0;
    while(i<T){
        pthread_join(tid[i],NULL);
        i++;
    }
    return 0;
}