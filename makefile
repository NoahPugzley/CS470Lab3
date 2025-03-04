CC = gcc
CFLAGS = -Wall -Wextra -O2

all: rr sjf

rr: RR_inital.c
	$(CC) $(CFLAGS) -o rr RR_inital.c

sjf: SJF_inital.c
	$(CC) $(CFLAGS) -o sjf SJF_inital.c

clean:
	rm -f rr sjf