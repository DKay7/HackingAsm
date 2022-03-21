CXX=g++
CXXFLAGS=-Wall -Wextra -ggdb3 -g 
DEPS=default_hash_functions.h
OBJ=hack_for_sasha.o default_hash_functions.o 
ODIR=obj

%.o: %.c $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

hack: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

# hack_asm: $(OBJ)
# 	$(CC) -S -masm=intel -o $@  $(CFLAGS)

.PHONY: clean

clean:
	rm -f ./*.o

