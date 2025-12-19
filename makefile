CFLAGS  = -std=c99 \
	  -pipe \
	  -ggdb3 -Wstrict-overflow=5 -fstack-protector-all \
          -W -Wall -Wextra \
	  -Wbad-function-cast \
	  -Wcast-align \
	  -Wcast-qual \
	  -Wconversion \
	  -Wfloat-equal \
	  -Wformat-y2k \
	  -Winit-self \
	  -Winline \
	  -Winvalid-pch \
	  -Wmissing-declarations \
	  -Wmissing-field-initializers \
	  -Wmissing-format-attribute \
	  -Wmissing-include-dirs \
	  -Wmissing-noreturn \
	  -Wmissing-prototypes \
	  -Wnested-externs \
	  -Wnormalized=nfc \
	  -Wold-style-definition \
	  -Woverlength-strings \
	  -Wpacked \
	  -Wpadded \
	  -Wpointer-arith \
	  -Wredundant-decls \
	  -Wshadow \
	  -Wsign-compare \
	  -Wstack-protector \
	  -Wstrict-aliasing=2 \
	  -Wstrict-prototypes \
	  -Wundef \
	  -Wunsafe-loop-optimizations \
	  -Wvolatile-register-var \
	  -Wwrite-strings

INCLUDES = -I./include

#------------------------------------------------------------------------------
.PHONY : all clean

#------------------------------------------------------------------------------
all : test

test : src/test.o src/graph.o
	$(CC) $(CFLAGS) -o $@ $^ -lcgraph

src/test.o: src/test.c include/graph.h
	$(CC) $(CFLAGS) $(INCLUDES) -c src/test.c -o src/test.o

src/graph.o: src/graph.c include/graph.h
	$(CC) $(CFLAGS) $(INCLUDES) -c src/graph.c -o src/graph.o


#------------------------------------------------------------------------------
clean :
	$(RM) test src/*.o