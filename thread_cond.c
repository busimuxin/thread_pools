#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;                    //声明互斥量mutex
pthread_cond_t cond;                      //声明条件变量cond

void *procf(void *arg) //father线程
{ 
     while(1){
         pthread_cond_wait(&cond, &mutex);
         printf("爸爸吃橙子!\n");
         sleep(1);
     }

}
void *procm(void *arg)  //mother线程
{ 
    while(1){
        sleep(4);
        pthread_cond_signal(&cond); 
        printf("妈妈叫吃橙子!\n");
        
    }
}
void *procs(void *arg)  //son线程
{ 
    while(1){
        pthread_cond_wait(&cond, &mutex);
        printf("儿子吃橙子!\n");

        sleep(1);
    }
}
void *procd(void *arg)  //daughter线程
{ 
    while(1){

        pthread_cond_wait(&cond, &mutex);
        printf("女儿吃橙子!\n");



        sleep(1);
    }

}
 
int main()
{ 
    pthread_t father;  //定义线程
    pthread_t mother;
    pthread_t son;
    pthread_t daughter;

	pthread_mutex_init(&mutex, NULL);   //初始化互斥量
    pthread_cond_init(&cond, NULL);  //初始化条件变量

    pthread_create(&daughter,NULL,procd,NULL);   //创建线程
    pthread_create(&son,NULL,procs,NULL);

    pthread_create(&father,NULL,procf,NULL); 
    pthread_create(&mother,NULL,procm,NULL);

    // 等待线程结束
    void * result;
    if(pthread_join(father, &result) == -1){
        puts("fail to recollect father");
        exit(1);
    }

    if(pthread_join(mother, &result) == -1){
        puts("fail to recollect mother");
        exit(1);
    }
    if(pthread_join(daughter, &result) == -1){
        puts("fail to recollect daughter");
        exit(1);
    }
    if(pthread_join(son, &result) == -1){
        puts("fail to recollect son");
        exit(1);
    }

    pthread_cond_destroy(&cond);

    return 0;

}

