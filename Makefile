CC=g++  -std=c++11
CFLAGS=-c -Wall -Ofast
LDFLAGS=
SOURCES=lsh.cpp my_vector.cpp NNpair.cpp h_funs.cpp g_funs.cpp ht.cpp
SOURCESCUBE = cube.cpp my_vector.cpp h_funs.cpp g_funs.cpp cube_ht.cpp NNpair.cpp
SOURCESCURVEGRIDHPR = curve_grid_hypercube.cpp curve.cpp curve_point.cpp grid.cpp my_vector.cpp
SOURCESCURVEGRIDLSH = curve_grid_lsh.cpp curve_point.cpp curve.cpp grid.cpp my_vector.cpp NNpair.cpp
SOURCESCURVEPRJHPR = curve_projection_hypercube.cpp curve.cpp curve_point.cpp grid.cpp my_vector.cpp
SOURCESCURVEPRJLSH = curve_projection_lsh.cpp curve.cpp curve_point.cpp grid.cpp my_vector.cpp
OBJECTS=$(SOURCES:.cpp=.o)
OBJECTSCUBE=$(SOURCESCUBE:.cpp=.o)
OBJECTSCURVEGRIDHPR=$(SOURCESCURVEGRIDHPR:.cpp=.o)
OBJECTSCURVEGRIDLSH=$(SOURCESCURVEGRIDLSH:.cpp=.o)
OBJECTSCURVEPRJHPR=$(SOURCESCURVEPRJHPR:.cpp=.o)
OBJECTSCURVEPRJLSH=$(SOURCESCURVEPRJLSH:.cpp=.o)
EXECUTABLE=lsh
EXECUTABLECUBE=cube
EXECUTABLECURVEGRIDHPR=curve_grid_hypercube
EXECUTABLECURVEGRIDLSH=curve_grid_lsh
EXECUTABLECURVEPRJHPR=curve_projection_hypercube
EXECUTABLECURVEPRJLSH=curve_projection_lsh

#VECTORS
#LSH
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

#hypercube
a1:	$(SOURCESCUBE) $(EXECUTABLECUBE)

$(EXECUTABLECUBE): $(OBJECTSCUBE)
	$(CC) $(LDFLAGS) $(OBJECTSCUBE) -o $@

#CURVES
#grid-hypercube
a2: $(SOURCESCURVEGRIDHPR) $(EXECUTABLECURVEGRIDHPR)

$(EXECUTABLECURVEGRIDHPR): $(OBJECTSCURVEGRIDHPR)
	$(CC) $(LDFLAGS) $(OBJECTSCURVEGRIDHPR) -o $@

#grid-lsh
a3: $(SOURCESCURVEGRIDLSH) $(EXECUTABLECURVEGRIDLSH)

$(EXECUTABLECURVEGRIDLSH): $(OBJECTSCURVEGRIDLSH)
	$(CC) $(LDFLAGS) $(OBJECTSCURVEGRIDLSH) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

#run:
#	./$(EXECUTABLE) -d /home/ioanna/Desktop/sample_datasets/a_vectors/siftsmall/input_small_id_n -q /home/ioanna/Desktop/sample_datasets/a_vectors/XS/query_xs -k 4 -L 3 -o /home/ioanna/Desktop/outputfile.txt

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(OBJECTSCUBE) $(EXECUTABLECUBE) $(OBJECTSCURVEGRIDHPR) $(EXECUTABLECURVEGRIDHPR) $(OBJECTSCURVEGRIDLSH) $(EXECUTABLECURVEGRIDLSH) $(OBJECTSCURVEPRJHPR) $(EXECUTABLECURVEPRJHPR) $(OBJECTSCURVEPRJLSH) $(EXECUTABLECURVEPRJLSH)
