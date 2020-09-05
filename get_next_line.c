/*SUBJECT*/
/*Assignment name  : get_next_line
Expected files   : get_next_line.c get_next_line.h
Allowed functions: read, free, malloc
--------------------------------------------------------------------------------

Write a function will store, in the parameter "line", a line that has been read from the file descriptor 0.
Your function must be prototyped as follows: int get_next_line(char **line);
Your function should be memory leak free.
What we call a "line that has been read" is a succession of 0 to n characters that end with '\n' (ascii code 0x0a) or with End Of File (EOF).
The string stored in the parameter "line" should not contained any '\n'.
The parameter is the address of a pointer to a character that will be used to store the line read.
The return value can be 1, 0 or -1 depending on whether a line has been read, when the reading has been completed (meaning read has returned 0), or if an error has happened respectively.
When you've reached the End Of File, you must store the current buffer in "line". If the buffer is empty you must store an empty string in "line".
When you've reached the End Of File, your function should keep 0 memory allocated with malloc except the last buffer that you should have stored in "line".
What you've stored in "line" should be free-able.
Calling your function get_next_line in a loop will therefore allow you to read the text available on a file descriptor one line at a time until the end of the text, no matter the size of either the text or one of its lines.
Make sure that your function behaves well when it reads from a file, from the standard output, from a redirection etc.
No call to another function will be done on the file descriptor between 2 calls of get_next_line.
Finally we consider that get_next_line has an undefined behavior when reading from a binary file.
You should use the test.sh to help you test your get_next_line.*/
	
#include "get_next_line.h"

int ft_strlen(char *s)
{
	int len = 0;
	while (s[len])
		len++;
	return len;
}

char *ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	return NULL;
}

char *ft_strjoin(char *s1, char *s2)
{
	char *new;
	new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	int i = 0;

	while (*s1)
		new[i++] = *s1++;
	while (*s2) 
		new[i++] = *s2++;
	new[i] = '\0';
	return (new);
}

char *ft_substr(char *s, int start, int len)
{
	char *sub;

	sub = malloc(len + 1);
	int i = 0;

	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';

	return (sub);
}

char *ft_strdup(char *s)
{
	char *dup; 

	dup = malloc(ft_strlen(s) + 1);
	while(*s)
		*dup++ = *s++;
	*dup = '\0';

	return (dup);
}

int get_next_line(char **line)
{
	static char *remainder;
	char *tmp;
	int len;
	int bytes = 1;
	char buf[2];

	remainder = (remainder == NULL) ? ft_strdup("") : remainder;

	while (bytes > 0 && !ft_strchr(remainder, '\n'))
	{
		bytes = read(0, buf, 1);
		buf[bytes] = '\0';
		tmp = ft_strjoin(remainder, buf);
		free(remainder);
		remainder = tmp;
	}
	if (ft_strchr(remainder, '\n'))
	{
		len = ft_strlen(remainder) - 1;
		*line = ft_substr(remainder, 0, len);
		free(remainder);
		remainder = ft_strdup("");
	}
	if (bytes == 0)
	{
		*line = ft_strdup(remainder);
		free(remainder);
		remainder = NULL;
	}
	return (bytes);
}

/* not a part of assignment */

#include <stdio.h>
#include <string.h>

int main(void)
{
	int		r;
	char	*line;

	line = NULL;
	while ((r = get_next_line(&line)) > 0)
	{
		printf("[%s]\n", line);
		free(line);
		line = NULL;
	}
	printf("[%s]", line);
	free(line);
	line = NULL;
}
