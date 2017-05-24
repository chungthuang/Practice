// gcc -Wall -lc++ -o double_linked_list double_linked_list.cpp 

#include <assert.h>
#include <iostream>
#include "double_linked_list.h"

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList()
{
	// Create a sentinel node
	this->head = (Node<T>*)malloc(sizeof(Node<T>));
	this->head->key = SENTINEL_VAL;
	this->head->next = NULL;
	this->head->prev = NULL;
	this->tail = this->head;
	this->size = 0;
}

template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList<T>()
{
	clear();
}

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList const & other)
{
	copy(other);
}

template <typename T>
DoubleLinkedList<T> & DoubleLinkedList<T>::operator=(DoubleLinkedList<T> const & rhs)
{
	if(this != &rhs)
	{
		clear();
		copy(rhs);
	}
	return *this;
}

template <typename T>
RET_VALUE DoubleLinkedList<T>::insert(T key)
{
	this->tail->next = (Node<T>*)malloc(sizeof(Node<T>));
	if(this->tail->next == NULL)
	{
		return CANNOT_ALLOCATE;
	}
	this->tail->next->prev = this->tail; // Point back
	this->tail = this->tail->next;
	this->tail->key = key;
	this->tail->next = NULL;
	this->size++;
	return SUCCESS;
}

template <typename T>
RET_VALUE DoubleLinkedList<T>::remove(T key)
{
	if(this->size == 0)
	{	
		return EMPTY_LIST;
	}

	Node<T>* curr = this->head->next;
	Node<T>* prev = this->head;
	while(curr != NULL)
	{
		if(curr->key == key)
		{
			prev->next = curr->next;
			if(curr->next != NULL)
			{
				curr->next->prev = prev;
			}
			else
			{
				this->tail = prev;
#if DEBUG
				assert(curr != this->tail); 
#endif
			}
			free(curr);
			this->size--;
			return SUCCESS;
		}
		prev = curr;
		curr = curr->next;
	}
	return KEY_NOT_FOUND;
}

template <typename T>
RET_VALUE DoubleLinkedList<T>::reverse()
{
	if(this->size >= 2)
	{
		int count = 0;
		int first_key = this->head->next->key;
		int last_key = this->tail->key;
		Node<T>* curr = this->head->next;

		// First node becomes last node and last node becomes first node (not counting sentinel node)
		this->head->next = this->tail; 
		this->tail = curr;  
		// Swap next and prev pointer
		curr->prev = curr->next;
		curr->next = NULL;
		curr = curr->prev;
		while(curr->next != NULL)
		{
			Node<T>* temp = curr->next;
			curr->next = curr->prev;
			curr->prev = temp;
			curr = temp;
			count++;
		}
		curr->next = curr->prev;
		curr->prev = this->head; // points to sentinel node
#if DEBUG
		assert(this->head->next->key == last_key); // Make sure first key and last key are swapped
		assert(this->tail->key == first_key);
		assert(count == this->size-2);
#endif 
	}	
	return SUCCESS;		
}

template<typename T>
int DoubleLinkedList<T>::getSize()
{
	return this->size;
}

template<typename T>
void DoubleLinkedList<T>::sort()
{
	if(this->size > 1)
	{
		// The first node is the sentinel node
		this->head->next = mergeSort(this->head->next, this->size);
		this->head->next->prev = this->head;
		tail = this->head->next;
		int count = 1;
		while(tail->next != NULL)
		{
			tail = tail->next;
			count++;
		}
#if DEBUG
		assert(this->size == count);
		Node<T>* curr = this->tail;
		for(int i = 0; i < this->size; i++)
		{
			curr = curr->prev;
		}
		assert(curr == this->head);
#endif
	}
}

template <typename T>
void DoubleLinkedList<T>::printForward()
{
	int count = 0;
	Node<T>* curr = this->head->next;
	Node<T>* next;
	std::cout << "Forward:" << std::endl;
	while(curr != NULL)
	{
		std::cout << curr->key;
		next = curr->next;
		curr = next;
		count++;
	}
	std::cout << std::endl;
#if DEBUG
	assert(count == this->size);
#endif 
}

template <typename T>
void DoubleLinkedList<T>::printBackward()
{
	int count = 0;
	Node<T>* curr = this->tail;
	Node<T>* prev;
	std::cout << "Backward:" << std::endl;
	while(curr != this->head)
	{
		std::cout << curr->key;
		prev = curr->prev;
		curr = prev;
		count++;
	}
	std::cout << std::endl;
#if DEBUG
	assert(count == this->size);
#endif 
}

