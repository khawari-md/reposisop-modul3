#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

 
pthread_t tid1;
pthread_t tid2;
int status;
 
void* salin1(void *arg)
{
    status = 0;
    char buf[BUFSIZ];
    size_t size;
 
    FILE* source = fopen("baca.txt", "r");
    FILE* dest = fopen("salin1.txt", "w+");

    while (size = fread(buf, 1, BUFSIZ, source)) {
        fwrite(buf, 1, size, dest);
    }

    fclose(source);
    fclose(dest);
 
    status = 1;
 
    return NULL;
}


void* salin2(void *arg)
{
    while(status != 1)
    {

    }

    char buf[BUFSIZ];
    size_t size;
 
    FILE* source = fopen("salin1.txt", "r+");
    FILE* dest = fopen("salin2.txt", "w+");

    while (size = fread(buf, 1, BUFSIZ, source)) {
        fwrite(buf, 1, size, dest);
    }

    fclose(source);
    fclose(dest);

}
 
int main(void)
{

    pthread_create(&(tid1), NULL, &salin1, NULL);
    pthread_create(&(tid2), NULL, &salin2, NULL);
 
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
 
    return 0;
}
