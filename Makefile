
DEST=dest
SOURCE=src
all: $(DEST) $(DEST)/libtconfig.a

$(DEST):
	mkdir -p $(DEST)

$(DEST)/libtconfig.a: $(SOURCE)/tconfig.cpp $(SOURCE)/tconfig.hh
	cd src && $(MAKE) 

$(DEST)/tests: $(SOURCE)/i32.test.cpp $(SOURCE)/char.test.cpp $(SOURCE)/str.test.cpp $(SOURCE)/bool.test.cpp $(SOURCE)/test.cpp
	cd src && $(MAKE) test


.PHONY: all test
