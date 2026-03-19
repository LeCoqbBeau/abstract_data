//
// Created by mscheman on 1/22/26.
//

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "deque.hpp"
#include "vector.hpp"
#include "functional.hpp"

namespace ft {


template <class T, class Container>
class queue;


template <class T, class Container>	bool operator==(queue<T, Container> CREF lhs, queue<T, Container> CREF rhs);
template <class T, class Container>	bool operator!=(queue<T, Container> CREF lhs, queue<T, Container> CREF rhs);
template <class T, class Container>	bool operator< (queue<T, Container> CREF lhs, queue<T, Container> CREF rhs);
template <class T, class Container>	bool operator<=(queue<T, Container> CREF lhs, queue<T, Container> CREF rhs);
template <class T, class Container>	bool operator> (queue<T, Container> CREF lhs, queue<T, Container> CREF rhs);
template <class T, class Container>	bool operator>=(queue<T, Container> CREF lhs, queue<T, Container> CREF rhs);


template <class T, class Container = deque<T> >
class queue {
	public:
		// Typedefs
		typedef Container									container_type;
		typedef typename container_type::value_type			value_type;
		typedef typename container_type::size_type			size_type;

		// Constructor
		explicit			queue(container_type CREF container = container_type()) : c(container) {}
		~queue() {}

		// Element Access
		value_type REF		front()						{ return c.front(); }
		value_type CREF		front() const				{ return c.front(); }
		value_type REF		back()						{ return c.back(); }
		value_type CREF		back() const				{ return c.back(); }

		// Capacity
		bool				empty() const				{ return c.empty(); }
		size_type			size() const				{ return c.size(); }

		// Modifiers
		void				push(value_type CREF value)	{ c.push_back(value); }
		void				pop()						{ c.pop_front(); }

		// Friends :D
		friend bool operator== <>(queue<T, Container> CREF lhs, queue<T, Container> CREF rhs);
		friend bool operator!= <>(queue<T, Container> CREF lhs, queue<T, Container> CREF rhs);
		friend bool operator<  <>(queue<T, Container> CREF lhs, queue<T, Container> CREF rhs);
		friend bool operator<= <>(queue<T, Container> CREF lhs, queue<T, Container> CREF rhs);
		friend bool operator>  <>(queue<T, Container> CREF lhs, queue<T, Container> CREF rhs);
		friend bool operator>= <>(queue<T, Container> CREF lhs, queue<T, Container> CREF rhs);

	protected:
		container_type		c;
};


template <class T, class Container = vector<T>, class Compare = ft::less<typename Container::value_type> >
class priority_queue {
	public:
		// Typedefs
		typedef Container									container_type;
		typedef Compare										value_compare;
		typedef typename container_type::value_type			value_type;
		typedef typename container_type::size_type			size_type;

		// Constructor
		explicit
		priority_queue(
			value_compare CREF comp = value_compare(),
			container_type CREF container = container_type()
		)	: c(container), comp(comp)
		{
			ft::make_heap(c.begin(), c.end(), comp);
		}

		template <class InputIt>
		priority_queue(
			InputIt first,
			InputIt last,
			value_compare CREF comp = value_compare(),
			container_type CREF container = container_type()
		)	: c(container), comp(comp)
		{
			c.insert(c.end(), first, last);
			ft::make_heap(c.begin(), c.end(), comp);
		}

		// Element Access
		value_type CREF				top() const					{ return c.front(); }

		// Capacity
		bool						empty() const				{ return c.empty(); }
		size_type					size() const				{ return c.size(); }

		// Modifiers
		void						push(value_type CREF value)	{ c.push_back(value); ft::push_heap(c.begin(), c.end(), comp); }
		void						pop()						{ ft::pop_heap(c.begin(), c.end(), comp); c.pop_back(); }

	protected:
		container_type				c;
		value_compare				comp;
};


# define QUEUE_COMPARISON_OPERATOR(op)	template <class T, class Container> bool operator op					\
										(ft::queue<T, Container> CREF lhs, ft::queue<T, Container> CREF rhs)	\
										{ return lhs.c op rhs.c; }

QUEUE_COMPARISON_OPERATOR(==);
QUEUE_COMPARISON_OPERATOR(!=);
QUEUE_COMPARISON_OPERATOR(<);
QUEUE_COMPARISON_OPERATOR(<=);
QUEUE_COMPARISON_OPERATOR(>);
QUEUE_COMPARISON_OPERATOR(>=);

#undef QUEUE_COMPARISON_OPERATOR


}

#endif //QUEUE_HPP
