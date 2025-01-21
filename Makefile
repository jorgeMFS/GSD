.PHONY: all clean test

all:
	$(MAKE) -C src

clean:
	$(MAKE) -C src clean
	rm -f scripts/*.fa

test:
	cd scripts && python3 generate_dna.py

install:
	$(MAKE) -C src install

.DEFAULT_GOAL := all 