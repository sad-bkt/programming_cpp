#include "Set.h"


list * Set::add(int x, list *p)
{
	auto node = new list;
	node->value = x;
	node->prev = p;
	node->next = nullptr;
	return node;
}

list * Set::create(int x)
{
	auto node = new list;
	node->value = x;
	node->prev = nullptr;
	node->next = nullptr;
	return node;
}

Set::Set() :
	SIZE(11)
{
	//list **set = (list **)calloc(SIZE, sizeof(list));
	/*this->value = 0;
	this->prev = NULL;
	this->next = NULL;*/
	//list **set = (list **)calloc(SIZE, sizeof(list *)); //????
	//Set *set = new Set();
	//std::vector<list *> set;
	set.resize(SIZE);
	for (int i = 0; i < SIZE; ++i)
	{
		set[i] = nullptr;
	}
		
	//std::cout << "вызвался стандартный конструктор" << this << std::endl;
}

Set::Set(int max_size) :
	SIZE(max_size)
{
	//list *set[SIZE];
	//list **set = (list **)calloc(SIZE, sizeof(list *));
	set.resize(SIZE);
	for (int i = 0; i < SIZE; ++i)
	{
		set[i] = nullptr;
	}

	std::cout << "вызвался конструктор макс размер" << this << std::endl;
}

/*Set::Set(int i = 0, Set *p = NULL, Set *n = NULL) :
	value(i),
	prev(p),
	next(n)
{
	std::cout << "вызвался конструктор " << this << std::endl;
}*/

Set::Set(const Set &other)
{
	this->SIZE = other.SIZE;
	this->set = std::vector<list *>(this->SIZE);
	//[this->SIZE];
	for (int i = 0; i < this->SIZE; ++i)
	{
		this->set[i] = other.set[i];
	}
	//std::cout << "вызвался конструктор копирования " << this << std::endl;
}

Set::~Set()
{
	set.clear();
//	delete &SIZE;
	//std::cout << "вызвался деструктор " << std::endl;
}

int Set::hash1(int x)
{
	if (x > 0)
		return x % SIZE;
	else
		return ((abs(x) / SIZE + 1) * SIZE + x) % SIZE;
}

void Set::insert(int x)
{
	int h = hash1(x);
	if (set[h] == nullptr)
		set[h] = create(x);
	else
	{
		list *p = set[h];
		if (p->value == x)
			return;
		while (p->next != nullptr)
		{
			if (p->next->value == x)
				return;
			p = p->next;
		}
		p->next = add(x, p);
	}
}

void Set::del(int x)
{
	int h = hash1(x);
	if (set[h] == nullptr)
		return;
	else
	{
		list *p = set[h];
		if (p->value == x)
		{
			set[h] = p->next;
			free(p);
			return;
		}
		while (p->next != nullptr)
		{
			if (p->next->value == x)
			{
				p = p->next;
				p->prev = p->next;
				p->next = p->prev;
				free(p);
				return;
			}
			p = p->next;
		}
		return;
	}
}

bool Set::exist(int x)
{
	int h = hash1(x);
	if (set[h] == nullptr)
		return false;
	else
	{
		list *p = set[h];
		if (p->value == x)
			return true;
		while (p->next != nullptr)
		{
			if (p->next->value == x)
				return true;
			p = p->next;
		}
		return false;
	}
}
Set Set::intersection(Set s1, Set s2)
{
	//Set s;
	Set s = Set(s1.SIZE + s2.SIZE);
	for (int i = 0; i < s1.SIZE; ++i)
	{
		list *p = s1.set[i];
		while (p != nullptr)
		{
			if (s2.exist(p->value))
				s.insert(p->value);
			p = p->next;
		}
	}
	return s;
}

Set Set::unions(Set s1, Set s2)
{
	Set s = s1;
	for (int i = 0; i < s2.SIZE; i++)
	{
		list *p = s2.set[i];
		while (p != nullptr)
		{
			s.insert(p->value);
			p = p->next;
		}
		
	}
	return s;
}