#include <stdio.h>
#include "thread.h"
#include "xtimer.h"

static char thread_1_stack[THREAD_STACKSIZE_MAIN];
static char thread_2_stack[THREAD_STACKSIZE_MAIN];
static kernel_pid_t thread_1_pid, thread_2_pid;

static void *thread_1(void *arg);
static void *thread_2(void *arg);

int main(void)
{
  printf("thread yield example\n");

  thread_1_pid = thread_create(thread_1_stack,
                              sizeof(thread_1_stack),
                              (THREAD_PRIORITY_MAIN - 1),
                              THREAD_CREATE_STACKTEST,
                              thread_1,
                              NULL,
                              "thread 1");

  thread_2_pid = thread_create(thread_2_stack,
                               sizeof(thread_2_stack),
                               (THREAD_PRIORITY_MAIN - 1),
                               THREAD_CREATE_STACKTEST,
                               thread_2,
                               NULL,
                               "thread 2");

  return 0;
}

static void *thread_1(void *arg)
{
  (void)arg;

  printf("thread 1 is starting\n");
  uint32_t cnt = 0;

  while (1)
  {
    printf("[t1] %ld before yield\n", cnt);
    xtimer_sleep(1);
    thread_yield();
    printf("[t1] %ld after yield\n", cnt);
    xtimer_sleep(1);
    cnt++;
  }

  return NULL;
}

static void *thread_2(void *arg)
{
  (void)arg;

  printf("thread 2 is starting\n");
  uint32_t cnt = 0;

  while (1)
  {
    printf("[t2] %ld before yield\n", cnt);
    xtimer_sleep(1);
    thread_yield();
    printf("[t2] %ld after yield\n", cnt);
    xtimer_sleep(1);
    cnt++;
  }

  return NULL;
}
