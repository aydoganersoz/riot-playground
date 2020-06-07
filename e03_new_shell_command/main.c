#include <stdio.h>
#include "shell.h"
#include "shell_commands.h"

static int cmd_handler(int argc, char **argv);

int main(void)
{
  printf("new shell command example\n");

  char line_buf[SHELL_DEFAULT_BUFSIZE];

  // last element of the array is necessary
  static const shell_command_t shell_commands[] = {
      {"aydu", "aydu cmd help", cmd_handler},
      {NULL, NULL, NULL}};

  shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

  return 0;
}

static int cmd_handler(int argc, char **argv)
{
  printf("cmd: %s\n", argv[0]);
  for (int i = 1; i < argc; i++)
  {
    printf("arg%d: %s\n", i, argv[i]);
  }

  return 0;
}