#include <math.h>
#include "root.h"
#define MAX_IT 1e200
#define NOT_FOUND (-1)

int root(double (*f)(double), double a, double b, double eps, double *x)
{
	int it;
	double c, val_c, val_a = f(a);

	for( it = 0; it<MAX_IT; it++ )
	{
		c = (a + b)/2;
		val_c = f(c);

		if( fabs(val_c)<eps )
		{
			*x = c;
			return it;
		}

		if( (a<=c && a>=c) || (b<=c && b>=c) )
			break;

		if( val_a*val_c<=0 )
		{
			b = c;
		} else
		{
			a = c;
			val_a = val_c;
		}
	}

	return NOT_FOUND;
}
