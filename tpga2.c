#include "tpga2.h"

#include <string.h>

// Exercice sélectionné
int _opt_selex = 0;

// Options exercice 1
char* _optex_filename = 0;

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
	while ((c = getopt(argc, argv, "12o:")) != EOF)
	{
		switch (c)
		{
			case '1': _opt_selex = 1; break;
			
			case '2': _opt_selex = 2; break; 

			case 'o': _optex_filename = optarg; break;

			default: usage();
		}
	}

	if (!_opt_selex)
	{
		usage();
		return EXIT_SUCCESS;
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(5,5);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("TP Géométrie Algorithmique #2");

	winInit();

	if (_opt_selex == 1)
	{
		if (_optex_filename == 0)
			usage();
		else
			tpga2_ex1();
	}
	else if(_opt_selex == 2)
	{
		if (_optex_filename == 0)
			usage();
		else
			tpga2_ex2();
	}
	

	return EXIT_SUCCESS;
}
