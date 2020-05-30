#include<math.h>
#include<stdio.h>
#define MAX_N 1e+7
#define ERROR_N (-1)
#include "integral.h"
#include"fun9.h"
double g(double x);
static double u;
static double kl;
int fun(double a,double b, double eps,double *r)
{
	double h,sum1 = 0,sum2 = 0,buf,fa,fb,s1 = 0,s2 = 0,Eps,ss1 = 0,ss2 = 0;
	int i,n = 1,it;
	Eps = eps;
	kl = b;
	h = (b - a)/2;
	u = a;
	it = fun9(&g,0,kl,Eps,&fa);
	u = b;
       	it += fun9(&g,0,kl,Eps,&fb);

	for(i = 1;i<n;i++) //считаем sum1
	{
		u = a + 2*i*h;
		it += fun9(&g,0,1,Eps,&s1);
		ss1 += s1;
		u = a + 2*i*h + h;
		it += fun9(&g,0,1,Eps,&s2);
		ss2 += s2;
	}
	u = a + h;
	fun9(&g,0,1,Eps,&buf);
	ss2 = (ss2 + buf);
	sum1 = 2*ss1/3*h + 4*ss2/3*h + h*(fa + fb)/3;

	n = n*2;h = h/2;  //считаем sum2
	if(n>MAX_N)
		return -1;
	ss1 = ss1 + ss2;
	for(i = 0;i<n;i++)
	{
		u = a + 2*i*h + h;fun9(&g,0,1,Eps,&buf);
		sum2 = sum2 + buf;
	}
	ss2 = sum2;
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
		{
			u = a + 2*i*h + h;
			fun9(&g,0,1,Eps,&buf);
			sum2 += buf;
		}
		s2 = sum2;
		sum2 = sum2*h*4/3;
		sum2 += 2*s1/3*h + (fa + fb)*h/3;
	}
	*r = sum2;
	return n;	
}
double g(double x)
{
	return sqrt(x*u*u + kl*kl/(1 + x*x));
}
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
