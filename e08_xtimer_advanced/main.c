#include <stdio.h>
#include "thread.h"
#include "msg.h"
#include "xtimer.h"

#define PERIOD_INDEPENDENT_THREAD (3 * US_PER_SEC)
#define DELAY_TMR_CALLBACK (1 * US_PER_SEC)

static char receiver_thread_stack[THREAD_STACKSIZE_MAIN];
static char independent_thread_stack[THREAD_STACKSIZE_MAIN];
static kernel_pid_t receiver_thread_pid, independent_thread_pid;

xtimer_t tmr, tmr2;

static void *receiver_thread(void *arg);
static void *independent_thread(void *arg);

static void tmr_callback(void *arg);

int main(void)
{
  printf("xtimer advanced example\n");

  receiver_thread_pid = thread_create(receiver_thread_stack,
                                      sizeof(receiver_thread_stack),
                                      (THREAD_PRIORITY_MAIN - 1),
                                      THREAD_CREATE_STACKTEST,
                                      receiver_thread,
                                      NULL,
                                      "receiver thread");

  independent_thread_pid = thread_create(independent_thread_stack,
                                         sizeof(independent_thread_stack),
                                         (THREAD_PRIORITY_MAIN - 1),
                                         THREAD_CREATE_STACKTEST,
                                         independent_thread,
                                         NULL,
                                         "independent thread");

  return 0;
}

static void *receiver_thread(void *arg)
{
  (void)arg;

  printf("receiver thread is starting\n");
  msg_t msg;

  while (1)
  {
    msg_receive(&msg);
    printf("message received with value: %ld\n", msg.content.value);
  }

  return NULL;
}

static void *independent_thread(void *arg)
{
  (void)arg;

  printf("independent thread is starting\n");
  xtimer_ticks32_t last_wakeup = xtimer_now();
  tmr.callback = tmr_callback;

  while (1)
  {
    xtimer_periodic_wakeup(&last_wakeup, PERIOD_INDEPENDENT_THREAD);
    tmr.arg = (void *)&last_wakeup.ticks32;
    xtimer_set(&tmr, DELAY_TMR_CALLBACK);
    printf("independent thread last wake up: %ld\n", last_wakeup.ticks32);
  }

  return NULL;
}

static void tmr_callback(void *arg)
{
  msg_t msg;

  msg.content.value = *((uint32_t *)arg);
  printf("timer callback is called with arg: %ld\n", msg.content.value);
  xtimer_set_msg(&tmr2, 0, &msg, receiver_thread_pid);
}
