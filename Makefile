CC := gcc
CFLAGS := -O2
BIN_NAME := keylogger

all: $(BIN_NAME)

$(BIN_NAME): keylogger.o key_util.o
	gcc $(CFLAGS) keylogger.o key_util.o -o $(BIN_NAME)

clean:
	rm *.o $(BIN_NAME)
