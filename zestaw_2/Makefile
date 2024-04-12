OBJS	= przeciecie_multizbiorow.o rownosc_multizbiorow.o roznica_multizbiorow.o roznica_symetryczna_multizbiorow.o sprawdzanie_podzbiorow.o suma_multizbiorow.o testy.o zestaw_2.o
SOURCE	= przeciecie_multizbiorow.c rownosc_multizbiorow.c roznica_multizbiorow.c roznica_symetryczna_multizbiorow.c sprawdzanie_podzbiorow.c suma_multizbiorow.c testy.c zestaw_2.c
HEADER	= plik_naglowkowy.h
OUT	= wynik
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 =

.PHONY: all clean test check

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

przeciecie_multizbiorow.o: przeciecie_multizbiorow.c
	$(CC) $(FLAGS) przeciecie_multizbiorow.c

rownosc_multizbiorow.o: rownosc_multizbiorow.c
	$(CC) $(FLAGS) rownosc_multizbiorow.c

roznica_multizbiorow.o: roznica_multizbiorow.c
	$(CC) $(FLAGS) roznica_multizbiorow.c

roznica_symetryczna_multizbiorow.o: roznica_symetryczna_multizbiorow.c
	$(CC) $(FLAGS) roznica_symetryczna_multizbiorow.c

sprawdzanie_podzbiorow.o: sprawdzanie_podzbiorow.c
	$(CC) $(FLAGS) sprawdzanie_podzbiorow.c

suma_multizbiorow.o: suma_multizbiorow.c
	$(CC) $(FLAGS) suma_multizbiorow.c

testy.o: testy.c
	$(CC) $(FLAGS) testy.c

zestaw_2.o: zestaw_2.c
	$(CC) $(FLAGS) zestaw_2.c


clean:
	del /q $(OBJS) $(OUT)
	del /Q $(OBJS) $(OUT) wynik.exe

test: testy.o $(OUT)
	./$(OUT)

check: $(OUT)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)
	@echo "Checking memory usage with valgrind..."
	@valgrind ./$(OUT)



