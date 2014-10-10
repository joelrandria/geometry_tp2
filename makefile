CFLAGS = -c -g -Wall -std=gnu99
GL_INCLUDE = -I/usr/include/GL
GL_LIBDIR = -L. -L/usr/X11R6/lib
GL_LIBRARIES = -lglut -lGL -lm -lGLU # -lXmu -lXext -lXi -lX11
CC = gcc
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

job: tpga2 #dox
	./tpga2 -1 -otest.txt
	#one -c4 && two -n100 && $(BROWSER) DOX/html/index.html &
	#tpga2 -2 && tpga2 -3 && tpga2 -4 && tpga2 -5 && $(BROWSER) DOX/html/index.html &

tpga2: tpga2.o tpga2_ex1.o vertex.o vertex_ring.o
	$(CC) $(GL_LIBDIR) tpga2.o tpga2_ex1.o vertex.o vertex_ring.o $(GL_LIBRARIES) -o $@

tpga2.o: tpga2.c
	$(CC) $(GL_INCLUDE) $(CFLAGS) $<

clean:
	@echo "operating system = $(OS)"
	rm -rf *.o tpga2 DOX

################################################################################
# Generate doxygen documentation of file two.c using command file two.dox.
#dox: two.c two.h
#	rm -rf DOX
#	doxygen two.dox
#

