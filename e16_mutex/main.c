#include <stdio.h>
#include "thread.h"
#include "xtimer.h"
#include "board.h"
#include "periph/gpio.h"

static char thread_1_thread_stack[THREAD_STACKSIZE_MAIN];
static char thread_2_thread_stack[THREAD_STACKSIZE_MAIN];
static mutex_t print_lock;
static volatile bool mutex_enabled;

static void *thread_1_thread(void *arg);
static void *thread_2_thread(void *arg);
static void safe_print_thread_number(uint8_t num);
static void print_thread_number(uint8_t num);
static void btn0_callback(void *arg);

int main(void)
{
  puts("mutex example");

  mutex_enabled = true;

  gpio_init_int(BTN0_PIN, BTN0_MODE, GPIO_FALLING, btn0_callback, NULL);

  thread_create(thread_1_thread_stack,
                sizeof(thread_1_thread_stack),
                (THREAD_PRIORITY_MAIN - 1),
                THREAD_CREATE_STACKTEST,
                thread_1_thread,
                NULL,
                "thread 1 thread");

  thread_create(thread_2_thread_stack,
                sizeof(thread_2_thread_stack),
                (THREAD_PRIORITY_MAIN - 1),
                THREAD_CREATE_STACKTEST,
                thread_2_thread,
                NULL,
                "thread 2 thread");

  return 0;
}

static void *thread_1_thread(void *arg)
{
  (void)arg;

  puts("thread 1 is starting...");
  xtimer_sleep(1);

  while (1)
  {
    safe_print_thread_number(1);
    thread_yield();
  }

  return NULL;
}

static void *thread_2_thread(void *arg)
{
  (void)arg;

  puts("thread 2 is starting...");
  xtimer_sleep(1);

  while (1)
  {
    safe_print_thread_number(2);
    thread_yield();
  }

  return NULL;
}

static void safe_print_thread_number(uint8_t num)
{
  if (mutex_enabled)
  {
    mutex_lock(&print_lock);
    print_thread_number(num);
    mutex_unlock(&print_lock);
  }
  else
  {
    print_thread_number(num);
  }
}

static void print_thread_number(uint8_t num)
{
  printf("this is ");
  thread_yield();
  printf("thread %d\n", num);
}

static void btn0_callback(void *arg)
{
  (void)arg;

  mutex_enabled = !mutex_enabled;
}
