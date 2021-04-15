/*
** EPITECH PROJECT, 2020
** str_split
** File description:
** str_split function
*/

#include <stdlib.h>

int array_length(char **array)
{
    int i = 0;

    for (; array[i] != 0; i++)
        continue;
    return (i);
}

int count_line(const char *content, char split)
{
    if (!content)
        return (-1);
    int count = 0;
    for (int i = 0; content[i] != 0; i++)
        if (content[i] == split)
            count++;
    return (count);
}

int count_character_line(const char *content, char split, int line)
{
    int count_char = 0;
    int count_line = 0;
    for (int i = 0; content[i] != 0; i++) {
        if (content[i] == split) {
            count_line++;
            i++;
        }
        if (count_line == line)
            count_char++;
    }
    return (count_char);
}

static char **init_split(char *c, char s)
{
    int size = count_line(c, s) + 1;
    char **array = malloc(sizeof(char*) * (size + 1));
    for (int i = 0; i < size; i++)
        array[i] = malloc(sizeof(char) * (count_character_line(c, s, i) + 1));
    return (array);
}

char **str_split(char *c, char split)
{
    char **array = init_split(c, split);
    int index_x = 0;
    int index_y = 0;

    for (int i = 0; c[i] != 0; i++) {
        if (c[i] != split) {
            array[index_y][index_x] = c[i];
            index_x++;
        } else {
            array[index_y][index_x] = 0;
            index_y++;
            index_x = 0;
        }
    }
    array[index_y][index_x] = 0;
    array[index_y+1] = 0;
    return (array);
}