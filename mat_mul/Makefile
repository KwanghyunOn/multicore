TARGET=main
OBJECTS=util.o mat_mul.o

CFLAGS=-std=c99 -O3 -Wall
LDFLAGS=-lm -pthread

all: $(TARGET)

$(TARGET): $(OBJECTS)

clean:
	rm -rf $(TARGET) $(OBJECTS)

run: $(TARGET)
	./$(TARGET)
