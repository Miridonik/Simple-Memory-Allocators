#pragma once
#include "includes.h"
class List
{
public:
	List() ;
	//~List();
	void push_forward(void* data);
	void* pop_front();
	std::size_t Length();
	void Reset();
private:
	struct Node
	{
		Node()
		{
			p_next = nullptr;
		}
		Node(Node* p_next)
		{
			this->p_next = p_next;
		}
		Node(const Node& src) = delete;
		Node(const Node&& src) = delete;
		Node* p_next;
	};
	Node* head;
	std::size_t size;
};


inline List::List()
{
	head = nullptr;
	size = 0;
}

inline void List::push_forward(void* data)
{
	if (head == nullptr)
	{
		head = (Node*)data;
		new (head)Node();
	}
	else
	{
		Node* next = head;
		head = (Node*)data;
		new(head)Node(next);
	}
	size++;
}

inline void* List::pop_front()
{
	if (head == nullptr)
		return nullptr;
	else
	{
		Node* new_head = head->p_next;
		void* data = (void*)((std::size_t)head + 4);
		//delete head ////////////////////
		//delete head;
		head = new_head;
		size--;
		return data;
	}
}

//inline List::~List()
//{
//	if (head == nullptr)
//		return;
//	Node* current = head;
//	while (current != nullptr)
//	{
//		Node* next = current->p_next;
//		delete current;
//		current = next;
//	}
//}

inline std::size_t List::Length()
{
	return size;
}

inline void List::Reset()
{
	head = nullptr;
	size = 0;
}