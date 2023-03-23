CXX=g++
CXXFLAGS=-Wall -Wextra -fsanitize=address
DEPS=
OBJ=patcher.o 
ODIR=obj
IFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

%.o: %.c $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

patcher: $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(IFLAGS)  

.PHONY: clean

clean:
	rm -f ./*.o

