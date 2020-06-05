CPPFLAGS = -Wall -g -I headers
CC = gcc
src = $(wildcard src/*.c)
obj = $(patsubst src/%.c,build/%.o,$(src))
headers = $(wildcard headers/*.h)
server: $(obj)
	$(CC) -o $@ $^
build/%.o: src/%.c $(headers)
	$(CC) -c -o $@ $< ($CPPFLAGS)
clean:
	rm -rf build/*.o server
