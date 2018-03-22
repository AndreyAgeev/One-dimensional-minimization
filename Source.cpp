#include <math.h>
#include <iostream>
#include <stdio.h>
static int count_calls;
static double epsilon = 1e-1;
double function(double x)
{
	count_calls++;
	return x / (1 + pow(x, 2));
}
int F(int n)
{
	//F(n)
	int x = 1;
	//F(n-1)
	int y = 0;
	for (int i = 1; i < n; i++)
	{
		x += y;
		y = x - y;
	}
	return x;
}

int createN(double a, double b, double l = 0.5)
{
	int n = 0;
	while (F(n) <= fabs(b - a) / l)
		n++;
	std::cout << "n = " << n << std::endl;
	return n;
}
void fibb(double &a, double &b)
{
	static double n, x1, x2, y1, y2, l = 0.01;
	if (count_calls == 0)
	{
		std::cout << "fibb" << std::endl;
		n = createN(a, b, l);
		x1 = a + (b - a) * F(n - 2) / F(n);
		x2 = a + (b - a) * F(n - 1) / F(n);
		y1 = function(x1);
		y2 = function(x2);
	}
	if (n == 1)
		return;
	n--;
	if (n == 1)
		return;
	if (y1 > y2)
	{
		a = x1;
		x1 = x2;
		x2 = b - (x1 - a);
		y1 = y2;
		y2 = function(x2);
	}
	else
	{
		b = x2;
		x2 = x1;
		x1 = a + (b - x2);
		y2 = y1;
		y1 = function(x1);
	}

}
void  dih(double &a, double &b)
{
	if(count_calls == 0)
	    std::cout << "dih" << std::endl;
	double nx = (a + b) / 2, eps = (b-a) / 20;
	if (function(nx - eps) < function(nx + eps))
		b = nx;
	else
		a = nx;
}
void  gold(double &a, double &b)
{
	static double phi, x1, x2, f1, f2;
	if (count_calls == 0)
	{
		std::cout << "gold" << std::endl;
		phi = (1.0 + sqrt(5)) / 2.0;
		x1 = a + (b - a) / (phi + 1);
		x2 = b - (b - a) / (phi + 1);
		f1 = function(x1);
		f2 = function(x2);
	}
	if (f1 < f2)
	{
		b = x2;
		if (fabs(b - a) < epsilon)
			return;
		x2 = x1;
		f2 = f1;
		x1 = a + (b - a) / (phi + 1);
		f1 = function(x1);
	}
	else
	{
		a = x1; 
		if (fabs(b - a) < epsilon)
			return;
		x1 = x2;
		f1 = f2;
		x2 = b - (b - a) / (phi + 1);
		f2 = function(x2);
	}
}
void Call_method(double a, double b, void(*method)(double&, double&))
{
	int step = 0;
	count_calls = 0;
	while (fabs(b - a) > epsilon)
	{
        method(a, b);
		step++;
		printf("step %2d: (%5.3lf, %5.3lf)\n", step, a, b);
	}
	std::cout << count_calls << std::endl;
}

int main(void)
{
	double a = -2, b = -0.5;
	void ((*mass_meth[3]))(double&, double&) = {fibb, dih, gold};
	for (auto i = 0; i < 3; i++)
	{
		Call_method(a, b, mass_meth[i]);
	}
	return 0;
}