CC = gcc -Wall
CP = cp
RM = rm -f
srcdir = ./src/
bindir = ./bin/
docdir = ./doc/
savedir = ./save/
SRC = $(wildcard $(srcdir)*.c)
HEAD = $(wildcard $(srcdir)*.h)
OBJ = $(subst $(srcdir), $(bindir),$(SRC:.c=.o))
PROG = test

all : $(PROG)

$(PROG) : $(OBJ)
	$(CC) $^ -o $@ -lm
$(bindir)%.o : $(srcdir)%.c
	$(CC) -c $^ -o $@

.PHONY : save
save :
	$(CP) $(SRC) $(savedir)
	$(CP) $(HEAD) $(savedir)
.PHONY : doc
doc:
	doxygen -g
clean :
	$(RM) $(OBJ)
dir :
	mkdir src
	mkdir bin
	mkdir doc
	mkdir save

docf :
	doxygen Doxyfile
	mv html ./doc/
	mv latex ./doc/
	mv Doxyfile ./doc/
