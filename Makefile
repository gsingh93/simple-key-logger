all: keylogger.o key_util.o
	gcc keylogger.o key_util.o -o keylogger
