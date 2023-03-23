CXX=g++
CXXFLAGS=-Wall -Wextra -s -fno-stack-protector
DEPS=default_hash_functions.h
OBJ=hack_for_sasha.o default_hash_functions.o 
ODIR=obj

%.o: %.c $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

hack: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

.PHONY: clean

clean:
	rm -f ./*.o

