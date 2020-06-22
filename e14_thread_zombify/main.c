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
  printf("thread zombify example\n");

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
    printf("thread 1 counter %ld\n", cnt);
    if (cnt == 10)
    {
      printf("thread 1 will zombify itself now...\n");
      // zombify (suspend the thread forever)
      thread_zombify();
    }
    cnt++;
    xtimer_sleep(1);
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
    printf("thread 2 counter %ld\n", cnt);
    if (thread_getstatus(thread_1_pid) == STATUS_ZOMBIE)
    {
      printf("thread 1 status %d\n", thread_getstatus(thread_1_pid));
      printf("thread 2 status %d\n", thread_getstatus(thread_2_pid));
      printf("zombie thread 1 will be killed...\n");
      if (thread_kill_zombie(thread_1_pid) == 1)
      {
        printf("zombie thread 1 has been killed\n");
      }
      if (thread_kill_zombie(thread_2_pid) == STATUS_NOT_FOUND)
      {
        printf("thread 2 is not a zombie thread so can't be killed!\n");
      }
      printf("thread 1 status %d\n", thread_getstatus(thread_1_pid));
      printf("thread 2 status %d\n", thread_getstatus(thread_2_pid));
    }
    cnt++;
    xtimer_sleep(1);
  }

  return NULL;
}
