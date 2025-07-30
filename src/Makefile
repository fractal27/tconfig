
build:=../build
TESTFLAGS=
#TESTFLAGS:=-DDEBUG


all: $(build)/libtconfig.a $(build)/tconfig.o

test:
	g++ -o $(build)/test test.cpp tconfig.cpp -lgtest $(TESTFLAGS)

$(build)/tconfig.o: tconfig.cpp tconfig.hh
	g++ -c tconfig.cpp -o $(build)/tconfig.o

$(build)/libtconfig.a: $(build)/tconfig.o
	ar rvs $(build)/libtconfig.a $(build)/tconfig.o

.PHONY: test all
