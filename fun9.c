#include<math.h>
#include<stdio.h>
#define MAX_N 1e+7
#include"fun9.h"
#define ERROR_N (-1)
int fun9(double (*f)(double),double a,double b, double eps,double *r)
{
	double h,sum1 = 0,sum2 = 0,fa,fb,s1 = 0,s2 = 0;
	int i,n = 1;
	h = (b - a)/2;
	fa = f(a); fb = f(b);

	for(i = 1;i<n;i++) //считаем sum1
	{
		s1 += f(a + 2*i*h);
		s2 += f(a + 2*i*h + h);
	}
	s2 = (s2 + f(a + h));
	sum1 = 2*s1/3*h + 4*s2/3*h + h*(fa + fb)/3;

	n = n*2;h = h/2;  //считаем sum2
	if(n>MAX_N)
		return -1;
	s1 = s1 + s2;
	for(i = 0;i<n;i++)
		sum2 = sum2 + f(a + 2*i*h + h);
	s2 = sum2;
	sum2 = sum2*h*4/3;
	sum2 += 2*s1/3*h + (fa + fb)*h/3;

	while(fabs(sum1 - sum2)>eps)
	{
		sum1 = sum2;sum2 = 0;
		n = n*2;h = h/2;
		if(n>MAX_N)
			return -1;
		s1 = s1 + s2;
		for(i = 0;i<n;i++)
			sum2 += f(a + 2*i*h + h);
		s2 = sum2;
		sum2 = sum2*h*4/3;
		sum2 += 2*s1/3*h + (fa + fb)*h/3;
	}
	*r = sum2;
	return n;	
}

