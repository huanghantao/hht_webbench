CC = gcc
TARGET = hht_webbench
DIRS = $(shell find . -maxdepth 3 -type d)
VPATH = $(DIRS)
C_FILES_PATH = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))
C_FILES = $(notdir $(C_FILES_PATH))
OBJS = $(patsubst %.c, obj/%.o, $(C_FILES))

$(TARGET):$(OBJS)
	-rm -f $@
	$(CC) -o $(TARGET) $(OBJS) -g

obj/%.o:%.c
	$(CC) -c -o $@ $< -g

.PHONY:clean
clean:
	-rm -f $(TARGET)
	-rm -f obj/*.o
	-rm -f core.*