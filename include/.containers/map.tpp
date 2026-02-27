//
// Created by mscheman on 2/4/26.
//

#ifndef MAP_TPP
#define MAP_TPP

//
//	ft::map<>
//


// Constructors
template <typename Key, typename T, typename Compare, typename Allocator>
ft::map<Key, T, Compare, Allocator>::map(key_compare CREF comp, allocator_type CREF allocator)
	: _tree(comp, allocator)
{}


template <typename Key, typename T, typename Compare, typename Allocator>
template <typename InputIt>
ft::map<Key, T, Compare, Allocator>::map(InputIt first, InputIt last, key_compare CREF comp, allocator_type CREF allocator)
	: _tree(comp, allocator)
{
	insert(first, last);
}


template <typename Key, typename T, typename Compare, typename Allocator>
ft::map<Key, T, Compare, Allocator>::map(map CREF rhs)
	: _tree(rhs._tree._comp, rhs._tree._allocator)
{
	*this = rhs;
}


template <typename Key, typename T, typename Compare, typename Allocator>
ft::map<Key, T, Compare, Allocator> REF
ft::map<Key, T, Compare, Allocator>::operator = (map CREF rhs)
{
	if (this != &rhs) {
		_tree.clear();
		insert(rhs.begin(), rhs.end());
	}
	return *this;
}


template <typename Key, typename T, typename Comp, typename Allocator>
ft::map<Key, T, Comp, Allocator>::~map()
{}


