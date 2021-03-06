#include "fdf.h"
#include <stdlib.h>
#include <unistd.h>

char **malloc_bzero(size_t count)
{
	char** res;
	size_t i;

	i = 0;
	res = malloc(count);
	while (i < count / sizeof(char *))
		res[i++] = 0;
	return res;
}

int error(char *s)
{
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	return (0);
}

int size(char **splitted)
{
	int i;

	i = 0;
	while (splitted[i])
		i++;
	return i;
}

void swap_(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(*(split + i));
		i++;
	}
	free(split);
}
