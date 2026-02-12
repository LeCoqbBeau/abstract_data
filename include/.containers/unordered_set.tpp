//
// Created by mscheman on 2/4/26.
//

#ifndef UNORDERED_SET_TPP
#define UNORDERED_SET_TPP

//
//	unordered_set<Key, Hash, KeyEqual, Allocator>
//


// Constructors
template <class Key, class Hash, class KeyEqual, class Allocator>
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::unordered_set(UST_DEFAULT_PARAMETERS)
	: _hashmap(n, hash, equal, allocator)
{}


template <class Key, class Hash, class KeyEqual, class Allocator>
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::unordered_set(allocator_type CREF allocator)
	: _hashmap(HASHMAP_INIT_SIZE, hasher(), key_equal(), allocator)
{}


template <class Key, class Hash, class KeyEqual, class Allocator>
template <class InputIt>
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::unordered_set(InputIt first, InputIt last, UST_DEFAULT_PARAMETERS)
	: _hashmap(HASHMAP_INIT_SIZE, hasher(), key_equal(), allocator)
{
	_hashmap.insert(first, last);
}


template <class Key, class Hash, class KeyEqual, class Allocator>
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::unordered_set(unordered_set CREF rhs)
	: _hashmap(rhs)
{}


template <class Key, class Hash, class KeyEqual, class Allocator>
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::unordered_set(unordered_set CREF rhs, allocator_type allocator)
	: _hashmap(rhs)
{
	_hashmap._allocator = allocator;
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::unordered_set REF
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::operator = (unordered_set CREF rhs)
{
	if (this != &rhs) {
		_hashmap = rhs._hashmap;
	}
	return *this;
}


// Capacity
template <class Key, class Hash, class KeyEqual, class Allocator>
bool
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::empty() const
{
	return _hashmap.empty();
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::size_type
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::size() const
{
	return _hashmap.empty();
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::size_type
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::max_size() const
{
	return _hashmap.max_size();
}


// Iterators
template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::iterator
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::begin()
{
	return _hashmap.begin();
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::const_iterator
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::begin() const
{
	return _hashmap.begin();
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::local_iterator
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::begin(size_type n)
{
	return _hashmap.begin(n);
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::const_local_iterator
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::begin(size_type n) const
{
	return _hashmap.begin(n);
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::const_iterator
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::cbegin() const
{
	return _hashmap.cbegin();
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::const_local_iterator
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::cbegin(size_type n) const
{
	return _hashmap.cbegin(n);
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::iterator
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::end()
{
	return _hashmap.end();
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::const_iterator
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::end() const
{
	return _hashmap.end();
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::local_iterator
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::end(size_type n)
{
	return _hashmap.end(n);
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::const_local_iterator
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::end(size_type n) const
{
	return _hashmap.end(n);
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::const_iterator
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::cend() const
{
	return _hashmap.cend();
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::const_local_iterator
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::cend(size_type n) const
{
	return _hashmap.cend(n);
}


// Element Lookup
template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::iterator
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::find(key_type CREF key)
{
	return _hashmap.find(key);
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::const_iterator
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::find(key_type CREF key) const
{
	return _hashmap.find(key);
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::size_type
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::count(key_type CREF key) const
{
	return _hashmap.count(key);
}


template <class Key, class Hash, class KeyEqual, class Allocator>
ft::pair<typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::iterator, typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::iterator>
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::equal_range(key_type CREF key)
{
	return _hashmap.equal_range(key);
}


template <class Key, class Hash, class KeyEqual, class Allocator>
ft::pair<typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::const_iterator, typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::const_iterator>
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::equal_range(key_type CREF key) const
{
	return _hashmap.equal_range(key);
}


// Modifiers
template <class Key, class Hash, class KeyEqual, class Allocator>
ft::pair<typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::iterator, bool>
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::insert(value_type CREF value)
{
	iterator	elem = _tree.find(val);
	bool		isNew = false;
	if (elem == _tree.end()) {
		elem = _tree.insert(val);
		isNew = true;
	}
	return ft::make_pair(elem, isNew);
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::iterator
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::insert(const_iterator hint, value_type CREF value)
{
	(void)hint;
	iterator inserted = _hashmap.find(value);
	if (inserted == _hashmap.end())
		inserted = _hashmap.insert(value);
	return inserted;
}


template <class Key, class Hash, class KeyEqual, class Allocator>
template <class InputIt>
void
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::insert(InputIt first, InputIt last)
{
	_hashmap.insert(first, last);
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::iterator
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::erase(const_iterator position)
{
	return _hashmap.erase(position);
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::size_type
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::erase(key_type CREF key)
{
	return _hashmap.erase(key);
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::iterator
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::erase(const_iterator first, const_iterator last)
{
	return _hashmap.erase(first, last);
}


template <class Key, class Hash, class KeyEqual, class Allocator>
void
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::clear()
{
	_hashmap.clear();
}


template <class Key, class Hash, class KeyEqual, class Allocator>
void
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::swap(unordered_set REF rhs)
{
	_hashmap.swap(rhs);
}


// Buckets
template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::size_type
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::bucket_count() const
{
	return _hashmap.bucket_count();
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::size_type
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::max_bucket_count() const
{
	return _hashmap.max_bucket_count();
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::size_type
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::bucket_size(size_type n) const
{
	return _hashmap.bucket_size(n);
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::size_type
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::bucket(key_type CREF key) const
{
	return _hashmap.bucket(key);
}


// Hash policy
template <class Key, class Hash, class KeyEqual, class Allocator>
float
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::load_factor() const
{
	return _hashmap.load_factor();
}


template <class Key, class Hash, class KeyEqual, class Allocator>
float
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::max_load_factor() const
{
	return _hashmap.max_load_factor();
}


template <class Key, class Hash, class KeyEqual, class Allocator>
void
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::max_load_factor(float f)
{
	_hashmap.max_load_factor(f);
}


template <class Key, class Hash, class KeyEqual, class Allocator>
void
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::rehash(size_type n)
{
	_hashmap.rehash(n);
}


template <class Key, class Hash, class KeyEqual, class Allocator>
void
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::reserve(size_type n)
{
	_hashmap.reserve(n);
}


// Observers
template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::hasher
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::hash_function() const
{
	return _hashmap.hash_function();
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::key_equal
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::key_eq() const
{
	return _hashmap.key_eq();
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::unordered_set<Key, Hash, KeyEqual, Allocator>::allocator_type
ft::unordered_set<Key, Hash, KeyEqual, Allocator>::get_allocator() const
{
	return _hashmap.get_allocator();
}



#endif //UNORDERED_SET_TPP
