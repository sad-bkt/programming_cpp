#pragma once
#include <string>
#include <vector>
#include<malloc.h>
#include<stdlib.h>
#include<algorithm>
#include<vector>
#include<iostream>

struct list
{
	int value;
	list *prev;
	list *next;
};

class Set
{
private:
	

public:
	/*int value;
	Set *prev;
	Set *next;*/

	
	int SIZE;
	std::vector <list *> set;

	Set();
	Set(int max_size);
	//Set(int i, Set *p, Set *n);
	Set(const Set &other);
	~Set();
	list *add(int x, list *p);
	list *create(int x);
	int hash1(int x);
	void insert(int x);
	void del(int x);
	bool exist(int x);
	Set intersection(Set s1, Set s2);
	Set unions(Set s1, Set s2);
};

