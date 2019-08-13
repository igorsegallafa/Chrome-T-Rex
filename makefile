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
