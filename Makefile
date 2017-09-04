
CXX=clang++
CXXFLAGS=-std=c++14

COMPILE-CXX=$(CXX) -c $< $(CXXFLAGS) -o $@

build/%.o: %.cpp
	$(COMPILE-CXX)

tests/build/%.o: tests/%.cpp
	$(COMPILE-CXX)

clean:
	@rm -f tests/build/*
	@rm -f build/*
