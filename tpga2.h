#ifndef __TPGA2_H__
#define __TPGA2_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <unistd.h>
#include <GL/glut.h>

#include "vertex.h"
#include "tpga2_ex1.h"

#define WINDOW_WIDTH 680
#define WINDOW_HEIGHT 680

// Accès aux options de la ligne de commandes
extern char *optarg;
extern int opterr;

// Options exercice 1
extern char* _optex_filename;

#endif
