#include <stdio.h>
#include "thread.h"
#include "msg.h"
#include "shell.h"
#include "shell_commands.h"

static char printer_thread_stack[THREAD_STACKSIZE_MAIN];
static kernel_pid_t printer_thread_pid;

static void *printer_thread(void *arg);

static int send_cmd_handler(int argc, char **argv);

int main(void)
{
  printf("thread ipc example\n");

  printer_thread_pid = thread_create(printer_thread_stack,
                                     sizeof(printer_thread_stack),
                                     (THREAD_PRIORITY_MAIN - 1),
                                     THREAD_CREATE_STACKTEST,
                                     printer_thread,
                                     NULL,
                                     "printer thread");

  char line_buf[SHELL_DEFAULT_BUFSIZE];

  // last element of the array is necessary
  static const shell_command_t shell_commands[] = {
      {"send", "prints argument", send_cmd_handler},
      {NULL, NULL, NULL}};

  shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

  return 0;
}

static void *printer_thread(void *arg)
{
  (void)arg;

  printf("printer thread is starting\n");
  msg_t msg;

  while (1)
  {
    msg_receive(&msg);
    printf("Message received: %s\n", (char *)msg.content.ptr);
  }

  return NULL;
}

static int send_cmd_handler(int argc, char **argv)
{
  if (argc != 2)
  {
    printf("wrong usage\n");
    return -1;
  }

  msg_t msg;

  msg.content.ptr = argv[1];
  msg_send(&msg, printer_thread_pid);

  return 0;
}
