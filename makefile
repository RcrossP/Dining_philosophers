#Editor rcrossp
#Date	20180503

TARGET = Dining_philosophers
SRC_DIR = ./
INC_DIR = ./

CC     = gcc
CFLAGE = -Wall -pthread
SRC    = $(wildcard $(SRC_DIR)*.c)
OBJ    = $(SRC:%.c=%.o)
DEP    = $(SRC:%.c=%.d)

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGE) $^ -o $@

-include $(DEP)

%.o :%.c
	$(CC) $(CFLAGES) -MMD -c $< -o $@

.PHONY: clean
clean :
	rm -f $(TARGET) $(OBJ) $(DEP)
