BIN=./bin
SOURCES=$(filter-out linenoise.c, $(wildcard src/**/*.c src/*.c *.c))

beaksh: linenoise.h linenoise.c build check

beaksh: linenoise.c beaksh.c
	$(CC) -Wall -W -Os -g -o $(BIN)/beaksh linenoise.c beaksh.c

build:
	@mkdir -p $(BIN)

clean:
	rm -f $(BIN)/beaksh
	rm -rf `find $(BIN) -name "*.dSYM" -print`

BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'

check:
	@echo Files with potentially dangerous functions:
	@egrep $(BADFUNCS) $(SOURCES) || true
