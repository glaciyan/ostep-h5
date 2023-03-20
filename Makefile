CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=$(STD)
CPPCHECK = cppcheck --enable=warning,style --std=$(STD)
STD = c11

TARGETS = h5-1 h5-2 h5-3 h5-4 h5-5 h5-6 h5-7 h5-8
SOURCES = $(TARGETS:=.c)

.PHONY: all cppcheck clean

all: $(TARGETS)

cppcheck: $(SOURCES)
	$(CPPCHECK) $(SOURCES)

clean:
	$(RM) $(TARGETS) h5-2.txt