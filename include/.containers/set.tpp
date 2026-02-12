//
// Created by mscheman on 2/4/26.
//

#ifndef SET_TPP
#define SET_TPP

//
//	ft::set<>
//


// Constructors
template <typename Key, typename Compare, typename Allocator>
ft::set<Key, Compare, Allocator>::set(key_compare CREF comp, allocator_type CREF allocator)
	: _tree(comp, allocator)
{}


template <typename Key, typename Compare, typename Allocator>
template <typename InputIt>
ft::set<Key, Compare, Allocator>::set(InputIt first, InputIt last, key_compare CREF comp, allocator_type CREF allocator)
	: _tree(comp, allocator)
{
	insert(first, last);
}


template <typename Key, typename Compare, typename Allocator>
ft::set<Key, Compare, Allocator>::set(set CREF rhs)
	: _tree(rhs._tree._comp, rhs._tree._allocator)
{
	*this = rhs;
}


template <typename Key, typename Compare, typename Allocator>
ft::set<Key, Compare, Allocator> REF
ft::set<Key, Compare, Allocator>::operator = (set CREF rhs)
{
	if (this != &rhs) {
		_tree.clear();
		insert(rhs.begin(), rhs.end());
	}
	return *this;
}


template <typename T, typename Comp, typename Allocator>
ft::set<T, Comp, Allocator>::~set()
{}


// Iterators
template <typename T, typename Comp, typename Allocator>
typename ft::set<T, Comp, Allocator>::iterator
ft::set<T, Comp, Allocator>::begin()
{
	return _tree.begin();
}


template <typename T, typename Comp, typename Allocator>
typename ft::set<T, Comp, Allocator>::const_iterator
ft::set<T, Comp, Allocator>::begin() const
{
	return _tree.begin();
}


template <typename T, typename Comp, typename Allocator>
typename ft::set<T, Comp, Allocator>::iterator
ft::set<T, Comp, Allocator>::end()
{
	return _tree.end();
}


template <typename T, typename Comp, typename Allocator>
typename ft::set<T, Comp, Allocator>::const_iterator
ft::set<T, Comp, Allocator>::end() const
{
	return _tree.end();
}


template <typename T, typename Comp, typename Allocator>
typename ft::set<T, Comp, Allocator>::reverse_iterator
ft::set<T, Comp, Allocator>::rbegin()
{
	return _tree.rbegin();
}


template <typename T, typename Comp, typename Allocator>
typename ft::set<T, Comp, Allocator>::const_reverse_iterator
ft::set<T, Comp, Allocator>::rbegin() const
{
	return _tree.rbegin();
}


template <typename T, typename Comp, typename Allocator>
typename ft::set<T, Comp, Allocator>::reverse_iterator
ft::set<T, Comp, Allocator>::rend()
{
	return _tree.rend();
}


template <typename T, typename Comp, typename Allocator>
typename ft::set<T, Comp, Allocator>::const_reverse_iterator
ft::set<T, Comp, Allocator>::rend() const
{
	return _tree.rend();
}


// Capacity
template <typename T, typename Comp, typename Allocator>
bool
ft::set<T, Comp, Allocator>::empty() const
{
	return _tree.empty();
}


template <typename T, typename Comp, typename Allocator>
typename ft::set<T, Comp, Allocator>::size_type
ft::set<T, Comp, Allocator>::size() const
{
	return _tree.size();
}


template <typename T, typename Comp, typename Allocator>
typename ft::set<T, Comp, Allocator>::size_type
ft::set<T, Comp, Allocator>::max_size() const
{
	return _tree.max_size();
}


// Modifiers
template <typename T, typename Comp, typename Allocator>
ft::pair<typename ft::set<T, Comp, Allocator>::iterator, bool>
ft::set<T, Comp, Allocator>::insert(value_type CREF val)
{
	iterator	elem = _tree.find(val);
	bool		isNew = false;
	if (elem == _tree.end()) {
		elem = _tree.insert(val);
		isNew = true;
	}
	return ft::make_pair(elem, isNew);
}


template <typename T, typename Comp, typename Allocator>
typename ft::set<T, Comp, Allocator>::iterator
ft::set<T, Comp, Allocator>::insert(iterator position, value_type CREF val)
{
	(void)position;
	iterator inserted = _tree.find(val);
	if (inserted == _tree.end())
		inserted = _tree.insert(val);
	return inserted;
}


template <typename T, typename Comp, typename Allocator>
template <typename InputIt>
void
ft::set<T, Comp, Allocator>::insert(InputIt first, InputIt last)
{
	while (first != last) {
		insert(*first);
		++first;
	}
}


template <typename T, typename Comp, typename Allocator>
void
ft::set<T, Comp, Allocator>::erase(iterator position)
{
	_tree._fastErase(position._current);
}


template <typename T, typename Comp, typename Allocator>
typename ft::set<T, Comp, Allocator>::size_type
ft::set<T, Comp, Allocator>::erase(value_type CREF val)
{
	typedef typename rbt_type::remove_result	remove_result;

	remove_result result = _tree.erase(val);
	if (result.parentNode == result.replacementNode && result.parentNode == &_tree._sentinel)
		return 0;
	return 1;
}


