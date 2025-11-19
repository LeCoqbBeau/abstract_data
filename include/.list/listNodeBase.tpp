//
// Created by mscheman on 11/19/25.
//

#ifndef LIST_NODE_BASE_TPP
#define LIST_NODE_BASE_TPP

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

	if(a.mpNext == &b)
		a.mpNext = a.mpPrev = &a;
	else
		a.mpNext->mpPrev = a.mpPrev->mpNext = &a;

	if(b.mpNext == &a)
		b.mpNext = b.mpPrev = &b;
	else
		b.mpNext->mpPrev = b.mpPrev->mpNext = &b;
}


inline void ft::ListNodeBase::insert_range(ListNodeBase *pFirst, ListNodeBase *pLast) FT_NOTHROW {

}


inline void ft::ListNodeBase::remove_range(ListNodeBase *pFirst, ListNodeBase *pLast) FT_NOTHROW {

}


#endif //LIST_NODE_BASE_TPP
