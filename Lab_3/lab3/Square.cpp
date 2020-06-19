#include "Square.h"

Square::Square() :
	l(1),
	angle(0.5),
	p({ 1, 1 })
{
}

Square::Square(int l_, Point p_, double angle_) :
	l(l_),
	angle(angle_),
	p(p_)
{
}

Square::~Square()
{
}

void Square::increase(int r)
{
	this->l += r;
	this->p.x -= r * sin(this->angle);
	this->p.y += r * cos(this->angle);
}

void Square::add_vector(Point v)
{
	this->p.x += v.x;
	this->p.y += v.y;
}



Stack::Stack()
{
}

Stack::~Stack()
{
	//delete s;
}

void Stack::print()
{
	std::cout << "Print: ";
	while (!s.empty())
	{
		std::cout << s.top() << " ";
		s.pop();
	}
	std::cout << "\n";
}