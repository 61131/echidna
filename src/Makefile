# echidna - IEC 61131-3 Virtual Machine

SUBDIRS:= bytecode hardware operator protobuf runtime standard

.PHONY: $(SUBDIRS)

CC ?= $(CROSS)gcc
AR ?= $(CROSS)ar
STRIP ?= $(CROSS)strip

GIT_VERSION := $(shell git --no-pager describe --tags --always --dirty)
TIMESTAMP := $(shell date +'%Y%m%d')

CFLAGS := -Wall -g -std=c99 -fPIC
DEFINES += $(foreach VAR,GIT_VERSION TIMESTAMP,-D$(VAR)="$($(VAR))") -D_POSIX_C_SOURCE=200809L
INCLUDES := -I. -Iinclude
LIBS := $(foreach VAR,ev jansson m protobuf-c pthread,-l$(VAR))

TARGET := echidna
LIBRARY := libechidna.a

OBJS:= grammar.o lexer.o block.o bytecode.o bytecode/generate.o bytecode/label.o bytecode/stack.o cast.o config.o echidna.o file.o frame.o function.o hex.o json.o ll.o log.o operator/arithmetic.o operator/boolean.o operator/call.o operator/comparison.o operator/inputs.o operator/jump.o operator/logical.o operator/operand.o operator/parameter.o operator/return.o parameter.o parse.o protobuf/config.o protobuf/file.o protobuf/pou.o protobuf/symbol.o protobuf/value.o queue.o runtime.o runtime/bytecode.o runtime/call.o runtime/context.o runtime/error.o runtime/function.o runtime/parameter.o runtime/task.o sha256.o standard.o standard/arithmetic.o standard/bistable.o standard/bitstring.o standard/bitwise.o standard/comparison.o standard/counters.o standard/edge.o standard/numeric.o standard/select.o standard/string.o standard/timers.o standard/type.o stats.o strl.o symbol.o token.o tree.o unit.o value.o

# TODO: Change $(LIBRARY) to test?!

ifneq ($(filter $(LIBRARY),$(MAKECMDGOALS)),)
CFLAGS += -fprofile-arcs -ftest-coverage -DNDEBUG
endif

all: clean grammar.o $(SUBDIRS) $(TARGET)

$(TARGET): $(OBJS) main.o
	$(CC) $(CFLAGS) $(DEFINES) $^ -o $@ $(LIBS)

$(LIBRARY): clean $(OBJS)
	$(AR) rcs $@ $(OBJS)

.c.o:
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

grammar.c: grammar.y
	bison -Wall -t -v $^ -o $@ 2>&1
	#bison -Wall $^ -o $@ 2>&1

grammar.o: grammar.c
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -c $< 

lexer.c: lexer.l
	flex -o $@ $^

bytecode:
	make -C $@

hardware:
	make -C $@

operator:
	make -C $@

protobuf:
	make -C $@

runtime:
	make -C $@

standard:
	make -C $@

link:
	$(CC) $(CFLAGS) $(DEFINES) $^ -o $@ $(LIBS)

clean:
	for SUBDIR in $(SUBDIRS); do make -C $$SUBDIR $@ ; done
	rm -f grammar.c grammar.h grammar.log grammar.output lexer.c *.o *.gcda *.gcno *.gcov
	rm -f $(TARGET) $(LIBRARY) core

