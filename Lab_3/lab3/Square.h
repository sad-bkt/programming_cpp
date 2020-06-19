#pragma once
#include<cmath>
#include<stack>
#include<iostream>

//task 2

struct Point
{
	int x;
	int y;
};

class Square
{

private:
	Point p;//left higher corner
	int l;
	int angle;

public:

	Square();
	~Square();
	Square(int l_, Point p_, double angle_);

	bool operator==(Square &other) const
	{
		return this->l == other.l;
	}

	bool operator!=(Square &other) const
	{
		return this->l != other.l;
	}

	bool operator<(Square &other) const
	{
		return this->l < other.l;
	}

	bool operator>(Square &other) const
	{
		return this->l > other.l;
	}

	void increase(int r);
	void add_vector(Point v);
};

//task 5

class Stack
{
private:
	std::stack <int> s;

public:
	
	Stack();
	~Stack();

	void operator<<(int &a)
	{
		this->s.push(a);
	}
	void operator<<(int a)
	{
		this->s.push(a);
	}

	int operator>>(int &a)
	{
		a = this->s.top();
		s.pop();
		return a;
	}

	void print();
};