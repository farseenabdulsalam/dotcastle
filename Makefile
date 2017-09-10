SRCDIR := src
BUILDDIR := build
INCDIR := include

TESTSRCDIR := test
TESTBUILDDIR := $(TESTSRCDIR)/build

CXX := clang++
CXXFLAGS := -std=c++14 -Wall
INCFLAGS := -I $(INCDIR)
LIBFLAGS := -lboost_system -lboost_filesystem -lfmt

TESTLIBFLAGS := -lboost_unit_test_framework

TESTSRCFILES := $(notdir $(wildcard $(TESTSRCDIR)/*.cpp))
TESTBINFILES := $(subst .cpp,,$(TESTSRCFILES))

SRCFILES := $(notdir $(wildcard $(SRCDIR)/*.cpp))
OBJFILES := $(subst .cpp,.o,$(SRCFILES))

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $< $(CXXFLAGS) $(INCFLAGS) -o $@

$(TESTBUILDDIR)/%.test: $(TESTSRCDIR)/%.test.cpp $(BUILDDIR)/%.o 
	$(CXX) $^ $(INCFLAGS) $(LIBFLAGS) $(TESTLIBFLAGS) $(CXXFLAGS) -o $@

tests: $(TESTBUILDDIR)/$(TESTBINFILES)
	@for i in $^; do echo $$i;$$i; done

all: $(BUILDDIR)/$(OBJFILES)

clean:
	@rm -f $(TESTBUILDDIR)/*
	@rm -f $(BUILDDIR)/*
