find_sources=$(foreach directory,$(call list_directories, $1),$(wildcard $(directory)*.cpp))
list_directories=$(foreach directory,$(sort $(dir $(wildcard $1*))),$(directory) $(call list_directories, $(directory)*/))

CC=g++
CXXFLAGS=-Wall -g -std=c++17
LDFLAGS=
SRCs=$(call find_sources, src/)
OBJs=$(SRCs:.cpp=.o)
EXEC=AgeOfWar

AgeOfWar: $(OBJs)
	$(CC) -o $@ $^ $(LDFLAGS)
	
%.o: %.cpp
	$(CC) -o $@ -c $< $(CXXFLAGS)
	
.PHONY: clean

clean:
	rm -rf $(OBJs)
	
cleanall: clean 
	rm -rf $(EXEC)
