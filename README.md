# beaksh

I was curious about how for I could get in writing a minimal but still
somewhat useful UNIX shell in an hour - this was the result. An hour buys
you fork/exec's and nothing in the way of command line parsing. More
features that would make it considerable more useful:

* builtin commands (e.g. `cd`)
* history / persistent history
* PATH configuration
* job control
* pipes/redirection

# Development

To develop this, check out [linenoise](https://github.com/antirez/linenoise) and drop `linenoise.h` and `linenoise.c` alongside the other files in the project and run `make`.
