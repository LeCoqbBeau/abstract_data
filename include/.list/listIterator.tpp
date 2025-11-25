//
// Created by mscheman on 11/19/25.
//

#ifndef LIST_ITERATOR_TPP
#define LIST_ITERATOR_TPP

template <typename T, typename Pointer, typename Reference>
ft::ListIterator<T, Pointer, Reference>::ListIterator() FT_NOTHROW
	: mpNode()
{}


template <typename T, typename Pointer, typename Reference>
typename ft::ListIterator<T, Pointer, Reference>::this_type
ft::ListIterator<T, Pointer, Reference>::next() const FT_NOTHROW
{
	return ListIterator(mpNode->mpNext);
}


template <typename T, typename Pointer, typename Reference>
typename ft::ListIterator<T, Pointer, Reference>::this_type
ft::ListIterator<T, Pointer, Reference>::prev() const FT_NOTHROW
{
	return ListIterator(mpNode->mpPrev);
}


template <typename T, typename Pointer, typename Reference>
typename ft::ListIterator<T, Pointer, Reference>::reference
ft::ListIterator<T, Pointer, Reference>::operator * () const FT_NOTHROW
{
	return static_cast<node_type*>(mpNode)->mValue;
}


template <typename T, typename Pointer, typename Reference>
typename ft::ListIterator<T, Pointer, Reference>::pointer
ft::ListIterator<T, Pointer, Reference>::operator -> () const FT_NOTHROW
{
	return &static_cast<node_type*>(mpNode)->mValue;
}


template <typename T, typename Pointer, typename Reference>
typename ft::ListIterator<T, Pointer, Reference>::this_type REF
ft::ListIterator<T, Pointer, Reference>::operator ++ () FT_NOTHROW
{
	mpNode = mpNode->mpNext;
	return *this;
}


template <typename T, typename Pointer, typename Reference>
typename ft::ListIterator<T, Pointer, Reference>::this_type
ft::ListIterator<T, Pointer, Reference>::operator ++ (int) FT_NOTHROW
{
	this_type temp(*this);
	mpNode = mpNode->mpNext;
	return temp;
}


template <typename T, typename Pointer, typename Reference>
typename ft::ListIterator<T, Pointer, Reference>::this_type REF
ft::ListIterator<T, Pointer, Reference>::operator -- () FT_NOTHROW
{
	mpNode = mpNode->mpPrev;
	return *this;
}


template <typename T, typename Pointer, typename Reference>
typename ft::ListIterator<T, Pointer, Reference>::this_type
ft::ListIterator<T, Pointer, Reference>::operator -- (int) FT_NOTHROW
{
	this_type temp(*this);
	mpNode = mpNode->mpPrev;
	return temp;
}


template <typename T, typename Pointer, typename Reference>
ft::ListIterator<T, Pointer, Reference>::ListIterator(ListNodeBase const* pNode) FT_NOTHROW
	: mpNode(const_cast<base_node_type*>(pNode))
{}


#endif //LIST_ITERATOR_TPP
