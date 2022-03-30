executable = gpio
source = gpio.c

CC = gcc
LDFLAGS = -lpthread

all: $(executable)

$(executable): $(source)
	$(CC) -o $(executable) $(source) $(LDFLAGS)

clean:
	rm -rf gpio
