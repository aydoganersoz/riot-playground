#include <stdio.h>
#include "thread.h"
#include "msg.h"
#include "board.h"
#include "xtimer.h"
#include "periph/rtc.h"
#include "periph/gpio.h"

#define LED_ON_DURATION (1U)
#define RTC_ALARM_PERIOD (5U)

static char receiver_thread_stack[THREAD_STACKSIZE_DEFAULT];
static kernel_pid_t receiver_thread_pid;
static struct tm rtc_time;

static void *receiver_thread(void *arg);
static void rtc_alarm_callback(void *arg);
static void set_rtc_alarm(void);

int main(void)
{
  printf("rtc alarm example\n");

  gpio_init(LED1_PIN, GPIO_OUT);
  LED1_OFF;

  rtc_init();
  rtc_poweron();
  rtc_tm_normalize(&rtc_time);

  receiver_thread_pid = thread_create(receiver_thread_stack,
                                      sizeof(receiver_thread_stack),
                                      (THREAD_PRIORITY_MAIN - 1),
                                      THREAD_CREATE_STACKTEST,
                                      receiver_thread,
                                      NULL,
                                      "receiver thread");

  msg_t msg;
  msg_send(&msg, receiver_thread_pid);

  return 0;
}

static void *receiver_thread(void *arg)
{
  (void)arg;

  printf("receiver thread is starting\n");

  while (1)
  {
    msg_t msg;

    msg_receive(&msg);
    LED1_ON;
    xtimer_sleep(LED_ON_DURATION);
    LED1_OFF;
    rtc_get_time(&rtc_time);
    printf("rtc time is: %d:%d:%d\n", rtc_time.tm_hour, rtc_time.tm_min, rtc_time.tm_sec);
    set_rtc_alarm();
  }

  return NULL;
}

static void rtc_alarm_callback(void *arg)
{
  (void)arg;
  msg_t msg;

  msg_send_int(&msg, receiver_thread_pid);
}

static void set_rtc_alarm(void)
{
  rtc_time.tm_sec += RTC_ALARM_PERIOD;
  rtc_set_alarm(&rtc_time, rtc_alarm_callback, NULL);
}
