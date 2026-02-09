
#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <bits/this_thread_sleep.h>

#include "ftdef.hpp"
#include "algorithm.hpp"
#include "functional.hpp"
#include "pair.hpp"


#define RBT_LEFT	0
#define RBT_RIGHT	1
#define RBT_BLACK	'B'
#define RBT_RED		'R'
#define RBT_NODE(base) (static_cast<ft::internal::rbt_node<T>*>(base))

namespace ft { namespace internal {


struct rbt_node_base {
	// Typedefs
	typedef rbt_node_base	this_type;
	typedef char			color_type;
	typedef	bool			side_type;

	// Constructor
	rbt_node_base(this_type* parent = NULL, color_type color = RBT_RED)
		: parent(parent), color(color) { ft::fill_n(next, 2, reinterpret_cast<this_type*>(NULL)); }
	~rbt_node_base() {}

	// Methods
	this_type* REF	left();
	this_type* CREF	left() const;
	this_type* REF	right();
	this_type* CREF	right() const;
	this_type*		min();
	this_type*		max();
	this_type*		rotate(side_type side);
	this_type*		nextNode();
	this_type*		prevNode();

	// Attributes
	this_type*	next[2];
	this_type*	parent;
	color_type	color;
};


template <typename T>
struct rbt_node : rbt_node_base {
	// Nested structure
	struct RemoveResult {
		// Constructor
		RemoveResult(rbt_node* rNode = NULL, rbt_node* pNode = NULL, color_type c = RBT_BLACK)
			: replacementNode(rNode), parentNode(pNode), removedColor(c) {}

		// Attributes
		rbt_node*	replacementNode;
		rbt_node*	parentNode;
		color_type	removedColor;
	};

	// Typedefs
	typedef rbt_node<T>			this_type;
	typedef rbt_node_base		base_type;
	typedef	T					value_type;
	typedef RemoveResult		remove_result;


	// Constructor
	rbt_node(value_type CREF val = value_type(), base_type* parent = NULL)
		: rbt_node_base(parent, RBT_RED), value(val) {}

	// Methods
#define COMPARE_TEMPLATE template <typename Compare>
	COMPARE_TEMPLATE 	this_type*										find(value_type CREF val, Compare comp) const;
	template <typename Allocator, typename FreeFunc>	remove_result	erase(Allocator allocator, FreeFunc free);
	COMPARE_TEMPLATE 	this_type*										insert(this_type* node, Compare comp);
	COMPARE_TEMPLATE 	ft::size_t										count(value_type CREF val, Compare comp) const;
	COMPARE_TEMPLATE	this_type const*								lower_bound(value_type CREF val, Compare comp) const;
	COMPARE_TEMPLATE	this_type const*								upper_bound(value_type CREF val, Compare comp) const;
	COMPARE_TEMPLATE	ft::pair<this_type const*, this_type const*>	equal_range(value_type CREF val, Compare comp) const;
#undef COMPARE_TEMPLATE


	// Attributes
	value_type		value;
};


template <typename T, typename Ref, typename Ptr, typename extractKey>
struct rbt_iterator
	: iterator<ft::bidirectional_iterator_tag, T, ft::ptrdiff_t, Ptr, Ref>
{
	// Typedefs
	typedef rbt_iterator<T, Ref, Ptr, extractKey>	this_type;
	typedef T										value_type;
	typedef Ref										reference;
	typedef Ptr										pointer;
	typedef ft::ptrdiff_t							difference_type;
	typedef ft::internal::rbt_node<T>				node_type;
	typedef ft::internal::rbt_node_base				base_type;

	// Constructors
	explicit	rbt_iterator(base_type const* sentinel = NULL, node_type *node = NULL) : _current(node), _sentinel(sentinel) {}
				rbt_iterator(iterator<T, T REF, T*, extractKey> CREF rhs) : _current(rhs._current), _sentinel(rhs._sentinel) {}
				~rbt_iterator() {}

	// In/Equality Operator
	template <class U, class URef, class UPtr, class UExtractKey>
	bool operator	== (rbt_iterator<U, URef, UPtr, UExtractKey> CREF rhs) { return this->_current == rhs._current; }
	template <class U, class URef, class UPtr, class UExtractKey>
	bool operator	!= (rbt_iterator<U, URef, UPtr, UExtractKey> CREF rhs) { return this->_current != rhs._current; }

	// Dereference Operator
	reference	operator  * () { return _current->value; }
	pointer		operator -> () { return &(operator*()); }

	// Shift Operators
	this_type REF	operator ++ () {
		if (_current != _sentinel)
			_current = RBT_NODE(_current->nextNode());
		if (!_current)
			_current = RBT_NODE(const_cast<base_type*>(_sentinel));
		return *this;
	}
	this_type		operator ++ (int) { this_type tmp = *this; operator++(); return tmp; }

	this_type REF	operator -- () {
		if (_current == _sentinel)
			_current = RBT_NODE(_sentinel->right());
		else
			_current = RBT_NODE(_current->prevNode());
		if (!_current)
			_current = RBT_NODE(_sentinel);
		return *this;
	}
	this_type		operator -- (int) { this_type tmp = *this; operator--(); return tmp; }

	// Attributes
	node_type	*_current;
	base_type	const* _sentinel;
};


template <
	typename T,
	typename Comp = ft::less<T>,
	typename Allocator = allocator<T>,
	typename extractKey = ft::false_type,
	bool mutableIterators = false
>
struct rbt {
	public:
		// Base Typedefs
		typedef T												key_type;
		typedef T												value_type;
		typedef Comp											key_compare;
		typedef Comp											value_compare;
		typedef Allocator										allocator_type;
		typedef value_type REF									reference;
		typedef value_type CREF									const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;

