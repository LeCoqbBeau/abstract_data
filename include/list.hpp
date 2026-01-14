#ifndef LIST_H
#define LIST_H

#include ".helper/ftdef.hpp"
#include ".helper/iterator.hpp"
#include ".helper/type_traits.hpp"

namespace ft {

template<typename T, typename Allocator = std::allocator<T> >
class list;


template <typename T>
struct _doublyLinkedList {
	// Constructors
	explicit _doublyLinkedList(T CREF value = T())
		: value(value), next(NULL), prev(NULL) {};
	_doublyLinkedList(_doublyLinkedList CREF src)
		: value(src.value), next(src.next), prev(src.prev) {};

	// Attributes
	T					value;
	_doublyLinkedList	*next;
	_doublyLinkedList	*prev;
};


template <class T, class TRef, class TPtr>
struct _listIterator
	: public ft::iterator<ft::bidirectional_iterator_tag, T, ft::ptrdiff_t, TRef, TPtr>
{
	// Typedef
	typedef _listIterator<T, TRef, TPtr>				this_type;
	typedef T											value_type;
	typedef TRef										reference;
	typedef TPtr										pointer;
	typedef typename ft::list<value_type>::node_type	node_type;

	// Constructor
	explicit	_listIterator(node_type node = 0) : _currentNode(node) {};
				_listIterator(_listIterator<T, T REF, T*> CREF rhs) : _currentNode(rhs._currentNode) {};
				~_listIterator() {};

	// In/Equality Operator
	template <class U, class URef, class UPtr>
	bool operator	== (_listIterator<U, URef, UPtr> CREF rhs) { return this->_currentNode == rhs._currentNode; }
	template <class U, class URef, class UPtr>
	bool operator	!= (_listIterator<U, URef, UPtr> CREF rhs) { return this->_currentNode != rhs._currentNode; }

	// Dereference Operator
	reference	operator  * () { return _currentNode->value; }
	pointer		operator -> () { return &(operator*()); }

	// Shift Operators
	this_type REF	operator ++ () { _currentNode = _currentNode->next; return *this; }
	this_type		operator ++ (int) { this_type tmp = *this; _currentNode = _currentNode->next; return tmp; }
	this_type REF	operator -- () { _currentNode = _currentNode->prev; return *this; }
	this_type		operator -- (int) { this_type tmp = *this; _currentNode = _currentNode->prev; return tmp; }

	// Attributes
	node_type	_currentNode;
};


template<class T, class Allocator>
class list {
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
		typedef _listIterator<T, T REF, T*>				iterator;
		typedef _listIterator<T, T CREF, T const*>		const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef _doublyLinkedList<value_type>*			node_type;

		// Constructors & Destructors
		explicit				list(allocator_type CREF alloc = allocator_type());
		explicit				list(size_type n, value_type CREF val = value_type(), allocator_type CREF alloc = allocator_type());
		template<class InputIt>	list (InputIt first, InputIt last, allocator_type CREF alloc = allocator_type());
								list(list CREF x);
		list REF operator		= (list CREF rhs);
		~list();

		// Iterators
		iterator				begin();
		const_iterator			begin() const;
		iterator				end();
		const_iterator			end() const;
		reverse_iterator		rbegin();
		const_reverse_iterator	rbegin() const;
		reverse_iterator		rend();
		const_reverse_iterator	rend() const;

		// Capacity
		bool		empty() const;
		size_type	size() const;
		size_type	max_size() const;

		// Element Access
		reference		front();
		const_reference	front() const;
		reference		back();
		const_reference	back() const;

