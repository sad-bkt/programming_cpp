#include <iostream>
#include <string>
#include <clocale>
#include "Set.h"

using namespace std;
int const LENGTH = 10;//count of sets

class Menu 
{
public:
	Set arr[LENGTH];//массив указателей на сеты и ввод в форме номер сета, действие, аргументы
	string st;
	int x, number_of_set;
	Menu()
	{
		st = "insert";
		number_of_set = 0;
		x = 100;
	}
	~Menu() = default;
	void actions()
	{
		cout << "The request has the form:\n"
			"<number of set> <action> <value>\n"
			"where <number of set> in [0..9]\n"
			"<action> in {insert, delete, exist} and <value> is integer in [-10^9 .. 10^9]\n"
			"<action> in {union, intersection} and <value>(number_of _set) in [0..9]\n"
			"";
	}
	void options()
	{
		if (st == "insert")
			arr[number_of_set].insert(x);
		else if (st == "delete")
			arr[number_of_set].del(x);
		else if (st == "exist")
		{
			if (arr[number_of_set].exist(x))
				cout << "true\n";
			else
				cout << "false\n";
		}
		else if (st == "union")
		{
			Set s;
			s = s.unions(arr[number_of_set], arr[x]);
			for (int i = 0; i < s.set.size(); i++)
				if (s.set[i] != NULL)
					cout << s.set[i]->value << " ";
			cout << endl;
		}
		else if(st == "intersection")
		{
			Set s;
			s = s.intersection(arr[number_of_set], arr[x]);
			for (int i = 0; i < s.set.size(); i++)
				if (s.set[i] != NULL)
					cout << s.set[i]->value << " ";
			cout << endl;
		}
		else
		{
			cout << "Invalid input" << endl;
		}
	}

	void work()
	{
		while (cin >> number_of_set)
		{
			cin >> st;
			cin >> x;
			options();
		}
	}
};
int main()
{
	setlocale(LC_ALL, "Russian");

	//**s = new Set(0, NULL, NULL);
	// list *set[SIZE]; 
	//Set **set = (set **)calloc(SIZE, sizeof(Set));

	/*for (int i = 0; i < LENGTH; i++) {
		Set *a = new Set();
		arr[i] = new Set();
	}*/

	Menu m;
	m.actions();
	m.work();
	system("pause");
	return 0;
}

