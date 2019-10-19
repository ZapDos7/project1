CC=g++  -std=c++11
CFLAGS=-c -Wall -Ofast
LDFLAGS=
SOURCES=lsh.cpp my_vector.cpp NNpair.cpp h_funs.cpp g_funs.cpp ht.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=lsh

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

run:
	./$(EXECUTABLE) -d ../sample_datasets/1_vectors/siftsmall/input_small_id_n -q ../sample_datasets/1_vectors/siftsmall/query_small_id_n -k 4 -L 5 -o ../outputfile

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
