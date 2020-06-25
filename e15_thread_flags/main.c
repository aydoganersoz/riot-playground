#include <stdio.h>
#include "thread.h"
#include "thread_flags.h"
#include "xtimer.h"
#include "periph/gpio.h"

static thread_flags_t event0_flag = 0x0001;
static thread_flags_t event1_flag = 0x0002;
static thread_flags_t event2_flag = 0x0004;
static char one_receiver_thread_stack[THREAD_STACKSIZE_MAIN];
static char any_receiver_thread_stack[THREAD_STACKSIZE_MAIN];
static char all_receiver_thread_stack[THREAD_STACKSIZE_MAIN];
static kernel_pid_t one_receiver_thread_pid;
static kernel_pid_t any_receiver_thread_pid;
static kernel_pid_t all_receiver_thread_pid;

static void *one_receiver_thread(void *arg);
static void *any_receiver_thread(void *arg);
static void *all_receiver_thread(void *arg);
static void btn0_callback(void *arg);
static void btn1_callback(void *arg);
static void btn2_callback(void *arg);

int main(void)
{
  printf("thread flags example\n");

  gpio_init(LED1_PIN, GPIO_OUT);
  gpio_init(LED2_PIN, GPIO_OUT);
  gpio_init(LED3_PIN, GPIO_OUT);
  LED1_OFF;
  LED2_OFF;
  LED3_OFF;
  gpio_init_int(BTN0_PIN, BTN0_MODE, GPIO_FALLING, btn0_callback, NULL);
  gpio_init_int(BTN1_PIN, BTN1_MODE, GPIO_FALLING, btn1_callback, NULL);
  gpio_init_int(BTN2_PIN, BTN2_MODE, GPIO_FALLING, btn2_callback, NULL);

  one_receiver_thread_pid = thread_create(one_receiver_thread_stack,
                                          sizeof(one_receiver_thread_stack),
                                          (THREAD_PRIORITY_MAIN - 1),
                                          THREAD_CREATE_STACKTEST,
                                          one_receiver_thread,
                                          NULL,
                                          "one receiver thread");

  any_receiver_thread_pid = thread_create(any_receiver_thread_stack,
                                          sizeof(any_receiver_thread_stack),
                                          (THREAD_PRIORITY_MAIN - 1),
                                          THREAD_CREATE_STACKTEST,
                                          any_receiver_thread,
                                          NULL,
                                          "any receiver thread");

  all_receiver_thread_pid = thread_create(all_receiver_thread_stack,
                                          sizeof(all_receiver_thread_stack),
                                          (THREAD_PRIORITY_MAIN - 1),
                                          THREAD_CREATE_STACKTEST,
                                          all_receiver_thread,
                                          NULL,
                                          "all receiver thread");

  return 0;
}

static void *one_receiver_thread(void *arg)
{
  (void)arg;

  while (1)
  {
    thread_flags_wait_one(event0_flag);
    printf("the waiting flag is set\n");
    LED1_TOGGLE;
  }

  return NULL;
}

static void *any_receiver_thread(void *arg)
{
  (void)arg;

  while (1)
  {
    thread_flags_wait_any(event0_flag | event1_flag | event2_flag);
    printf("a waiting flag is set\n");
    LED2_TOGGLE;
  }

  return NULL;
}

static void *all_receiver_thread(void *arg)
{
  (void)arg;

  while (1)
  {
    thread_flags_wait_all(event0_flag | event1_flag | event2_flag);
    printf("all the waiting flags are set\n");
    LED3_TOGGLE;
  }

  return NULL;
}

static void btn0_callback(void *arg)
{
  (void)arg;

  thread_flags_set((thread_t *)thread_get(one_receiver_thread_pid), event0_flag);
}

static void btn1_callback(void *arg)
{
  (void)arg;

  thread_flags_set((thread_t *)thread_get(any_receiver_thread_pid), event1_flag);
}

static void btn2_callback(void *arg)
{
  (void)arg;

  thread_flags_set((thread_t *)thread_get(all_receiver_thread_pid), event0_flag | event1_flag | event2_flag);
}
