#pragma once

#include <iostream>
#include <algorithm>

using namespace std;

template <class T>
class RingBuffer {


private:
	size_t size;
	size_t capacity;
	T *it_begin;
	T *it_end;
	T *arr_begin;
	T *arr_end;


public:

	struct Position
	{
		size_t size;
		size_t capacity;
		T *arr_begin;
		T *arr_end;
		T *it_begin;
		T *it_end;
		T* p;//указатель на сам итератор

		explicit Position(T* p, T* arr_begin, T* arr_end, T* it_begin, T* it_end, size_t size, size_t capacity)
			: p(p),
			arr_begin(arr_begin),
			arr_end(arr_end),
			it_begin(it_begin),
			it_end(it_end),
			size(size),
			capacity(capacity)
		{}

		T& value() const
		{
			return *p;
		}

		bool equal(const Position& other) const
		{
			return p == other.p;
		}

		void increment()
		{
			if (p == arr_end - 1)
				p = arr_begin;
			else
				p++;
		}

		void decrement()
		{
			if (p == arr_begin)
				p = arr_end - 1;
			else
				p--;
		}

		void move_n(int n)
		{
			if (n > 0)
				for (int i = 0; i < n; ++i) {
					this->increment();
				}
			else
				for (int j = 0; j < -n; ++j) {
					this->decrement();
				}
		}

		int distance(const Position& other) const
		{
			size_t i = 0;
			T* it = it_begin;
			while (it != this->p && it != other.p) //it != it_end &&
				it++;
			if (it == this->p)
				while (it != other.p) {
					it++;
					i++;
				}
			else
				while (it != this->p)
				{
					it++;
					i--;
				}
			return i;
			//return other.p - this->p;

		}
	};

	struct iterator : std::iterator<std::random_access_iterator_tag, T>
	{

		Position pos;
		iterator(Position pos) :
			pos(pos)
		{}

		iterator() = default;
		iterator(const iterator&) = default;
		iterator& operator=(const iterator&) = default;
		~iterator() = default;
		T& operator*() const
		{
			return pos.value();
		}
		iterator& operator++()
		{
			pos.increment();
			return *this;
		}
		iterator operator++(int)
		{
			auto old = *this;
			++(*this);
			return old;
		}

		//T* operator->() const{};

		iterator& operator--()
		{
			pos.decrement();
			return *this;
		}
		iterator operator--(int)
		{
			auto old = *this;
			--(*this);
			return old;
		}
		T& operator[](int n) const
		{
			auto tmp = *this;
			tmp += n;
			return *tmp;
		}
		iterator& operator+=(int n)
		{
			pos.move_n(n);
			return *this;
		}
		iterator& operator-=(int n)
		{
			return *this += -n;
		}

		bool operator==(const iterator& it) const
		{
			return this->pos.equal(it.pos);
		}
		bool operator!=(const iterator& it) const
		{
			return !(this->operator==(it));
		}

		bool operator<(const iterator& it) const
		{
			return this->pos.distance(it.pos) > 0;
		}

		bool operator>(const iterator& it) const
		{
			return it.operator<(*this);
		}
		bool operator<=(const iterator& it) const
		{
			return !(it.operator>(*this));
		}
		bool operator>=(const iterator& it) const
		{
			return !(this->operator<(it));
		}
		iterator operator+(int n)
		{
			iterator new_it(this->pos);
			new_it.operator+=(n);
			return new_it;
		}

		friend iterator operator+(int n, iterator it)
		{
			return it + n;
		}

		iterator operator-(int n)
		{
			iterator new_it(this->pos);
			new_it.operator-=(n);
			return new_it;
		}
		int operator-(const iterator& it)
		{
			return it.pos.distance(this->pos);
		}
	};

	// Операции, необходимые для всех категорий итераторов.
	void swap(iterator& a, iterator& b)
	{
		swap(a.pos, b.pos);
	}

	RingBuffer()
	{
		size = 0;
		capacity = 100;
		arr_begin = (T*)calloc(sizeof(T), 2 * capacity);
		if (arr_begin == nullptr)
			throw bad_alloc();
		arr_end = arr_begin + capacity;
		it_begin = arr_begin;
		it_end = arr_begin;
	}

	RingBuffer(int cap)
	{
		size = 0;
		capacity = cap + 1;
		arr_begin = (T*)calloc(sizeof(T), 2 * capacity);
		if (arr_begin == nullptr)
			throw bad_alloc();
		arr_end = arr_begin + capacity;
		it_begin = arr_begin;
		it_end = arr_begin;
	}

	~RingBuffer()
	{
		if (arr_begin)
			free(arr_begin);
		//if (arr_end)
			//free(arr_end);
	}

	void push_front(T v)//вставка в начало
	{
		size++;
		if (size > capacity)
			throw "can't push the element in the baff";
		if (it_begin == arr_begin)
			it_begin = arr_end;
		it_begin--;
		*it_begin = v;
	}
	void push_back(T v)//вставка в конец
	{
		size++;
		if (size > capacity)
			throw "can't push the element in the baff";
		*it_end = v;
		if (it_end == arr_end)
			it_end = arr_begin;
		else
			it_end++;
	}
	void pop_front()//удаление из начала
	{
		if (size == 0)
			throw "can't pop the element from the baff";
		if (it_begin + 1 == arr_end)
			it_begin = arr_begin;
		else
			it_begin++;
		size--;
	}
	void pop_back()//удаление из конца
	{
		if (size == 0)
			throw "can't pop the element from the baff";
		if (it_end == arr_begin)
			it_end = arr_end;
		else
			it_end--;
		size--;
	}
	void push_it(T v)//вставка по итератору
	{
		size++;
		if (size > capacity)
			throw "can't push the element in the baff";
	}
	void pop_it()//удаление по итератору
	{
		if (size == 0)
			throw "can't pop the element from the baff";
		size--;
	}

	iterator begin()
	{
		return iterator(Position(it_begin, arr_begin, arr_end, it_begin, it_end, size, capacity));
	}

	iterator end()
	{
		return iterator(Position(it_end, arr_begin, arr_end, it_begin, it_end, size, capacity));
	}
	void change_capacity(int cap)
	{
		if (cap < size)
			cap = size;
		capacity = cap + 1;
		T* new_arr = (T*)calloc(sizeof(T), 2 * capacity);
		T* it = it_begin;
		T* it_new = new_arr;
		while (it != arr_end && it != it_end)
		{
			*it_new = *it;
			it++;
			it_new++;
		}
		it = arr_begin;
		while (it != it_end)
		{
			*it_new = *it;
			it++;
			it_new++;
		}
		free(arr_begin);
		arr_begin = new_arr;
		arr_end = arr_begin + capacity;
		it_begin = arr_begin;
		it_end = it_begin + size;
	}
	T& operator[](int index) //доступ по индексу
	{
		return *(it_begin + index);
	}

	void print()
	{
		for (RingBuffer<T>::iterator it = this->begin(); it != this->end(); ++it)
			cout << *it << " ";
		cout << "\n";
	}
};

