CFLAGS = -c -g -Wall
GL_INCLUDE    = -I/usr/include/GL
GL_LIBDIR    = -L. -L/usr/X11R6/lib
GL_LIBRARIES = -lglut -lGL -lm -lGLU # -lXmu -lXext -lXi -lX11
CC=gcc
OS = "unknown"

# Add objectiveC library for MacOSX.
ifneq ($(strip $(shell $(CC) -v 2>&1 | grep -i "Apple")),)
 GL_INCLUDE    = -I/usr/X11R6/include
 GL_LIBRARIES += -lobjc
 BROWSER = dillo
 OS = "osx"
endif
# Nothing to be done for Linux :o)
ifneq ($(strip $(shell $(CC) -v 2>&1 | grep -i "Linux")),)
 OS = "linux"
 BROWSER = mozilla
endif
#
job: one one_part2 two dox
	./one -c4 && ./one_part2 && ./two -n100 && $(BROWSER) DOX/html/index.html &

one: one.o triangle2f.o vertex2f.o
	$(CC) $(GL_LIBDIR) one.o triangle2f.o vertex2f.o $(GL_LIBRARIES) -o $@
one.o : one.c vertex2f.c
	$(CC) $(GL_INCLUDE) $(CFLAGS) $<

one_part2: one_part2.o triangle2f.o vertex2f.o vertex2f_ring.o polygone2f.o rect2f.o
	$(CC) $(GL_LIBDIR) one_part2.o triangle2f.o vertex2f.o vertex2f_ring.o polygone2f.o rect2f.o $(GL_LIBRARIES) -o $@
one_part2.o : one_part2.c
	$(CC) $(GL_INCLUDE) $(CFLAGS) $<

two: two.o
	$(CC) $(GL_LIBDIR) two.o $(GL_LIBRARIES) -o $@
two.o : two.c
	$(CC) $(GL_INCLUDE) $(CFLAGS) $<
#
clean:
	@echo "operating system = $(OS)"
	rm -rf *.o one one_part2 two DOX

################################################################################
# Generate doxygen documentation of file two.c using command file two.dox.
dox: two.c two.h
	rm -rf DOX
	doxygen two.dox
#

