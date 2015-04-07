beaksh: linenoise.h linenoise.c

beaksh: linenoise.c beaksh.c
	$(CC) -Wall -W -Os -g -o beaksh linenoise.c beaksh.c

clean:
	rm -f beaksh
	rm -rf beaksh.dSYM
