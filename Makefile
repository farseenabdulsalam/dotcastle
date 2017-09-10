CXX := clang++
CXXFLAGS := -std=c++14 -Wall
INC := -I include
LIB := -lboost


SRCDIR := src
BUILDDIR := build
INCDIR := include
TESTSRCDIR := test
TESTBUILDDIR := $(TESTSRCDIR)/build

TESTSRCFILES := $(wildcard $(TESTSRCDIR)/*.cpp)
TESTBINFILES := $(subst .cpp,,$(TESTSRCFILES))

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $< $(CXXFLAGS) $(INC) $(LIB) -o $@

$(TESTBUILDDIR)/%.test: $(TESTSRCDIR)/%.test.cpp $(BUILDDIR)/%.o 
	$(CXX) $^ $(INC) $(LIB) $(CXXFLAGS) -o $@

tests: $(TESTBINFILES)
	for i in $^; do echo $i;$i; done

clean:
	@rm -f tests/build/*
	@rm -f build/*
