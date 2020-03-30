
# This makefile builds two binaries - libclog.so and clog_ctl

CC = gcc
RM = rm -f

LIB_CFLAGS = -fPIC -Wall -I./inc
LDFLAGS = -shared
LIB_SRCS = clog.c clog_utils.c
LIB_OBJS = $(LIB_SRCS:.c=.o)

TARGET_LIB = libclog.so
TARGET_BIN = clog_ctl
EXT_LIB = -lrt
BUILD_DIR = ./build

vpath %.c ./src
vpath %.h ./inc

BIN_CFLAGS = -Wall -I./inc
BIN_SRCS = clog_ctl.c
BIN_OBJS = $(BIN_SRCS:.c=.o)

.PHONY: clean

all: ${TARGET_LIB} ${TARGET_BIN}

$(TARGET_LIB): $(LIB_OBJS)
	@$(CC) ${LDFLAGS} -o $@ $^ $(EXT_LIB)
	@echo " LD $@"

$(LIB_OBJS): $(LIB_SRCS)
	@$(CC) $(LIB_CFLAGS) -c $^
	@echo " CC $^"

$(TARGET_BIN): $(BIN_OBJS)
	@$(CC) -o $@ $^ $(EXT_LIB)
	@echo " LD $@"

$(BIN_OBJS): $(BIN_SRCS)
	@$(CC) $(BIN_CFLAGS) -c $^
	@echo " CC $^"

clean:
	@${RM} ${TARGET_LIB} ${LIB_OBJS}
	@${RM} ${TARGET_BIN} ${BIN_OBJS}
	@echo " RM ${TARGET_LIB} ${LIB_OBJS} ${TARGET_BIN} ${BIN_OBJS}"
