# application name
APPLICATION = e17_semaphore

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
USEMODULE += sema

# application specific cflags
CFLAGS += -DDEBUG_ASSERT_VERBOSE

include $(RIOTBASE)/Makefile.include