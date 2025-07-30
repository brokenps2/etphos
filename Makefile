SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
TARGET := eax2
C_FILES := $(wildcard $(SRC_DIR)/*.c)
ASM_FILES := $(wildcard $(SRC_DIR)/*.s)
ASM_OBJ := $(patsubst $(SRC_DIR)/%.s, $(OBJ_DIR)/%.o, $(ASM_FILES))
C_OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(C_FILES))
CFLAGS := -std=gnu99 -g -ffreestanding -O2 -Wall -Wextra
LDFLAGS := -ffreestanding -g -O2 -nostdlib

image: $(BIN_DIR)/$(TARGET)
	cp $(BIN_DIR)/$(TARGET) isodir/boot/$(TARGET)
	grub-mkrescue -o $(BIN_DIR)/$(TARGET).iso isodir

$(BIN_DIR)/$(TARGET): $(C_OBJ) $(ASM_OBJ)
	i686-elf-gcc -Tlinker.ld -o $@ $(LDFLAGS) $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	i686-elf-gcc $(CFLAGS) -c -o $@ $< 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	nasm -felf32 -o $@ $<


