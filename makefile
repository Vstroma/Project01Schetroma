

CC = gcc				# compiler gcc


CFLAGS = -Wall -Werror			## flags for compiler		

SOURCES = MypsSchetroma.c readproc.c CPUInfo.c MemInfo.c
HEADERS = flag.h
EXECUTABLE = MypsSchetroma


OBJECTS = $(SOURCES:.c=.o)

all: $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS)					# compile sources files into executable
	$(CC) $(CFLAGS) -o $@ $^


%.o: %.c $(HEADERS)							# compiles sources into object
	$(CC) $(CFLAGS) -c -o $@ $<


clean:								# clean
	rm -f $(EXECUTABLE) $(OBJECTS)