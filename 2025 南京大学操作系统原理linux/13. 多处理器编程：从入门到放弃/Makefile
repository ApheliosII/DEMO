CXX := g++
CXXFLAGS := -Wall -g

text: text.cc 
	$(CXX) $(CXXFLAGS) -o $@ $< -pthread

clean:
	rm -f text

.PHONY: clean
