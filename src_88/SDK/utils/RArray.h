#ifndef SDK_ARRAY_H_INCLUDED
#define SDK_ARRAY_H_INCLUDED

#include "stdinc.h"

		template <class T>
		class Array;

		template <class T>
		void ClearArrayData(Array<T>& ary);

        template <class T> class Array
        {
			friend void ClearArrayData<>(Array<T>& ary);

        protected:
            void _safedel()
            {
                if(_buf != NULL)
                    delete [] _buf;
                _buf = NULL;
                length = 0;
                cursor = 0;
				truelength = 0;

                if(_sorted_indices != NULL) delete [] _sorted_indices;
                _sorted_indices = NULL;
            }

        public:
			 T*  _buf;

			int length, cursor;
			int truelength;
            int _indices_length;

            int* _sorted_indices;

			inline int Length() const { return length;}
			inline int GetAllocatedSize() { return truelength;}

			inline Array<T>()
			{
				length = 0;
				cursor = 0;
				truelength = 0;
				_buf = NULL;
                _sorted_indices = NULL;
                _indices_length = 0;
            }

			inline Array<T>(int count)
            {
				cursor = 0;
				truelength = 0;
				length = 0;
				_buf = NULL;
                _sorted_indices = NULL;
                _indices_length = 0;
				//SetCapacity(count);
				New(count);
				length = 0;
			}

			inline Array<T>(const Array<T>& src)
            {
				length = 0;
				cursor = 0;
				truelength = 0;
				_buf = NULL;
                _sorted_indices = NULL;
                _indices_length = 0;
				SetLength(src.length);
				//memcpy(_buf, src._buf, src.length * sizeof(T));
                for(int i = 0; i < src.length; i++) _buf[i] = src[i];
            }

            inline ~Array<T>()
            {
                _safedel();
            }

            inline T& operator[](int i) const
            {
                //ASSERT( i < length);
                return _buf[i];
            }

            inline T& Get(int i)
            {
                //ASSERT( i < length);
                return _buf[i];
            }
			
			inline void SetCapacity(const int capacity)
			{

				cursor = 0;
				truelength = 0;
				length = 0;
				_buf = NULL;
				_sorted_indices = NULL;
				_indices_length = 0;
				//SetCapacity(count);
				New(capacity);
				length = 0;

				/*
				int len = length;
				if(capacity > truelength)
				{
					Array<T> copy;
					if (len > 0)
					{
					copy.Copy(_buf, length);
					}

					New(capacity);

					//memcpy(_buf, copy._buf, copy.Length() * sizeof(T));
					if (len > 0)
					for(int i = 0; i < copy.Length(); i++) _buf[i] = copy[i];
					length = len;
				}
				else if (capacity < truelength)
				{
					Array<T> copy;
					copy.Copy(_buf, capacity);

					New(capacity);

					//memcpy(_buf, copy._buf, copy.Length() * sizeof(T));
					for(int i = 0; i < copy.Length(); i++) _buf[i] = copy[i];
					if (len < capacity)
						length = len;
					else
						length = capacity;
				}
				*/
			}

            inline void Set(const T& value)
            {
                for(int i = 0; i < length; _buf[i++] = value);
            }

            inline Array<T>& operator = (const Array<T>& src)
            {
                _safedel();
                Copy(src.ptr(), src.length);
                return *this;
            }

            inline bool operator != (T* l)
            {
                return _buf != l;        
            }

            inline bool operator == (T* l)
            {
                return _buf == l;        
            }

            operator T* ()
            {
                return _buf;
            }

            inline T* ptr() const
            {
                return _buf;
            }

            inline void New(const int count)
            {
                if(count > truelength)
                {
                    _safedel();
					truelength = 32;
					while(count > truelength)
						truelength += 32;
                    _buf = new T[truelength];
                    memset(_buf, 0, sizeof(T) * truelength);
                }
                length = count;
            }

           inline  void New()
            {
                _safedel();
				SetLength(32);
            }

            inline void SetLength(const int& count)
            {
				if(count > length)
                {
                    New(count);
                }
				else
					length = count;
            }

            inline void SetLengthAndKeepData(const int& count)
            {
				if(count > truelength)
                {
                    Array<T> copy;
                    copy.Copy(_buf, length);

					New(count);

                    //memcpy(_buf, copy._buf, copy.Length() * sizeof(T));
					for(int i = 0; i < copy.Length(); i++) _buf[i] = copy[i];
				}
				else
					length = count;
            }
			
            inline void Delete()
            {
                //_safedel();
				SetLength(0);
            }

			inline void Clean()
			{
				SetLength(0);
			}

            inline void Copy(const T* src, const int& count)
            {
                SetLength(count);
				//memcpy(_buf, src, count * sizeof(T));
                for(int i = 0; i < count; i++) _buf[i] = src[i];
            }

			inline void Append(T *start, int count)
			{
				for(int i =0;i<count;i++)
				{
					Push(start[i]);
				}

			}
			
			inline void Push(T el)
			{
                const int len = length + 1;
                SetLengthAndKeepData(len);
                _buf[len-1] = el;
			}

			inline T& Pop()
			{
				
				//ASSERT(length > 0);
 				length--;
				return _buf[length];
			
			}

			inline bool IsEmpty()
			{
				return (length == 0);
			}


			inline T& Last()
			{
				//ASSERT(length > 0);
				return _buf[length-1];
			}


			inline T& First()
			{
				//ASSERT(length > 0);
				return _buf[0];
			}
			inline T PopFirst()
			{
				T ret = First();
				RemoveNo(0);
				return ret;

			}

            inline void SetNo(const int& index, T el)
            {
                if(index >= length)
                    SetLengthAndKeepData(index + 1);
                _buf[index] = el;
            }

			inline void Insert(const int& index, T el)
			{

                SetLengthAndKeepData(length + 1);

				const int l = length;
                for(int i = l-1; i > index; i--)
                     _buf[i] = _buf[i-1];

				_buf[index] = el;
                

			}

            inline void Remove(T el)
            {
                const int l = length;
                for(int i = 0; i < l; i++)
                    if(_buf[i] == el)
                    {
                        for(int j = i + 1; j < l; j++)
                            _buf[j - 1] = _buf[j];
                        length--;
                        break;
                    }
            }

            inline void RemoveNo(int index)
            {
                if (index >= length)
                    return;
				for(int j = index + 1; j < length; j++)
					_buf[j - 1] = _buf[j];
				length--;
            }



            inline void Copy(Array<T>& source)
            {
                Copy(source.ptr(), source.length);
            }

			inline void AddArray(Array<T>& addarray)
			{

				//SetLengthAndKeepData(length + addarray.length);
				//memcpy(_buf + length, addarray.ptr(), addarray.length * sizeof(T));

				for(int i = 0 ;i<addarray.length;i++)
					Push(addarray[i]);

			}

			inline int Find(T& obj) const
			{
                for(int i = 0; i < length; i++)
                    if(_buf[i] == obj) return i;

                return -1;
			}

            inline bool Contains(T obj) const
            {
                for(int i = 0; i < length; i++)
                    if(_buf[i] == obj) return true;

                return false;
            }

            inline void SetCursor(const int& c)
            {
                cursor = c;
            }

            inline int GetCursor()
            {
                return cursor;
            }

            inline T& GetCursorElem()
            {
                return _buf[cursor];
            }

            typedef int (*CompareFunc)(T& e1, T& e2);

            inline void Sort(CompareFunc cf)
            {
                if((_sorted_indices != NULL && _indices_length < length) || (_sorted_indices == NULL))
                {
                    if(_sorted_indices != NULL)
                        delete [] _sorted_indices;
                    _sorted_indices = new int[length];
                    _indices_length = length;
                }
                
                for(int i = 0; i < length; i++) _sorted_indices[i] = i;

                quicksort(0, length - 1, cf);
            }

            inline void Swap(T& e1, T& e2)
            {
                T aux = e1;
                e1 = e2;
                e2 = aux;
            }

            void SwapInd(int i, int j)
            {
                int aux = _sorted_indices[i];
                _sorted_indices[i] = _sorted_indices[j];
                _sorted_indices[j] = aux;

            }

        protected:
            int choose_pivot(int i, int j)
            {
                return ((i+j) >> 1);
            }

            void quicksort(int m, int n, CompareFunc cf)
            {
                int i, j, k;
                T key;
                if(m < n)
                {
                    k = choose_pivot(m, n);

                    Swap(_buf[m], _buf[k]);
                    SwapInd(m, k);

                    key = _buf[m];
                    i = m + 1;
                    j = n;
                    while(i <= j)
                    {
                        while((i <= n) && (cf(_buf[i], key) <= 0))
                            i++;
                        while((j >= m) && (cf(_buf[j], key) > 0))
                            j--;
                        if(i < j)
                        {
                            Swap(_buf[i], _buf[j]);
                            SwapInd(i, j);
                        }
                    }
                    // swap two elements
                    Swap(_buf[m], _buf[j]);
                    SwapInd(m, j);
                    // recursively sort the lesser list
                    quicksort(m, j - 1, cf);
                    quicksort(j + 1, n, cf);
                }
            }
        };

		template <class T>
		void ClearArrayData(Array<T>& ary)
		{
			for (T* el = ary._buf, *end = ary._buf + ary.Length(); el < end; el++)
			{				
				delete (*el);
				*el = NULL;
			}

			ary._safedel();
		}

#endif