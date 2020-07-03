#include <stdio.h>
#include "thread.h"
#include "xtimer.h"
#include "sema.h"

static char thread_1_stack[THREAD_STACKSIZE_MAIN];
static char thread_2_stack[THREAD_STACKSIZE_MAIN];
static char thread_3_stack[THREAD_STACKSIZE_MAIN];
static char thread_4_stack[THREAD_STACKSIZE_MAIN];
static sema_t sem;

static void *thread_1(void *arg);
static void *thread_2(void *arg);
static void *thread_3(void *arg);
static void *thread_4(void *arg);
static void use_protected_resource(uint8_t thread_id);

int main(void)
{
  puts("semaphore example");

  sema_create(&sem, 2);
  printf("I am main thread - semaphore value is %d\n", sem.value);

  thread_create(thread_1_stack,
                sizeof(thread_1_stack),
                (THREAD_PRIORITY_MAIN - 1),
                THREAD_CREATE_STACKTEST,
                thread_1,
                NULL,
                "thread 1");

  thread_create(thread_2_stack,
                sizeof(thread_2_stack),
                (THREAD_PRIORITY_MAIN - 1),
                THREAD_CREATE_STACKTEST,
                thread_2,
                NULL,
                "thread 2");

  thread_create(thread_3_stack,
                sizeof(thread_3_stack),
                (THREAD_PRIORITY_MAIN - 1),
                THREAD_CREATE_STACKTEST,
                thread_3,
                NULL,
                "thread 3");

  thread_create(thread_4_stack,
                sizeof(thread_4_stack),
                (THREAD_PRIORITY_MAIN - 1),
                THREAD_CREATE_STACKTEST,
                thread_4,
                NULL,
                "thread 4");

  return 0;
}

static void use_protected_resource(uint8_t thread_id)
{
  printf("Thread %d locked a semaphore - remaining semaphore value is %d\n", thread_id, sem.value);
}

static void *thread_1(void *arg)
{
  (void)arg;

  xtimer_usleep(1000);

  sema_wait(&sem);
  use_protected_resource(1);
  xtimer_sleep(10); // lock for 10 seconds
  sema_post(&sem);

  return NULL;
}

static void *thread_2(void *arg)
{
  (void)arg;

  xtimer_usleep(1000);

  sema_wait(&sem);
  use_protected_resource(2);
  xtimer_sleep(10); // lock for 10 seconds
  sema_post(&sem);

  return NULL;
}

static void *thread_3(void *arg)
{
  (void)arg;

  xtimer_sleep(1);

  sema_wait(&sem);
  use_protected_resource(3);
  xtimer_sleep(2); // lock for 2 seconds
  sema_post(&sem);

  return NULL;
}

static void *thread_4(void *arg)
{
  (void)arg;

  xtimer_sleep(1);

  while (1)
  {
    sema_wait(&sem);
    use_protected_resource(4);
    xtimer_sleep(1); // lock for 2 seconds
    sema_post(&sem);
    thread_yield();
  }

  return NULL;
}
