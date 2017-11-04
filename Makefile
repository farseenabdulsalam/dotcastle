SRCDIR := src
BUILDDIR := build
INCDIR := include

TESTSRCDIR := test
TESTBUILDDIR := $(TESTSRCDIR)/build

CXX := clang++
CXXFLAGS := -std=c++14 -Wall
INCFLAGS := -I $(INCDIR)
LIBFLAGS := -lboost_system -lboost_filesystem -lboost_program_options

TESTLIBFLAGS := -lboost_unit_test_framework

TESTSRCFILES := $(notdir $(wildcard $(TESTSRCDIR)/*.cpp))
TESTBINFILES := $(subst .cpp,,$(TESTSRCFILES))

SRCFILES := $(notdir $(wildcard $(SRCDIR)/*.cpp))
OBJFILES := $(subst .cpp,.o,$(SRCFILES))


$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp 
	$(CXX) -c $< $(CXXFLAGS) $(INCFLAGS) -o $@

.SECONDEXPANSION: # looks like this needed for % to expand inside wildcard
$(TESTBUILDDIR)/%: $(TESTSRCDIR)/%.cpp $(BUILDDIR)/$$(shell echo  $$* | sed -r s/_[a-zA-Z0-9_]+/.o/)
	$(CXX) $^ $(INCFLAGS) $(LIBFLAGS) $(TESTLIBFLAGS) $(CXXFLAGS) -o $@

tests: $(foreach file,$(TESTBINFILES),$(TESTBUILDDIR)/$(file))
	@for i in $^; do echo $$i;$$i; done

all: $(BUILDDIR)/$(OBJFILES)

clean:
	@rm -f $(TESTBUILDDIR)/*
	@rm -f $(BUILDDIR)/*

dotcastle: $(BUILDDIR)/main.o
	$(CXX) $< $(LIBFLAGS) -o $@

$(shell mkdir -p $(BUILDDIR))
$(shell mkdir -p $(TESTBUILDDIR))
