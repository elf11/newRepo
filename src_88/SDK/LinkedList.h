
#ifndef LINKEDLIST__H
#define LINKEDLIST__H

template <class T>
class LinkedNode
{
public :
	T data;
	LinkedNode<T> *Next,*Prev;
};

template <class T>
class LinkedList
{
public :
	LinkedNode<T> *First,*Last;

	LinkedList<T>(void);
	~LinkedList<T>(void);

	void AppendRight(LinkedNode<T> *Node);
	void Remove(LinkedNode<T> *Node);
};

template <class T>
LinkedList<T>::LinkedList<T>(void)
{
	First = Last = NULL;
}

template <class T>
LinkedList<T>::~LinkedList<T>(void)
{
	while (First != NULL)
	{
		Last = First->Next;
		delete First;
		First = Last;
	}
}

template <class T>
void LinkedList<T>::AppendRight(LinkedNode<T> *Node)
{
	if (Last == NULL)
	{
		First = Last = Node;
		Node->Prev = NULL;
		Node->Next = NULL;
	}
	else
	{
		Last->Next = Node;
		Node->Prev = Last;
		Node->Next = NULL;
		Last = Node;
	}
}

template <class T>
void LinkedList<T>::Remove(LinkedNode<T> *Node)
{
	if (Node->Prev == NULL)
	{
		First = Node->Next;
	}
	else
	{
		Node->Prev->Next = Node->Next;
	}

	if (Node->Next == NULL)
	{
		Last = Node->Prev;
	}
	else
	{
		Node->Next->Prev = Node->Prev;
	}
}


#endif
