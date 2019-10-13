# echidna - IEC 61131-3 compiler and virtual machine

CC?= $(CROSS)gcc
AR?= $(CROSS)ar

SRCDIR:= ../../../src

CFLAGS:= -Wall -g -std=c99
DEFINES:= -D_POSIX_C_SOURCE=200809L
INCLUDE_TEMPLATE:= -I! -I!/include
INCLUDES:= $(subst !,.,$(INCLUDE_TEMPLATE)) \
	$(subst !,../..,$(INCLUDE_TEMPLATE)) \
	$(subst !,$(SRCDIR),$(INCLUDE_TEMPLATE)) 

TARGET:= libsuite.a
OBJS:= abs.o cosine.o sine.o sqrt.o tangent.o tests.o suite.o

all: clean $(TARGET)

$(TARGET): $(OBJS)
	$(AR) rcs $@ $^

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -c $<

clean:
	rm -f $(TARGET) core *.o

