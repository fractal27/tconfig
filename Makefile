#MAKEFILE 


all:
	cd src && $(MAKE)

test:
	cd src && $(MAKE) test

clean:
	rm build/*.o build/*.a build/*.so

.PHONY: test all clean

