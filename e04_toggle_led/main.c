#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "shell_commands.h"
#include "board.h"

#define USAGE_STR "toggle <state> (state: on/off)\n"

static int cmd_handler(int argc, char **argv);

int main(void)
{
  printf("toggle led example\n");

  char line_buf[SHELL_DEFAULT_BUFSIZE];

  // last element of the array is necessary
  static const shell_command_t shell_commands[] = {
      {"toggle", USAGE_STR, cmd_handler},
      {NULL, NULL, NULL}};

  shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

  return 0;
}

static int cmd_handler(int argc, char **argv)
{
  if (argc != 2)
  {
    printf("%s", USAGE_STR);
    return -1;
  }

  if (memcmp(argv[1], "on", 2) == 0)
  {
    LED0_ON;
  }
  else if (memcmp(argv[1], "off", 3) == 0)
  {
    LED0_OFF;
  }
  else
  {
    printf("%s", USAGE_STR);
    return -1;
  }

  return 0;
}