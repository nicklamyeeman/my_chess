/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** open_read
*/

#include "chess.h"

char **array_copy(char **array)
{
	int k = 0;
	int len = array_len(array);
	char **copy = NULL;

	if (array == NULL || len == 0)
		return copy;
	copy = malloc(sizeof(char *) * (len+ 1));
	for (k = 0; k != len; k++)
		copy[k] = strdup(array[k]);
	copy[k] = NULL;
	return copy;
}

void free_array(char **array)
{
	for (int i = 0; array[i] != NULL; i++)
		free(array[i]);
	free(array);
}

void free_ressource(char *buffer, char **exploded)
{
	free(buffer);
	free_array(exploded);
}

int array_len(char **array)
{
	int i = 0;

	if (array == NULL)
		return 0;
	for (i = 0; array[i] != NULL; i++);
	return i;
}

int usage(int return_value)
{
	if (return_value == 84)
	    fprintf(stderr, "USAGE\n\t./my_chess\n");	
	else
	    printf("USAGE\n\t./my_chess\n");
    return (return_value);
}

char *open_read_file(char *filepath)
{
	int fd = open(filepath, O_RDONLY);    
	if (fd == -1) {
		fprintf(stderr, "Can't open file : %s\n", filepath);
		return (NULL);
	}

	struct stat *st = malloc(sizeof(struct stat));
    stat(filepath, st);

	char *result = malloc(st->st_size + 1);
	int	size = st->st_size;
	while (size != 0)
		size = read(fd, result, size);
    result[st->st_size] = '\0';

	close(fd);
    free(st);
	return (result);
}
