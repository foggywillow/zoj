#include <stdio.h>

int main()
{
	int T;
	int n, i;
	int price;
	int first, second;
	int index;

	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		index = 0; first = second = 0;
		for (i = 1; i <= n; i++)
		{
			scanf("%d", &price);
			if (price > first)
			{
				index = i;
				second = first;
				first = price;
			}
			if (price > second && price < first)
			{
				second = price;
			}
		}
		printf("%d %d\n", index, second);
	}

	return 0;
}
