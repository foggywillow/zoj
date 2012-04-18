#include <stdio.h>

int main()
{
	int T;
	int start, end;
	int count;
	int i, j;

	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &start, &end);
		count = 0;
		for (i = start; i <= end; i++)
		{
			for (j = 1; j <= 9; j++)
			{
				if (i % 100 == (j * j))
				{
					count++;
					break;
				}
			}
			for (j = 10; j <= 12; j++)
			{
				if (i % 1000 == (j * j))
				{
					count++;
					break;
				}
			}
		}

		printf("%d\n", count);
	}

	return 0;
}
