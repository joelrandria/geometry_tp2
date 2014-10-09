#include "tpga2.h"
#include "tpga2_ex1.h"

#include <string.h>

// Exercice sélectionné
int _opt_selex = 0;

// Options exercice 1
char* _optex1_filename = 0;
char* _test = 0;

void winInit()
{
  gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
}

void usage()
{
  printf("Usage: ./tpga2 {-1 -ofilename }\r\n");
}

int main(int argc, char **argv)
{
  int c;

  opterr = 0;
  while ((c = getopt(argc, argv, "1o:i:")) != EOF)
  {
    switch (c)
    {
    case '1': _opt_selex = 1; break;

    case 'o': _optex1_filename = optarg; break;
    case 'i': _test = optarg; break;

    default: usage(); break;
    }
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowPosition(5,5);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("My first OpenGL window...");

  winInit();

  if (_opt_selex == 1)
  {
    if (_optex1_filename == 0)
      usage();
    else
      tpga2_ex1(_optex1_filename);
  }

  return EXIT_SUCCESS;
}
