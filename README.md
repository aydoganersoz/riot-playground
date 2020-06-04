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
