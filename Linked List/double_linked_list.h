#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#define SENTINEL_VAL 0xAAAAAAAA 
#define DEBUG        1

enum RET_VALUE
{	
	SUCCESS,
	KEY_NOT_FOUND,
	EMPTY_LIST,
	CANNOT_ALLOCATE

};

template <typename T>
struct Node
{
	T key;
	Node<T>* next;
	Node<T>* prev;
};

// This class uses a sentinel node

template <class T>
class DoubleLinkedList
{
	public:

		DoubleLinkedList();

		~DoubleLinkedList();

		DoubleLinkedList(DoubleLinkedList const & other);

		DoubleLinkedList<T> & operator=(const DoubleLinkedList<T> & rhs);

		RET_VALUE insert(T key); 
		
		RET_VALUE remove(T key);
		
		RET_VALUE reverse();

		int getSize();

		void sort();

		void printForward();

		void printBackward();
	
	private:
		void copy(DoubleLinkedList<T> const & other);

		void clear();

		Node<T>* mergeSort(Node<T>* start, int length);

		Node<T>* split(Node<T>* start, int splitIndex);

		Node<T>* merge(Node<T>* left, Node<T>* right, int left_length, int right_length);


		Node<T>* head;
		Node<T>* tail;
		
		int size;
};

#endif 