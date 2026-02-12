//
// Created by mscheman on 1/22/26.
//

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "deque.hpp"
#include "vector.hpp"
#include ".helper/functional.hpp"

namespace ft {


template <class T, class Container = deque<T> >
class queue {
	public:
		// Typedefs
		typedef Container									container_type;
		typedef typename container_type::value_type			value_type;
		typedef typename container_type::size_type			size_type;
		typedef typename container_type::reference			reference;
		typedef typename container_type::const_reference	const_reference;

		// Constructor
		explicit queue(container_type CREF container = container_type()) : c(container) {}
		~queue() {}

		// Element Access
		reference		front() { return c.front(); }
		const_reference	front() const { return c.front(); }
		reference		back() { return c.back(); }
		const_reference	back() const { return c.back(); }

		// Capacity
		bool	empty() const { return c.empty(); }
		bool	size() const { return c.size(); }

		// Modifiers
		void	push(value_type CREF value) { c.push_back(value); }
		void	pop() { c.pop_front(); }

	protected:
		container_type	c;
};


template <class T, class Container = vector<T>,  class Compare = ft::less<typename Container::value_type> >
class priority_queue {
	public:
		// Typedefs
		typedef Container									container_type;
		typedef Compare										value_compare;
		typedef typename container_type::value_type			value_type;
		typedef typename container_type::size_type			size_type;
		typedef typename container_type::reference			reference;
		typedef typename container_type::const_reference	const_reference;

		// Constructor
		explicit priority_queue(value_compare CREF comp = value_compare(), container_type CREF container = container_type())
			: c(container), comp(comp) {}
		template <class InputIt> priority_queue(InputIt first, InputIt last, value_compare CREF comp = value_compare(), container_type CREF container = container_type())
			: c(container), comp(comp) { c.insert(c.end(), first, last); ft::make_heap(c.begin(), c.end(), comp); }

		// Element Access
		reference		front()						{ return c.front(); }
		const_reference	front() const				{ return c.front(); }
		reference		back()						{ return c.back(); }
		const_reference	back() const				{ return c.back(); }

		// Capacity
		bool			empty() const				{ return c.empty(); }
		bool			size() const				{ return c.size(); }

		// Modifiers
		void			push(value_type CREF value)	{ c.push_back(value); ft::push_heap(c.begin(), c.end(), comp); }
		void			pop()						{ ft::pop_heap(c.begin(), c.end(), comp); c.pop_front(); }

	protected:
		container_type	c;
		value_compare	comp;
};

}


# define QUEUE_COMPARISON_OPERATOR(op)	template <class T, class Container> bool operator op						\
											(ft::queue<T, Container> CREF lhs, ft::queue<T, Container> CREF rhs)	\
										{ return lhs.c op rhs.c; }

# define PRIO_QUEUE_COMPARISON_OPERATOR(op)	template <class T, class Container> bool operator op						\
												(ft::queue<T, Container> CREF lhs, ft::queue<T, Container> CREF rhs)	\
											{ return lhs.c op rhs.c; }


QUEUE_COMPARISON_OPERATOR(==);
QUEUE_COMPARISON_OPERATOR(!=);
QUEUE_COMPARISON_OPERATOR(<);
QUEUE_COMPARISON_OPERATOR(<=);
QUEUE_COMPARISON_OPERATOR(>);
QUEUE_COMPARISON_OPERATOR(>=);


#undef QUEUE_COMPARISON_OPERATOR

#endif //QUEUE_HPP
