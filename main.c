#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <string.h>

struct to_th
{
    char *filename;
    char *buff;

};


void * write_line_th(struct to_th *args)
{
    char *filename = args->filename;
    char *str = args->buff;
    FILE *f = fopen(filename, "a");
    fwrite(str, strlen(str), 1, f);
    fclose(f);
}


int main(int argc, char *argv[]) {
    pthread_t thread1;
    pthread_t thread2;
    char *in_file = argv[1];
    char *out_file1 = argv[2];
    char *out_file2 = argv[3];
    char buff[50];
    FILE *f = fopen(in_file, "r");
    int i = 0;

    while(fgets(buff,sizeof(buff),f))
    {
        if (i%2==0) {
            struct to_th args = {out_file1, buff};
            pthread_create(&thread1, NULL, write_line_th,& args);
            pthread_join(thread1, NULL);
        } else{
            struct to_th args = {out_file2, buff};
            pthread_create(&thread2, NULL, write_line_th, &args);
            pthread_join(thread2, NULL);
        }


    }



    return 0;
}