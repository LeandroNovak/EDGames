#include "LinkedList.h"



template<typename T>
LinkedList<T>::LinkedList()
{
	head = nullptr;
	sizeList = 0;
}

template<typename T>
bool LinkedList<T>::insertAfter(int pos, T info)
{
	if (empty())
	{
		head = new Node;
		head->info = info;
		head->pos = sizeList;
		head->next = nullptr;
		sizeList++;
		return true;
	}
	else
	{
		if (pos < sizeList)
		{
			Node* aux;
			aux = head;
			while (aux->pos != pos)
			{
				aux = aux->next;
			}
			Node* newNode = new Node;
			newNode->info = info;
			newNode->next = aux-> next;
			newNode->pos = 
		}
		else
		{
			return false;
		}

	}
}

template<typename T>
bool LinkedList<T>::insertBefore(int pos, T info)
{
}

template<typename T>
void LinkedList<T>::remove(int pos)
{
}

template<typename T>
bool LinkedList<T>::empty()
{
	return false;
}

template<typename T>
bool LinkedList<T>::size()
{
	return false;
}
