#include <stdio.h>

int main()
{
	int T;

	int d, t;
	double oldprice, newprice;

	scanf("%d",&T);
	while (T--)
	{
		scanf("%d%d",&d,&t);

		oldprice = 10;
		if (d > 3 && d < 10)
			oldprice += (d - 3)*2;
		if (d >= 10)
			oldprice += (14 + (d - 10) * 3);
		
		oldprice += t / 5.0 * 2;
		oldprice++;

		newprice = 11;
		if (d > 3 && d < 10)
			newprice += (d - 3) * 2.5;
		if (d >= 10)
			newprice += (7*2.5 + (d - 10) * 3.75);

		newprice += 2.5 * t / 4.0;

		printf("%d\n", (int)(newprice+0.5) - (int)(oldprice+0.5));
	}

	return 0;
}
