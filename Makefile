all: build

build:
	make -C ./build

.PHONY: clean
clean:
	rm gram.c gram.h
