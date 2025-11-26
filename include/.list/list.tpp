
#ifndef LIST_TPP
#define LIST_TPP

#include ".helper/algorithm.h"
#include ".helper/functional.h"

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
	DoInsert(&internalNode(), first, last, ft::is_integral<InputIterator>());
}


template <class T, class Allocator>
ft::list<T, Allocator>::list(this_type CREF other)
	: base_type(other.internalAllocator())
{
	DoInsert(&internalNode(), const_iterator(other.internalNode().mpNext), const_iterator(&other.internalNode()), ft::false_type());
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::this_type REF
ft::list<T, Allocator>::operator = (this_type CREF other) {
	if (this != &other)
		DoAssign(other.begin(), other.end(), ft::false_type());
	return *this;
}


template <typename T, typename Allocator>
void ft::list<T, Allocator>::swap(this_type REF x)
{
	if (internalAllocator() == x.internalAllocator()) // If allocators are equivalent...
		DoSwap(x);
	else // else swap the contents.
	{
		const this_type temp(*this); // Can't call eastl::swap because that would
		*this = x;                   // itself call this member swap function.
		x     = temp;
	}
}


template <class T, class Allocator>
void ft::list<T, Allocator>::assign(size_type n, value_type CREF value)
{
	DoAssignValues(n, value);
}


template <class T, class Allocator>
template <typename InputIterator>
void ft::list<T, Allocator>::assign(InputIterator first, InputIterator last)
{
	DoAssign(first, last, ft::is_integral<InputIterator>());
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
bool ft::list<T, Allocator>::empty() const FT_NOTHROW {
	return internalNode().mpNext == &internalNode();
}


template <typename T, typename Allocator>
typename ft::list<T, Allocator>::size_type
ft::list<T, Allocator>::size() const FT_NOTHROW {
	return static_cast<size_type>(
		ft::distance(
			const_iterator(internalNode().mpNext),
				const_iterator(&internalNode())
		)
	);
}


template <typename T, typename Allocator>
typename ft::list<T, Allocator>::size_type
ft::list<T, Allocator>::max_size() const FT_NOTHROW {
	return static_cast<size_type>(
		internalNodeAllocator().max_size()
	);
}


template <class T, class Allocator>
void ft::list<T, Allocator>::resize(size_type n, value_type CREF value)
{
	iterator current(internalNode().mpNext);
	size_type i = 0;

	while((current.mpNode != &internalNode()) && (i < n))
	{
		++current;
		++i;
	}
	if(i == n)
		erase(current, &internalNode());
	else
		insert(&internalNode(), n - i, value);
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
void ft::list<T, Allocator>::push_front(value_type CREF value)
{
	DoInsertValue(internalNode().mpNext, value);
}


template <class T, class Allocator>
void ft::list<T, Allocator>::push_back(value_type CREF value)
{
	DoInsertValue(&internalNode(), value);
}


template <class T, class Allocator>
void ft::list<T, Allocator>::pop_front()
{
	DoErase(internalNode().mpNext);
}


template <class T, class Allocator>
void ft::list<T, Allocator>::pop_back()
{
	DoErase(internalNode().mpPrev);
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::iterator
ft::list<T, Allocator>::insert(iterator position, value_type CREF value)
{
	ListNodeBase *const pNode = DoCreateNode(value);
	pNode->insert(position.mpNode);
	return pNode;
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::iterator
ft::list<T, Allocator>::insert(iterator position, size_type count, value_type CREF value)
{
	iterator itPrev(position.mpNode);
	--itPrev;
	DoInsertValues(position.mpNode, count, value);
	return ++itPrev;
}


template <class T, class Allocator>
template <class InputIterator>
typename ft::list<T, Allocator>::iterator
ft::list<T, Allocator>::insert(iterator position, InputIterator first, InputIterator last)
{
	iterator itPrev(position.mpNode);
	--itPrev;
	DoInsert(position.mpNode, first, last, IS_INTEGRAL_TT(InputIterator)());
	return ++itPrev;
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::iterator
ft::list<T, Allocator>::erase(iterator position)
{
	++position;
	DoErase(position.mpNode->mpPrev);
	return iterator(position.mpNode);
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::iterator
ft::list<T, Allocator>::erase(iterator first, iterator last)
{
	while (first != last)
		first = erase(first);
	return iterator(last.mpNode);
}


template <class T, class Allocator>
void ft::list<T, Allocator>::clear() FT_NOTHROW
{
	DoClear();
	DoInit();
}


template <class T, class Allocator>
void ft::list<T, Allocator>::remove(value_type CREF value)
{
	iterator current(internalNode().mpNext);

	while (current.mpNode != &internalNode())
	{
		if (FT_LIKELY(!(*current == value)))
			++current;
		else
		{
			++current;
			DoErase(current.mpNode->mpPrev);
		}
	}
}


template <class T, class Allocator>
template <class Predicate>
void ft::list<T, Allocator>::remove_if(Predicate predicate)
{
	iterator current(internalNode().mpNext);

	for (iterator first(internalNode().mpNext), last(&internalNode()); first != last; )
	{
		iterator temp(first);
		++temp;
		if (predicate(static_cast<node_type*>(first.mpNode)->mValue))
			DoErase(first.mpNode);
		first = temp;
	}
}


template <class T, class Allocator>
void ft::list<T, Allocator>::reverse() FT_NOTHROW
{
	internalNode().reverse();
}


template <class T, class Allocator>
void ft::list<T, Allocator>::splice(iterator position, this_type REF x)
{
	if (internalAllocator() == x.internalAllocator())
	{
		if (!x.empty())
			(position.mpNode)->splice(x.internalNode().mpNext, &x.internalNode());
	}
	else
	{
		insert(position, x.begin(), x.end());
		x.clear();
	}
}


template <class T, class Allocator>
void ft::list<T, Allocator>::splice(iterator position, this_type REF x, iterator i)
{
	if (internalAllocator() == x.internalAllocator())
	{
		iterator i2(i.mpNode);
		++i2;
		if ((position != i) && (position != i2))
			(position.mpNode)->splice(i.mpNode, i2.mpNode);
	}
	else
	{
		insert(position, *i);
		x.erase(i);
	}
}


template <class T, class Allocator>
void ft::list<T, Allocator>::splice(iterator position, this_type REF x, iterator first, iterator last)
{
	if (internalAllocator() == x.internalAllocator())
	{
		if (first != last)
			(position.mpNode)->splice(first.mpNode, last.mpNode);
	}
	else
	{
		insert(position, first, last);
		x.erase(first, last);
	}
}


template <class T, class Allocator>
void ft::list<T, Allocator>::merge(this_type REF other)
{
	if (this != &other)
	{
		iterator       first(begin());
		iterator       firstX(other.begin());
		iterator const last(end());
		iterator const lastX(other.end());

		while ((first != last) && (firstX != lastX))
		{
			if (*firstX < *first)
			{
				iterator next(firstX);

				splice(first, other, firstX, ++next);
				firstX = next;
			}
			else
				++first;
		}

		if (firstX != lastX)
			splice(last, other, firstX, lastX);
	}
}


template <class T, class Allocator>
template <class Compare>
void ft::list<T, Allocator>::merge(this_type REF other, Compare compare)
{
	if (this != &other)
	{
		iterator       first(begin());
		iterator       firstX(other.begin());
		iterator const last(end());
		iterator const lastX(other.end());

		while ((first != last) && (firstX != lastX))
		{
			if (compare(*firstX, *first))
			{
				iterator next(firstX);

				splice(first, other, firstX, ++next);
				firstX = next;
			}
			else
				++first;
		}

		if (firstX != lastX)
			splice(last, other, firstX, lastX);
	}
}


template <class T, class Allocator>
void ft::list<T, Allocator>::unique()
{
	iterator       first(begin());
	iterator const last(end());

	if (first != last)
	{
		iterator next(first);

		while (++next != last)
		{
			if (*first == *next)
			{
				DoErase(next.mpNode);
				next = first;
			}
			else
			{
				first = next;
			}
		}
	}
}


template <class T, class Allocator>
template <class BinaryPredicate>
void ft::list<T, Allocator>::unique(BinaryPredicate predicate)
{
	iterator       first(begin());
	iterator const last(end());

	if (first != last)
	{
		iterator next(first);

		while (++next != last)
		{
			if (predicate(*first, *next))
			{
				DoErase(next.mpNode);
				next = first;
			}
			else
			{
				first = next;
			}
		}
	}
}


template <typename T, typename Allocator>
void ft::list<T, Allocator>::sort()
{
	ft::less<value_type> compare;
	DoSort(begin(), end(), size(), compare);
}


template <typename T, typename Allocator>
template <typename Compare>
void ft::list<T, Allocator>::sort(Compare compare)
{
	DoSort(begin(), end(), size(), compare);
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
void ft::list<T, Allocator>::DoAssign(Integer n, Integer value, ft::true_type)
{
	DoAssignValues(static_cast<size_type>(n), static_cast<value_type>(value));
}


template <class T, class Allocator>
template <typename Integer>
void ft::list<T, Allocator>::DoInsert(ListNodeBase *pNode, Integer n, Integer value, ft::true_type)
{
	DoInsertValues(pNode, static_cast<size_type>(n), static_cast<value_type>(value));
}


template <typename T, typename Allocator>
template <typename InputIterator>
void ft::list<T, Allocator>::DoAssign(InputIterator first, InputIterator last, ft::false_type)
{
	node_type *pNode = static_cast<node_type*>(internalNode().mpNext);

	for (; (pNode != &internalNode()) && (first != last); ++first)
	{
		pNode->mValue = *first;
		pNode         = static_cast<node_type*>(pNode->mpNext);
	}

	if (first == last)
		erase(iterator(pNode), &internalNode());
	else
		DoInsert(&internalNode(), first, last, ft::false_type());
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

	if (n)
		DoInsertValues(&internalNode(), n, value);
	else
		erase(iterator(pNode), &internalNode());
}


template <class T, class Allocator>
template <typename InputIterator>
void ft::list<T, Allocator>::DoInsert(ListNodeBase *pNode, InputIterator first, InputIterator last, ft::false_type)
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
		internalNode(),
		x.internalNode()
	);
	ft::swap(internalAllocator(), x.internalAllocator());
}


template <class T, class Allocator>
template <typename Compare>
typename ft::list<T, Allocator>::iterator
ft::list<T, Allocator>::DoSort(iterator i1, iterator end2, size_type n, Compare REF compare)
{
	// A previous version of this function did this by creating temporary lists,
	// but that was incompatible with fixed_list because the sizes could be too big.
	// We sort subsegments by recursive descent. Then merge as we ascend.
	// Return an iterator to the beginning of the sorted subsegment.
	// Start with a special case for small node counts.
	switch (n)
	{
		case 0:
		case 1:
			return i1;

		case 2:
			// Potentialy swap these two nodes and return the resulting first of them.
			if (compare(*--end2, *i1))
			{
				end2.mpNode->remove();
				end2.mpNode->insert(i1.mpNode);
				return end2;
			}
			return i1;

		case 3:
		{
			// We do a list insertion sort. Measurements showed this improved performance 3-12%.
			iterator lowest = i1;

			for (iterator current = i1.next(); current != end2; ++current)
			{
				if (compare(*current, *lowest))
					lowest = current;
			}

			if (lowest == i1)
				++i1;
			else
			{
				lowest.mpNode->remove();
				lowest.mpNode->insert(i1.mpNode);
			}

			if (compare(*--end2, *i1)) // At this point, i1 refers to the second element in this three element segment.
			{
				end2.mpNode->remove();
				end2.mpNode->insert(i1.mpNode);
			}

			return lowest;
		}
	 }

	// Divide the range into two parts are recursively sort each part. Upon return we will have
	// two halves that are each sorted but we'll need to merge the two together before returning.
	iterator  result;
	size_type nMid = (n / 2);
	iterator  end1 = ft::next(i1, (difference_type)nMid);
			  i1   = DoSort(i1, end1, nMid, compare);        // Return the new beginning of the first sorted sub-range.
	iterator  i2   = DoSort(end1, end2, n - nMid, compare);  // Return the new beginning of the second sorted sub-range.

	// If the start of the second list is before the start of the first list, insert the first list
	// into the second at an appropriate starting place.
	if(compare(*i2, *i1))
	{
		// Find the position to insert the first list into the second list.
		iterator ix = i2.next();
		while((ix != end2) && compare(*ix, *i1))
			++ix;

		// Cut out the initial segment of the second list and move it to be in front of the first list.
		ListNodeBase* i2Cut     = i2.mpNode;
		ListNodeBase* i2CutLast = ix.mpNode->mpPrev;
		result = i2;
		end1   = i2 = ix;
		ListNodeBase::remove_range(i2Cut, i2CutLast);
		i1.mpNode->insert_range(i2Cut, i2CutLast);
	}
	else
	{
		result = i1;
		end1   = i2;
	}

	// Merge the two segments. We do this by merging the second sub-segment into the first, by walking forward in each of the two sub-segments.
	for(++i1; (i1 != end1) && (i2 != end2); ++i1) // while still working on either segment...
	{
		if(compare(*i2, *i1)) // If i2 is less than i1 and it needs to be merged in front of i1...
		{
			// Find the position to insert the i2 list into the i1 list.
			iterator ix = i2.next();
			while((ix != end2) && compare(*ix, *i1))
				++ix;

			// Cut this section of the i2 sub-segment out and merge into the appropriate place in the i1 list.
			ListNodeBase* i2Cut     = i2.mpNode;
			ListNodeBase* i2CutLast = ix.mpNode->mpPrev;
			if(end1 == i2)
				end1 = ix;
			i2 = ix;
			ListNodeBase::remove_range(i2Cut, i2CutLast);
			i1.mpNode->insert_range(i2Cut, i2CutLast);
		}
	}

	return result;
}


#endif