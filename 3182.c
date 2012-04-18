#include <stdio.h>

int F(int n)
{
	int m;
	int t;

	if (n == 1)
		return 1;
	else if (n == 2)
		return 2;
	else
	{
		m = F(n - 1);
		t = F(n - 2);
		m += (2 * t) + 1;
		return m;
	}
}

int main()
{
	int T;
	int n;

	scanf("%d",&T);
	while (T--)
	{
		scanf("%d",&n);
		printf("%d\n",F(n));
	}
}