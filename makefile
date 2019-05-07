CFLAGS  = -Wall

#------------------------------------------------------------------------------
.PHONY : all clean

#------------------------------------------------------------------------------
all : pokemon

pokemon :
	gcc $(CFLAGS) main.c pokemon.c batalha.c mapa.c -o pokemon

#------------------------------------------------------------------------------
clean :
	$(RM) pokemon

rebuild: clean all