#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;                    //����������mutex
pthread_cond_t cond;                      //������������cond

void *procf(void *arg) //father�߳�
{ 
     while(1){
         pthread_cond_wait(&cond, &mutex);
         printf("�ְֳԳ���!\n");
         sleep(1);
     }

}
void *procm(void *arg)  //mother�߳�
{ 
    while(1){
        sleep(4);
        pthread_cond_signal(&cond); 
        printf("����гԳ���!\n");
        
    }
}
void *procs(void *arg)  //son�߳�
{ 
    while(1){
        pthread_cond_wait(&cond, &mutex);
        printf("���ӳԳ���!\n");

        sleep(1);
    }
}
void *procd(void *arg)  //daughter�߳�
{ 
    while(1){

        pthread_cond_wait(&cond, &mutex);
        printf("Ů���Գ���!\n");



        sleep(1);
    }

}
 
int main()
{ 
    pthread_t father;  //�����߳�
    pthread_t mother;
    pthread_t son;
    pthread_t daughter;

	pthread_mutex_init(&mutex, NULL);   //��ʼ��������
    pthread_cond_init(&cond, NULL);  //��ʼ����������

    pthread_create(&daughter,NULL,procd,NULL);   //�����߳�
    pthread_create(&son,NULL,procs,NULL);

    pthread_create(&father,NULL,procf,NULL); 
    pthread_create(&mother,NULL,procm,NULL);

    // �ȴ��߳̽���
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

