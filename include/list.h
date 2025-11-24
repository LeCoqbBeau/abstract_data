//
// Created by mscheman on 9/8/25.
//

#ifndef LIST_H
#define LIST_H

#include ".helper/algorithm.h"
#include ".list/DoublyLinkedList.h"
#include ".helper/ftdef.h"
#include ".helper/iterator.h"
#include ".helper/pair.h"
#include ".helper/type_traits.h"

namespace ft {

struct ListNodeBase {
	ListNodeBase *mpNext;
	ListNodeBase *mpPrev;

	void insert(ListNodeBase *pNext) FT_NOTHROW;
	void remove() FT_NOTHROW;
	void splice(ListNodeBase *pFirst, ListNodeBase *pLast) FT_NOTHROW;
	void reverse() FT_NOTHROW;
	static void swap(ListNodeBase REF a, ListNodeBase REF b) FT_NOTHROW;

	void insert_range(ListNodeBase *pFirst, ListNodeBase *pLast) FT_NOTHROW;
	static void remove_range(ListNodeBase *pFirst, ListNodeBase *pLast) FT_NOTHROW;
};

template<typename T> struct ListNode : public ListNodeBase {
	T mValue;
};

template<typename T, typename Pointer = T*, typename Reference = T REF>
struct ListIterator : public ft::iterator<bidirectional_iterator_tag, T> {
	typedef ListIterator<T, Pointer, Reference>		this_type;
	typedef ListIterator<T, T*, T REF>				iterator;
	typedef ListIterator<T, T const*, T CREF>		const_iterator;
	typedef ft::size_t								size_type;
	typedef ft::ptrdiff_t							difference_type;
	typedef T										value_type;
	typedef Pointer									pointer;
	typedef Reference								reference;
	typedef	ListNodeBase							base_node_type;
	typedef ListNode<T>								node_type;

	public:
		base_node_type *mpNode;

	public:
		ListIterator() FT_NOTHROW;
		ListIterator(ListNodeBase const* pNode) FT_NOTHROW;
		template <typename Iterator>
		ListIterator(
			Iterator CREF x,
			ENABLE_IF_TT(
				IS_SAME_V(Iterator, iterator) && !IS_SAME_V(this_type, iterator),
				void*
			) = 0
		) : mpNode(x.mpNode)
		{}

		this_type	next() const FT_NOTHROW;
		this_type	prev() const FT_NOTHROW;

		reference	operator * () const FT_NOTHROW;
		pointer		operator -> () const FT_NOTHROW;

		this_type REF	operator++() FT_NOTHROW;
		this_type		operator++(int) FT_NOTHROW;

		this_type REF	operator--() FT_NOTHROW;
		this_type		operator--(int) FT_NOTHROW;
};


template <typename T, typename Allocator>
class ListBase {
	public:
		typedef T														value_type;
		typedef Allocator												allocator_type;
		typedef ListNode<T>												node_type;
		typedef ft::size_t												size_type;
		typedef ft::ptrdiff_t											difference_type;
		typedef ListNodeBase											base_node_type;
		typedef typename Allocator::template rebind<node_type>::other	node_allocator_type;

	protected:
		ListBase();
		ListBase(allocator_type CREF a);
		~ListBase();

		node_type	*DoAllocateNode(value_type CREF value = value_type());
		void		DoFreeNode(node_type *pNode);

		void		DoInit() FT_NOTHROW;
		void		DoClear() FT_NOTHROW;

	public:
		allocator_type REF get_allocator() FT_NOTHROW;
		allocator_type CREF get_allocator() const FT_NOTHROW;

	protected:
		ft::pair<base_node_type, allocator_type>	mNodeAllocator;

		base_node_type REF internalNode() FT_NOTHROW { return mNodeAllocator.first(); }
		base_node_type CREF internalNode() const FT_NOTHROW { return mNodeAllocator.first(); }
		allocator_type REF internalAllocator() FT_NOTHROW { return mNodeAllocator.second(); }
		allocator_type CREF internalAllocator() const FT_NOTHROW { return mNodeAllocator.second(); }
		node_allocator_type internalNodeAllocator() { return node_allocator_type(internalAllocator()); }
		node_allocator_type CREF internalNodeAllocator() const { return node_allocator_type(internalAllocator()); }
};


template <class T, class Allocator = std::allocator<T> >
class list : public ListBase<T, Allocator> {
	typedef ListBase<T, Allocator>	base_type;
	typedef list<T, Allocator>		this_type;

	protected:
		using base_type::mNodeAllocator;
		using base_type::DoAllocateNode;
		using base_type::DoFreeNode;
		using base_type::DoClear;
		using base_type::DoInit;
		using base_type::internalNode;
		using base_type::internalAllocator;
		using base_type::internalNodeAllocator;

