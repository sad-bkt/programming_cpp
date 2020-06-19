#include <iostream>
#include <string>

using namespace std;

//D

template <typename T>
T pow(T a, int n) {
	T res = 1;
	for (int i = 0; i < n; i++)
		res *= a;
	return res;
}
// G

class BaseException : public exception {
public:
	explicit BaseException(const string &msg = "") {
		cerr << msg;
	}
};

class QueueOverflow : public BaseException {
public:
	explicit QueueOverflow(int index, int N) :
		BaseException("Queue overflow, index = " + to_string(index) + ", but max size = " + to_string(N) + "\n") {}
};

class QueueIndexOutOfRange : public BaseException {
public:
	explicit QueueIndexOutOfRange(int index) :
		BaseException("Index out of range = " + to_string(index) + "\n") {}
};

class QueueEmpty : public BaseException {
public:
	explicit QueueEmpty() :
		BaseException("Queue empty, can't pop the element\n") {}
};

template<int N, class T>
class Queue {
private:
	int index;//указывает на следующий элемент
public:
	T *q;
	
	Queue() {
		q = (T *)calloc(sizeof(T), N);
		index = 0;
	}

	void push(T element) {
		if (index < 0)
			throw QueueIndexOutOfRange(index);
		else if (index >= N)
			throw QueueOverflow(index, N);
		else {
			*(q + index) = element;
			index++;
		}	
	}

	T pop() {
		if (index == 0)
			throw QueueEmpty();
		else
		{
			T el = q[0];
			for (int i = 0; i < index - 1; i++)
				q[i] = q[i + 1];
			index--;
			return el;
		}
	}
};

int main() {
	std::cout << pow(2, 3) << "\n";
	std::cout << pow(0.1, 3) << "\n";

	try
	{
		Queue<5, int> q1{}, q2{};

		q2.pop();

		for (int i = 0; i < 6; i++)
		{
			q1.push(i);
			cout << i << " ";
		}
	}
	catch (const QueueOverflow& ex)
	{
		cout << "ERROR!! QueueOverflow\n";
		cout << ex.what() << "\n";
	}
	catch (const QueueIndexOutOfRange& ex)
	{
		cout << "ERROR!! QueueIndexOutOfRange\n";
		cout << ex.what() << "\n";
	}
	catch (const QueueEmpty& ex)
	{
		cout << "ERROR!! QueueEmpty\n";
		cout << ex.what() << "\n";
	}
	catch (const std::exception& ex)
	{
		cout << "ERROR!! exception\n";
		cout << ex.what() << "\n";
	}
	

	system("pause");
	return 0;
}