#include "semaphore.h"
// #include "user.h"
#include "defs.h"
#define mutex 1
#define writeblock 2
int data, rcount;


void initrwlock()
{
data = 0,rcount = 0;
sem_init(mutex, 1);
sem_init(writeblock, 1);
}

void reader(void *arg)
{
  int f;
  f = ((int)arg);
  sem_wait(mutex);
  rcount = rcount + 1;
  if(rcount==1)
   sem_wait(writeblock);
  sem_signal(mutex);
  cprintf("Data read by the reader%d is %d\n",f,data);
//   sleep(1);
  sem_wait(mutex);
  rcount = rcount - 1;
  if(rcount==0)
   sem_signal(writeblock);
  sem_signal(mutex);
}

void writer(void *arg)
{
  int f;
  f = ((int) arg);
  sem_wait(writeblock);
  data++;
  cprintf("Data writen by the writer%d is %d\n",f,data);
//   sleep(1,);
  sem_signal(writeblock);
}
