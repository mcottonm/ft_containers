/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 10:22:06 by mcottonm          #+#    #+#             */
/*   Updated: 2021/03/25 15:07:35 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "ft_list.hpp"

namespace ft
{
	template<typename T, class Allocator=std::allocator<T> >
	class deque
	{
	public:
		typedef typename 		vector<T>::value_type 			_Sequence_value_type;
		typedef typename        vector<T>::value_type            value_type;
		typedef typename        vector<T>::reference             reference;
      	typedef typename        vector<T>::const_reference       const_reference;
      	typedef typename        vector<T>::size_type             size_type;
		typedef typename        vector<T>::allocator_type         allocator_type;
      	typedef                	vector<T>                         container_type;
		typedef typename 		vector<T>::const_iterator			const_iterator;
		typedef typename 		vector<T>::iterator					iterator;
		typedef typename 		vector<T>::const_reverse_iterator	const_reverse_iterator;
		typedef typename 		vector<T>::reverse_iterator			reverse_iterator;
		
	private:
		container_type c;
		allocator_type allocator;
	
	public:
		
		explicit deque(const allocator_type& alloc = allocator_type()): c(alloc) {}

		explicit deque(size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type()): c(n, val, alloc) {}

		template <typename _Val, template< typename > class  _InputIterator>
		deque(_InputIterator <_Val> first, _InputIterator <_Val> last,
				const allocator_type& alloc = allocator_type()): c(first, last, alloc) {}

		deque (const deque& x): c(x.c) {}
		
		~deque() {}
		
		deque& operator= (const deque& x) {c = x.c; return *this;}
		
//Iterators:
	
		iterator begin() {return c.begin();}
		iterator end() {return c.end();}
		const_iterator begin() const {return c.begin();}
		const_iterator end() const {return c.end();}
		reverse_iterator rbegin() {return c.rbegin();}
		reverse_iterator rend() {return c.rend();}
		const_reverse_iterator rbegin() const {return c.rbegin();}
		const_reverse_iterator rend() const {return c.rend();}

//Capacity:

		size_type size() const
		{
			return c.size();
		}
		
		size_type max_size() const
		{
			return allocator.max_size();
		}

		void resize (size_type n, value_type val = value_type())
		{
			return c.resize(n,val);
		}

		bool empty() const
		{
			return c.empty();
		}

//Element access:
	
		reference operator[] (size_type n)
		{
			return c[n];
		}

		const_reference operator[] (size_type n) const
		{
			return(c[n]);
		}

		reference at(size_type n)
		{
			return(c.at(n));
		}

		const_reference at(size_type n) const
		{
			return(c.at(n));
		}
		
		reference front()
		{
			return(c.front());
		}

		const_reference front() const
		{
			return(c.front());
		}
		
		reference back()
		{
			return(c.back());
		}

		const_reference back() const
		{
			return(c.back());
		}

//Modifiers:
		
		template <typename _Val, template< typename > class  _InputIterator>
		void assign(_InputIterator <_Val> first, _InputIterator <_Val> last)
		{
			c.assign(first, last);
		}

		void assign(size_type n, const value_type& val)
		{
			c.assign(n, val);
		}

		void push_back(const value_type& val)
		{
			c.push_back(val);
		}

		void push_front(const value_type& val)
		{
			c.insert(begin(), val);
		}

		void pop_back()
		{
			c.pop_back();
		}

		void pop_front()
		{
			c.erase(end() - 1);
		}

		iterator insert(iterator position, const value_type& val)
		{
			return c.insert(position, val);
		}

		void insert(iterator position, size_type n, const value_type& val)
		{
			c.insert(position, n, val);
		}

		template <typename _Val, template< typename > class  _InputIterator>
    	void insert (iterator position, _InputIterator <_Val> first, _InputIterator <_Val>  last)
		{
			c.insert(position, first, last);
		}
		
		iterator erase (iterator position)
		{
			return c.erase(position);
		}
		
		iterator erase (iterator first, iterator last)
		{
			return c.erase(first, last);
		}

		void swap(deque& x)
		{
			c.swap(x);
		}

		void clear()
		{
			c.clear();
		}
	};
	
	template <class T, class Alloc>
  	bool operator!= (const deque<T,Alloc>& l, const deque<T,Alloc>& r)
	{
		if (l.size() - r.size())
			return true;
		for (size_t i = 0; i < l.size(); i++)
			if (l[i] != r[i])
				return true;
		return false;
	}
	
	template <class T, class Alloc>
  	bool operator== (const deque<T,Alloc>& l, const deque<T,Alloc>& r)
	{
		if (l.size() - r.size())
			return false;
		for (size_t i = 0; i < l.size(); i++)
			if (l[i] != r[i])
				return false;
		return true;
	}
	
	template <class T, class Alloc>
  	bool operator>= (const deque<T,Alloc>& l, const deque<T,Alloc>& r)
	{
		for (size_t i = 0; (i != l.size() && i != r.size()); i++) {
			if (l[i] > r[i]) return true;
			if (r[i] > l[i]) return false;
		}
		return (l.size() >= r.size());
	}
	
	template <class T, class Alloc>
 	bool operator<= (const deque<T,Alloc>& l, const deque<T,Alloc>& r)
	{
		for (size_t i = 0; (i != l.size() && i != r.size()); i++) {
			if (l[i] < r[i]) return true;
			if (r[i] < l[i]) return false;
		}
		return (l.size() <= r.size());
	}
	
	template <class T, class Alloc>
  	bool operator> (const deque<T,Alloc>& l, const deque<T,Alloc>& r)
	{
		for (size_t i = 0; (i != l.size() && i != r.size()); i++) {
			if (l[i] > r[i]) return true;
			if (r[i] > l[i]) return false;
		}
		return (l.size() > r.size());
	}
	
	template <class T, class Alloc>
  	bool operator< (const deque<T,Alloc>& l, const deque<T,Alloc>& r)
	{
		for (size_t i = 0; (i != l.size() && i != r.size()); i++) {
			if (l[i] < r[i]) return true;
			if (r[i] < l[i]) return false;
		}
		return (l.size() < r.size());
	}
	
	template <class T, class Alloc>
 	void swap (deque<T,Alloc>& x, deque<T,Alloc>& y)
	{
		x.swap(y);
	}
}