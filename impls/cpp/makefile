# Makefile for the extractor program

OBJS = main.o HTMLReader/LiteHTMLAttributes.o HTMLReader/LiteHTMLEntityResolver.o HTMLReader/LiteHTMLReader.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

extractor: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o extractor

main.o: main.cpp HTMLReader/LiteHTMLReader.h
	$(CC) $(CFLAGS) main.cpp

HTMLReader/LiteHTMLAttributes.o: HTMLReader/LiteHTMLAttributes.cpp HTMLReader/LiteHTMLAttributes.h
	$(CC) $(CFLAGS) HTMLReader/LiteHTMLAttributes.cpp

HTMLReader/LiteHTMLEntityResolver.o: HTMLReader/LiteHTMLEntityResolver.cpp HTMLReader/LiteHTMLEntityResolver.h
	$(CC) $(CFLAGS) HTMLReader/LiteHTMLEntityResolver.cpp

HTMLReader/LiteHTMLReader.o: HTMLReader/LiteHTMLReader.cpp HTMLReader/LiteHTMLReader.h HTMLReader/LiteHTMLEntityResolver.h HTMLReader/LiteHTMLTag.h
	$(CC) $(CFLAGS) HTMLReader/LiteHTMLReader.cpp

clean:
	\rm *.o extractor
	\rm HTMLReader/*.o