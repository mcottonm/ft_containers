/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:11:24 by mcottonm          #+#    #+#             */
/*   Updated: 2021/03/12 16:12:15 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>



namespace ft
{
	template <typename T>
	class iterator
	{
	public:
		typedef T			value_type;
		typedef ptrdiff_t	difference_type;
		typedef value_type* pointer;
		typedef value_type&	reference;
		
	private:
		pointer				ptr;
		
	public:
		iterator():ptr(0) {}
		iterator(const iterator& other): ptr(other.ptr) {}
		iterator(const pointer other): ptr(other) {}
		~iterator() {}
		iterator & operator= (const iterator& other) { ptr = other.ptr; return *this; }
		iterator & operator= (const pointer other) { ptr = other; return *this; }
		reference operator* () const { return *ptr; }
		pointer operator-> () { return ptr; }
		reference operator[] (difference_type n) const { return ptr[n]; }
		iterator operator+ (difference_type n) const { return iterator(ptr + n); }
		iterator &operator++() { ++ptr; return *this; }
		iterator operator++(int) { return iterator(ptr++); }
		iterator &operator+=(difference_type n) { ptr += n; return *this; }
		iterator operator-(difference_type n) { return iterator(ptr - n); }
		iterator &operator--() { --ptr; return *this; }
		iterator operator--(int) { return iterator(ptr--); }
		iterator &operator-=(difference_type n) { ptr -= n; return *this; }
		
		friend bool operator!=(const iterator& l, const iterator& r)
		{
			return l.ptr != r.ptr;
		}
		
		friend bool operator==(const iterator& l, const iterator& r)
		{
			return l.ptr == r.ptr;
		}

		friend bool operator>=(const iterator& l, const iterator& r)
		{
			return l.ptr >= r.ptr;
		}

		friend bool operator<=(const iterator& l, const iterator& r)
		{
			return l.ptr <= r.ptr;
		}
		
		friend bool operator<(const iterator& l, const iterator& r)
		{
			return l.ptr < r.ptr;
		}

		friend bool operator>(const iterator& l, const iterator& r)
		{
			return l.ptr > r.ptr;
		}
		
		friend difference_type operator-(const iterator& l, const iterator& r)
		{
			return l.ptr - r.ptr;
		}
		
		friend difference_type operator+(const iterator& l, const iterator& r)
		{
			return l.ptr + r.ptr;
		}
	};
}