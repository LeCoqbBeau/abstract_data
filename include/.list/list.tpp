
#ifndef LIST_TPP
# define LIST_TPP

template <class T, class Allocator>
ft::list<T, Allocator>::list(allocator_type CREF allocator)
	: base_type(allocator)
{}


template <class T, class Allocator>
ft::list<T, Allocator>::list(size_type n, value_type CREF value, allocator_type CREF allocator)
	: base_type(allocator)
{
	DoInsertValues(&internalNode(), n, value);
}


template <class T, class Allocator>
template <typename InputIterator>
ft::list<T, Allocator>::list(InputIterator first, InputIterator last, allocator_type CREF allocator)
	: base_type(allocator)
{
	DoInsert(&internalNode(), first, last, traits::is_integral<InputIterator>());
}


template <class T, class Allocator>
ft::list<T, Allocator>::list(this_type CREF other)
	: base_type(other.internalAllocator())
{
	DoInsert(&internalNode(), const_iterator(other.internalNode().mpNext), const_iterator(&other.internalNode()), traits::false_type());
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::this_type REF
ft::list<T, Allocator>::operator = (this_type CREF other) {
	if (this != &other)
		DoAssign(other.begin(), other.end(), traits::false_type());
	return *this;
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::iterator ft::list<T, Allocator>::begin() FT_NOTHROW {
	return iterator(internalNode().mpNext);
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::const_iterator ft::list<T, Allocator>::begin() const FT_NOTHROW {
	return const_iterator(internalNode().mpNext);
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::iterator ft::list<T, Allocator>::end() FT_NOTHROW {
	return iterator(&internalNode());
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::const_iterator ft::list<T, Allocator>::end() const FT_NOTHROW {
	return const_iterator(&internalNode());
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::reverse_iterator ft::list<T, Allocator>::rbegin() FT_NOTHROW {
	return reverse_iterator(&internalNode());
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::const_reverse_iterator ft::list<T, Allocator>::rbegin() const FT_NOTHROW {
	return reverse_iterator(&internalNode());
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::reverse_iterator ft::list<T, Allocator>::rend() FT_NOTHROW {
	return reverse_iterator(internalNode().mpNext);
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::const_reverse_iterator ft::list<T, Allocator>::rend() const FT_NOTHROW {
	return reverse_iterator(internalNode().mpNext);
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::reference
ft::list<T, Allocator>::front() {
	return static_cast<node_type*>(internalNode().mpNext)->mValue;
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::const_reference
ft::list<T, Allocator>::front() const {
	return static_cast<node_type*>(internalNode().mpNext)->mValue;
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::reference
ft::list<T, Allocator>::back() {
	return static_cast<node_type*>(internalNode().mpPrev)->mValue;
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::const_reference
ft::list<T, Allocator>::back() const {
	return static_cast<node_type*>(internalNode().mpPrev)->mValue;
}


template <class T, class Allocator>
bool ft::list<T, Allocator>::empty() const FT_NOTHROW {
	return internalNode().mpNext == &internalNode();
}


template <typename T, typename Allocator>
typename ft::list<T, Allocator>::size_type
ft::list<T, Allocator>::size() const FT_NOTHROW {
	return static_cast<size_type>(
		ft::distance(
			const_iterator(internalNode().mpNext,
				const_iterator(&internalNode))
		)
	);
}


// Protected
template <class T, class Allocator>
typename ft::list<T, Allocator>::node_type*
ft::list<T, Allocator>::DoCreateNode(value_type CREF value)
{
	return DoAllocateNode(value);
}


template <typename T, typename Allocator>
template <typename Integer>
void ft::list<T, Allocator>::DoAssign(Integer n, Integer value, traits::true_type)
{
	DoAssignValues(static_cast<size_type>(n), static_cast<value_type>(value));
}


template <class T, class Allocator>
template <typename Integer>
void ft::list<T, Allocator>::DoInsert(ListNodeBase *pNode, Integer n, Integer value, traits::true_type)
{
	DoInsertValues(pNode, static_cast<size_type>(n), static_cast<value_type>(value));
}


template <typename T, typename Allocator>
template <typename InputIterator>
void ft::list<T, Allocator>::DoAssign(InputIterator first, InputIterator last, traits::false_type)
{
	node_type *pNode = static_cast<node_type*>(internalNode().mpNext);

	for (; (pNode != &internalNode()) && (first != last); ++first)
	{
		pNode->mValue = *first;
		pNode         = static_cast<node_type*>(pNode->mpNext);
	}

	if (first == last)
		erase(const_iterator(pNode), &internalNode());
	else
		DoInsert(&internalNode(), first, last, traits::false_type());
}


template <typename T, typename Allocator>
void ft::list<T, Allocator>::DoAssignValues(size_type n, value_type CREF value)
{
	node_type *pNode = static_cast<node_type*>(internalNode().mpNext);

	for (; (pNode != &internalNode()) && (n > 0); --n)
	{
		pNode->mValue = value;
		pNode         = static_cast<node_type*>(pNode->mpNext);
	}

	if(n)
		DoInsertValues(&internalNode(), n, value);
	else
		erase(const_iterator(pNode), &internalNode());
}


template <class T, class Allocator>
template <typename InputIterator>
void ft::list<T, Allocator>::DoInsert(ListNodeBase *pNode, InputIterator first, InputIterator last, traits::false_type)
{
	for (; first != last; ++first)
		DoInsertValue(pNode, *first);
}


template <class T, class Allocator>
void ft::list<T, Allocator>::DoInsertValues(ListNodeBase *pNode, size_type n, value_type CREF value)
{
	for(; n; --n)
		DoInsertValue(pNode, value);
}


template <class T, class Allocator>
void ft::list<T, Allocator>::DoInsertValue(ListNodeBase *pNode, value_type CREF value)
{
	node_type* const pNodeNew = DoCreateNode(value);
	pNodeNew->insert(pNode);
}


template <typename T, typename Allocator>
void ft::list<T, Allocator>::DoErase(ListNodeBase *pNode)
{
	pNode->remove();
	static_cast<node_type*>(pNode)->~node_type();
	DoFreeNode(static_cast<node_type*>(pNode));
}


template <typename T, typename Allocator>
void ft::list<T, Allocator>::DoSwap(this_type REF x) {
	ListNodeBase::swap(
		static_cast<ListNodeBase REF>(internalNode()),
		static_cast<ListNodeBase REF>(x.internalNode())
	);
	algo::swap(internalAllocator(), x.internalNode());
}



#endif