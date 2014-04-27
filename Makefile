CC = gcc
CFLAGS = -ansi -Wall -O2 -m32 -fno-builtin -fno-stack-protector -I$(INC_DIR)
LD = ld
LDFLAGS = -m elf_i386 -T $(LDSCRIPT)
LDSCRIPT = link.ld
AS = nasm
ASFLAGS = -f elf32

C_DIR = src
ASM_DIR = asm
OBJ_DIR = obj
INC_DIR = ./include

C_SRC = $(wildcard $(C_DIR)/*.c)
ASM_SRC = $(wildcard $(ASM_DIR)/*.asm)
C_OBJ = $(C_SRC:$(C_DIR)/%.c=$(OBJ_DIR)/%.o)
ASM_OBJ = $(ASM_SRC:$(ASM_DIR)/%.asm=$(OBJ_DIR)/%.o)
OBJ = $(C_OBJ) $(ASM_OBJ)
EXEC = kernel

.PHONY: all
all: $(EXEC)

$(EXEC): $(OBJ)
	$(LD) $(OBJ) $(LIBS) $(LDFLAGS) -o $@
	
$(OBJ_DIR)/%.o: $(C_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJ_DIR)/%.o: $(ASM_DIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@
	
.PHONY: clean
clean:
	-rm -f $(EXEC) $(OBJ_DIR)/*.o

.PHONY: print
print:
	@echo ASM src: $(ASM_SRC)
	@echo C src: $(C_SRC)
	@echo Obj: $(OBJ)
	@echo Exec: $(EXEC)
