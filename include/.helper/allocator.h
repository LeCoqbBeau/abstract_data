//
// Created by mscheman on 11/27/25.
//

#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "ftdef.h"
#include "new.h"
#include "limits.h"


namespace ft
{
template <class T>
struct allocator
{
	typedef T				value_type;
	typedef T*				pointer;
	typedef T const*		const_pointer;
	typedef T REF			reference;
	typedef T CREF			const_reference;
	typedef ft::size_t		size_type;
	typedef ft::ptrdiff_t	difference_type;
	template <class U>
	struct rebind
	{
		typedef allocator<U> other;
	};

	allocator() FT_NOTHROW {}
	allocator(allocator CREF other) FT_NOTHROW  {}
	template <class U>
	allocator(allocator<U> CREF other) FT_NOTHROW {}
	~allocator() {}

	pointer address(reference x) const
	{
		return reinterpret_cast<pointer>(
			&const_cast<char REF>(
				reinterpret_cast<char const volatile REF>(x)
			)
		);
	}


	const_pointer address(const_reference x) const
	{
		return reinterpret_cast<const_pointer>(
			&const_cast<char REF>(
				reinterpret_cast<char const volatile REF>(x)
			)
		);
	}


	pointer allocate(size_type n, void const* hint = 0)
	{
		(void)hint;
		if (n > ft::numeric_limits<size_t>::max() / sizeof(T))
			throw ft::bad_array_new_length();
		try {
			return ::operator new (n * sizeof(T));
		} catch (...) {
			throw ft::bad_alloc();
		}
	}


	void deallocate(T* p, ft::size_t n)
	{
		(void)n;
		if (p)
			::operator delete(p);
	}


	size_type max_size() const FT_NOTHROW
	{
		return ft::numeric_limits<size_type>::max() / sizeof(value_type);
	}


	void construct(pointer p, const_reference val)
	{
		::new(static_cast<void*>(p)) T(val);
	}


	void destroy(pointer p)
	{
		p->~T();
	}


};


}


template <class T1, class T2>
bool operator == (ft::allocator<T1> CREF lhs, ft::allocator<T2> CREF rhs) FT_NOTHROW
{
	(void)lhs;
	(void)rhs;
	return true;
}


template <class T1, class T2>
bool operator != (ft::allocator<T1> CREF lhs, ft::allocator<T2> CREF rhs) FT_NOTHROW
{
	return !(lhs == rhs); // evaluate to false
}

#endif //ALLOCATOR_H
