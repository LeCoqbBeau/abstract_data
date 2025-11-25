//
// Created by mscheman on 11/19/25.
//

#ifndef LIST_NODE_BASE_TPP
#define LIST_NODE_BASE_TPP

#include ".helper/algorithm.h"

inline void ft::ListNodeBase::insert(ListNodeBase *pNext) FT_NOTHROW {
	mpNext = pNext;
	mpPrev = pNext->mpPrev;
	pNext->mpPrev->mpNext = this;
	pNext->mpPrev = this;
}


inline void ft::ListNodeBase::remove() FT_NOTHROW {
	mpNext->mpPrev = mpPrev;
	mpPrev->mpNext = mpNext;
}


inline void ft::ListNodeBase::splice(ListNodeBase *pFirst, ListNodeBase *pLast) FT_NOTHROW {
	pLast->mpPrev->mpNext  = this;
	pFirst->mpPrev->mpNext = pLast;
	this->mpPrev->mpNext  = pFirst;

	ListNodeBase* const pTemp = this->mpPrev;
	this->mpPrev  = pLast->mpPrev;
	pLast->mpPrev  = pFirst->mpPrev;
	pFirst->mpPrev = pTemp;
}


inline void ft::ListNodeBase::reverse() FT_NOTHROW {
	ListNodeBase *pNode = this;
	do
	{
		ListNodeBase *const pTemp = pNode->mpNext;
		pNode->mpNext = pNode->mpPrev;
		pNode->mpPrev = pTemp;
		pNode         = pNode->mpPrev;
	}
	while(pNode != this);
}


inline void ft::ListNodeBase::swap(ListNodeBase REF a, ListNodeBase REF b) FT_NOTHROW {
	ft::swap(a, b);

	if (a.mpNext == &b) {
		a.mpPrev = &a;
		a.mpNext = a.mpPrev;
	} else {
		a.mpPrev->mpNext = &a;
		a.mpNext->mpPrev = a.mpPrev->mpNext;
	}

	if (b.mpNext == &a) {
		b.mpPrev = &b;
		b.mpNext = b.mpPrev;
	} else {
		b.mpPrev->mpNext = &b;
		b.mpNext->mpPrev = b.mpPrev->mpNext;
	}
}


inline void ft::ListNodeBase::insert_range(ListNodeBase *pFirst, ListNodeBase *pLast) FT_NOTHROW {
	mpPrev->mpNext = pFirst;
	pFirst->mpPrev = mpPrev;
	mpPrev         = pLast;
	pLast->mpNext = this;
}


inline void ft::ListNodeBase::remove_range(ListNodeBase *pFirst, ListNodeBase *pLast) FT_NOTHROW {
	pLast->mpNext->mpPrev = pFirst->mpPrev;
	pFirst->mpPrev->mpNext = pLast->mpNext;
}


#endif //LIST_NODE_BASE_TPP