	public:
		typedef T										value_type;
		typedef T*										pointer;
		typedef T const*								const_pointer;
		typedef T REF									reference;
		typedef T CREF									const_reference;
		typedef ListIterator<T, T*, T&>					iterator;
		typedef ListIterator<T, T const*, T CREF>		const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef typename base_type::size_type			size_type;
		typedef typename base_type::difference_type		difference_type;
		typedef typename base_type::allocator_type		allocator_type;
		typedef typename base_type::node_type			node_type;
		typedef typename base_type::base_node_type		base_node_type;

		using base_type::get_allocator;

	public:
		explicit list(allocator_type CREF allocator = allocator_type());
		explicit list(size_type n, value_type CREF value, allocator_type CREF allocator = allocator_type());
		template <class InputIterator> list(InputIterator first, InputIterator last, allocator_type CREF allocator = allocator_type());
		list(this_type CREF other);

		this_type REF operator = (this_type CREF other);

		void assign(size_type n, value_type CREF value);
		template <class InputIterator> void assign(InputIterator first, InputIterator last);

		iterator				begin() FT_NOTHROW;
		const_iterator			begin() const FT_NOTHROW;

		iterator				end() FT_NOTHROW;
		const_iterator			end() const FT_NOTHROW;

		reverse_iterator		rbegin() FT_NOTHROW;
		const_reverse_iterator	rbegin() const FT_NOTHROW;

		reverse_iterator		rend() FT_NOTHROW;
		const_reverse_iterator	rend() const FT_NOTHROW;

		bool		empty() const FT_NOTHROW;
		size_type	size() const FT_NOTHROW;
		size_type	max_size() const FT_NOTHROW;

		void resize(size_type n, value_type val = value_type());

		reference		front();
		const_reference	front() const;

		reference		back();
		const_reference	back() const;

		void push_front(value_type CREF val);
		void push_back(value_type CREF val);

		void pop_front();
		void pop_back();

		iterator insert(iterator position, value_type CREF value);
		iterator insert(iterator position, size_type count, value_type CREF value);
		template<class InputIt> iterator insert(iterator position, InputIt first, InputIt last);

		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);

		void clear() FT_NOTHROW;

		void remove(value_type CREF val);

		template <class Predicate> void remove_if(Predicate pred);

		void reverse() FT_NOTHROW;

		void splice(iterator position, this_type REF x);
		void splice(iterator position, this_type REF x, iterator i);
		void splice(iterator position, this_type REF x, iterator first, iterator last);

	public:
		void merge(this_type REF other);

		template <class Compare> void merge(this_type REF x, Compare compare);

		void unique();

		template <class BinaryPredicate> void unique(BinaryPredicate pred);

		void sort();

		template <class Compare> void sort(Compare comp);

	protected:
		node_type*	DoCreateNode(value_type CREF value = value_type());

		template <typename Integer>
		void DoAssign(Integer n, Integer value, traits::true_type);

		template <typename InputIterator>
		void DoAssign(InputIterator first, InputIterator last, traits::false_type);

		void DoAssignValues(size_type n, value_type CREF value);

		template <typename Integer>
		void DoInsert(ListNodeBase *pNode, Integer n, Integer value, traits::true_type);

		template <typename InputIterator>
		void DoInsert(ListNodeBase *pNode, InputIterator first, InputIterator last, traits::false_type);

		void DoInsertValues(ListNodeBase *pNode, size_type n, value_type CREF value);

		void DoInsertValue(ListNodeBase* pNode, value_type CREF value);

		void DoErase(ListNodeBase *pNode);

		void DoSwap(this_type REF x);

		template <typename Compare>
		iterator DoSort(iterator i1, iterator end2, size_type n, Compare REF compare);
};

