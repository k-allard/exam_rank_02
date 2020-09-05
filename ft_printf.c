#include <stdlib.h>				//for malloc
#include <unistd.h>				//for write
#include <stdarg.h>				//for variable num of args

int g_result;					//num of chars printed
int g_width;
int g_prec;

static void ft_putchar(char c)
{
	write(1, &c, 1);
	g_result++;
}

static void ft_putstr(char *str, int len)
{
	while (*str && len > 0)
	{
		ft_putchar(*str);
		str++;
		len--;
	}
}

int ft_strlen(char *s)
{
	int len = 0;
	while (s[len])
		len++;
	return len;
}

static char *ft_itoa(unsigned long nbr, int base)
{
	int len = 0;
	char *str = NULL;

	/*will count num of digits*/
	unsigned long temp_nbr = nbr;
	if (nbr == 0)
		len++;
	while (temp_nbr > 0)
	{
		temp_nbr /= base;
		len++;
	}

	str = malloc(len + 1);
	str[len] = '\0';
	while (len > 0)						//will fill our array of chars starting from the end
	{
		str[len - 1] = nbr % base;
		if (nbr % base > 9)				//means that we are dealing with hex
			str[len - 1] += 'a' - 10;
		else
			str[len - 1] += '0';
		nbr /= base;
		len--;
	}
	return (str);
}

static void ft_printf_x(unsigned long nbr)
{
	char *str;
	str = ft_itoa(nbr, 16);
	int len = ft_strlen(str);

	if (g_prec != -1 && g_prec > len)
		len = g_prec;
	while (g_width > len)
	{
		ft_putchar(' '); 
		g_width--; 
	}
	while (len > ft_strlen(str))
	{
		ft_putchar('0'); 
		len--; 
	}
	ft_putstr(str, ft_strlen(str));
	free(str);
}

static void ft_printf_d(long nbr)
{
	char *str;
	int minus = 0;
	
	if (nbr < 0)
	{
		minus = 1; 
		nbr *= -1; 
	}
	str = ft_itoa(nbr, 10);
	int len = ft_strlen(str);

	if (g_prec != -1 && g_prec > len)
		len = g_prec;
	if (minus == 1 && g_width > 0)
		g_width--;
	while (g_width > len)
	{ 
		ft_putchar(' '); 
		g_width--; 
	}
	if (minus == 1)
		ft_putchar('-');
	while (len > ft_strlen(str))
	{
		ft_putchar('0'); 
		len--; 
	}
	ft_putstr(str, ft_strlen(str));
	free(str);
}

static void ft_printf_s(char *str)
{
	int len = ft_strlen(str);

	if (g_prec != -1 && g_prec < len)
		len = g_prec;
	while (g_width > len)
	{ 
		ft_putchar(' '); 
		g_width--; 
	}
	ft_putstr(str, len);
}

int ft_printf(const char *str, ... )
{
	g_result = 0;
	int i = 0;
	va_list ap;

	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			g_width = 0;
			g_prec = -1;								//flag -1 means that precision is not determined
			while (str[i] >= '0' && str[i] <= '9')		//parsing of width
			{
				g_width = g_width * 10 + (str[i] - '0');
				i++;
			}
			if (str[i] == '.')
			{
				g_prec = 0;								//precision is found!
				i++;
				while (str[i] >= '0' && str[i] <= '9')	//parsing of precision
				{
					g_prec = g_prec * 10 + (str[i] - '0');
					i++;
				}
			}
			if (str[i] == 's')
				ft_printf_s(va_arg(ap, char *));
			else if (str[i] == 'x')
				ft_printf_x(va_arg(ap, unsigned int));
			else if (str[i] == 'd')
				ft_printf_d(va_arg(ap, int));
			else
				ft_putchar(str[i]);
		}
		else
			ft_putchar(str[i]);
		i++;
	}
	va_end(ap);
	return (g_result);
}

/* delete before upload */

#include <stdio.h>

int main(void)
{
	printf("    [%10.2s]\n", "toto");
	ft_printf("MY: [%10.2s]\n\n", "toto");
	printf("    Magic [%s] is [%10.5d] [%10.5d]\n", "number", -42, -42);
	ft_printf("MY: Magic [%s] is [%10.5d] [%10.5d]\n\n", "number", -42, -42);
	printf("    Hexadecimal for [%.5d] is [%10.5x]\n", -42, 42);
	ft_printf("MY: Hexadecimal for [%.5d] is [%10.5x]\n\n", -42, 42);
}
