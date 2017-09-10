CXX := clang++
CXXFLAGS := -std=c++14 -Wall
INC := -I include
LIB := -lboost


SRCDIR := src
BUILDDIR := build
INCDIR := include
TESTSRCDIR := test
TESTBUILDDIR := $(TESTSRCDIR)/build

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	echo $@
	echo $^
	echo $<
	#$(CXX) -c $< $(CXXFLAGS) $(INC) $(LIB) -o $@

$(TESTBUILDDIR)/%.test: $(BUILDDIR)/%.o $(TESTSRCDIR)/%.test.cpp
	$(CXX) $< $(CXXFLAGS) -o $@

testall: $(wildcard $(TESTBUILDDIR)/*.test)
	echo $^
	for i in $@; do echo $i; done

clean:
	@rm -f tests/build/*
	@rm -f build/*
