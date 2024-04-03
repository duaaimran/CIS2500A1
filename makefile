imranDuaaA1: imranDuaaA1.o imranDuaaA1Main.o
	gcc imranDuaaA1.o imranDuaaA1Main.c -o imranDuaaA1 -lm
imranDuaaA1.o: imranDuaaA1.c givenA1.h
	gcc -Wall -std=c99 -c imranDuaaA1.c -lm
imranDuaaA1Main.o: imranDuaaA1Main.c givenA1.h
	gcc -Wall -std=c99 -c imranDuaaA1Main.c -lm
clean:
	rm *.o imranDuaaA1
