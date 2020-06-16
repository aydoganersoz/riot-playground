# application name
APPLICATION = e11_rtc_alarm

# board
BOARD ?= native

# absolute path of RIOT-OS
RIOTBASE ?= $(CURDIR)/../RIOT

# enable safety checking for development
DEVELHELP ?= 1

# don't show compiler invocation lines:
QUIET ?= 1

# use modules
USEMODULE += xtimer

# required features
FEATURES_REQUIRED += periph_rtc
FEATURES_REQUIRED += periph_gpio

# application specific cflags
CFLAGS += -DDEBUG_ASSERT_VERBOSE

include $(RIOTBASE)/Makefile.include