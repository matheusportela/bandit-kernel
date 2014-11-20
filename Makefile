# Cross-compiler
CC = i686-elf-gcc
LD = i686-elf-ld
AS = nasm
#AS = i686-elf-ar

# C building settings
CFLAGS = -O2 -ansi
CFLAGS += -finline-functions -ffreestanding
CFLAGS += -Wall -Wextra -Wno-unused-function -Wno-unused-parameter
CFLAGS += -pedantic -fno-omit-frame-pointer
CFLAGS = -ansi -Wall -O2 -m32 -fno-builtin -fno-stack-protector -I$(INC_DIR)

# Linker settings
LDFLAGS = -m elf_i386 -T $(LDSCRIPT)
LDSCRIPT = link.ld

# Assembler settings
ASFLAGS = -f elf

# C source and object files
C_DIR = src
C_SRC = $(wildcard $(C_DIR)/*.c)
C_OBJ = $(C_SRC:$(C_DIR)/%.c=$(OBJ_DIR)/%.o)

# Assembly source and object files
ASM_DIR = asm
ASM_SRC = $(wildcard $(ASM_DIR)/*.asm)
ASM_OBJ = $(ASM_SRC:$(ASM_DIR)/%.asm=$(OBJ_DIR)/%-asm.o)

# Object files directory
OBJ_DIR = obj

# Header source files
INC_DIR = ./include
HEADERS_SRC = $(wildcard $(INC_DIR)/*.h)

# All object files
OBJ = $(ASM_OBJ) $(C_OBJ)

# Executable kernel file
EXEC = kernel

.PHONY: all
all: $(EXEC)

$(EXEC): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $(OBJ)
	
$(OBJ_DIR)/%.o: $(C_DIR)/%.c ${HEADERS_SRC}
	$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJ_DIR)/%-asm.o: $(ASM_DIR)/%.asm
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
