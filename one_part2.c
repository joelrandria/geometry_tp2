#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <assert.h>
#include <time.h>

#include <GL/glut.h>

#include "vertex2f.h"
#include "vertex2f_ring.h"
#include "triangle2f.h"
#include "polygone2f.h"
#include "rect2f.h"

#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT 300

extern char *optarg;
extern int opterr;

int displayChoice = 0;
char *lineOption[] = { "GL_POINTS", "GL_LINES", "GL_LINE_STRIP", "GL_LINE_LOOP", "GL_POLYGON"};

vertex2f* g_polygone = 0;
int g_polygone_browsing_direction = VERTEX_FORWARD_LINK;
rect2f* g_polygone_bounding_rect = 0;

int g_random_point_count = 50;
vertex2f** g_random_points = 0;

void winInit (void)
{
  gluOrtho2D(g_polygone_bounding_rect->down_left->coords[X_COORD],
	     get_rect2f_width(g_polygone_bounding_rect),
	     g_polygone_bounding_rect->down_left->coords[Y_COORD],
	     get_rect2f_height(g_polygone_bounding_rect));
}

void initializePolygone()
{
  g_polygone = insert_vertex2f_in_ring(g_polygone, new_vertex2f(5755, 2978), VERTEX_FORWARD_LINK);
  g_polygone = insert_vertex2f_in_ring(g_polygone, new_vertex2f(6505, 3203), VERTEX_FORWARD_LINK);
  g_polygone = insert_vertex2f_in_ring(g_polygone, new_vertex2f(6805, 2003), VERTEX_FORWARD_LINK);
  g_polygone = insert_vertex2f_in_ring(g_polygone, new_vertex2f(5005, 1778), VERTEX_FORWARD_LINK);
  g_polygone = insert_vertex2f_in_ring(g_polygone, new_vertex2f(5305, 2228), VERTEX_FORWARD_LINK);
  g_polygone = insert_vertex2f_in_ring(g_polygone, new_vertex2f(3880, 2678), VERTEX_FORWARD_LINK);
  g_polygone = insert_vertex2f_in_ring(g_polygone, new_vertex2f(4105, 5003), VERTEX_FORWARD_LINK);
  g_polygone = insert_vertex2f_in_ring(g_polygone, new_vertex2f(4855, 4553), VERTEX_FORWARD_LINK);
  g_polygone = insert_vertex2f_in_ring(g_polygone, new_vertex2f(4705, 5903), VERTEX_FORWARD_LINK);
  g_polygone = insert_vertex2f_in_ring(g_polygone, new_vertex2f(3055, 4478), VERTEX_FORWARD_LINK);
  g_polygone = insert_vertex2f_in_ring(g_polygone, new_vertex2f(2230, 5228), VERTEX_FORWARD_LINK);
  g_polygone = insert_vertex2f_in_ring(g_polygone, new_vertex2f(3205, 7703), VERTEX_FORWARD_LINK);
  g_polygone = insert_vertex2f_in_ring(g_polygone, new_vertex2f(3280, 5678), VERTEX_FORWARD_LINK);
  g_polygone = insert_vertex2f_in_ring(g_polygone, new_vertex2f(6805, 7328), VERTEX_FORWARD_LINK);
  g_polygone = insert_vertex2f_in_ring(g_polygone, new_vertex2f(8755, 5753), VERTEX_FORWARD_LINK);
  g_polygone = insert_vertex2f_in_ring(g_polygone, new_vertex2f(8380, 4328), VERTEX_FORWARD_LINK);
  g_polygone = insert_vertex2f_in_ring(g_polygone, new_vertex2f(6580, 4703), VERTEX_FORWARD_LINK);
  g_polygone = insert_vertex2f_in_ring(g_polygone, new_vertex2f(8005, 4928), VERTEX_FORWARD_LINK);
  g_polygone = insert_vertex2f_in_ring(g_polygone, new_vertex2f(6730, 6128), VERTEX_FORWARD_LINK);
  g_polygone = insert_vertex2f_in_ring(g_polygone, new_vertex2f(5605, 5003), VERTEX_FORWARD_LINK);
  g_polygone = insert_vertex2f_in_ring(g_polygone, new_vertex2f(5830, 3653), VERTEX_FORWARD_LINK);
  g_polygone = insert_vertex2f_in_ring(g_polygone, new_vertex2f(5155, 3278), VERTEX_FORWARD_LINK);
  g_polygone = insert_vertex2f_in_ring(g_polygone, new_vertex2f(5155, 3278), VERTEX_FORWARD_LINK);
  g_polygone = insert_vertex2f_in_ring(g_polygone, new_vertex2f(5755, 2978), VERTEX_FORWARD_LINK);

  switch (get_polygone2f_rotation_direction(g_polygone))
  {
  case CLOCKWISE_DIRECTION:
    g_polygone_browsing_direction = VERTEX_BACKWARD_LINK;
    printf("Polygone ordonné dans le sens horaire => Affichage dans le sens inverse.\r\n");
    break;
  case COUNTERCLOCKWISE_DIRECTION:
    g_polygone_browsing_direction = VERTEX_FORWARD_LINK;
    printf("Polygone ordonné dans le sens trigonométrique => Affichage dans cet ordre.\r\n");
    break;
  default:
    printf("Polygone dégénéré.\r\n");
    break;
  }

  g_polygone_bounding_rect = get_polygone2f_bounding_rect(g_polygone);
}
void initializePoints()
{
  int i;

  g_random_points = malloc(sizeof(float*) * g_random_point_count);
  for (i = 0; i < g_random_point_count; ++i)
    g_random_points[i] = new_random_vertex2f(WINDOW_WIDTH, WINDOW_HEIGHT);
}
void initializeData()
{
  initializePolygone();
  initializePoints();
}

void drawPolygone()
{
  vertex2f* it;
  vertex2f* beginning;

  glBegin(GL_POLYGON);
  glColor3f(1.0, 1.0, 1.0);

  it = beginning = g_polygone;
  while (it->links[VERTEX_RING_LINK][g_polygone_browsing_direction] != beginning)
  {
    glVertex2f(it->coords[X_COORD], it->coords[Y_COORD]);
    
    it = it->links[VERTEX_RING_LINK][g_polygone_browsing_direction];
  }

  glEnd();
}
void drawPoints()
{
  int i;
  int vertex_location;
  
  glBegin(GL_POINTS);
  for (i = 0; i < g_random_point_count; ++i)
  {
    /* vertex_location = locate_vertex_triangle2f(g_triangle, g_random_points[i]); */
    /* switch (vertex_location) */
    /* { */
    /* case INSIDE_LOCATION: glColor3f(0.0, 1.0, 0.0); break; */
    /* case OUTSIDE_LOCATION: glColor3f(1.0, 0.0, 0.0); break; */
    /* default: glColor3f(0.0, 0.0, 1.0); break; */
    /* } */

    /* glVertex2f(g_random_points[i]->coords[X_COORD], g_random_points[i]->coords[Y_COORD]); */
  }
  glEnd();
}

void display (void)
{
  glColor3f(0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  drawPolygone();
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

  initializeData();
  winInit();

  glutDisplayFunc(display);
  glutMainLoop();  
  
  return EXIT_SUCCESS;  
}
