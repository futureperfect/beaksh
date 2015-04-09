BIN=./bin

beaksh: linenoise.h linenoise.c build

beaksh: linenoise.c beaksh.c
	$(CC) -Wall -W -Os -g -o $(BIN)/beaksh linenoise.c beaksh.c

build:
	@mkdir -p $(BIN)

clean:
	rm -f $(BIN)/beaksh
	rm -rf `find $(BIN) -name "*.dSYM" -print`
