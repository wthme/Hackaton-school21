CFLAGS=-std=c11

ifeq ($(shell uname), Linux)
	CHKFLAGS=-pthread -lcheck_pic -pthread -lrt -lm -lsubunit
else
	CHKFLAGS=-lcheck
endif

.PHONY: all test clean run install uninstal

all: clean install

install:
	@mkdir -p build
	qmake6 Mediatekkka.pro -o build/
	@cd build; make
	@cd ../
	@mkdir -p app
	@cp -r build/Mediatekkka app/

uninstall:
	@rm -rf app

clean:
	@rm -rf *.a *.o *.out
	@rm -rf build

