# Compiler
CCC = g++

# Objectfiles
OBJS = tetris.o gamemotor.o graphics.o toplist.o

# Name of program
BIN = tetris

# Flags
FLAGS = -lallegro -lallegro_color -lallegro_primitives -lallegro_ttf -lallegro_font -g

# How to compile
.cc.o:
	$(CCC) -c $(FLAGS) -o $@ $<

# Linking objectfiles
$(BIN): $(OBJS)
	$(CCC) $(OBJS) $(FLAGS) -o $(BIN)


# Objectfiles' dependencies
tetris.o: tetris.cc tetris.hh graphics.hh gamemotor.hh toplist.hh
gamemotor.o: gamemotor.hh graphics.hh toplist.hh
graphics.o: graphics.hh toplist.hh
toplist.o: toplist.hh

# Cleaning
clean:
	rm -f $(BIN) $(OBJS) *~ core
