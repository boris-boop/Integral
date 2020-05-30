#include<math.h>
#include "root.h"
#include"solve.h"
#include "integral.c"

double f(double x);

int solve(double a,double b,double eps,double *x)
{
	double h,bk1,bk2,Eps = eps;
	int i,it;
	b = 10;
	h = 1/1000;
	for(i = 0;i<1000;i++)
	{
		it = fun(0,a,Eps,&bk1);
		it = fun(0,a+h,Eps,&bk2);
		if((bk1 - f(a))*(bk2 - f(a + h))<0)
			printf("a + h = %lf a = %lf\n",a + h,a);
		a += h;
	}
	*x = 10*b;
	return it;
}
double f(double x)
{
	return x*x - 1;
}
