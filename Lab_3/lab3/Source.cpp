#include <iostream>
#include "Square.h"

int main()
{
	Square sq1(2, { 0,0 }, 0);
	Square sq2(2, { 0,1 }, 2);
	if (sq1 != sq2)
		std::cout << "==\n";
	Square sq3(1, { 0,1 }, 2);
	if (sq1.operator!=(sq3))
		std::cout << "!=\n";
	if (sq1.operator>(sq3))
		std::cout << ">\n";
	if (sq3.operator<(sq1))
		std::cout << "<\n";
	if(sq1==sq2)
		std::cout << "==\n";


	Stack st;
	st.operator<<(1);
	st.operator<<(2);
	int a;
	st.operator>>(a);
	std::cout << "\n" << a << "\n";
	st.print();

	st << 1;
	st << 2;
	st.print();

	system("pause");
	return 0;
}