//
// Created by mscheman on 11/20/25.
//

#ifndef LIST_BASE_TPP
#define LIST_BASE_TPP

#include <limits>

#include ".helper/ftexcept.h"

template <typename T, typename Allocator>
ft::ListBase<T, Allocator>::ListBase()
	: mNodeAllocator(base_node_type(), allocator_type())
{
	DoInit();
}


template <typename T, typename Allocator>
ft::ListBase<T, Allocator>::ListBase(allocator_type CREF a)
	: mNodeAllocator(base_node_type(), a)
{
	DoInit();
}


template <typename T, typename Allocator>
ft::ListBase<T, Allocator>::~ListBase()
{
	DoClear();
}


template <typename T, typename Allocator>
typename ft::ListBase<T, Allocator>::node_type*
ft::ListBase<T,Allocator>::DoAllocateNode(value_type CREF value) {
	node_type *pNode;
	try {
		pNode = internalNodeAllocator().allocate(sizeof(node_type));
	} catch (...) {
		throw ft::bad_alloc();
	}
	internalNodeAllocator().construct(pNode, node_type());
	pNode->mValue = value;
	return pNode;
}


template <typename T, typename Allocator>
void ft::ListBase<T,Allocator>::DoFreeNode(node_type *pNode) {
	internalNodeAllocator().deallocate(pNode, 1);
}


template <typename T, typename Allocator>
void ft::ListBase<T, Allocator>::DoInit() FT_NOTHROW {
	internalNode().mpNext = &internalNode();
	internalNode().mpPrev = &internalNode();
}


template <typename T, typename Allocator>
void ft::ListBase<T, Allocator>::DoClear() FT_NOTHROW {
	base_node_type *p = internalNode().mpNext;

	while(p != &internalNode())
	{
		node_type *pTemp = static_cast<node_type*>(p);
		p = p->mpNext;
		pTemp->~node_type();
		internalNodeAllocator().deallocate(pTemp, 1);
	}
}


template <typename T, typename Allocator>
typename ft::ListBase<T, Allocator>::allocator_type REF
ft::ListBase<T,Allocator>::get_allocator() FT_NOTHROW {
	return internalAllocator();
}


template <typename T, typename Allocator>
typename ft::ListBase<T, Allocator>::allocator_type CREF
ft::ListBase<T,Allocator>::get_allocator() const FT_NOTHROW {
	return internalAllocator();
}


#endif //LIST_BASE_TPP
