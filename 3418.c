#include <stdio.h>

int f(int,int);

int main()
{
	int T;
	int m,n;
	int A[100];
	int a,b;
	int i,j;
	int min;
	int t;

	scanf("%d",&T);
	while (T--)
	{
		scanf("%d%d",&m,&n);
		for (i = 0; i < m; i++)
		{
			scanf("%d",&A[i]);
		}
		for (j = 0; j < n; j++)
		{
			scanf("%d",&b);
			min = 100;
			a = 1000001;
			for (i = 0; i < m; i++)
			{
				t = f(A[i],b);
				if (t <= min)
				{
					if (t == min && A[i] >= a)
					{
						continue;
					}
					min = t;
					a = A[i];
				}
			}
			printf("%d\n",a);
		}
	}

	return 0;
}

int f(int a, int b)
{
	int n = 0;
	int t = a ^ b;

	while (t > 0)
	{
		n += (t & 1);
		t >>= 1;
	}

	return n;
}

