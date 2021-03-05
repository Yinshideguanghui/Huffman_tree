#pragma once
#include<iostream>
using namespace std;

enum Error_code { success, underflow, overflow, Range_error, not_present, fail };

template <class Node_entry>
struct Node		//½Úµã
{
	Node_entry entry;
	Node<Node_entry>* next;

	Node() {}
	Node(Node_entry entry_, Node<Node_entry>* link = NULL) :entry(entry_), next(link) {}
};

template<class List_entry>
class List		//±í
{
public:
	List() { count = 0; head = NULL; }
	List(const List<List_entry>& copy);
	//void operator = (const List<List_entry>& copy);
	~List() { clear(); }

	int size()const;
	bool empty()const;
	void clear();
	void traverse(void(*visit)(List_entry&));

	Error_code retrieve(int position, List_entry& x)const;
	//Error_code replace(int position, const List_entry& x);
	Error_code remove(int position, List_entry& x);
	Error_code insert(int position, const List_entry& x);
protected:
	int count;
	Node<List_entry>* head;
	Node<List_entry>* set_position(int position)const;
};