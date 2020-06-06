#include <stdio.h>
#include "thread.h"
#include "msg.h"
#include "xtimer.h"

#ifndef ONE_SECOND_DURATION
#define ONE_SECOND_DURATION (1000000U)
#endif

static char thread_1_stack[THREAD_STACKSIZE_MAIN];
static char thread_2_stack[THREAD_STACKSIZE_MAIN];
static kernel_pid_t thread_1_pid, thread_2_pid;

static void *thread_1(void *arg);
static void *thread_2(void *arg);

int main(void)
{
  printf("thread pingpong example\n");

  thread_1_pid = thread_create(thread_1_stack,
                               sizeof(thread_1_stack),
                               (THREAD_PRIORITY_MAIN - 1),
                               THREAD_CREATE_STACKTEST,
                               thread_1,
                               (void *)"1",
                               "thread 1");

  thread_2_pid = thread_create(thread_2_stack,
                               sizeof(thread_2_stack),
                               (THREAD_PRIORITY_MAIN - 1),
                               THREAD_CREATE_STACKTEST,
                               thread_2,
                               (void *)"2",
                               "thread 2");

  printf("thread 1 pid: %d\n", thread_1_pid);
  printf("thread 2 pid: %d\n", thread_2_pid);

  return 0;
}

static void *thread_1(void *arg)
{
  printf("thread %s is starting to receive\n", (char *)arg);
  msg_t msg;

  while (1)
  {
    msg_receive(&msg);
    printf("message from thread 2 is recevied: %ld\n", msg.content.value);
  }

  return NULL;
}

static void *thread_2(void *arg)
{
  printf("thread %s is starting to send\n", (char *)arg);
  msg_t msg;

  while (1)
  {
    msg_send(&msg, thread_1_pid);
    printf("message from thread 2 is sent: %ld\n", msg.content.value);
    msg.content.value++;
    xtimer_sleep(1);
  }

  return NULL;
}