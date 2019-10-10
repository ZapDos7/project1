CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=lsh.cpp my_vector.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=lsh

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)