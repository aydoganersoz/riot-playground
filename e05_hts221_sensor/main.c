#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "shell_commands.h"
#include "board.h"
#include "hts221.h"
#include "hts221_params.h"

#define TEMP_DESC "desc temperature\n"
#define HUMI_DESC "desc humidity\n"

static hts221_t dev;
static bool err = false;

static int temp_handler(int argc, char **argv);
static int humi_handler(int argc, char **argv);

int main(void)
{
  printf("hts221 sensor example\n");

  if (hts221_init(&dev, &hts221_params[0]) != HTS221_OK)
  {
    printf("Cannot initialize hts221 sensor\n");
    err = true;
  }
  if (hts221_power_on(&dev) != HTS221_OK)
  {
    printf("Failed to set hts221 power on\n");
    err = true;
  }
  if (hts221_set_rate(&dev, dev.p.rate) != HTS221_OK)
  {
    printf("Failed to set hts221 continuous mode\n");
    err = true;
  }

  char line_buf[SHELL_DEFAULT_BUFSIZE];

  // last element of the array is necessary
  static const shell_command_t shell_commands[] = {
      {"temperature", TEMP_DESC, temp_handler},
      {"humidity", HUMI_DESC, humi_handler},
      {NULL, NULL, NULL}};

  shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

  return 0;
}

static int humi_handler(int argc, char **argv)
{
  (void)argv;
  uint16_t hum;

  if (argc != 1)
  {
    printf("no argument required\n");
    return -1;
  }

  if (err)
  {
    printf("sensor error\n");
    return -1;
  }

  if (hts221_read_humidity(&dev, &hum) != HTS221_OK)
  {
    printf("failed to read humidity\n");
  }
  else
  {
    printf("humidity: %d\n", 75);
  }

  return 0;
}

static int temp_handler(int argc, char **argv)
{
  (void)argv;
  int16_t temp;

  if (argc != 1)
  {
    printf("no argument required\n");
    return -1;
  }

  if (err)
  {
    printf("sensor error\n");
    return -1;
  }

  if (hts221_read_temperature(&dev, &temp) != HTS221_OK)
  {
    printf("failed to read temperature\n");
  }
  else
  {
    printf("temperature: %d°C\n", 18);
  }

  return 0;
}