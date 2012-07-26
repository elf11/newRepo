#pragma once

template<class T, unsigned int maxSize>
class ManagedArray
{
public:
	//statics
	static T*			array[maxSize];
	static unsigned int	numElements;
	
	static void ClearAll()	{ while(numElements) delete *array; }
	static void Swap(T *e1, T *e2)
	{
		e1->index ^= e2->index;
		e2->index ^= e1->index;
		e1->index ^= e2->index;
		array[e1->index] = e1;
		array[e2->index] = e2;
	}
	
	//member
	unsigned int		index; //indexed array: O(1) access/add/remove time
	
	ManagedArray()
	{
		if(numElements < maxSize)
		{
			index = numElements++;
			array[index] = (T *) this;
		}
		else index = maxSize;
	}
	
	virtual ~ManagedArray()
	{
		if(array[index] == ((T *) this))
		{
			--numElements;
			if(numElements > 0)
			{
				array[index] = array[numElements];
				array[index]->index = index;
			}
		}
	}
};

template<class T, unsigned int maxSize>
T*				ManagedArray<T, maxSize>::array[maxSize];

template<class T, unsigned int maxSize>
unsigned int	ManagedArray<T, maxSize>::numElements = 0;

