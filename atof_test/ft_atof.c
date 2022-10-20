#include <stdio.h>
static float ft_fastexp_helper(float x, unsigned int pow, float acc)
{
	if (pow == 0) 
		return (acc);
	if (pow % 2 == 0)
		return (ft_fastexp_helper(x * x, pow / 2, acc));
	if (pow % 2 == 1)
		return (ft_fastexp_helper(x * x, pow / 2, acc * x));
}

float ft_fastexp(float x, unsigned int pow)
{ 
	return (ft_fastexp_helper(x, pow, 1.0));
}

float	ft_atof(char *rep)
{
	int		ten_pow = 0; // divide final result by 10 to this power
	int		found_dot = 0;
	float 	acc = 0.0;

	while (*rep)
	{
		if (*rep == '.')
			found_dot = 1;
		else
		{
			if (found_dot)
				++ten_pow;
			acc *= 10.0;
			acc += *rep - '0';
		}
		++rep;
		// TODO if near overflowing, divide by 10 ^ ten_pow, and reset ten_pow
	}	
	float hundred = 100.0;
	float exp = ft_fastexp(10.0, ten_pow);
	printf("acc %f %x, div %f %x, 100 %x\n",
		   acc, 	   
		   *(unsigned int *) &acc,
		   exp,
		   *(unsigned int *) &exp,
		   *(unsigned int *) &hundred
		   );

// 	return (acc / ft_fastexp(10, ten_pow));
	return (92854.0 / 100.0);
}

float wtf()
{	return (92854.0 / 100.0);}

// int main()
// {
// 	float test = 92854.0 / 100.0;
// 	printf("%f \n", test);
// 	printf("div %f, atof %f, exp %f\n",
// 		92854.0 / 100.0,
// 		ft_atof("928.54"),
// 		ft_fastexp(10.0, 2));
// 	printf("wtf %f\n", wtf());
// // 	printf("%f\n", ft_atof("928.54"));
// 	return (0);
// }

#include <stdlib.h>
int main()
{
	printf("%f %f\n", atof("928.54"), (float) atof("928.54"));
	// output : 28.540000 928.539978 
}
