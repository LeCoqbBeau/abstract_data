//
// Created by mscheman on 9/8/25.
//

#ifndef LIST_H
#define LIST_H

#include ".helper/algorithm.h"
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

	template <typename T, typename PointerA, typename ReferenceA, typename PointerB, typename ReferenceB>
	bool operator != (
		ft::ListIterator<T, PointerA, ReferenceA> CREF a,
		ft::ListIterator<T, PointerB, ReferenceB> CREF b
	) FT_NOTHROW
	{
		return a.mpNode != b.mpNode;
	}


	template <typename T, typename Pointer, typename Reference>
	bool operator != (
		ft::ListIterator<T, Pointer, Reference> CREF a,
		ft::ListIterator<T, Pointer, Reference> CREF b
	) FT_NOTHROW
	{
		return a.mpNode != b.mpNode;
	}


	template <typename T, typename PointerA, typename ReferenceA, typename PointerB, typename ReferenceB>
	bool operator == (
		ft::ListIterator<T, PointerA, ReferenceA> CREF a,
		ft::ListIterator<T, PointerB, ReferenceB> CREF b
	) FT_NOTHROW
	{
		return a.mpNode == b.mpNode;
	}


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
		allocator_type get_allocator() const FT_NOTHROW;

	protected:
		ft::pair<base_node_type, allocator_type>	mNodeAllocator;

		base_node_type REF internalNode() FT_NOTHROW { return mNodeAllocator.first(); }
		base_node_type CREF internalNode() const FT_NOTHROW { return mNodeAllocator.first(); }
		allocator_type REF internalAllocator() FT_NOTHROW { return mNodeAllocator.second(); }
		allocator_type CREF internalAllocator() const FT_NOTHROW { return mNodeAllocator.second(); }
		node_allocator_type internalNodeAllocator() { return node_allocator_type(internalAllocator()); }
		node_allocator_type internalNodeAllocator() const { return node_allocator_type(internalAllocator()); }
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

		void swap(this_type REF x);

		void assign(size_type n, value_type CREF value = value_type());
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

		void resize(size_type n, value_type CREF value = value_type());

		reference		front();
		const_reference	front() const;

		reference		back();
		const_reference	back() const;

		void push_front(value_type CREF value);
		void push_back(value_type CREF value);

		void pop_front();
		void pop_back();

		iterator insert(iterator position, value_type CREF value);
		iterator insert(iterator position, size_type count, value_type CREF value);
		template<class InputIt> iterator insert(iterator position, InputIt first, InputIt last);

		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);

		void clear() FT_NOTHROW;

		void remove(value_type CREF value);

		template <class Predicate> void remove_if(Predicate predicate);

		void reverse() FT_NOTHROW;

		void splice(iterator position, this_type REF x);
		void splice(iterator position, this_type REF x, iterator i);
		void splice(iterator position, this_type REF x, iterator first, iterator last);

	public:
		void merge(this_type REF other);

		template <class Compare> void merge(this_type REF other, Compare compare);

		void unique();

		template <class BinaryPredicate> void unique(BinaryPredicate predicate);

		void sort();

		template <class Compare> void sort(Compare compare);

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
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
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

template <class T, class Allocator>
void swap(ft::list<T, Allocator> REF a, ft::list<T, Allocator> REF b)
{
	a.swap(b);
}


#include ".list/listNodeBase.tpp"
#include ".list/listIterator.tpp"
#include ".list/listBase.tpp"
#include ".list/list.tpp"

#endif //LIST_H
