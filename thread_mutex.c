#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int share_num = 0;
pthread_mutex_t mutex;

static void * print_a(void *);
static void * print_b(void *);

int main(){

  pthread_t t0;
  pthread_t t1;

  // 初始化互斥锁
  if (pthread_mutex_init(&mutex, NULL) != 0){
          // 互斥锁初始化失败
          return -1;
  }

  // 创建线程A
  if(pthread_create(&t0, NULL, print_a, NULL) == -1){
      puts("fail to create pthread t0");
      exit(1);
  }

  if(pthread_create(&t1, NULL, print_b, NULL) == -1){
      puts("fail to create pthread t1");
      exit(1);
  }

  // 等待线程结束
  void * result;
  if(pthread_join(t0, &result) == -1){
      puts("fail to recollect t0");
      exit(1);
  }

  if(pthread_join(t1, &result) == -1){
      puts("fail to recollect t1");
      exit(1);
  }

  pthread_mutex_destroy(&mutex);


  return 0;
}


// 线程A 方法
static void * print_a(void *a){
  for(int i = 0;i < 100000; i++){
      if (pthread_mutex_lock(&mutex) != 0){
              fprintf(stdout, "lock error!\n");
      }
      share_num++;
      pthread_mutex_unlock(&mutex);

      printf("aa  >>> thread - 1 - %d  \n", share_num);
  }
  return NULL;

}

// 线程B 方法
static void * print_b(void *b){
  for(int i=0;i<100000;i++){
      if (pthread_mutex_lock(&mutex) != 0){
                    fprintf(stdout, "lock error!\n");
      }

      share_num++;
      pthread_mutex_unlock(&mutex);

      printf("bb    >>>    thread - 2 - %d  \n", share_num);
  }
  return NULL;
}
