/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ra_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:11:24 by mcottonm          #+#    #+#             */
/*   Updated: 2021/04/14 16:49:08 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>



namespace ft
{
	template <typename T>
	class Iterator
	{
	public:
		typedef Iterator<T>		self_type;
		typedef T			value_type;
		typedef ptrdiff_t	difference_type;
		typedef value_type* pointer;
		typedef value_type&	reference;
		
	private:
		pointer				ptr;
		
	public:
		
		Iterator():ptr(0) {}
		Iterator(const Iterator& other): ptr(other.ptr) {}
		Iterator(const pointer other): ptr(other) {}
		~Iterator() {}
		
		template <template <typename> class const_iterator>
		operator const_iterator<const value_type>() 
		{
			return const_iterator<const value_type>(ptr);
		}
		
		pointer base() const
		{
			return(ptr);
		}
		
		Iterator & operator= (const Iterator& other) { ptr = other.ptr; return *this; }
		Iterator & operator= (const pointer other) { ptr = other; return *this; }
		reference operator* () const { return *ptr; }
		pointer operator-> () { return ptr; }
		reference operator[] (difference_type n) const { return ptr[n]; }
		Iterator operator+ (difference_type n) const { return Iterator(ptr + n); }
		Iterator &operator++() { ++ptr; return *this; }
		Iterator operator++(int) { return Iterator(ptr++); }
		Iterator &operator+=(difference_type n) { ptr += n; return *this; }
		Iterator operator-(difference_type n) { return Iterator(ptr - n); }
		Iterator &operator--() { --ptr; return *this; }
		Iterator operator--(int) { return Iterator(ptr--); }
		Iterator &operator-=(difference_type n) { ptr -= n; return *this; }
		
		friend bool operator!=(const Iterator& l, const Iterator& r)
		{
			return l.ptr != r.ptr;
		}
		
		friend bool operator==(const Iterator& l, const Iterator& r)
		{
			return l.ptr == r.ptr;
		}

		friend bool operator>=(const Iterator& l, const Iterator& r)
		{
			return l.ptr >= r.ptr;
		}

		friend bool operator<=(const Iterator& l, const Iterator& r)
		{
			return l.ptr <= r.ptr;
		}
		
		friend bool operator<(const Iterator& l, const Iterator& r)
		{
			return l.ptr < r.ptr;
		}

		friend bool operator>(const Iterator& l, const Iterator& r)
		{
			return l.ptr > r.ptr;
		}
		
		friend difference_type operator-(const Iterator& l, const Iterator& r)
		{
			return l.ptr - r.ptr;
		}
		
		friend difference_type operator+(const Iterator& l, const Iterator& r)
		{
			return l.ptr + r.ptr;
		}
	};

	template <typename Iterator>
	class reverseIterator
	{
	public:
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
	private:
		pointer				ptr;
		
	public:
		reverseIterator():ptr(0) {}
		reverseIterator(const Iterator& other): ptr(other.base() - 1) {}
		reverseIterator(const reverseIterator& other): ptr(other.ptr) {}
		reverseIterator(const pointer other): ptr(other) {}
		virtual ~reverseIterator() {}
		
		pointer base() const
		{
			return(ptr);
		}
		
		template <template <typename> class const_iterator>
		operator const_iterator<const value_type>() 
		{
			return const_iterator<const value_type>(ptr);
		}
		
		reverseIterator & operator= (const reverseIterator& other) { ptr = other.ptr; return *this; }
		reverseIterator & operator= (const pointer other) { ptr = other; return *this; }
		reference operator* () const { return *ptr; }
		pointer operator-> () { return ptr; }
		reverseIterator operator+ (difference_type n) const { return reverseIterator(ptr - n); }
		reverseIterator &operator++() { --ptr; return *this; }
		reverseIterator operator++(int) { return reverseIterator(ptr--); }
		reverseIterator &operator+=(difference_type n) { ptr -= n; return *this; }
		reverseIterator operator-(difference_type n) { return reverseIterator(ptr + n); }
		reverseIterator &operator--() { ++ptr; return *this; }
		reverseIterator operator--(int) { return reverseIterator(ptr++); }
		reverseIterator &operator-=(difference_type n) { ptr += n; return *this; }

		friend bool operator!=(const reverseIterator& l, const reverseIterator& r)
		{
			return l.ptr != r.ptr;
		}
		
		friend bool operator==(const reverseIterator& l, const reverseIterator& r)
		{
			return l.ptr == r.ptr;
		}

		friend bool operator>=(const reverseIterator& l, const reverseIterator& r)
		{
			return l.ptr <= r.ptr;
		}

		friend bool operator<=(const reverseIterator& l, const reverseIterator& r)
		{
			return l.ptr >= r.ptr;
		}
		
		friend bool operator<(const reverseIterator& l, const reverseIterator& r)
		{
			return l.ptr > r.ptr;
		}

		friend bool operator>(const reverseIterator& l, const reverseIterator& r)
		{
			return l.ptr < r.ptr;
		}
		
		friend difference_type operator-(const reverseIterator& l, const reverseIterator& r)
		{
			return l.ptr + r.ptr;
		}
		
		friend difference_type operator+(const reverseIterator& l, const reverseIterator& r)
		{
			return l.ptr - r.ptr;
		}
	};
}