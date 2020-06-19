//2, 4, 7
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>

using namespace std;


//2
//возвращает true, если хотя бы один из элементов диапазона
//удовлетворяет некоторому предикату.Иначе false
template<class Object, class Pred>
bool any_of(Object &object, Pred func)
{
	typename Object::iterator it = object.begin();
	while (it != object.end())
	{
		if (func(*it))
			return true;
		it++;
	}
	return false;
}

//4
//one_of - возвращает true, если ровно один элемент диапазона удовлетворяет
//некоторому предикату.Иначе false
template<class Object, class Pred>
bool one_of(Object &object, Pred func)
{
	class Object::iterator it = object.begin();
	int count = 0;
	while (it != object.end() && count < 2)
	{
		if (func(*it))
			count++;
		it++;
	}
	if (count == 1)
		return true;
	else
		return false;
}

//7
//find_not - находит первый элемент, не равный заданному
template<class Object>
//typename iterator_traits<Object>::value_type find_not(Object object, T x)
auto find_not(Object& object, typename Object::value_type x)
{
	typename Object::iterator it = object.begin();

	while (it != object.end())
	{
		if (*it != x)
			return it;
		it++;
	}
	return it;
}

template<class Object>
void print(Object object)
{
	typename Object::const_iterator it = object.begin();
	while (it != object.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}


class Point
{
public:
	double x, y;

	Point(double x_, double y_) :
		x(x_),
		y(y_)
	{
	}
	bool operator==(const Point &p) const
	{
		return (this->x == p.x) && (this->y == p.y);
	}

	bool operator<(const Point &p) const
	{
		return (this->x < p.x) || (this->y < p.y);
	}

	bool operator!=(const Point &p) const
	{
		return (this->x != p.x) || (this->y != p.y);
	}

	/*ostream& operator<<(const Point &p) const
	{
		cout << p.x << " " << p.y;
		return cout;
	}*/
};

std::ostream& operator<<(std::ostream &out, const Point &p)
{
	out << "(" << p.x << ", " << p.y << ")";
	return out;
}

class Compare {
public:
	bool operator()(Point p) {
		return p == Point(0, 1);
	}
};

//template<class T, class N>
bool equalN(const int& x)
{
	return x == 2;
}

bool funk(const Point& p)
{
	return p.x == 1 && p.y == 1;
}

int main()
{
	vector<int> v = { 5, 4, 2, 2, 1, 0 };
	print(v);
	cout << any_of(v, equalN) << endl;
	cout << one_of(v, equalN) << endl;
	cout << *(find_not(v, 4)) << endl;

	cout << endl;

	set<Point> s;
	/*
	s.push({ 0, 0 });
	s.push({ 1, 1 });
	s.push({ 0, 1 });
	s.push({ 0, 0 });
	s.push({ 0, 1 });
	*/
	s.insert({ 0, 0 });
	s.insert({ 1, 1 });
	s.insert({ 0, 1 });
	s.insert({ 0, 0 });
	s.insert({ 0, 1 });
	print(s);
	cout << any_of(s, Compare()) << endl;//функциональный объект
	cout << any_of(s, funk) << endl;//функция //подумать, можно ли с аргументом
	cout << one_of(s, funk) << endl;
	cout << *(find_not(s, { 0,0 })) << endl;

	system("pause");
	return 0;
}