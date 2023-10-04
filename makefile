
CC = gcc

CFLAGS = -Wall -Werror

TARGET = readproc
SOURCES = readproc.c MemInfo.c CPUInfo.c flag.C
OBJECTS = $(SOURCES: .c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS)	-o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