template <typename T, typename Comp, typename Allocator>
void
ft::set<T, Comp, Allocator>::erase(iterator first, iterator last)
{
	while (first != last) {
		iterator next = ++first;
		_tree._fastErase(*first);
		first = next;
	}
}


template <typename T, typename Comp, typename Allocator>
void
ft::set<T, Comp, Allocator>::swap(set REF other)
{
	_tree.swap(other._tree);
}


template <typename T, typename Comp, typename Allocator>
void
ft::set<T, Comp, Allocator>::clear()
{
	_tree.clear();
}


// Observers
template <typename T, typename Comp, typename Allocator>
typename ft::set<T, Comp, Allocator>::key_compare
ft::set<T, Comp, Allocator>::key_comp() const
{
	return _tree.key_comp();
}


template <typename T, typename Comp, typename Allocator>
typename ft::set<T, Comp, Allocator>::value_compare
ft::set<T, Comp, Allocator>::value_comp() const
{
	return _tree.value_comp();
}


// Operations
template <typename T, typename Comp, typename Allocator>
typename ft::set<T, Comp, Allocator>::iterator
ft::set<T, Comp, Allocator>::find(value_type CREF val) const
{
	return _tree.find(val);
}


template <typename T, typename Comp, typename Allocator>
typename ft::set<T, Comp, Allocator>::size_type
ft::set<T, Comp, Allocator>::count(value_type CREF val) const
{
	return _tree.count(val);
}


template <typename T, typename Comp, typename Allocator>
typename ft::set<T, Comp, Allocator>::iterator
ft::set<T, Comp, Allocator>::lower_bound(value_type CREF val) const
{
	return _tree.lower_bound(val);
}


template <typename T, typename Comp, typename Allocator>
typename ft::set<T, Comp, Allocator>::iterator
ft::set<T, Comp, Allocator>::upper_bound(value_type CREF val) const
{
	return _tree.upper_bound(val);
}


template <typename T, typename Comp, typename Allocator>
ft::pair<
	typename ft::set<T, Comp, Allocator>::iterator,
	typename ft::set<T, Comp, Allocator>::iterator
>
ft::set<T, Comp, Allocator>::equal_range(value_type CREF val) const
{
	return _tree.equal_range(val);
}


// Allocator
template <typename T, typename Comp, typename Allocator>
typename ft::set<T, Comp, Allocator>::allocator_type
ft::set<T, Comp, Allocator>::get_allocator() const
{
	return _tree.get_allocator();
}


//
//	ft::multiset<>
//


// Constructors
template <typename Key, typename Compare, typename Allocator>
ft::multiset<Key, Compare, Allocator>::multiset(key_compare CREF comp, allocator_type CREF allocator)
	: _tree(comp, allocator)
{}


template <typename Key, typename Compare, typename Allocator>
template <typename InputIt>
ft::multiset<Key, Compare, Allocator>::multiset(InputIt first, InputIt last, key_compare CREF comp, allocator_type CREF allocator)
	: _tree(comp, allocator)
{
	insert(first, last);
}


template <typename Key, typename Compare, typename Allocator>
ft::multiset<Key, Compare, Allocator>::multiset(multiset CREF rhs)
	: _tree(rhs._tree._comp, rhs._tree._allocator)
{
	*this = rhs;
}


template <typename Key, typename Compare, typename Allocator>
ft::multiset<Key, Compare, Allocator> REF
ft::multiset<Key, Compare, Allocator>::operator = (multiset CREF rhs)
{
	if (this != &rhs) {
		_tree.clear();
		insert(rhs.begin(), rhs.end());
	}
	return *this;
}


template <typename T, typename Comp, typename Allocator>
ft::multiset<T, Comp, Allocator>::~multiset()
{}


// Iterators
template <typename T, typename Comp, typename Allocator>
typename ft::multiset<T, Comp, Allocator>::iterator
ft::multiset<T, Comp, Allocator>::begin()
{
	return _tree.begin();
}


template <typename T, typename Comp, typename Allocator>
typename ft::multiset<T, Comp, Allocator>::const_iterator
ft::multiset<T, Comp, Allocator>::begin() const
{
	return _tree.begin();
}


template <typename T, typename Comp, typename Allocator>
typename ft::multiset<T, Comp, Allocator>::iterator
ft::multiset<T, Comp, Allocator>::end()
{
	return _tree.end();
}


template <typename T, typename Comp, typename Allocator>
typename ft::multiset<T, Comp, Allocator>::const_iterator
ft::multiset<T, Comp, Allocator>::end() const
{
	return _tree.end();
}


template <typename T, typename Comp, typename Allocator>
typename ft::multiset<T, Comp, Allocator>::reverse_iterator
ft::multiset<T, Comp, Allocator>::rbegin()
{
	return _tree.rbegin();
}


template <typename T, typename Comp, typename Allocator>
typename ft::multiset<T, Comp, Allocator>::const_reverse_iterator
ft::multiset<T, Comp, Allocator>::rbegin() const
{
	return _tree.rbegin();
}


