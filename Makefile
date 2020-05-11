EXEC=testjson.exe
SOURCES=main.c json.c
OBJECTS=$(SOURCES:.c=.o)
CC=gcc
CFLAGS=-W -Wall
 
.PHONY: default clean
 
default: $(EXEC)
 
json.o: json.c json.h
main.o: main.c json.h
 
%.o: %.c
		$(CC) -o $@ -c $< $(CFLAGS)

$(EXEC): $(OBJECTS)
		$(CC) -o $@ $^

clean:
	rm -rf $(EXEC) $(OBJECTS) $(SOURCES:.c=.c~) $(SOURCES:.c=.h~) Makefile~