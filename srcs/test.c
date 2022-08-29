
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <curses.h>
#include <term.h>

#define PATH_MAX 4096

int	main()
{
	tputs(tgetstr("cl", NULL), 1, aff_c);
	return (0);
}
