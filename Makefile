#
# Makefile for the Emphatic FUSE daemon.
#
# Author: Matthew Signorini
#


COMMON_SRC = huffman.c heap.c node.c utils.c alphabet.c
COMMON_OBJS = $(COMMON_SRC:%.c=%.o)

ALL_SRC = $(COMMON_SRC) squash.c puff.c
ALL_OBJS = $(COMMON_OBJS) squash.o puff.o

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -O0 -g


all:		squash puff tags

squash:	$(COMMON_OBJS) squash.o
	$(CC) $(CFLAGS) -o squash $(COMMON_OBJS) squash.o

puff:	$(COMMON_OBJS) puff.o
	$(CC) $(CFLAGS) -o puff $(COMMON_OBJS) puff.o

compile:	$(ALL_OBJS)

clean:
	/bin/rm $(ALL_OBJS)

scrub:		clean
	/bin/rm squash puff

# Use cscope to build a tags database. If you do not have cscope installed
# at your site, you may wish to change this to invoke ctags instead.
tags:		$(ALL_SRC)
	cscope -b

# Use gcc to figure out what header files each source file depends on. The
# list of dependencies is then included in the Makefile, to ensure that
# if a header file is modified, the appropriate source files are 
# recompiled.
Depend:		$(ALL_SRC)
	gcc $(CFLAGS) -MM $(ALL_SRC) > Depend

.PHONY:		all clean scrub tags compile


include Depend

# vim: ts=8 sw=4 noet
