//
// Created by mscheman on 1/22/26.
//

#ifndef STACK_HPP
#define STACK_HPP

#include "deque.hpp"

namespace ft {


template <class T, class Container = ft::deque<T> >
class stack {
	public:
		// Typedefs
		typedef Container									container_type;
		typedef typename container_type::value_type			value_type;
		typedef typename container_type::size_type			size_type;
		typedef typename container_type::reference			reference;
		typedef typename container_type::const_reference	const_reference;

		// Constructor
		explicit stack(container_type CREF container = container_type()) : c(container) {}
		~stack() {}

		// Element Access
		reference		top() { return c.back(); }
		const_reference	top() const { return c.back(); }

		// Capacity
		bool	empty() const { return c.empty(); }
		bool	size() const { return c.size(); }

		// Modifiers
		void	push(value_type CREF value) { c.push_back(value); }
		void	pop() { c.pop_back(); }

	protected:
		container_type	c;
};


}


# define STACK_COMPARISON_OPERATOR(op)	template <class T, class Container> bool operator op						\
											(ft::stack<T, Container> CREF lhs, ft::stack<T, Container> CREF rhs)	\
										{ return lhs.c op rhs.c; }

l
STACK_COMPARISON_OPERATOR(==);
STACK_COMPARISON_OPERATOR(!=);
STACK_COMPARISON_OPERATOR(<);
STACK_COMPARISON_OPERATOR(<=);
STACK_COMPARISON_OPERATOR(>);
STACK_COMPARISON_OPERATOR(>=);


#undef STACK_COMPARISON_OPERATOR

#endif //STACK_HPP
