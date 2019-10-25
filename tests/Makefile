# echidna - IEC 61131-3 compiler and virtual machine

LIBS_SUBDIR:= block callback cast echidna grammar ll queue sha256 standard/arithmetic standard/bitstring standard/bitwise standard/comparison standard/numeric standard/select standard/string stats strl tree unit value

.PHONY: $(LIBS_SUBDIR)

CC?= $(CROSS)gcc
AR?= $(CROSS)ar

SRCDIR:= ../src

CFLAGS:= -Wall -g -std=c99
DEFINES:= -D_POSIX_C_SOURCE=200809L
INCLUDE_TEMPLATE:= -I! -I!/include
INCLUDES:= $(subst !,.,$(INCLUDE_TEMPLATE)) \
	$(subst !,$(SRCDIR),$(INCLUDE_TEMPLATE)) 
LIBS:= $(patsubst %,%/libsuite.a,$(LIBS_SUBDIR)) \
	-L$(SRCDIR) $(foreach VAR,echidna ev gcov jansson m protobuf-c pthread,-l$(VAR))

TARGET:= run
OBJS:= main.o munit.o

all: clean $(TARGET)

$(TARGET): munit $(OBJS)
	for SUBDIR in $(LIBS_SUBDIR); do make -C $$SUBDIR ; done
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LIBS)
	test -x ./$@ && ./$@

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -c $<

munit.o: munit munit/munit.o

munit:
	git clone https://github.com/nemequ/munit.git

proper: clean
	rm -fr munit

clean:
	for SUBDIR in $(LIBS_SUBDIR); do make -C $$SUBDIR $@ ; done
	rm -f $(TARGET) core *.o

