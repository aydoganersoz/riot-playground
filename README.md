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

Hello world application. Playing with `printf`.

### e02_thread_pingpong

One thread is sending a message to another one every one second. Playing with `thread_create`, `msg_receive`, `msg_send`, `xtimer_sleep`.

### e03_new_shell_command

Defining a new shell command. Playing with `shell_run`.

### e04_toggle_led

Toggling a LED. Playing with `LED*_<state>`.

### e05_hts221_sensor

Reading temperature and humidity values from HTS221 sensor. Playing with `hts221_*`.

### e06_thread_concurrency

Writing to and reading from a mutual buffer using mutex. Playing with `mutex_lock`, `mutex_unlock`, `xtimer_usleep`, `xtimer_now`.

### e07_thread_ipc

A blocking receive call in a thread is waiting for a message from the shell. Playing with `msg_send`, `msg_receive`.

### e08_xtimer_advanced

An independent thread is waking up every three seconds and setting a timer which is associated with a callback function. When callback function is invoked, it sends an immediate message to the receiver thread. Playing with `msg_receive`, `xtimer_now`, `xtimer_periodic_wakeup`, `xtimer_set`, `xtimer_set_msg`.

### e09_exti_interrupt

Button press event is detected by an EXTI interrupt. When callback function is invoked, it sends an immediate message to a receiver thread to blink a LED. Playing with `gpio_init`, `gpio_init_int`, `msg_send_int`, `gpio_cb_t`, `LED*_<state>`.

### e10_uart_read

Characters are read by a UART receive interrupt. When callback function is invoked, it sends an immediate message to a receiver thread to print the characters read. Playing with `uart_init`, `msg_init_queue`, `msg_send_int`, `uart_rx_cb_t`, `DEBUG_ASSERT_VERBOSE`.

### e11_rtc_alarm

An RTC alarm is set every five seconds. When callback function of the RTC alarm interupt is invoked, it sends an immediate message to a receiver thread to toggle a LED for one second. Playing with `rtc_set_alarm`, `rtc_alarm_cb_t`, `rtc_get_time`, `rtc_tm_normalize`, `rtc_poweron`, `rtc_init`.

### e12_thread_sleep_wakeup

An EXTI interrupt is waking up a sleeping thread. Playing with `thread_sleep`, `thread_wakeup`, `msg_send_int`, `msg_try_receive`.

### e13_thread_yield

Two same priority threads yield in the middle of their loop. Playing with `thread_yield`.
