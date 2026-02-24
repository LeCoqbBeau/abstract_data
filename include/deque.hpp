//
// Created by mscheman on 10/27/25.
//

#ifndef DEQUE_HPP
#define DEQUE_HPP

#include ".helper/ftdef.hpp"
#include ".helper/algorithm.hpp"
#include ".helper/iterator.hpp"
#include ".helper/type_traits.hpp"

# define DEQUE_ARRAY_SIZE 16
# define DEQUE_INIT_ARRAY_NUM 8
# define DEQUE_AT_EXCEPTION_MSG ("deque::at(): index n out of bounds")

namespace ft {
template <typename T, typename Allocator = ft::allocator<T> >
class deque;


template <typename T, typename TRef, typename TPtr>
struct _dequeIterator
	: public ft::iterator<ft::random_access_iterator_tag, T, ft::ptrdiff_t, TRef, TPtr>
{
	// Typedefs
	typedef _dequeIterator<T, TRef, TPtr>	this_type;
	typedef T								value_type;
	typedef TRef							reference;
	typedef TPtr							pointer;
	typedef ft::ptrdiff_t					difference_type;

	// Constructor
	explicit	_dequeIterator(value_type** map = 0, value_type *curr = 0);
	_dequeIterator(_dequeIterator<T, T REF, T*> CREF iterator);
	~_dequeIterator() {}

	// In/Equality Operator
	template <class U, class URef, class UPtr>
	bool operator	== (_dequeIterator<U, URef, UPtr> CREF rhs) const;
	template <class U, class URef, class UPtr>
	bool operator	!= (_dequeIterator<U, URef, UPtr> CREF rhs) const;

	// Dereference Operator
	reference	operator		* () { return *_mCurrent; }
	pointer		operator		->() { return _mCurrent; }

	// Shift Operators
	this_type REF	operator	++ ();
	this_type		operator	++ (int);
	this_type REF	operator	+= (difference_type n);
	this_type		operator	+  (difference_type n);
	this_type REF	operator	-- ();
	this_type		operator	-- (int);
	this_type REF	operator	-= (difference_type n);
	this_type		operator	-  (difference_type n);
	template <class U, class URef, class UPtr>
	difference_type	operator	- (_dequeIterator<U, URef, UPtr> CREF rhs) const;

	// Attributes
	value_type*		_mCurrent;	// Current element in buffer
	value_type*		_mBegin;	// Start of buffer
	value_type*		_mEnd;		// End of buffer
	value_type**	_mMap;		// Map that holds the current buffer
};


template <typename T, typename Allocator>
class deque {
	public:
		// Typedefs
		typedef T										value_type;
		typedef Allocator								allocator_type;
		typedef	ft::size_t								size_type;
		typedef ft::ptrdiff_t							difference_type;
		typedef value_type REF							reference;
		typedef value_type CREF							const_reference;
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;
		typedef _dequeIterator<T, T REF, T*>			iterator;
		typedef _dequeIterator<T, T CREF, T const*>		const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		// Constructor
		explicit							deque(allocator_type CREF allocator = allocator_type());
		explicit							deque(size_type n, value_type CREF val = value_type(), allocator_type CREF allocator = allocator_type());
		template <typename InputIt>			deque(InputIt first, InputIt last, allocator_type CREF allocator = allocator_type());
		deque(deque CREF rhs);
		deque REF				operator	= (deque CREF rhs);
		~deque();

		// Iterators
		iterator							begin();
		const_iterator						begin() const;
		iterator							end();
		const_iterator						end() const;
		reverse_iterator					rbegin();
		const_reverse_iterator				rbegin() const;
		reverse_iterator					rend();
		const_reverse_iterator				rend() const;

		// Capacity
		size_type							size() const;
		size_type							max_size() const;
		void								resize(size_type n, value_type CREF val = value_type());
		bool								empty() const;

		// Element Access
		reference				operator	[] (size_type n);
		const_reference			operator	[] (size_type n) const;
		reference 							at(size_type n);
		const_reference 					at(size_type n) const;
		reference							front();
		const_reference						front() const;
		reference							back();
		const_reference						back() const;

		// Modifiers
		void								assign(size_type n, value_type CREF value);
		template <typename InputIt> void	assign(InputIt first, InputIt last);
		void								push_back(value_type CREF value);
		void								push_front(value_type CREF value);
		void								pop_back();
		void								pop_front();
		iterator							insert(iterator position, value_type CREF value);
		void								insert(iterator position, size_type count, value_type CREF value);
		template <typename InputIt> void	insert(iterator position, InputIt first, InputIt last);
		iterator							erase(iterator position);
		iterator							erase(iterator first, iterator last);
		void								swap(deque REF other);
		void								clear();

		// Allocator
		allocator_type						get_allocator() const;

	protected:
		// Typedefs
		typedef typename allocator_type::template rebind<value_type*>::other _mapAllocator_type;

		// Helper Functions
		void								_init(size_type size);
		void								_assignHelper(size_type n, value_type CREF val, ft::true_type);
		template <typename InputIt> void	_assignHelper(InputIt first, InputIt last, ft::false_type);
		void								_expandBack();
		void								_expandFront();
		void								_reserveBack(size_type n);
		void								_reserveFront(size_type n);
		iterator							_insertHelper(iterator pos, size_type n, value_type CREF val, ft::true_type);
		template <typename InputIt> void	_insertHelper(iterator pos, InputIt first, InputIt last, ft::false_type);
		void								_clearHelper(bool preserveMap = false);
		value_type**						_allocateMap(size_type n);
		value_type*							_allocateBuffer();
		void								_reallocateMap(size_type n);

		// Attributes
		value_type**						_map;
		size_type							_mapSize;
		iterator							_start;
		iterator							_end;
		mutable allocator_type				_allocator;
		_mapAllocator_type					_mapAllocator() { return _mapAllocator_type(_allocator); }


};


template <typename T, typename Allocator>
void swap(ft::deque<T, Allocator> REF x, ft::deque<T, Allocator> REF y) {
	x.swap(y);
}


# define DEQUE_COMPARISON_OPERATOR(op)	template <class T, class Allocator> bool operator op						\
										(ft::deque<T, Allocator> CREF lhs, ft::deque<T, Allocator> CREF rhs)

DEQUE_COMPARISON_OPERATOR(==)	{ return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }
DEQUE_COMPARISON_OPERATOR(!=)	{ return !(lhs == rhs); }
DEQUE_COMPARISON_OPERATOR(<)	{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
DEQUE_COMPARISON_OPERATOR(<=)	{ return !(rhs < lhs); }
DEQUE_COMPARISON_OPERATOR(>)	{ return (rhs < lhs); }
DEQUE_COMPARISON_OPERATOR(>=)	{ return !(lhs < rhs); }

#undef DEQUE_COMPARISON_OPERATOR


}


#include ".containers/deque.tpp"


#undef DEQUE_ARRAY_SIZE
#undef DEQUE_INIT_ARRAY_NUM
#undef DEQUE_AT_EXCEPTION_MSG

#endif //DEQUE_HPP