		// Modifiers
		void								assign(size_type count, value_type CREF value);
		template<class InputIt>	void		assign(InputIt first, InputIt last);
		void								push_front(value_type CREF val);
		void								pop_front();
		void								push_back(value_type CREF val);
		void								pop_back();
		iterator							insert(iterator position, value_type CREF value);
		iterator							insert(iterator position, size_type count, value_type CREF value);
		template<class InputIt> iterator	insert(iterator position, InputIt first, InputIt last);
		iterator							erase(iterator position);
		iterator							erase(iterator first, iterator last);
		void								swap(list REF x);
		void								resize(size_type n, value_type CREF val = value_type());
		void								clear();

		// Operations
		void									splice(iterator position, list REF other);
		void									splice(iterator position, list REF other, iterator it);
		void									splice(iterator position, list REF other, iterator first, iterator last);
		void									remove(value_type CREF val);
		template <class Predicate> void			remove_if(Predicate pred);
		void									unique();
		template <class BinaryPredicate> void	unique(BinaryPredicate pred);
		void									merge(list REF other);
		template <class Compare> void			merge(list REF other, Compare comp);
		void									sort();
		template <class Compare> void			sort(Compare comp);
		void									reverse();

		// Observers
		allocator_type							get_allocator() const;

	protected:
		// Typedef
		typedef typename allocator_type::template rebind<_doublyLinkedList<value_type> >::other _nodeAllocator;

		// Helper methods
		node_type									_createNode() const;
		node_type									_createNode(value_type CREF val) const;
		void										_assignHelper(size_type n, value_type CREF val, ft::true_type);
		template <class InputIt> void				_assignHelper(InputIt first, InputIt last, ft::false_type);
		iterator									_insertHelper(iterator position, list REF other);
		list										_insertHelper(size_type n, value_type CREF val, ft::true_type);
		template <class InputIt> list				_insertHelper(InputIt first, InputIt last, ft::false_type);
		node_type									_duplicate() const;
		void										_shrinkHelper(size_type n);
		void										_clearHelper();
		node_type									_delBackHelper(node_type node);
		template <class Compare> void				_initMergeSort(Compare comp);
		template <class Compare> node_type			_split(Compare comp, node_type head, size_type size);
		template <class Compare> node_type			_merge(	Compare comp,
															node_type left, size_type leftSize,
															node_type right, size_type rightSize);
		void										_cleanList(node_type removed);
		_nodeAllocator								_getNodeAllocator();

		// Attributes
		node_type									_sentinel;
		mutable _nodeAllocator						_allocator;
};


template <typename T, typename Allocator>
void swap(list<T, Allocator> REF x, list<T, Allocator> REF y) {
	x.swap(y);
}


}


# define LIST_COMPARISON_OPERATOR(op) template <class T, class Allocator> bool operator op					\
										(ft::list<T, Allocator> CREF lhs, ft::list<T, Allocator> CREF rhs)

LIST_COMPARISON_OPERATOR(==) {
	typedef typename ft::list<T, Allocator>::iterator iterator;
	iterator	leftIt = lhs.begin();
	iterator	rightIt = rhs.begin();
	while (leftIt != lhs.end() && rightIt != rhs.end()) {
		if (*leftIt != *rightIt)
			return false;
		++leftIt;
		++rightIt;
	}
	return true;
}


LIST_COMPARISON_OPERATOR(!=) {
	return !(lhs == rhs);
}


LIST_COMPARISON_OPERATOR(<) {
	typedef typename ft::list<T, Allocator>::iterator iterator;
	iterator	leftIt = lhs.begin();
	iterator	rightIt = rhs.begin();
	while (leftIt != lhs.end() && rightIt != rhs.end()) {
		if (*rightIt < *leftIt)
			return false;
		++leftIt;
		++rightIt;
	}
	return true;
}


LIST_COMPARISON_OPERATOR(<=) {
	return !(rhs < lhs);
}


LIST_COMPARISON_OPERATOR(>) {
	return (rhs < lhs);
}


LIST_COMPARISON_OPERATOR(>=) {
	return !(lhs < rhs);
}


# undef LIST_COMPARISON_OPERATOR

#include ".containers/list.tpp"

#endif //LIST_H