ifneq ($(V), 1)
MAKEFLAGS += --no-print-dir
Q := @
endif

OPT_FLAGS = -O0 -g

CFLAGS += -Wall -Wextra -Werror -Wno-char-subscripts\
	$(OPT_FLAGS) -std=gnu99 -g3 -MD \
	-I.
LDFLAGS += $(OPT_FLAGS)

SRC =			\
	fake6502.c	\
	acia6850.c	\
	cdcacm.c	\
	main.c		\

ROM = ../osi_bas/ROM.HEX

CROSS_COMPILE ?= arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
OBJCOPY = $(CROSS_COMPILE)objcopy

CFLAGS += -mcpu=cortex-m3 -mthumb \
	-DSTM32F1 -DDISCOVERY_STLINK -I../libopencm3/include \
	-I .
LDFLAGS_BOOT := $(LDFLAGS) --specs=nano.specs \
	-lopencm3_stm32f1 -Wl,--defsym,_stack=0x20005000 \
	-Wl,-T,bluepill.ld -nostartfiles -lc \
	-Wl,-Map=mapfile -mthumb -mcpu=cortex-m3 -Wl,-gc-sections \
	-L../libopencm3/lib
LDFLAGS = $(LDFLAGS_BOOT)

LDFLAGS += --specs=nosys.specs

all:	pill_6502.bin

host_clean:
	-$(Q)$(RM) pill_6502.bin

OBJ = $(SRC:.c=.o)
OBJ += $(ROM:.HEX=.o)

pill_6502.elf: version.h $(OBJ)
	@echo "  LD      $@"
	$(Q)$(CC) -o $@ $(OBJ) $(LDFLAGS)

%.o:	%.c
	@echo "  CC      $<"
	$(Q)$(CC) $(CFLAGS) -c $< -o $@

%.o:	%.HEX
	@echo "  OBJCOPY $@.bin"
	$(Q)$(OBJCOPY) -I ihex -O binary $^ $@.bin
	@echo "  OBJCOPY $@"
	$(Q)$(OBJCOPY) -I binary -O elf32-littlearm -B arm --rename-section .data=.rodata,alloc,load,readonly,data,contents $@.bin $@

%.bin:	%.elf
	@echo "  OBJCOPY $@"
	$(Q)$(OBJCOPY) -O binary $^ $@

.PHONY:	clean host_clean FORCE

clean:	host_clean
	$(Q)echo "  CLEAN"
	-$(Q)$(RM) -f *.o *.d *~ *.elf *.bin $(HOSTFILES)
	-$(Q)$(RM) -f mapfile version.h

version.h: FORCE
	$(Q)echo "  GIT     version.h"
	$(Q)echo "#define FIRMWARE_VERSION \"`git describe --always --dirty`\"" > $@

-include *.d
