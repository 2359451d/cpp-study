tldmonitor: tldmonitor.o date.o tldlist.o
	clang -fsanitize=address -fno-omit-frame-pointer -O1 -g -Wall -Werror -o tldmonitor tldmonitor.o date.o tldlist.o
	# clang -Wall -Werror -o tldmonitor tldmonitor.o date.o tldlist.o

date.o: date.h date.c
	clang -fsanitize=address -fno-omit-frame-pointer -O1 -g -Wall -Werror -o date.o -c date.c
	# clang -Wall -Werror -o date.o -c date.c

tldlist.o: tldlist.h tldlist.c
	clang -fsanitize=address -fno-omit-frame-pointer -O1 -g -Wall -Werror -o tldlist.o -c tldlist.c
	# clang -Wall -Werror -o tldlist.o -c tldlist.c

tldmonitor.o: tldmonitor.c date.h tldlist.h
	clang -fsanitize=address -fno-omit-frame-pointer -O1 -g -Wall -Werror -o tldmonitor.o -c tldmonitor.c
	# clang -Wall -Werror -o tldmonitor.o -c tldmonitor.c

clean:
	rm -f *.o tldmonitor
	# rm -f date.o tldmonitor.o tldmonitor