template <typename T, typename Comp, typename Allocator>
typename ft::multiset<T, Comp, Allocator>::reverse_iterator
ft::multiset<T, Comp, Allocator>::rend()
{
	return _tree.rend();
}


template <typename T, typename Comp, typename Allocator>
typename ft::multiset<T, Comp, Allocator>::const_reverse_iterator
ft::multiset<T, Comp, Allocator>::rend() const
{
	return _tree.rend();
}


// Capacity
template <typename T, typename Comp, typename Allocator>
bool
ft::multiset<T, Comp, Allocator>::empty() const
{
	return _tree.empty();
}


template <typename T, typename Comp, typename Allocator>
typename ft::multiset<T, Comp, Allocator>::size_type
ft::multiset<T, Comp, Allocator>::size() const
{
	return _tree.size();
}


template <typename T, typename Comp, typename Allocator>
typename ft::multiset<T, Comp, Allocator>::size_type
ft::multiset<T, Comp, Allocator>::max_size() const
{
	return _tree.max_size();
}


// Modifiers
template <typename T, typename Comp, typename Allocator>
typename ft::multiset<T, Comp, Allocator>::iterator
ft::multiset<T, Comp, Allocator>::insert(value_type CREF val)
{
	return _tree.insert(val);
}


template <typename T, typename Comp, typename Allocator>
typename ft::multiset<T, Comp, Allocator>::iterator
ft::multiset<T, Comp, Allocator>::insert(iterator position, value_type CREF val)
{
	(void)position;
	return _tree.insert(val);
}


template <typename T, typename Comp, typename Allocator>
template <typename InputIt>
void
ft::multiset<T, Comp, Allocator>::insert(InputIt first, InputIt last)
{
	while (first != last) {
		_tree.insert(*first);
		++first;
	}
}


template <typename T, typename Comp, typename Allocator>
void
ft::multiset<T, Comp, Allocator>::erase(iterator position)
{
	_tree._fastErase(position._current);
}


template <typename T, typename Comp, typename Allocator>
typename ft::multiset<T, Comp, Allocator>::size_type
ft::multiset<T, Comp, Allocator>::erase(value_type CREF val)
{
	typedef typename rbt_type::remove_result	remove_result;

	size_type	count = -1;
	remove_result result;
	do {
		result = _tree.erase(val);
		++count;
	}
	while (result.parentNode == result.replacementNode && result.parentNode == &_tree._sentinel);
	return count;
}


template <typename T, typename Comp, typename Allocator>
void
ft::multiset<T, Comp, Allocator>::erase(iterator first, iterator last)
{
	while (first != last) {
		iterator next = ++first;
		_tree._fastErase(*first);
		first = next;
	}
}


template <typename T, typename Comp, typename Allocator>
void
ft::multiset<T, Comp, Allocator>::swap(multiset REF other)
{
	_tree.swap(other._tree);
}


template <typename T, typename Comp, typename Allocator>
void
ft::multiset<T, Comp, Allocator>::clear()
{
	_tree.clear();
}


// Observers
template <typename T, typename Comp, typename Allocator>
typename ft::multiset<T, Comp, Allocator>::key_compare
ft::multiset<T, Comp, Allocator>::key_comp() const
{
	return _tree.key_comp();
}


template <typename T, typename Comp, typename Allocator>
typename ft::multiset<T, Comp, Allocator>::value_compare
ft::multiset<T, Comp, Allocator>::value_comp() const
{
	return _tree.value_comp();
}


// Operations
template <typename T, typename Comp, typename Allocator>
typename ft::multiset<T, Comp, Allocator>::iterator
ft::multiset<T, Comp, Allocator>::find(value_type CREF val) const
{
	return _tree.find(val);
}


template <typename T, typename Comp, typename Allocator>
typename ft::multiset<T, Comp, Allocator>::size_type
ft::multiset<T, Comp, Allocator>::count(value_type CREF val) const
{
	return _tree.count(val);
}


template <typename T, typename Comp, typename Allocator>
typename ft::multiset<T, Comp, Allocator>::iterator
ft::multiset<T, Comp, Allocator>::lower_bound(value_type CREF val) const
{
	return _tree.lower_bound(val);
}


template <typename T, typename Comp, typename Allocator>
typename ft::multiset<T, Comp, Allocator>::iterator
ft::multiset<T, Comp, Allocator>::upper_bound(value_type CREF val) const
{
	return _tree.upper_bound(val);
}


template <typename T, typename Comp, typename Allocator>
ft::pair<
	typename ft::multiset<T, Comp, Allocator>::iterator,
	typename ft::multiset<T, Comp, Allocator>::iterator
>
ft::multiset<T, Comp, Allocator>::equal_range(value_type CREF val) const
{
	return _tree.equal_range(val);
}


// Allocator
template <typename T, typename Comp, typename Allocator>
typename ft::multiset<T, Comp, Allocator>::allocator_type
ft::multiset<T, Comp, Allocator>::get_allocator() const
{
	return _tree.get_allocator();
}


#endif //SET_TPP
