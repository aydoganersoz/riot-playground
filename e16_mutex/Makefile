# application name
APPLICATION = e16_mutex

# board
BOARD ?= native

# absolute path of RIOT-OS
RIOTBASE ?= $(CURDIR)/../RIOT

# enable safety checking for development
DEVELHELP ?= 1

# don't show compiler invocation lines:
QUIET ?= 1

# use xtimer module
USEMODULE += xtimer

# required features
FEATURES_REQUIRED += periph_gpio
FEATURES_REQUIRED += periph_gpio_irq

include $(RIOTBASE)/Makefile.include