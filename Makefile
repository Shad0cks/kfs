NAME=kfs
CC=gcc
LD=ld

CP := cp
RM := rm -rf
MKDIR := mkdir -pv

BIN = kernel
CFG = grub.cfg
ISO_PATH := iso

BOOT_PATH := $(ISO_PATH)/boot
GRUB_PATH := $(BOOT_PATH)/grub

CFLAGS= \
-nostdlib \
-fno-builtin \
-fno-exceptions \
-fno-stack-protector \
-nodefaultlibs \
-m32

SOURCES_FILES	=	kernel.c \
					keyboard.c \
					utils.c	\
					ports.c \
					gdt.c

HEADERS			=	inc/kernel.h \
					inc/gdt.h

SOURCES_DIR		=	src


SOURCES			=	$(addprefix $(SOURCES_DIR)/, $(SOURCES_FILES))

OBJECTS			= 	$(SOURCES:.c=.o)

$(SOURCES_DIR)/%.o: $(SOURCES_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all

all: 	bootloader kernel linker iso
		@echo Make has completed.

bootloader:		boot.asm
				nasm -f elf32 boot.asm -o boot.o

kernel: $(OBJECTS)

linker: linker.ld boot.o $(OBJECTS)
		${LD} -m elf_i386 -T linker.ld -o kernel boot.o $(OBJECTS)

iso: kernel
	$(MKDIR) $(GRUB_PATH)
	$(CP) $(BIN) $(BOOT_PATH)
	$(CP) $(CFG) $(GRUB_PATH)
	grub-file --is-x86-multiboot $(BOOT_PATH)/$(BIN)
	grub-mkrescue -o ${NAME}.iso $(ISO_PATH)

.PHONY: fclean

fclean:
	$(RM) src/*.o *.o $(BIN) *iso $(ISO_PATH)

re:				fclean all