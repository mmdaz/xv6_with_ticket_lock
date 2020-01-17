// #include "semaphore.h"
#include "defs.h"
struct semaphore {
  struct spinlock lock;
  int value;
  int active;
};
struct semaphore sema[32];

int
sem_init(int sem, int value)
{
  acquire(&sema[sem].lock);

  if (sema[sem].active == 0)
  {
     sema[sem].active = 1;
     sema[sem].value = value;
  }
  else
  {
     return -1;
  }  

  release(&sema[sem].lock);

  return 0;
}


int
sem_destroy(int sem)
{
  acquire(&sema[sem].lock);
  sema[sem].active = 0;
  release(&sema[sem].lock);

  return 0; 
}

int sem_wait(int sem)
{
   int count = 1;
  acquire(&sema[sem].lock);

  if (sema[sem].value >= count)
  {
     sema[sem].value = sema[sem].value - count;
  }
  else
  {
     while (sema[sem].value < count)
     {  
        sleep(&sema[sem],&sema[sem].lock);
     }
     sema[sem].value = sema[sem].value - count;
  }

  release(&sema[sem].lock);

  return 0;
}


int sem_signal(int sem)
{
    int count =1;
  acquire(&sema[sem].lock);

  sema[sem].value = sema[sem].value + count;
  wakeup(&sema[sem]); 
  release(&sema[sem].lock);

  return 0;
}
