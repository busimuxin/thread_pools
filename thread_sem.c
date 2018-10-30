#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

sem_t empty;  //����������ɷŵ�ˮ����
sem_t apple;  //����ƻ����
sem_t orange; //���Ƴ�����
pthread_mutex_t work_mutex;                    //����������work_mutex

void *procf(void *arg) //father�߳�
          { 
             while(1){
                 sem_wait(&empty);     //ռ��һ�����ӿռ䣬�ɷ�ˮ������1
                 pthread_mutex_lock(&work_mutex);     //����
                 printf("�ְַ���һ��ƻ��!\n");
                 sem_post(&apple);     //�ͷ�һ��apple�ź��ˣ��ɳ�ƻ������1
                 pthread_mutex_unlock(&work_mutex);   //����
                 sleep(3);
             }
 
           }
void *procm(void *arg)  //mother�߳�
          { 
            while(1){
                sem_wait(&empty);
                pthread_mutex_lock(&work_mutex);     //����
                printf("�������һ������!\n");
                sem_post(&orange);
                pthread_mutex_unlock(&work_mutex);   //����
                sleep(4);
            }
           }
void *procs(void *arg)  //son�߳�
          { 
            while(1){
                sem_wait(&apple);       //ռ��һ��ƻ���ź������ɳ�ƻ������1 
                pthread_mutex_lock(&work_mutex);     //����
                printf("���ӳ���һ��ƻ��!\n");
                sem_post(&empty);       //����һ��ƻ�����ͷ�һ�����ӿռ䣬�ɷ�ˮ������1
                pthread_mutex_unlock(&work_mutex);   //����
                sleep(1);
            }
           }
void *procd(void *arg)  //daughter�߳�
          { 
            while(1){
                sem_wait(&orange);
                pthread_mutex_lock(&work_mutex);     //����
                printf("Ů������һ������!\n");
                sem_post(&empty);
                pthread_mutex_unlock(&work_mutex);   //����
                sleep(2);
            }
 
           }
 
int main()
{ 
    pthread_t father;  //�����߳�
    pthread_t mother;
    pthread_t son;
    pthread_t daughter;

    sem_init(&empty, 0, 1);  //�ź�����ʼ��
    sem_init(&apple, 0, 0);
    sem_init(&orange, 0, 0);
	pthread_mutex_init(&work_mutex, NULL);   //��ʼ��������
 
    pthread_create(&father,NULL,procf,NULL);  //�����߳�
    pthread_create(&mother,NULL,procm,NULL);
    pthread_create(&daughter,NULL,procd,NULL);
    pthread_create(&son,NULL,procs,NULL);

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
    return 0;

}

