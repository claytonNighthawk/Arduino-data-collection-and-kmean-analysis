CC = g++
CFLAGS = -g -Wall -std=c++11
KMEAN_OBJECTS = centroid.o kmean.o 
TEST_OBJ = test.o
MAIN_OBJ = fileparser.o main.o 


%.o: %.cpp
	$(CC) -c $(CFLAGS) $<

test: $(KMEAN_OBJECTS) $(TEST_OBJ)
	$(CC) -o $@ $(TEST_OBJ) $(KMEAN_OBJECTS)

main: $(KMEAN_OBJECTS) $(MAIN_OBJ)
	$(CC) -o $@ $(MAIN_OBJ) $(KMEAN_OBJECTS)

# Remove all objects and test- programs 
clean: 
	$(RM) *.o *.out test main
