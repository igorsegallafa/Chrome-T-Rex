# ========================================================
# >> UFPR 2017 - João Vitor Moreira  - GRR20171621     <<
# >> UFPR 2017 - Igor Segalla Farias - GRR20176543     <<
# ========================================================

CFLAGS = -Wall

LDLIBS = $(OBJETOS) -lncurses

BIBLIOTECAS = Globals.h $(addsuffix .h,$(GAMEFILES))

GAMEFILES = Game		\
			World		\
			Render		\
			Menu		\
			Help		\
			Ranking

#Arquivos .o
OBJETOS = $(addsuffix .o,$(GAMEFILES))

.PHONY : all clean

all: Main

Main: Main.o

Main.o: $(OBJETOS)

$(OBJETOS): $(BIBLIOTECAS)

clean:
	-rm -f $(OBJETOS) Main.o

purge: clean
	-rm -f Main
