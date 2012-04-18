#include <stdio.h>

int main()
{
	char s[1024];
	int i;

	while (scanf("%s", &s) != EOF)
	{
		i = 0;
		while (*(s + i))
		{
			if (*(s + i) == 'Z')
			{
				putchar('Z');
				*(s + i) = ' ';
			}
			i++;
		}
		i = 0;
		while (*(s + i))
		{
			if (*(s + i) == 'O')
			{
				putchar('O');
				*(s + i) = ' ';
			}
			i++;
		}
		i = 0;
		while (*(s + i))
		{
			if (*(s + i) == 'J')
			{
				putchar('J');
				*(s + i) = ' ';
			}
			i++;
		}
		i = 0;
		while (*(s + i))
		{
			if (*(s + i) == '7')
			{
				putchar('7');
				*(s + i) = ' ';
			}
			i++;
		}
		i = 0;
		while (*(s + i))
		{
			if (*(s + i) != ' ')
				putchar(*(s + i));
			i++;
		}
		putchar('\n');
	}

	return 0;
}
