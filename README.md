# RIOT-OS examples

## How to build an example

From the root directory:

```bash
make BOARD=<board> -C <example>
```

## How to build and flash an example

From the root directory:

```bash
make BOARD=<board> -C <example> flash
```

## How to access STDIO via UART

From the root directory:

```bash
make BOARD=<board> -C <example> term
```

## Examples

### e01_hello_world

Hello world application. Playing with `printf` function.

### e02_thread_pingpong

One thread is sending a message to another one every 1 second. Playing with `thread_create`, `msg_receive`, `msg_send`, `xtimer_sleep` functions.

### e03_new_shell_command

New (custom) shell command. Playing with `shell_run` function.

### e04_toggle_led

Toggling LED. Playing with `LED*_<state>` macros.

### e05_hts221_sensor

Reading temperature and humidity from HTS221 sensor. Playing with `hts221_*` functions.

### e06_thread_concurrency

Writing to and reading from a mutual buffer using mutex. Playing with `mutex_lock`, `mutex_unlock`, `xtimer_usleep`, `xtimer_now` functions.

### e07_thread_ipc

A blocking receive call in a separate thread is waiting for a message from the shell. Playing with `msg_send`, `msg_receive` functions.

### e08_xtimer_advanced

An independent thread is waking up every three seconds and setting a timer with a callback function. When callback function is invoked, it sends an immediate message to the receiver thread. Playing with `msg_receive`, `xtimer_now`, `xtimer_periodic_wakeup`, `xtimer_set`, `xtimer_set_msg` functions.
