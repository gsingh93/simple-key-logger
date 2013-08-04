CC := gcc
CFLAGS := -g -Wall
BIN_NAME := skeylogger
OBJS := skeylogger.o key_util.o options.o config.o

all: $(BIN_NAME)

$(BIN_NAME): $(OBJS)
	gcc $(CFLAGS) $(OBJS) -o $(BIN_NAME)

clean:
	rm -f *.o $(BIN_NAME)
