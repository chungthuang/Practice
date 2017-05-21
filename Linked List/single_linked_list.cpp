#include <assert.h>
#include <iostream>
#include "single_linked_list.h"

template <typename T>
SingleLinkedList<T>::SingleLinkedList()
{
	// Create a sentinel node
	this->head = (Node<T>*)malloc(sizeof(Node<T>));
	this->head->key = SENTINEL_VAL;
	this->tail = this->head;
	this->size = 0;
}

template <typename T>
SingleLinkedList<T>::~SingleLinkedList<T>()
{
	clear();
}

template <typename T>
SingleLinkedList<T>::SingleLinkedList(SingleLinkedList const & other)
{
	copy(other);
}

template <typename T>
SingleLinkedList<T> & SingleLinkedList<T>::operator=(SingleLinkedList<T> const & rhs)
{
	if(this != &rhs)
	{
		clear();
		copy(rhs);
	}
	return *this;
}

template <typename T>
RET_VALUE SingleLinkedList<T>::insert(int key)
{
	this->tail->next = (Node<T>*)malloc(sizeof(Node<T>));
	if(this->tail->next == NULL)
	{
		return CANNOT_ALLOCATE;
	}
	this->tail = this->tail->next;
	this->tail->key = key;
	this->tail->next = NULL;
	this->size++;
	return SUCCESS;
}

template <typename T>
RET_VALUE SingleLinkedList<T>::remove(int key)
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
RET_VALUE SingleLinkedList<T>::reverse()
{
	if(this->size >= 2)
	{
		int count = 0;
		int first_key = this->head->next->key;
		int last_key = this->tail->key;
		Node<T>* curr = this->head->next;
		Node<T>* next = curr->next;
		Node<T>* next_next = next->next; 
		curr->next = NULL;
		this->head->next = this->tail;
		this->tail = curr;
		while(next_next != NULL)
		{
			next->next = curr;
			curr = next;
			next = next_next;
			next_next = next_next->next;
			count++;
		}
		next->next = curr;
#if DEBUG
		assert(this->head->next->key == last_key); // Make sure first key and last key are swapped
		assert(this->tail->key == first_key);
		assert(count == this->size-2);
#endif 
	}	
	return SUCCESS;		
}

template <typename T>
void SingleLinkedList<T>::print()
{
	int count = 0;
	Node<T>* curr = this->head->next;
	Node<T>* next;
	while(curr != NULL)
	{
		std::cout << curr->key;
		next = curr->next;
		curr = next;
		count++;
	}
#if DEBUG
	assert(count == this->size);
#endif 
}

/*** Private functions ***/
template <typename T>
void SingleLinkedList<T>::copy(SingleLinkedList<T> const & other)
{
	Node<T>* other_curr = other.head;
	this->head = (Node<T>*)malloc(sizeof(Node<T>));
	this->head->key = other_curr->key;
	Node<T>* curr = this->head;
	other_curr = other_curr->next;
	while(other_curr != NULL)
	{
		curr->next = (Node<T>*)malloc(sizeof(Node<T>));
		curr->next->key = other_curr->key;
		curr = curr->next;
		other_curr = other_curr->next;
		this->size++;
	}
	this->tail = curr;
	curr->next = NULL;
#if DEBUG
		print();
		std::cout << std::endl;
		assert(this->size = other.size);
#endif
}

template <typename T>
void SingleLinkedList<T>::clear()
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


/*** Test ***/
int main(int argc, char* argv[])
{
	int keys[5] = {2,1,9,3,6};
	int randnum[5] = {3,1,0,4,2};
	SingleLinkedList<int> list = SingleLinkedList<int>();
	//SingleLinkedList<int> list2;
	std::cout << "Test insert" << std::endl;
	for(int i = 0; i < 5; i++)
	{
		std::cout << "Insert " << keys[i] << ":  ";
		list.insert(keys[i]);
		list.print();
		std::cout << std::endl;
	}

	std::cout << "Test reverse" << std::endl;
	list.reverse();
	list.print();
	std::cout << std::endl;

	std::cout << "Test copy constructor" << std::endl;
	SingleLinkedList<int> list2 = SingleLinkedList<int>(list);
	list2.print();
	std::cout << std::endl;

	std::cout << "Test operator=" << std::endl;
	SingleLinkedList<int> list3 = list2;
	list3.print();
	std::cout << std::endl;

	std::cout << "Test delete" << std::endl;
	for(int i = 0; i < 5; i++)
	{
		std::cout << "Remove " << keys[randnum[i]] << ":  ";
		list.remove(keys[randnum[i]]);
		list.print();
		std::cout << std::endl;
	}



	return 0;
}
