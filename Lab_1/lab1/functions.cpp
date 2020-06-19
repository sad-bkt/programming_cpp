#include <algorithm>
#include <vector>

void _3(int &a, int &b)
{
	if (a > b)
		a = a % b;
	else
		b = b % a;
}

void _3(int *a, int *b)
{
	if (*a == 0 || *b == 0)
	{
		*a = 0;
		*b = 0;
	}
	else if (*a > *b)
		*a %= *b;
	else
		*b %= *a;
}

void _8(double &c)
{
	c = 1 / c;
}

void _8(double *c)
{
	*c = 1 / *c;
}

void _11(double &radius, double &delta)
{
	radius -= delta;
}

void _11(double *radius, double *delta)
{
	*radius -= *delta;
}

void _16(int &n, int &m, int &i1, int &i2, std::vector<std::vector <int> > &matrix)//int((&matrix))[100][100] //link
{
	for (int j = 0; j < m; j++)
	{
		int t = matrix[i1][j];
		matrix[i1][j] = matrix[i2][j];
		matrix[i2][j] = t;
	}
}

void _16(int n, int m, int i1, int i2, std::vector<std::vector <int>> *matrix)//pointer
{
	for (int j = 0; j < m; j++)
	{
		int t = (*matrix)[i1][j];
		(*matrix)[i1][j] = (*matrix)[i2][j];
		(*matrix)[i2][j] = t;
	}
}