/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** open_read
*/

#include "chess.h"

void free_ressource(char *buffer, char **exploded)
{
	free(buffer);
	for (int i = 0; exploded[i] != NULL; i++)
		free(exploded[i]);
	free(exploded);
}

int array_len(char **array)
{
	int i = 0;
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
