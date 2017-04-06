# Name: Mark Redekopp
# email: redekopp@usc.edu

CC = compile
CFLAGS = -g -Wall
LDFLAGS =
SRCS =  character.cpp test_ocr.cpp bmplib.cpp
OBJ = $(SRCS:.cpp=.o)


all: test_ocr

test_ocr: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o test_ocr

#test_bbox: test_bbox.o
#	$(CC) $(CFLAGS) test_bbox.cpp bmplib.cpp -o test_bbox

.cpp.o:
	$(CC) $(CFLAGS) -c $<

character.o test_ocr.o : character.h bmplib.h

clean:
	rm -f *.o test_ocr test_bbox *~

tarit:
	tar cvf ocr.tar ocr1.bmp ocr2.bmp ocr3.bmp ocr4.bmp test_ocr.cpp character.h bmplib.h bmplib.cpp point.h Makefile
