#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <assert.h>
#include <time.h>

#include <GL/glut.h>

#include "triangle2f.h"
#include "vertex2f.h"

#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT 300

extern char *optarg;
extern int opterr;

int displayChoice = 0;

char *lineOption[] = { "GL_POINTS", "GL_LINES", "GL_LINE_STRIP", "GL_LINE_LOOP", "GL_POLYGON"};

vertex2f** g_triangle = 0;

int g_random_point_count = 50;
vertex2f** g_random_points = 0;

void winInit (void)
{
  gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);
}

void initializeData()
{
  int i;

  g_triangle = get_random_triangle2f(WINDOW_WIDTH, WINDOW_HEIGHT);

  g_random_points = malloc(sizeof(float*) * g_random_point_count);
  for (i = 0; i < g_random_point_count; ++i)
    g_random_points[i] = new_random_vertex2f(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void drawTriangle()
{
  glBegin(GL_LINE_LOOP);

  glColor3f(1.0, 1.0, 1.0);

  glVertex2f(g_triangle[0]->coords[X_COORD], g_triangle[0]->coords[Y_COORD]);
  glVertex2f(g_triangle[1]->coords[X_COORD], g_triangle[1]->coords[Y_COORD]);
  glVertex2f(g_triangle[2]->coords[X_COORD], g_triangle[2]->coords[Y_COORD]);

  glEnd();
}

void drawPoints()
{
  int i;
  int point_location;
  
  glBegin(GL_POINTS);
  for (i = 0; i < g_random_point_count; ++i)
  {
    point_location = locate_vertex_triangle2f(g_triangle, g_random_points[i]);
    switch (point_location)
    {
    case INSIDE_LOCATION: glColor3f(0.0, 1.0, 0.0); break;
    case OUTSIDE_LOCATION: glColor3f(1.0, 0.0, 0.0); break;
    default: glColor3f(0.0, 0.0, 1.0); break;
    }

    glVertex2f(g_random_points[i]->coords[X_COORD], g_random_points[i]->coords[Y_COORD]);
  }
  glEnd();
}

void display (void)
{
  glColor3f(0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  drawTriangle();
  drawPoints();

  glFlush();
}

int main(int argc, char **argv)  
{  
  int option;

  opterr = 0; /* set off std error messages in case wrong option is chosen */
  while ((option = getopt(argc, argv, "c:n:")) != EOF)
  {
    switch (option)
      {
      case 'c': if ((sscanf(optarg, "%d", &displayChoice) == 1) && displayChoice >= 0 && displayChoice <= 4)
	  break;
      case 'n': if ((sscanf(optarg, "%d", &g_random_point_count) == 1) && (g_random_point_count >= 0))
	  break;
      case '?': /* value returned by getopt if invalid option chosen */
      default : printf("Usage: %s -cX -nY, with X = 1, 2, 3 or 4 and Y >= 0 (50 by default).\n", argv[0]);
	displayChoice = 0;
	break;
      }
  }
  assert(displayChoice >= 0 && displayChoice <= 4);
  printf("Executing %s with line option %d = %s, n=%d.\n",
	 argv[0],
	 displayChoice,
	 lineOption[displayChoice],
	 g_random_point_count);
  glutInit(&argc, argv);  
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowPosition(5,5);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

  glutCreateWindow("My first OpenGL window...");  
  winInit();

  initializeData();

  glutDisplayFunc(display);
  glutMainLoop();  
  
  return EXIT_SUCCESS;  
}
