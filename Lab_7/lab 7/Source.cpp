#include <iostream>
#include <vector>
#include "RingBuffer.h"

using namespace std;

int main()
{
	RingBuffer<int> buf = RingBuffer<int>(10);
	buf.push_front(0);
	buf.push_back(1);
	buf.push_front(2);
	buf.push_back(3);
	buf.push_front(4);
	buf.push_back(5);
	buf.push_front(6);
	buf.push_back(7);
	buf.push_front(8);
	buf.push_back(9);
	buf.print();

	buf.pop_front();
	buf.print();

	buf.pop_back();
	buf.print();

	buf.change_capacity(20);

	for (auto it = buf.begin(); it != buf.end(); ++it)
		*it = *it + 1;
	buf.print();

	sort(buf.begin(), buf.end());
	buf.print();

	cout << *(find(buf.begin(), buf.end(), 5)) << endl;

	fill(buf.begin(), buf.end(), 1);
	buf.print();

	//system("pause");
	return 0;
}