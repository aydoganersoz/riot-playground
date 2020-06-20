#include <stdio.h>
#include "thread.h"
#include "msg.h"
#include "board.h"
#include "periph/gpio.h"

static char receiver_thread_stack[THREAD_STACKSIZE_MAIN];
static kernel_pid_t receiver_thread_pid;

static void *receiver_thread(void *arg);
static void gpio_callback(void *arg);

int main(void)
{
  printf("thread sleep example\n");

  gpio_init(LED1_PIN, GPIO_OUT);
  LED1_OFF;
  gpio_init_int(BTN1_PIN, BTN1_MODE, GPIO_FALLING, gpio_callback, NULL);

  receiver_thread_pid = thread_create(receiver_thread_stack,
                                      sizeof(receiver_thread_stack),
                                      (THREAD_PRIORITY_MAIN - 1),
                                      THREAD_CREATE_STACKTEST,
                                      receiver_thread,
                                      NULL,
                                      "receiver thread");

  return 0;
}

static void *receiver_thread(void *arg)
{
  (void)arg;

  printf("receiver thread is starting\n");
  msg_t msg;

  while (1)
  {
    thread_sleep();
    printf("message received from interrupt\n");
    msg_try_receive(&msg);
    LED1_TOGGLE;
  }

  return NULL;
}

static void gpio_callback(void *arg)
{
  (void)arg;

  msg_t msg;

  thread_wakeup(receiver_thread_pid);
  msg_send_int(&msg, receiver_thread_pid);
  printf("message sent from interrupt\n");
}
