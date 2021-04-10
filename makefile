#to input the cxx file, type: make input=filename



ROOTSYS  =  $(shell echo $ROOTSYS)

CXXFLAGS = $(shell root-config --cflags)

ROOTLIBS = $(shell root-config --libs)

MYLIBCXX  = $(subst .hh,.cxx,$(shell ls ./*hh))
MYLIBS    = $(subst .cxx,.o,$(shell ls $(MYLIBCXX)))

LIBS     := $(ROOTLIBS)

OPT      = -ggdb -Wall -Wshadow

GCC = /usr/bin/g++



all: main.exe
	


%.exe: %.o ./*.hh $(MYLIBS)
	@$(GCC) $(OPT) $(CXXFLAGS) -L. -o $@ $< $(MYLIBS) $(LIBS)

%.o: %.cxx
	@$(GCC) $(OPT) $(CXXFLAGS) -o $@ -c $<


clean:
	@rm -f *.o