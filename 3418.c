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
			min = 100;  /* the number of different bits of two ints in binary format must smaller than 100 */
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

/* return the number of different bits in the binary format of a and b
 * reference: http://blog.csdn.net/justpub/article/details/2292823
 */
int f(int a, int b)
{
	int n = 0;
	int x = a ^ b;

	x = x - ((x >> 1) & 0x55555555);    
	x = (x & 0x33333333) + ((x >> 2) & 0x33333333);    
	x = (x + (x >> 4)) & 0x0F0F0F0F;    
	x = x + (x >> 8);    
	x = x + (x >> 16);    
	return x & 0x0000003F;  

}

