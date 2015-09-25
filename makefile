###############################################################################
#
# File Name         : makefile
# Created By        : Julien Lacombe
# Creation Date     : septembre  1th, 2015
# Last Change       : septembre 10th, 2015 at 11:12:01
# Last Change       : septembre 10th, 2015 at 11:12:01
# Purpose           : It's allow to compile our project easier
#                       - all   : Compile all source presents
#                       - clean : Clean all objects and executable
#
###############################################################################

#### INITIAL PARAMETERS ####
EXECUTABLE=my_printf
SOURCES=$(wildcard *.c)
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
CC=gcc
OBJECTS=$(SOURCES:.c=.o)

#### TARGETS ####
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE)

clean:
	rm $(OBJECTS) $(EXECUTABLE)

