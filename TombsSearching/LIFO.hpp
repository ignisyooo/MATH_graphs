#ifndef LIFO_HPP
#define LIFO_HPP

struct Node
{
	Node * next;
	int value;
};

class Lifo
{
    Node *head;

public:
	Lifo();
	~Lifo();

	bool IsEmpty(void);
	int  TopValue(void);
	void Push(int elem);
	void Pop(void);
};

#endif /* LIFO_HPP */