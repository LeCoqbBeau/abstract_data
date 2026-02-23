#ifndef LIST_HPP
#define LIST_HPP

#include ".helper/algorithm.hpp"
#include ".helper/ftdef.hpp"
#include ".helper/iterator.hpp"
#include ".helper/type_traits.hpp"
#include ".helper/doublyLinkedList.hpp"

namespace ft {


template<class T, class Allocator = ft::allocator<T> >
class list {
	public:
		// Typedefs
		typedef T															value_type;
		typedef Allocator													allocator_type;
		typedef	ft::size_t													size_type;
		typedef ft::ptrdiff_t												difference_type;
		typedef value_type REF												reference;
		typedef value_type CREF												const_reference;
		typedef typename Allocator::pointer									pointer;
		typedef typename Allocator::const_pointer							const_pointer;
		typedef internal::_doublyLinkedListIterator<T, T REF, T*>			iterator;
		typedef internal::_doublyLinkedListIterator<T, T CREF, T const*>	const_iterator;
		typedef ft::reverse_iterator<iterator>								reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;

		// Constructors & Destructors
		explicit								list(allocator_type CREF alloc = allocator_type());
		explicit								list(size_type n, value_type CREF val = value_type(), allocator_type CREF alloc = allocator_type());
		template<class InputIt>					list (InputIt first, InputIt last, allocator_type CREF alloc = allocator_type());
		list(list CREF x);
		list REF operator						= (list CREF rhs);
		~list();

		// Iterators
		iterator								begin();
		const_iterator							begin() const;
		iterator								end();
		const_iterator							end() const;
		reverse_iterator						rbegin();
		const_reverse_iterator					rbegin() const;
		reverse_iterator						rend();
		const_reverse_iterator					rend() const;

		// Capacity
		bool									empty() const;
		size_type								size() const;
		size_type								max_size() const;

		// Element Access
		reference								front();
		const_reference							front() const;
		reference								back();
		const_reference							back() const;

		// Modifiers
		void									assign(size_type count, value_type CREF value);
		template <class InputIt>	void		assign(InputIt first, InputIt last);
		void									push_front(value_type CREF val);
		void									pop_front();
		void									push_back(value_type CREF val);
		void									pop_back();
		iterator								insert(iterator position, value_type CREF value);
		iterator								insert(iterator position, size_type count, value_type CREF value);
		template<class InputIt> iterator		insert(iterator position, InputIt first, InputIt last);
		iterator								erase(iterator position);
		iterator								erase(iterator first, iterator last);
		void									swap(list REF x);
		void									resize(size_type n, value_type CREF val = value_type());
		void									clear();

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
		typedef internal::_doublyLinkedListBase								_base_type;
		typedef internal::_doublyLinkedList<value_type>						_node_type;
		typedef typename allocator_type::template rebind<_node_type>::other	_nodeAllocator;

		// Helper methods
		_base_type*									_createNode(value_type CREF val) const;
		void										_assignHelper(size_type n, value_type CREF val, ft::true_type);
		template <class InputIt> void				_assignHelper(InputIt first, InputIt last, ft::false_type);
		iterator									_insertHelper(iterator position, list REF other);
		list										_insertHelper(size_type n, value_type CREF val, ft::true_type);
		template <class InputIt> list				_insertHelper(InputIt first, InputIt last, ft::false_type);
		void										_duplicate(_base_type *newSentinel) const;
		void										_shrinkHelper(size_type n);
		void										_clearHelper();
		template <class Compare> void				_initMergeSort(Compare comp);
		template <class Compare> _base_type*		_split(Compare comp, _base_type* head, size_type size);
		template <class Compare> _base_type*		_merge(	Compare comp,
															_base_type* left, size_type leftSize,
															_base_type* right, size_type rightSize);
		void										_cleanList(_base_type* removed);
		_nodeAllocator								_getNodeAllocator() const;

		// Attributes
		_base_type									_sentinel;
		mutable allocator_type						_allocator;
};


template <typename T, typename Allocator>
void swap(list<T, Allocator> REF x, list<T, Allocator> REF y) {
	x.swap(y);
}


# define LIST_COMPARISON_OPERATOR(op)	template <class T, class Allocator> bool operator op					\
										(ft::list<T, Allocator> CREF lhs, ft::list<T, Allocator> CREF rhs)

LIST_COMPARISON_OPERATOR(==) {
	if (lhs.size() != rhs.size())
		return false;
	return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}


LIST_COMPARISON_OPERATOR(!=) {
	return !(lhs == rhs);
}


LIST_COMPARISON_OPERATOR(<) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
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
}


#include ".containers/list.tpp"

#endif //LIST_HPP
