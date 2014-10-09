#include "tpga2.h"
#include "tpga2_ex2.h"

void winInit()
{
  gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
}

int main(int argc, char **argv)
{
  /* int c; */

  /* opterr = 0; */
  /* while ((c = getopt(argc, argv, "n:")) != EOF) */
  /* { */
  /* 	switch (c) */
  /* 	{ */
  /* 		case 'n': if ((sscanf(optarg, "%d", &nbPoints) != 1) || nbPoints <= 0) */
  /* 					nbPoints = 50; */
  /* 				  break; */
  /* 		case '?': printf("use option -nX (no space), with 0 < X.\n"); */
  /* 				  break; */
  /* 		default : printf("Shouldn't be here, really...\n"); */
  /* 				  break; */
  /* 	} */
  /* } */

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowPosition(5,5);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("My first OpenGL window...");

  winInit();

  tpga2_ex2();

  return EXIT_SUCCESS;
}
