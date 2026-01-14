//
// Created by mscheman on 10/27/25.
//

#ifndef DEQUE_H
#define DEQUE_H

#include ".helper/ftdef.hpp"
#include ".helper/iterator.hpp"
#include ".helper/type_traits.hpp"

# define DEQUE_ARRAY_SIZE 16
# define DEQUE_INIT_ARRAY_NUM 8

namespace ft
{
template <typename T, typename Allocator = ft::allocator<T> >
class deque;


template <typename T, typename TRef, typename TPtr>
struct _dequeIterator
	: public ft::iterator<ft::bidirectional_iterator_tag, T, ft::ptrdiff_t, TRef, TPtr>
{
	// Typedefs
	typedef _dequeIterator<T, TRef, TPtr>				this_type;
	typedef T											value_type;
	typedef TRef										reference;
	typedef TPtr										pointer;
	typedef ft::ptrdiff_t								difference_type;

	// Constructor
	explicit	_dequeIterator(value_type** map = 0, value_type *curr = 0);
				_dequeIterator(_dequeIterator<T, T REF, T*> CREF iterator);
				~_dequeIterator() {}

	// Dereference Operator
	reference	operator		* () { return *current; }
	pointer		operator		->() { return current; }

	// Shift Operators
	this_type REF	operator	++();
	this_type		operator	++(int);
	this_type REF	operator	+=(difference_type n);
	this_type		operator	+ (difference_type n);
	this_type REF	operator	--();
	this_type		operator	--(int);
	this_type REF	operator	-=(difference_type n);
	this_type		operator	- (difference_type n);

	// Attributes
	value_type*		current;	// Current element in buffer
	value_type*		begin;		// Start of buffer
	value_type*		end;		// End of buffer
	value_type**	map;		// Map that holds the current buffer
};


template <typename T, typename Allocator>
class deque {
	public:
		// Typedefs
		typedef T										value_type;
		typedef Allocator								allocator_type;
		typedef	ft::size_t								size_type;
		typedef ft::ptrdiff_t							difference_type;
		typedef typename Allocator::reference			reference;
		typedef typename Allocator::const_reference		const_reference;
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;
		typedef _dequeIterator<T, T REF, T*>			iterator;
		typedef _dequeIterator<T, T CREF, T const*>		const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		// Constructor
		explicit deque(allocator_type CREF allocator = allocator_type());
		explicit deque(size_type n, value_type CREF val = value_type(), allocator_type CREF allocator = allocator_type());
		//template <typename InputIt> deque(InputIt first, InputIt last, allocator_type CREF allocator = allocator_type());
		deque(deque CREF rhs);
		deque REF operator = (deque CREF rhs);
		~deque();

		// Iterators
		iterator				begin();
		const_iterator			begin() const;
		iterator				end();
		const_iterator			end() const;
		reverse_iterator		rbegin();
		const_reverse_iterator	rbegin() const;
		reverse_iterator		rend();
		const_reverse_iterator	rend() const;

		// Element Access
		reference		front();
		const_reference	front() const;
		reference		back();
		const_reference	back() const;

		// Modifiers
		void	push_back(value_type CREF val);
		void	push_front(value_type CREF val);

	public:
		// Typedefs
		typedef typename allocator_type::template rebind<value_type*>::other _mapAllocator_type;

		// Helper Functions
		void					_init(size_type size);
		void					_assignHelper(size_type n, value_type CREF val, ft::true_type);
		void					_expandBack();
		void					_expandFront();
		void					_clearHelper();
		value_type**			_allocateMap(size_type n);
		value_type*				_allocateBuffer();
		void					_reallocateMap(size_type n);

		// Attributes
		value_type**			_map;
		size_type				_mapSize;
		iterator				_start;
		iterator				_end;
		mutable allocator_type	_allocator;
		_mapAllocator_type		_mapAllocator() { return _mapAllocator_type(_allocator); }


};


}

#include ".containers/deque.tpp"

#endif //DEQUE_H
