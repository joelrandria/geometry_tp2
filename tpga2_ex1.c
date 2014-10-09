#include <stdio.h>

#include <GL/glut.h>

#include "tpga2.h"
#include "tpga2_ex1.h"

// Anneau de sommets créés par l'utilisateur
vertex_ring* _vring = 0;
int _polygone_closed = 0;

void tpga2_ex1()
{
  glutDisplayFunc(draw);
  glutMouseFunc(process_mouse_events);

  glutMainLoop();
}

void draw()
{
  glColor3f(0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  if (!_polygone_closed)
  {
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0, 1.0, 1.0);
  }
  else
  {
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 1.0, 0.0);
  }

  vertexring_run(_vring, draw_vertex, 0, VR_FORWARD);

  glEnd();
  glFlush();
  glutPostRedisplay();
}
void draw_vertex(vertex_ring* r, void* args)
{
  glVertex2f(r->v->coords[0], r->v->coords[1]);
}

void windowpos_to_glpos(int window_width, int window_height,
			int win_x, int win_y,
			float* gl_x, float* gl_y)
{
  *gl_x = win_x;
  *gl_y = window_height - win_y;
}
void process_mouse_events(int button, int state, int x, int y)
{
  float mouse_x;
  float mouse_y;
  vertex* clicked_vertex;

  if (_polygone_closed)
    return;

  if ((state == GLUT_UP) && (button == GLUT_LEFT_BUTTON))
  {
    windowpos_to_glpos(WINDOW_WIDTH, WINDOW_HEIGHT, x, y, &mouse_x, &mouse_y);

    clicked_vertex = vertexring_findbycoord(_vring, mouse_x, mouse_y, CLIC_SENSITIVITY);
    if (!clicked_vertex)
    {
      _vring = vertexring_enqueue(_vring, vertex_create(mouse_x, mouse_y), VR_FORWARD);

      printf("Nouveau point ajouté\r\n");
      printf("--- Points courants ---\r\n");
      vertexring_print(_vring, VR_FORWARD);
      printf("-----------------------\r\n");
    }
    else if (clicked_vertex == _vring->v)
    {
      _polygone_closed = 1;
      printf("Polygone saisi\r\n");
      vertexring_save(_vring, _optex1_filename);
      printf("Polygone sauvegardé dans le fichier '%s'\r\n", _optex1_filename);
    }
  }
}
