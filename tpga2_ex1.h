#ifndef __TPGA2_EX1_H__
#define __TPGA2_EX1_H__

#include "vertex_ring.h"

#define CLIC_SENSITIVITY 20

// Exécution de l'exercice 1
void tpga2_ex1();
void tpga2_ex2();

// Fonctions d'affichage
void draw();
void draw_vertex(vertex_ring* r, void* args);

// Gestionnaire d'évènements souris
void windowpos_to_glpos(int window_width, int window_height,
			int win_x, int win_y,
			float* gl_x, float* gl_y);
void process_mouse_events(int button, int state, int x, int y);

#endif
