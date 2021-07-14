#include "LIFO.hpp"

Lifo::Lifo()
{
	head = nullptr;
}

Lifo::~Lifo()
{
	while(head != nullptr)
    {
        Pop();
    }
}

bool Lifo::IsEmpty(void)
{
	return !head;
}

int Lifo::TopValue(void)
{
	if(head)
	{
		return head->value;
	}
	else
	{
		return -1;
	}
}

void Lifo::Push(int elem)
{
	Node *tmp = new Node;
	tmp->value = elem;
	tmp->next = head;
	head = tmp;
}

void Lifo::Pop(void)
{
	if (head)
	{
		Node *tmp = head;
		head = head->next;
		delete tmp;
	}
}
