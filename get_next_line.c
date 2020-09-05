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

/* delete before upload */

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