// template<class T, class Allocator = std::allocator<T> >
// class list {
// 	public:
// 		// Friend
// 		class iterator;
// 		class const_iterator;
//
// 		// Typedefs
// 		typedef T										value_type;
// 		typedef Allocator								allocator_type;
// 		typedef	size_t									size_type;
// 		typedef ptrdiff_t								difference_type;
// 		typedef typename Allocator::reference			reference;
// 		typedef typename Allocator::const_reference		const_reference;
// 		typedef typename Allocator::pointer				pointer;
// 		typedef typename Allocator::const_pointer		const_pointer;
// 		typedef iterator								iterator;
// 		typedef const_iterator							const_iterator;
// 		typedef ft::reverse_iterator<iterator>			reverse_iterator;
// 		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
//
// 		// Constructors & Destructors
// 		explicit list(allocator_type CREF alloc = allocator_type());
// 		explicit list(size_type n, value_type CREF val = value_type(), allocator_type CREF alloc = allocator_type());
// 		template<class InputIt> list (InputIt first, InputIt last, allocator_type CREF alloc = allocator_type());
// 		list(list CREF x);
// 		list REF operator = (list CREF x);
// 		~list();
//
// 		// Iterators
// 		iterator begin();
// 		const_iterator begin() const;
// 		iterator end();
// 		const_iterator end() const;
// 		reverse_iterator rbegin();
// 		const_reverse_iterator rbegin() const;
// 		reverse_iterator rend();
// 		const_reverse_iterator rend() const;
//
// 		// Capacity
// 		bool empty() const;
// 		size_type size() const;
// 		size_type max_size() const;
//
// 		// Element Access
// 		reference front();
// 		const_reference front() const;
// 		reference back();
// 		const_reference back() const;
//
// 		// Modifiers
// 		void assign(size_type count, value_type CREF value);
// 		template<class InputIt> void assign(InputIt first, InputIt last);
// 		void push_front(value_type CREF val);
// 		void pop_front();
// 		void push_back(value_type CREF val);
// 		void pop_back();
// 		iterator insert(iterator position, value_type CREF value);
// 		iterator insert(iterator position, size_type count, value_type CREF value);
// 		template<class InputIt> iterator insert(iterator position, InputIt first, InputIt last);
// 		iterator erase(iterator position);
// 		iterator erase(iterator first, iterator last);
// 		void swap(list REF x);
// 		void resize(size_type n, value_type CREF val = value_type());
// 		void clear();
//
// 		// Operations
// 		void splice(iterator position, list REF other);
// 		void splice(iterator position, list REF other, iterator it);
// 		void splice(iterator position, list REF other, iterator first, iterator last);
// 		void remove(value_type CREF val);
// 		template <class Predicate> void remove_if(Predicate pred);
// 		void unique();
// 		template <class BinaryPredicate> void unique(BinaryPredicate pred);
// 		void merge(list REF other);
// 		template <class Compare> void merge(list REF other, Compare comp);
// 		void sort();
// 		template <class Compare> void sort(Compare comp);
// 		void reverse();
//
// 		// Observers
// 		allocator_type get_allocator() const;
//
// 	private:
// 		// Typedef
// 		typedef DoublyLinkedList<value_type>		*_node;
// 		typedef typename Allocator::template rebind<DoublyLinkedList<value_type> >::other _nodeAllocator;
//
// 		// Helper methods
// 		_node										_createNode(value_type CREF val = value_type()) const;
// 		void										_assignHelper(size_type n, value_type CREF val, traits::true_type);
// 		template <class InputIt> void				_assignHelper(InputIt first, InputIt last, traits::false_type);
// 		iterator									_insertHelper(iterator position, list REF other);
// 		list										_insertHelper(size_type n, value_type CREF val, traits::true_type);
// 		template <class InputIt> list				_insertHelper(InputIt first, InputIt last, traits::false_type);
// 		_node										_duplicate() const;
// 		void										_shrinkHelper(size_type n);
// 		void										_clearHelper();
// 		_node										_delBackHelper(_node node);
// 		template <class Compare> void				_initMergeSort(Compare comp);
// 		template <class Compare> _node				_split(Compare comp, _node head, size_type size);
// 		template <class Compare> _node				_merge( Compare comp,
// 															_node left, size_type leftSize,
// 															_node right, size_type rightSize );
// 		void										_cleanList(_node removed);
//
// 		// Attributes
// 		_node										_sentinel;
// 		mutable _nodeAllocator						_allocator;
// 		size_type									_size;
//
// };

// template <typename T, typename Allocator>
// void swap(list<T, Allocator> REF x, list<T, Allocator> REF y) {
// 	x.swap(y);
// }

}

# define LIST_RELATIONAL_OPERATOR(op) template <class T, class Allocator> bool operator op					\
										(ft::list<T, Allocator> CREF lhs, ft::list<T, Allocator> CREF rhs)

LIST_RELATIONAL_OPERATOR(==) {
	typedef typename ft::list<T, Allocator>::const_iterator cit;
	cit lit = lhs.begin();
	cit rit = rhs.begin();
	cit lend = lhs.end();
	cit rend = rhs.end();

	while ((lit != lend && (rit != rend) && (*lit == *rit))) {
		++lit;
		++rit;
	}
	return (lit == lend) && (rit == rend);
}


LIST_RELATIONAL_OPERATOR(!=) {
	return !(lhs == rhs);
}


LIST_RELATIONAL_OPERATOR(<) {
	return ft::algo::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}


LIST_RELATIONAL_OPERATOR(<=) {
	return !(rhs < lhs);
}


LIST_RELATIONAL_OPERATOR(>) {
	return (rhs < lhs);
}


LIST_RELATIONAL_OPERATOR(>=) {
	return !(lhs < rhs);
}


# undef LIST_RELATIONAL_OPERATOR

// #include ".list/listIterators.h"
#include ".list/listNodeBase.tpp"
#include ".list/listIterator.tpp"
#include ".list/listBase.tpp"
#include ".list/list.tpp"

#endif //LIST_H
