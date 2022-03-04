/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** open_read
*/

#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdio.h>
#include <unistd.h>
#include "chess.h"

int usage(int return_value)
{
    printf("USAGE\n");
    printf("\t./my_chess\n");
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
