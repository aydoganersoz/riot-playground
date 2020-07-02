#include <stdio.h>
#include "thread.h"
#include "xtimer.h"
#include "sema.h"

static char thread_1_stack[THREAD_STACKSIZE_MAIN];
static char thread_2_stack[THREAD_STACKSIZE_MAIN];
static uint8_t thread_id;
static sema_t sem;

static void *thread_generic(void *arg);
static void use_protected_resource(uint8_t thread_id);

int main(void)
{
  puts("semaphore example");

  sema_create(&sem, 2);

  thread_id = 1;
  thread_create(thread_1_stack,
                sizeof(thread_1_stack),
                (THREAD_PRIORITY_MAIN - 1),
                THREAD_CREATE_STACKTEST,
                thread_generic,
                (void *)&thread_id,
                "thread 1");

  thread_id = 2;
  thread_create(thread_2_stack,
                sizeof(thread_2_stack),
                (THREAD_PRIORITY_MAIN - 1),
                THREAD_CREATE_STACKTEST,
                thread_generic,
                (void *)&thread_id,
                "thread 2");

  return 0;
}

static void *thread_generic(void *arg)
{
  uint8_t id = *((uint8_t *)arg);

  xtimer_usleep(1000);

  while (1)
  {
    sema_wait(&sem);
    use_protected_resource(id);
    sema_post(&sem);
    thread_yield();
  }

  return NULL;
}

static void use_protected_resource(uint8_t thread_id)
{
  xtimer_sleep(1);
  printf("I am thread %d - semaphore value is %d\n", thread_id, sem.value);
  xtimer_sleep(1);
}