// Iterators
template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::map<Key, T, Comp, Allocator>::iterator
ft::map<Key, T, Comp, Allocator>::begin()
{
	return _tree.begin();
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::map<Key, T, Comp, Allocator>::const_iterator
ft::map<Key, T, Comp, Allocator>::begin() const
{
	return _tree.begin();
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::map<Key, T, Comp, Allocator>::iterator
ft::map<Key, T, Comp, Allocator>::end()
{
	return _tree.end();
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::map<Key, T, Comp, Allocator>::const_iterator
ft::map<Key, T, Comp, Allocator>::end() const
{
	return _tree.end();
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::map<Key, T, Comp, Allocator>::reverse_iterator
ft::map<Key, T, Comp, Allocator>::rbegin()
{
	return _tree.rbegin();
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::map<Key, T, Comp, Allocator>::const_reverse_iterator
ft::map<Key, T, Comp, Allocator>::rbegin() const
{
	return _tree.rbegin();
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::map<Key, T, Comp, Allocator>::reverse_iterator
ft::map<Key, T, Comp, Allocator>::rend()
{
	return _tree.rend();
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::map<Key, T, Comp, Allocator>::const_reverse_iterator
ft::map<Key, T, Comp, Allocator>::rend() const
{
	return _tree.rend();
}


// Capacity
template <typename Key, typename T, typename Comp, typename Allocator>
bool
ft::map<Key, T, Comp, Allocator>::empty() const
{
	return _tree.empty();
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::map<Key, T, Comp, Allocator>::size_type
ft::map<Key, T, Comp, Allocator>::size() const
{
	return _tree.size();
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::map<Key, T, Comp, Allocator>::size_type
ft::map<Key, T, Comp, Allocator>::max_size() const
{
	return _tree.max_size();
}


// Element Access
template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::map<Key, T, Comp, Allocator>::mapped_type REF
ft::map<Key, T, Comp, Allocator>::operator[](key_type CREF key)
{
	value_type	pair(key, mapped_type());
	iterator elem = _tree.find(pair);
	if (elem == _tree.end())
		elem = _tree.insert(pair);
	return elem->second;
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::map<Key, T, Comp, Allocator>::mapped_type REF
ft::map<Key, T, Comp, Allocator>::at(key_type CREF key)
{
	iterator elem = _tree.find(ft::make_pair(key, mapped_type()));
	if (elem == _tree.end())
		throw ft::out_of_range(MAP_AT_EXCEPTION_MSG);
	return elem->second;
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::map<Key, T, Comp, Allocator>::mapped_type CREF
ft::map<Key, T, Comp, Allocator>::at(key_type CREF key) const
{
	iterator elem = _tree.find(key);
	if (elem == _tree.end())
		throw ft::out_of_range(MAP_AT_EXCEPTION_MSG);
	return elem->second;
}


// Modifiers
template <typename Key, typename T, typename Comp, typename Allocator>
ft::pair<typename ft::map<Key, T, Comp, Allocator>::iterator, bool>
ft::map<Key, T, Comp, Allocator>::insert(value_type CREF val)
{
	iterator	elem = _tree.find(val);
	bool		isNew = false;
	if (elem == _tree.end()) {
		elem = _tree.insert(val);
		isNew = true;
	}
	return ft::make_pair(elem, isNew);
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::map<Key, T, Comp, Allocator>::iterator
ft::map<Key, T, Comp, Allocator>::insert(iterator position, value_type CREF val)
{
	(void)position;
	iterator pos = _tree.find(val);
	if (pos != _tree.end())
		return pos;
	return _tree.insert(val);
}


template <typename Key, typename T, typename Comp, typename Allocator>
template <typename InputIt>
void
ft::map<Key, T, Comp, Allocator>::insert(InputIt first, InputIt last)
{
	while (first != last) {
		insert(*first);
		++first;
	}
}


template <typename Key, typename T, typename Comp, typename Allocator>
void
ft::map<Key, T, Comp, Allocator>::erase(iterator position)
{
	_tree._fastErase(position._current);
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::map<Key, T, Comp, Allocator>::size_type
ft::map<Key, T, Comp, Allocator>::erase(key_type CREF key)
{
	typedef typename rbt_type::remove_result	remove_result;

	remove_result result = _tree.erase(ft::make_pair(key, mapped_type()));
	if (result.parentNode == result.replacementNode && result.parentNode == &_tree._sentinel)
		return 0;
	return 1;
}


template <typename Key, typename T, typename Comp, typename Allocator>
void
ft::map<Key, T, Comp, Allocator>::erase(iterator first, iterator last)
{
	while (first != last) {
		iterator next = first;
		++next;
		_tree._fastErase(first._current);
		first = next;
	}
}


template <typename Key, typename T, typename Comp, typename Allocator>
void
ft::map<Key, T, Comp, Allocator>::swap(map REF other)
{
	_tree.swap(other._tree);
}


template <typename Key, typename T, typename Comp, typename Allocator>
void
ft::map<Key, T, Comp, Allocator>::clear()
{
	_tree.clear();
}


// Observers
template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::map<Key, T, Comp, Allocator>::key_compare
ft::map<Key, T, Comp, Allocator>::key_comp() const
{
	return _tree.key_comp();
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::map<Key, T, Comp, Allocator>::value_compare
ft::map<Key, T, Comp, Allocator>::value_comp() const
{
	return value_compare();
}


// Operations
template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::map<Key, T, Comp, Allocator>::iterator
ft::map<Key, T, Comp, Allocator>::find(value_type CREF val)
{
	return _tree.find(val);
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::map<Key, T, Comp, Allocator>::const_iterator
ft::map<Key, T, Comp, Allocator>::find(value_type CREF val) const
{
	return _tree.find(val);
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::map<Key, T, Comp, Allocator>::size_type
ft::map<Key, T, Comp, Allocator>::count(value_type CREF val) const
{
	return _tree.count(val);
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::map<Key, T, Comp, Allocator>::iterator
ft::map<Key, T, Comp, Allocator>::lower_bound(value_type CREF val) const
{
	return _tree.lower_bound(val);
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::map<Key, T, Comp, Allocator>::iterator
ft::map<Key, T, Comp, Allocator>::upper_bound(value_type CREF val) const
{
	return _tree.upper_bound(val);
}


template <typename Key, typename T, typename Comp, typename Allocator>
ft::pair<typename ft::map<Key, T, Comp, Allocator>::iterator>
ft::map<Key, T, Comp, Allocator>::equal_range(value_type CREF val) const
{
	return _tree.equal_range(val);
}


// Allocator
template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::map<Key, T, Comp, Allocator>::allocator_type
ft::map<Key, T, Comp, Allocator>::get_allocator() const
{
	return _tree.get_allocator();
}


//
//	ft::multimap<>
//


// Constructors
template <typename Key, typename T, typename Compare, typename Allocator>
ft::multimap<Key, T, Compare, Allocator>::multimap(key_compare CREF comp, allocator_type CREF allocator)
	: _tree(comp, allocator)
{}


template <typename Key, typename T, typename Compare, typename Allocator>
template <typename InputIt>
ft::multimap<Key, T, Compare, Allocator>::multimap(InputIt first, InputIt last, key_compare CREF comp, allocator_type CREF allocator)
	: _tree(comp, allocator)
{
	insert(first, last);
}


template <typename Key, typename T, typename Compare, typename Allocator>
ft::multimap<Key, T, Compare, Allocator>::multimap(multimap CREF rhs)
	: _tree(rhs._tree._comp, rhs._tree._allocator)
{
	*this = rhs;
}


template <typename Key, typename T, typename Compare, typename Allocator>
ft::multimap<Key, T, Compare, Allocator> REF
ft::multimap<Key, T, Compare, Allocator>::operator = (multimap CREF rhs)
{
	if (this != &rhs) {
		_tree.clear();
		insert(rhs.begin(), rhs.end());
	}
	return *this;
}


template <typename Key, typename T, typename Comp, typename Allocator>
ft::multimap<Key, T, Comp, Allocator>::~multimap()
{}


// Iterators
template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::multimap<Key, T, Comp, Allocator>::iterator
ft::multimap<Key, T, Comp, Allocator>::begin()
{
	return _tree.begin();
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::multimap<Key, T, Comp, Allocator>::const_iterator
ft::multimap<Key, T, Comp, Allocator>::begin() const
{
	return _tree.begin();
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::multimap<Key, T, Comp, Allocator>::iterator
ft::multimap<Key, T, Comp, Allocator>::end()
{
	return _tree.end();
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::multimap<Key, T, Comp, Allocator>::const_iterator
ft::multimap<Key, T, Comp, Allocator>::end() const
{
	return _tree.end();
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::multimap<Key, T, Comp, Allocator>::reverse_iterator
ft::multimap<Key, T, Comp, Allocator>::rbegin()
{
	return _tree.rbegin();
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::multimap<Key, T, Comp, Allocator>::const_reverse_iterator
ft::multimap<Key, T, Comp, Allocator>::rbegin() const
{
	return _tree.rbegin();
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::multimap<Key, T, Comp, Allocator>::reverse_iterator
ft::multimap<Key, T, Comp, Allocator>::rend()
{
	return _tree.rend();
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::multimap<Key, T, Comp, Allocator>::const_reverse_iterator
ft::multimap<Key, T, Comp, Allocator>::rend() const
{
	return _tree.rend();
}


// Capacity
template <typename Key, typename T, typename Comp, typename Allocator>
bool
ft::multimap<Key, T, Comp, Allocator>::empty() const
{
	return _tree.empty();
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::multimap<Key, T, Comp, Allocator>::size_type
ft::multimap<Key, T, Comp, Allocator>::size() const
{
	return _tree.size();
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::multimap<Key, T, Comp, Allocator>::size_type
ft::multimap<Key, T, Comp, Allocator>::max_size() const
{
	return _tree.max_size();
}


// Modifiers
template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::multimap<Key, T, Comp, Allocator>::iterator
ft::multimap<Key, T, Comp, Allocator>::insert(value_type CREF val)
{
	return _tree.insert(val);
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::multimap<Key, T, Comp, Allocator>::iterator
ft::multimap<Key, T, Comp, Allocator>::insert(iterator position, value_type CREF val)
{
	(void)position;
	return _tree.insert(val);
}


template <typename Key, typename T, typename Comp, typename Allocator>
template <typename InputIt>
void
ft::multimap<Key, T, Comp, Allocator>::insert(InputIt first, InputIt last)
{
	while (first != last) {
		_tree.insert(*first);
		++first;
	}
}


template <typename Key, typename T, typename Comp, typename Allocator>
void
ft::multimap<Key, T, Comp, Allocator>::erase(iterator position)
{
	_tree._fastErase(position._current);
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::multimap<Key, T, Comp, Allocator>::size_type
ft::multimap<Key, T, Comp, Allocator>::erase(key_type CREF key)
{
	typedef typename rbt_type::remove_result	remove_result;

	size_type		count = -1;
	remove_result	result;
	value_type		pair(key, mapped_type());
	do {
		result = _tree.erase(pair);
		++count;
	}
	while (!(result.parentNode == result.replacementNode && result.parentNode == &_tree._sentinel));
	return count;
}


template <typename Key, typename T, typename Comp, typename Allocator>
void
ft::multimap<Key, T, Comp, Allocator>::erase(iterator first, iterator last)
{
	while (first != last) {
		iterator next = first;
		++next;
		_tree._fastErase(first._current);
		first = next;
	}
}


template <typename Key, typename T, typename Comp, typename Allocator>
void
ft::multimap<Key, T, Comp, Allocator>::swap(multimap REF other)
{
	_tree.swap(other._tree);
}


template <typename Key, typename T, typename Comp, typename Allocator>
void
ft::multimap<Key, T, Comp, Allocator>::clear()
{
	_tree.clear();
}


// Observers
template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::multimap<Key, T, Comp, Allocator>::key_compare
ft::multimap<Key, T, Comp, Allocator>::key_comp() const
{
	return _tree.key_comp();
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::multimap<Key, T, Comp, Allocator>::value_compare
ft::multimap<Key, T, Comp, Allocator>::value_comp() const
{
	return value_compare();
}


// Operations
template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::multimap<Key, T, Comp, Allocator>::iterator
ft::multimap<Key, T, Comp, Allocator>::find(value_type CREF val)
{
	return _tree.find(val);
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::multimap<Key, T, Comp, Allocator>::const_iterator
ft::multimap<Key, T, Comp, Allocator>::find(value_type CREF val) const
{
	return _tree.find(val);
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::multimap<Key, T, Comp, Allocator>::size_type
ft::multimap<Key, T, Comp, Allocator>::count(value_type CREF val) const
{
	return _tree.count(val);
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::multimap<Key, T, Comp, Allocator>::iterator
ft::multimap<Key, T, Comp, Allocator>::lower_bound(value_type CREF val) const
{
	return _tree.lower_bound(val);
}


template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::multimap<Key, T, Comp, Allocator>::iterator
ft::multimap<Key, T, Comp, Allocator>::upper_bound(value_type CREF val) const
{
	return _tree.upper_bound(val);
}


template <typename Key, typename T, typename Comp, typename Allocator>
ft::pair<typename ft::multimap<Key, T, Comp, Allocator>::iterator>
ft::multimap<Key, T, Comp, Allocator>::equal_range(value_type CREF val) const
{
	return _tree.equal_range(val);
}


// Allocator
template <typename Key, typename T, typename Comp, typename Allocator>
typename ft::multimap<Key, T, Comp, Allocator>::allocator_type
ft::multimap<Key, T, Comp, Allocator>::get_allocator() const
{
	return _tree.get_allocator();
}


#endif //MAP_TPP
