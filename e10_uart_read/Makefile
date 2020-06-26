# application name
APPLICATION = e10_uart_read

# board
BOARD ?= native

# absolute path of RIOT-OS
RIOTBASE ?= $(CURDIR)/../RIOT

# enable safety checking for development
DEVELHELP ?= 1

# don't show compiler invocation lines:
QUIET ?= 1

# required features
FEATURES_REQUIRED += periph_uart

# application specific cflags
CFLAGS += -DDEBUG_ASSERT_VERBOSE

include $(RIOTBASE)/Makefile.include