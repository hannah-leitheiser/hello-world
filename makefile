# https://www.gnu.org/software/make/manual/html_node/Makefile-Contents.html
# https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
# https://stackoverflow.com/questions/7751342/how-to-execute-make-file
# https://stackoverflow.com/questions/3707517/make-file-echo-displaying-path-string

# https://www.gnu.org/software/make/manual/html_node/Echoing.html

IDIR =./
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = hello_world.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = hello_world.o command_line_args.o gettext.o messages.o debug_log.o printf.o word_wrap.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)



# https://stackoverflow.com/questions/16931770/makefile4-missing-separator-stop
hello_world: $(OBJ)
	@echo "Compiling Hello World."
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