/************************* Private functions *************************/
template <typename T>
void DoubleLinkedList<T>::copy(DoubleLinkedList<T> const & other)
{
	Node<T> *curr, *prev, *other_curr = other.head;
	this->head = (Node<T>*)malloc(sizeof(Node<T>));
	this->head->key = other_curr->key;
	curr = this->head;
	prev = NULL;
	other_curr = other_curr->next;
	while(other_curr != NULL)
	{
		curr->next = (Node<T>*)malloc(sizeof(Node<T>));
		curr->next->key = other_curr->key;
		curr->prev = prev;
		prev = curr;
		curr = curr->next;
		other_curr = other_curr->next;
		this->size++;
	}
	this->tail = curr;
	curr->prev = prev;
	curr->next = NULL;
#if DEBUG
		printForward();
		std::cout << std::endl;
		printBackward();
		std::cout << std::endl;
		assert(this->size = other.size);
#endif
}

template <typename T>
void DoubleLinkedList<T>::clear()
{
	int count = 0;
	Node<T>* curr = this->head->next;
	Node<T>* next;
	while(curr != NULL)
	{
		next = curr->next;
		free(curr);
		curr = next;
		count++;
	}
#if DEBUGs
	assert(count == this.size);
#endif 
}

template <typename T>
Node<T>* DoubleLinkedList<T>::mergeSort(Node<T>* start, int length)
{
	if(length == 1)
	{
		return start;
	}
	int mid = length/2;
	Node<T>* second = split(start,mid);
	Node<T>* left = mergeSort(start,mid);
	Node<T>* right = mergeSort(second,length-mid); 
	return merge(left,right,mid,length-mid);

}

template <typename T>
Node<T>* DoubleLinkedList<T>::split(Node<T>* start, int splitIndex)
{ 
	Node<T>* curr = start;
	for(int i = 0; i < splitIndex; i++)
	{
#if DEBUG
		assert(start != NULL);
#endif
		curr = curr->next;
	}
	return curr;
}

template <typename T>
Node<T>* DoubleLinkedList<T>::merge(Node<T>* left, Node<T>* right, int left_length, int right_length)
{
#if DEBUG
	assert(left_length > 0);
	assert(right_length > 0);
	assert(left->key != SENTINEL_VAL);
	assert(right->key != SENTINEL_VAL);
#endif
	Node<T>* start, *curr, *prev; 
	if(left->key < right->key)
	{
		start = left;
		curr = left;
		left = left->next;
		left_length--;
	}
	else
	{
		start = right;
		curr = right;
		right = right->next;
		right_length--;
	}
	prev = start;
	curr->prev = NULL;
	while(left_length > 0 || right_length > 0)
	{
		if(left_length == 0)
		{
			curr->next = right; 
			right = right->next;
			right_length--;
		}
		else if(right_length == 0)
		{
			curr->next = left;
			left = left->next;
			left_length--;	
		}
		else if(left->key < right->key)
		{
			curr->next = left;
			left = left->next;
			left_length--;
		}
		else
		{
			curr->next = right; 
			right = right->next;
			right_length--;
		}
		curr->prev = prev;
		prev = curr;
		curr = curr->next;
		curr->prev = prev;
	}
	curr->next = NULL;
	curr->prev = prev;
	return start;
}

/*** Test ***/
int main(int argc, char* argv[])
{
	int keys[5] = {2,1,9,3,6};
	int randnum[5] = {3,1,0,4,2};
	DoubleLinkedList<int> list = DoubleLinkedList<int>();
	//SingleLinkedList<int> list2;
	std::cout << "Test insert" << std::endl;
	for(int i = 0; i < 5; i++)
	{
		std::cout << "Insert " << keys[i] << ":  " << std::endl;
		list.insert(keys[i]);
		list.printForward();
		list.printBackward();
	}

	
	std::cout << "Test reverse" << std::endl;
	list.reverse();
	list.printForward();
	list.printBackward();
	

	std::cout << std::endl << "Test copy constructor" << std::endl;
	DoubleLinkedList<int> list2 = DoubleLinkedList<int>(list);
	list2.printForward();
	list.printBackward();

	std::cout << std::endl << "Test operator=" << std::endl;
	DoubleLinkedList<int> list3 = list2;
	list3.printForward();
	list.printBackward();

	std::cout << std::endl << "Test delete" << std::endl;
	for(int i = 0; i < 5; i++)
	{
		std::cout << "Remove " << keys[randnum[i]] << ":  " << std::endl;
		list.remove(keys[randnum[i]]);
		list.printForward();
		list.printBackward();
	}

	std::cout << std::endl << "Test sort" << std::endl;
	list2.sort();
	list2.printForward();
	list2.printBackward();

	std::cout << std::endl << "Test nested insert and remove" << std::endl;
	DoubleLinkedList<int> list4 = DoubleLinkedList<int>();
	list4.insert(7);
	list4.insert(2);
	list4.insert(1);
	list4.printForward();
	list4.remove(2);
	list4.remove(3);
	list4.printForward();

	return 0;
}
