#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <assert.h>

#include <unistd.h>

#include "sem.h"

int randInt() {
    return (rand() % 50) + 50;
}

struct BoundedBuffer {
  int start;
  int end;
  int size;
  int* buffer;
};

typedef struct BoundedBuffer BoundedBuffer;

BoundedBuffer * createBoundedBuffer(int size) {
  if (size < 1) return NULL;
  BoundedBuffer * bb = malloc(sizeof(BoundedBuffer));
  if (bb) {
    bb->start = 0;
    bb->end = size-1;
    bb->size = size;
    bb->buffer = malloc(sizeof(int) * size);
    if (!bb->buffer) {
      free(bb);
      return NULL;
    }
  }
  return bb;
}

void destroyBoundedBuffer(BoundedBuffer * bb) {
  if (!bb) return;
  free(bb->buffer);
  free(bb);
}

// after bounded buffer definition
sem_t fillCount;  // data in the buffer, 元素数信号量
sem_t emptyCount; // free space in the buffer, 空位数信号量

// 生产fun: buffer添加元素,移动start(当前size指针)
void addItem(BoundedBuffer * bb, int item) {
  if (!bb) return;
  bb->buffer[bb->start] = item;
  bb->start = (bb->start + 1) % bb->size; // move start one forward
}

// 生产者
void * producer(void * arg) {
  BoundedBuffer * bb = (BoundedBuffer*)arg;

  for (int i = 0; i < 10; i++) {
    sem_wait(emptyCount);//empty--, <0时当前线程阻塞在empty-cv队列(buffer满,即阻塞在ADD队列等待唤醒)

    int item = randInt();
    printf("produced item %d\n", item);
    addItem(bb, item);

    sem_signal(fillCount);//fill++, 唤醒fill-cv队列中阻塞的一个线程
    usleep(randInt());
  }
  return NULL;
}

// 消费func
int removeItem(BoundedBuffer * bb) {
  if (!bb) assert(0);
  // buffer is no longer empty
  bb->end = (bb->end + 1) % bb->size; // move end one forward
  int item = bb->buffer[bb->end];
  return item;
}

// 消费者
void * consumer(void * arg) {
  BoundedBuffer * bb = (BoundedBuffer*)arg;

  for (int i = 0; i < 10; i++) {
    sem_wait(fillCount); //fill--, <0时阻塞在fill-cv队列(buffer为空,即阻塞在Remove队列等待唤醒)

    int item = removeItem(bb);
    printf("    consumed item %d\n", item);

    sem_signal(emptyCount);//empty++, 唤醒empty-cv队列中的一个线程
    usleep(randInt());
  }
  return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t t1;
    pthread_t t2;
    int err;

    BoundedBuffer * bb = createBoundedBuffer(4);
    fillCount  = sem_create(0, 4);
    emptyCount = sem_create(4, 4);

    err = pthread_create(&t1, NULL, consumer, bb); assert(err == 0);
    err = pthread_create(&t2, NULL, producer, bb); assert(err == 0);

    err = pthread_join(t1, NULL); assert(err == 0);
    err = pthread_join(t2, NULL); assert(err == 0);

    destroyBoundedBuffer(bb);
    sem_destroy(fillCount);
    sem_destroy(emptyCount);
}