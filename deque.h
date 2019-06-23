
template<class T>
struct __deque_iterator
{
	T* first;
	T* last;
	T* cur;
	T** node;
};

template<class T>
class deque
{
public:
	typedef __deque_iterator<T> iterator;

private:

	T** _array_map;
	size_t _size;

	iterator _start;
	iterator _finish;
};