#include "ticketlock.h"
#include "defs.h"
int data1; 
int rcount;
struct ticketlock writelock, lock;


void initrwlock()
{
  data1 = 0;
  rcount = 0;
  initlock_t(&writelock,"wl");
  initlock_t(&lock,"l");
}

int reader()
{
  // int f;
  // f = ((int)arg);
  acquire_t(&lock);
  rcount = rcount + 1;
  if(rcount==1)
    acquire_t(&writelock);
  release_t(&lock);
  cprintf("data1 read by the reader is %d\n",data1);
//   sleep(1);
  acquire_t(&lock);
  rcount = rcount - 1;
  if(rcount==0)
    release_t(&writelock);
  release_t(&lock);
  return data1;
}

void writer()
{
  // int f;
  // f = ((int) arg);
  acquire_t(&writelock);
  data1++;
  cprintf("data1 writen by the writer is %d\n",data1);
//   sleep(1,);
  release_t(&writelock);
}
