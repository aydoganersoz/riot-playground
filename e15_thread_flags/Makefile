# application name
APPLICATION = e15_thread_flags

# board
BOARD ?= native

# absolute path of RIOT-OS
RIOTBASE ?= $(CURDIR)/../RIOT

# enable safety checking for development
DEVELHELP ?= 1

# don't show compiler invocation lines:
QUIET ?= 1

# use module
USEMODULE += xtimer
USEMODULE += core_thread_flags

# required featuresse modules
FEATURES_REQUIRED += periph_gpio
FEATURES_REQUIRED += periph_gpio_irq

# application specific cflags
CFLAGS += -DDEBUG_ASSERT_VERBOSE

include $(RIOTBASE)/Makefile.include