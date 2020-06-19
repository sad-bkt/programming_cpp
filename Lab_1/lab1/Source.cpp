#include <iostream>
#include <vector>

/*struct Matrix
{
	int const H, W;
	int a[H][W];
};*/

struct Circle
{
	double radius = 0;
};

#include "Header.h" //???
using namespace std;

int main() 
{
	int a, b;
	std::cout << "Enter integer a, b" << std::endl;
	std::cin >> a >> b;
	_3(a, b);
	std::cout << a << " " << b << std::endl;
	_3(&a, &b);
	std::cout << a << " " << b << std::endl;


	double c;
	std::cout << "Enter real number" << std::endl;
	std::cin >> c;
	_8(c);
	std::cout << c << std::endl;
	_8(&c);
	std::cout << c << std::endl;


	Circle circle;
	double delta;
	std::cout << "Enter radius and delta" << std::endl;
	std::cin >> circle.radius >> delta;
	_11(circle.radius, delta);
	std::cout << circle.radius << std::endl;
	_11(&circle.radius, &delta);
	std::cout << circle.radius << std::endl;


	std::cout << "Enter n, m, numbers of 2 lines and matrix" << std::endl;
	int n, m, i1, i2, x;
	std::vector<std::vector <int> > v(100, std::vector <int>(100));
	std::cin >> n >> m >> i1 >> i2;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			std::cin >> v[i][j];
		}
	std::cout << std::endl;
	_16(n, m, i1, i2, v);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			std::cout << v[i][j] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
	_16(n, m, i1, i2, &v);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			std::cout << v[i][j] << " ";
		std::cout << std::endl;
	}
	
	// массив

	/*std::cout << "Enter n, m, numbers of 2 lines and matrix" << std::endl;
	int n, m, i1, i2, matrix[100][100];
	std::cin >> n >> m >> i1 >> i2;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			std::cin >> matrix[i][j];

	_16_link(n, m, i1, i2, matrix);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			std::cout << matrix[i][j] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
	_16_pointer(n, m, i1, i2, &matrix);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			std::cout << matrix[i][j] << " ";
		std::cout << std::endl;
	}*/

	system("pause");
	return 0;
}