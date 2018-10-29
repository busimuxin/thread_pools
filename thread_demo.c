#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>


static void * print_a(void *);
static void * print_b(void *);

int main(){

  pthread_t t0;
  pthread_t t1;

  // �����߳�A
  if(pthread_create(&t0, NULL, print_a, NULL) == -1){
      puts("fail to create pthread t0");
      exit(1);
  }

  if(pthread_create(&t1, NULL, print_b, NULL) == -1){
      puts("fail to create pthread t1");
      exit(1);
  }

  // �ȴ��߳̽���
  void * result;
  if(pthread_join(t0, &result) == -1){
      puts("fail to recollect t0");
      exit(1);
  }

  if(pthread_join(t1, &result) == -1){
      puts("fail to recollect t1");
      exit(1);
  }


  return 0;
}


// �߳�A ����
void * print_a(void *a){
  for(int i = 0;i < 10; i++){
      sleep(1);
      puts("aa  >>> thread - 1");
  }
  return NULL;

}

// �߳�B ����
void * print_b(void *b){
  for(int i=0;i<20;i++){
      sleep(1);
      puts("bb    >>>    thread - 2");
  }
  return NULL;
}