		typedef rbt_iterator<T,
			CONDITIONAL_TT(mutableIterators, T REF, T CREF),
			CONDITIONAL_TT(mutableIterators, T *, T const*),
			extractKey
		>														iterator;
		typedef rbt_iterator<T, T CREF, T const*, extractKey>	const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef ft::ptrdiff_t									difference_type;
		typedef ft::size_t										size_type;

		// Inherited typedefs wrapper
		typedef rbt<T, Comp, Allocator>					this_type;
		typedef rbt_node<T>								node_type;
		typedef rbt_node_base							base_type;
		typedef base_type::color_type					color_type;
		typedef base_type::side_type					side_type;
		typedef typename node_type::remove_result		remove_result;

		// Constructors
		rbt(key_compare CREF comp = key_compare(), allocator_type CREF alloc = allocator_type())
			:  _sentinel(), _root(NULL), _comp(comp), _size(0), _allocator(alloc) {}
		~rbt();

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

		// Modifiers
		iterator		insert(value_type CREF val);
		remove_result	erase(value_type CREF val);
		void			swap(this_type REF other);
		void			clear();

		// Observers
		key_compare		key_comp() const;
		value_compare	value_comp() const;

		// Operations
		iterator						find(value_type CREF val);
		const_iterator					find(value_type CREF val) const;
		size_type						count(value_type CREF val) const;
		iterator						lower_bound(value_type CREF val) const;
		iterator						upper_bound(value_type CREF val) const;
		ft::pair<iterator, iterator>	equal_range(value_type CREF val) const;

		// Allocator
		allocator_type	get_allocator() const;


	public:
		// Typedefs
		typedef typename allocator_type::template rebind<node_type>::other _node_allocator_type;

		// Methods
		node_type*				_createNode(value_type CREF val);
		remove_result			_fastErase(node_type* toRemove);
		void					_insertFixup(node_type* inserted);
		void					_eraseFixup(remove_result result);
		void					_clearTree(node_type* node);

		// Static Members
		static void				_deallocateNode(_node_allocator_type allocator, node_type* node);

		// Attributes
		base_type				_sentinel;
		node_type*				_root;
		key_compare				_comp;
		size_type				_size;
		mutable allocator_type	_allocator;
		_node_allocator_type	_node_allocator() { return _node_allocator_type(_allocator); }
};


// Helper Class Definition
template <typename extractKey, typename Comp>
struct ValueComparator {};


template <typename Comp>
struct ValueComparator<ft::false_type, Comp>  { // Don't extract keys
	explicit ValueComparator(Comp CREF comp) : _comp(comp) {}
	template <typename T>	bool operator()(T CREF lhs, T CREF rhs) { return _comp(lhs, rhs); }
	template <typename T>	bool operator()(T CREF lhs, T CREF rhs) const { return _comp(lhs, rhs); }
	Comp CREF _comp;
};


template <typename Comp>
struct ValueComparator<ft::true_type, Comp>  { // Extract keys
	explicit ValueComparator(Comp CREF comp) : _comp(comp) {}
	template <typename T>	bool operator()(T CREF lhs, T CREF rhs) { return _comp(lhs.first, rhs.first); }
	template <typename T>	bool operator()(T CREF lhs, T CREF rhs) const { return _comp(lhs.first, rhs.first); }
	Comp CREF _comp;
};


} // namespace internal
} // namespace ft


// Helper Functions
template <typename T>
static
typename ft::internal::rbt_node<T>::remove_result
noChildRemove(ft::internal::rbt_node<T>* node);


template <typename T>
static
typename ft::internal::rbt_node<T>::remove_result
oneChildRemove(ft::internal::rbt_node<T>* node);


template <typename T>
static
typename ft::internal::rbt_node<T>::remove_result
twoChildrenRemove(ft::internal::rbt_node<T>* node);


#include "binary_trees.tpp"


#undef RBT_NODE
#undef RBT_RED
#undef RBT_BLACK
#undef RBT_RIGHT
#undef RBT_LEFT

#endif // BINARY_TREE_HPP
