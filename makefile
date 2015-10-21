CC=gcc
CFLAGS=-c -Wall -O2 `pkg-config --cflags cairo`
LDFLAGS=-lm -export-dynamic `pkg-config --libs cairo`
HEADERS=$(wildcard *.h)
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
TARGET=percolation


all: $(SOURCES) $(TARGET)
	
$(TARGET): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) 

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -rf *.o
