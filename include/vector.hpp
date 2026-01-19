//
// Created by mscheman on 1/19/26.
//

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include ".helper/algorithm.hpp"
#include ".helper/ftdef.hpp"
#include ".helper/iterator.hpp"

#define VECTOR_ARRAY_INIT_SIZE 16
#define VECTOR_AT_EXCEPTION_MSG ("vector::at(): index n out of bounds")


namespace ft {


template <typename T, typename Allocator = ft::allocator<T> >
class vector {
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
		typedef value_type *							iterator;
		typedef value_type const*						const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		// Constructors
		explicit 						vector(allocator_type CREF alloc = allocator_type());
		explicit 						vector(size_type n, value_type CREF val = value_type(), allocator_type CREF alloc = allocator_type());
		template <class InputIterator>	vector(InputIterator first, InputIterator last, allocator_type CREF alloc = allocator_type());
										vector(vector CREF rhs);
		vector REF operator				= (vector CREF rhs);
		~vector();

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
		size_type	size() const;
		size_type	max_size() const;
		void		resize(size_type n, value_type CREF val = value_type());
		size_type	capacity() const;
		bool		empty() const;
		void		reserve(size_type n);

		// Element Access
		reference		operator	[] (size_type n);
		const_reference operator	[] (size_type n) const;
		reference 					at(size_type n);
		const_reference 			at(size_type n) const;
		reference					front();
		const_reference				front() const;
		reference					back();
		const_reference				back() const;

		// Modifiers
		void									assign(size_type n, value_type CREF value);
		template <typename InputIt> void		assign(InputIt first, InputIt last);
		void									push_back(value_type CREF value);
		void									pop_back();
		iterator								insert(iterator position, value_type CREF val);
		void									insert(iterator position, size_type count, value_type CREF val);
		template <typename InputIt> iterator	insert(iterator position, InputIt first, InputIt last);
		iterator								erase(iterator position);
		iterator								erase(iterator first, iterator last);
		void									swap(vector CREF other);
		void									clear();

		// Allocator
		allocator_type							get_allocator() const;

	protected:
		// Helper Functions
		void									_init(size_type n);
		void									_assignHelper(size_type n, value_type CREF val, ft::true_type);
		template <typename InputIt> void		_assignHelper(InputIt first, InputIt last, ft::false_type);
		iterator								_insertHelper(iterator pos, size_type n, value_type CREF val, ft::true_type);
		template <typename InputIt> iterator	_insertHelper(iterator pos, InputIt first, InputIt last, ft::false_type);
		void									_reallocate(size_type n);

		// Attributes
		value_type*		_array;
		value_type*		_end;
		size_type		_size;
		allocator_type	_allocator;

};


template <typename T, typename Allocator>
void swap(ft::vector<T, Allocator> x, ft::vector<T, Allocator> y) {
	x.swap(y);
}


}



# define VECTOR_COMPARISON_OPERATOR(op) template <class T, class Allocator> bool operator op						\
											(ft::vector<T, Allocator> CREF lhs, ft::vector<T, Allocator> CREF rhs)

VECTOR_COMPARISON_OPERATOR(==) {
	if (lhs.size() != rhs.size())
		return false;
	return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}


VECTOR_COMPARISON_OPERATOR(!=) {
	return !(lhs == rhs);
}


VECTOR_COMPARISON_OPERATOR(<) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}


VECTOR_COMPARISON_OPERATOR(<=) {
	return !(rhs < lhs);
}


VECTOR_COMPARISON_OPERATOR(>) {
	return (rhs < lhs);
}


VECTOR_COMPARISON_OPERATOR(>=) {
	return !(lhs < rhs);
}


#include ".containers/vector.tpp"

#undef VECTOR_ARRAY_INIT_SIZE
#undef VECTOR_AT_EXCEPTION_MSG
#undef VECTOR_COMPARISON_OPERATOR

#endif //VECTOR_HPP
