CC=nvcc
CFLAGS=-c 
LDFLAGS=`pkg-config --libs opencv --cflags opencv`
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC)	$(LDFLAGS)	$(OBJECTS)	-o	$@

.cpp.o:
	$(CC)	$(CFLAGS)	$<	-o 	$@

clean: 
	rm *.o main
