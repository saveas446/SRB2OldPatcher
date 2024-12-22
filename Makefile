# Compiler
CC = gcc

# Compiler flags
CFLAGS = -g -O2

# Linker flags
LDFLAGS =

# Source directory
SRC_DIR = src

# Object directory
OBJ_DIR = obj

# Binary directory
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Output executable
TARGET = $(BIN_DIR)/SRB2Patcher.exe

# Build target
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile .c files to .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean target
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

run:
	$(TARGET)