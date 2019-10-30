# echidna - IEC 61131-3 Virtual Machine

.PHONY:

CC?= $(CROSS)gcc

GIT_VERSION:= $(shell git --no-pager describe --tags --always --dirty)
TIMESTAMP:= $(shell date +'%Y%m%d')

CFLAGS:= -Wall -g -std=c99 -fPIC
DEFINES+= $(foreach VAR,GIT_VERSION TIMESTAMP,-D$(VAR)="$($(VAR))") -D_POSIX_C_SOURCE=200809L
INCLUDES:= -I.. -I../include

OBJS:= arithmetic.o bistable.o bitstring.o bitwise.o comparison.o counters.o edge.o numeric.o rtc.o select.o string.o timers.o type.o

all: clean $(OBJS)

.c.o:
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

clean:
	rm -f core *.o *.gcda *.gcno

