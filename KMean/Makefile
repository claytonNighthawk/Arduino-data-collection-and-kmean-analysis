CC = g++
CFLAGS = -g -std=c++11
KMEAN_OBJECTS = centroid.o point.o kmean.o


%.o: %.cpp
	$(CC) -c $(CFLAGS) $<

test: $(KMEAN_OBJECTS)
	$(CC) -o $@ test.cpp $$(KMEAN_OBJECTS)

main: $(KMEAN_OBJECTS)
	$(CC) -o $@ main.cpp $(KMEAN_OBJECTS)

# Remove all objects and test- programs 
clean: 
	$(RM) *.o test main
