#pragma once

// Lista encadeada com elementos repetidos;

template <typename T>
class LinkedList
{
private:
	struct Node
	{
		T info;
		int index;
		struct Node* next;
	};

	Node* head;
	int sizeList;

public:
	LinkedList();
	bool insertAfter(int pos, T info);
	bool insertBefore(int pos, T info);
	void remove(int pos);
	bool empty();
	bool size();
};