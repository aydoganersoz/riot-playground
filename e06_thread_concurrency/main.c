#include <stdio.h>
#include "thread.h"
#include "xtimer.h"

#define PRINTER_THREAD_PERIOD (200U * US_PER_MS)
#define WRITER_THREAD_PERIOD (100U * US_PER_MS)

typedef struct
{
  char buffer[128];
  mutex_t lock;
} data_t;

static char printer_thread_stack[THREAD_STACKSIZE_MAIN];
static char writer_thread_stack[THREAD_STACKSIZE_MAIN];

static data_t data;

static void *printer_thread(void *arg);
static void *writer_thread(void *arg);

static void update_mutual_buffer(void);
static void read_mutual_buffer(void);

int main(void)
{
  puts("thread concurrency example");

  thread_create(printer_thread_stack,
                sizeof(printer_thread_stack),
                (THREAD_PRIORITY_MAIN - 1),
                THREAD_CREATE_STACKTEST,
                printer_thread,
                NULL,
                "printer thread");

  thread_create(writer_thread_stack,
                sizeof(writer_thread_stack),
                (THREAD_PRIORITY_MAIN - 1),
                THREAD_CREATE_STACKTEST,
                writer_thread,
                NULL,
                "writer thread");

  return 0;
}

static void *printer_thread(void *arg)
{
  (void)arg;

  puts("printer thread is starting...");

  while (1)
  {
    read_mutual_buffer();
  }

  return NULL;
}

static void *writer_thread(void *arg)
{
  (void)arg;

  puts("writer thread is starting...");

  while (1)
  {
    update_mutual_buffer();
  }

  return NULL;
}

static void update_mutual_buffer(void)
{
  mutex_lock(&data.lock);
  size_t p = sprintf(data.buffer, "start: %" PRIu32 "", xtimer_now().ticks32);
  xtimer_usleep(WRITER_THREAD_PERIOD);
  p += sprintf(&data.buffer[p], " - end: %" PRIu32 "", xtimer_now().ticks32);
  mutex_unlock(&data.lock);
}

static void read_mutual_buffer(void)
{
  mutex_lock(&data.lock);
  puts(data.buffer);
  xtimer_usleep(PRINTER_THREAD_PERIOD);
  mutex_unlock(&data.lock);
}