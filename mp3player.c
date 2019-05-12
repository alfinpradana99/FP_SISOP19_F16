#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<ao/ao.h>
#include<mpg123.h>
#include<dirent.h>
#include<sys/types.h>
#include<signal.h>
#define BITS 8

pthread_t tid1, tid2, tid3, tid4, tid5, tid6;
int status1 = 0;
int flag = 0;
int i=0;
int c=1;
int s=0;
int z=0;
char listlagu[1000][1000];

int play(char namalagu[])
{
    mpg123_handle *mh;
    unsigned char *buffer;
    size_t buffer_size;
    size_t done;
    int err;

    int driver;
    ao_device *dev;

    ao_sample_format format;
    int channels, encoding;
    long rate;

    /* initializations */
    ao_initialize();
    driver = ao_default_driver_id();
    mpg123_init();
    mh = mpg123_new(NULL, &err);
    buffer_size = mpg123_outblock(mh);
    buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));

    /* open the file and get the decoding format */
    mpg123_open(mh, namalagu);
    mpg123_getformat(mh, &rate, &channels, &encoding);

    /* set the output format and open the output device */
    format.bits = mpg123_encsize(encoding) * BITS;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;
    dev = ao_open_live(driver, &format, NULL);

    while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK) 
    {printf("\r");
        while(flag==2){printf("\r");
            if(flag==3) break;
        }
        if(s==1) break;
        ao_play(dev, buffer, done);
    }

    free(buffer);
    ao_close(dev);
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
    ao_shutdown();
    return 0;
}

void* comot(void *arg)
{
    DIR *dp;
    struct dirent *folder;
    char path[1000]="/home/alfin/Desktop/lagu/";
    dp = opendir(path);
    if (dp==NULL)
        return;
    printf("************************************************\nWelcome to the music player\n************************************************\nSONG LIST\n");
    while((folder=readdir(dp))!=NULL  ){printf("\r");
        char seme[1000];
        strcpy(seme, folder->d_name);
        int pjg = strlen(seme);
        if(seme[pjg-1]=='3' && seme[pjg-2]=='p' && seme[pjg-3]=='m' && seme[pjg-4]=='.')
        {
        i++;
        strcpy(listlagu[i], folder->d_name);
        printf("%d. %s\n", i, listlagu[i]);
        z++;
        }
    }
    closedir(dp);
    printf("\n------------------------------------------------\n");
    status1=1;
}

void* menu(void *arg)
{
    while(status1 != 1){printf("\r");}
    while(1){printf("\r");
    printf("1. Play song\n2. Pause song\n3. Resume\n4. Next\n5. Previous\n6. Exit\n------------------------------------------------\n");
    scanf("%d",&flag);
    }
}

void* bermain(void *arg)
{
    while(1){printf("\r");
        if(flag==1){
            char temp[1000]= "/home/alfin/Desktop/lagu/";
            strcat(temp, listlagu[c]);
            printf("playing now :%s\n", listlagu[c]);
            s= 0;
            play(temp);
        }
    }
}

void* next(void *arg)
{
    while(1){printf("\r");
        if(flag==4){
            s=1;
            if(c<z){c= c+1;}
            else c=1;
            flag=1;
        }
    }
}

void* prev(void *arg)
{
    while(1){printf("\r");
        if(flag==5){
            s=1;
            if (c>1){c= c-1;}
            else c=z;
            flag=1;
        }
    }
}

void* mati(void *arg)
{
    while(1){printf("\r");
        if(flag==6)
        {
            pthread_kill(tid1, SIGKILL);
            pthread_kill(tid2, SIGKILL);
            pthread_kill(tid4, SIGKILL);
            pthread_kill(tid5, SIGKILL);
            pthread_kill(tid6, SIGKILL);
            pthread_kill(tid3, SIGKILL);
        }
    }
}


int main(void)
{
    pthread_create(&(tid1), NULL, menu, NULL);
    pthread_create(&(tid2), NULL, bermain, NULL);
    pthread_create(&(tid3), NULL, mati, NULL);
    pthread_create(&(tid4), NULL, comot, NULL);
    pthread_create(&(tid5), NULL, next, NULL);
    pthread_create(&(tid6), NULL, prev, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
    pthread_join(tid5, NULL);
    pthread_join(tid6, NULL);

    return 0;
}