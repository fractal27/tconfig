DEST=../dest

all: $(DEST)/tconfig.o $(DEST)/libtconfig.a

$(DEST)/tconfig.o: tconfig.cpp tconfig.hh
	g++ -c tconfig.cpp -o $(DEST)/tconfig.o

$(DEST)/libtconfig.a: $(DEST)/tconfig.o
	ar rcs $(DEST)/libtconfig.a $(DEST)/tconfig.o
$(DEST)/runTests: str.test.cpp i32.test.cpp bool.test.cpp char.test.cpp test.cpp
	g++ test.cpp str.test.cpp i32.test.cpp bool.test.cpp char.test.cpp -lgtest -o $(DEST)/runTests

test: 
	$(MAKE) $(DEST)/runTests

build:
	$(MAKE)

.PHONY: test build
