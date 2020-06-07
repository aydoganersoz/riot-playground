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

One thread is sending a message to another one every 1 second. Playing with `thread_create`, `msg_receive`, `msg_send`, `xtimer_sleep`.

### e03_new_shell_command

New (custom) shell command. Playing with `shell_run`.
