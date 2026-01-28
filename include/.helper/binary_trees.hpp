
#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include "ftdef.hpp"
#include "algorithm.hpp"
#include "functional.hpp"

#define RBT_LEFT	0
#define RBT_RIGHT	1
#define RBT_BLACK	0
#define RBT_RED		1


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
	this_type*		nextNode(); // this is used for iterators purpose
	this_type*		prevNode(); // this is used for iterators purpose
	void			transplant(this_type* other);

	// Attributes
	this_type*	next[2];
	this_type*	parent;
	color_type	color;
};


template <typename T, typename Comp = ft::less<T> >
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
	typedef rbt_node<T, Comp>	this_type;
	typedef rbt_node_base		base_type;
	typedef	T					value_type;
	typedef Comp				value_compare;
	typedef RemoveResult		remove_result;


	// Constructor
	rbt_node(value_type CREF val = value_type(), base_type* parent = NULL)
		: rbt_node_base(parent, RBT_RED), value(val), comp(value_compare()) {}

	// Methods
	this_type*														find(value_type CREF val);
	this_type*														insert(this_type* node);
	template <typename Allocator, typename FreeFunc> remove_result	remove(Allocator allocator, FreeFunc free);


	// Attributes
	value_type		value;
	value_compare	comp;
};


template <typename T, typename Comp = ft::less<T>, typename Allocator = allocator<T> >
struct rb_tree {
	public:
		// Typedefs
		typedef T									value_type;
		typedef Comp								value_compare;
		typedef Allocator							allocator_type;
		typedef rbt_node<T, Comp>					node_type;
		typedef rbt_node_base						base_type;
		typedef base_type::color_type				color_type;
		typedef typename node_type::remove_result	remove_result;

		// Constructors
		rb_tree(allocator_type CREF alloc = allocator_type()) :  _sentinel(), _root(NULL), _allocator(alloc) {}
		~rb_tree();

		// Methods
		node_type*		begin();
		node_type*		begin() const;
		node_type*		end();
		node_type*		end() const;

		node_type*		find(value_type CREF val);
		node_type*		insert(value_type CREF val);
		remove_result	remove(value_type CREF val);


	public:
		// Typedefs
		typedef typename allocator_type::template rebind<node_type>::other _node_allocator_type;

		// Methods
		node_type*		_createNode(value_type CREF val);
		void			_removeCleanup(remove_result result);
		void			_clearTree(node_type* node);

		// Static Members
		static void		_deallocateNode(_node_allocator_type allocator, node_type* node);

		// Attributes
		base_type				_sentinel;
		node_type*				_root;
		mutable allocator_type	_allocator;
		_node_allocator_type	_node_allocator() { return _node_allocator_type(_allocator); }
};


} // namespace internal
} // namespace ft


template <typename T, typename Comp>
static
typename ft::internal::rbt_node<T, Comp>::remove_result
noChildRemove(ft::internal::rbt_node<T, Comp>* node);


template <typename T, typename Comp>
static
typename ft::internal::rbt_node<T, Comp>::remove_result
oneChildRemove(ft::internal::rbt_node<T, Comp>* node);


template <typename T, typename Comp>
static
typename ft::internal::rbt_node<T, Comp>::remove_result
twoChildrenRemove(ft::internal::rbt_node<T, Comp>* node);


#include "binary_trees.tpp"


#endif // BINARY_TREE_HPP
