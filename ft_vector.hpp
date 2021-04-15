/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 20:23:54 by mcottonm          #+#    #+#             */
/*   Updated: 2021/04/14 16:50:55 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <vector>
# include <cstring>
# include <string>
# include <cassert>
# include <utility>
# include <type_traits>
# include <algorithm>
# include "ft_ra_iterator.hpp"

// template <bool Res, typename T>
// 	struct enable_if {};

// 	template <typename T>
// 	struct enable_if<false, T> { typedef void type; };

// 	template <typename T>
// 	struct enable_if<true, T> { typedef T type; };

namespace ft
{
	template <class T, class Allocator=std::allocator<T> >
	class vector
	{
	public:
		typedef Allocator							allocator_type;
		typedef T									value_type;
		typedef std::size_t							size_type;
		typedef value_type&							reference;
		typedef const value_type&					const_reference;
		typedef value_type*							pointer;
		typedef const pointer						const_pointer;
		typedef Iterator<const value_type>			const_iterator;
		typedef Iterator<value_type>		   		iterator;
		typedef reverseIterator<iterator>	   		reverse_iterator;
		typedef reverseIterator<const_iterator>		const_reverse_iterator;
		

	private:
		allocator_type								allocator;
		pointer										data;
		size_type									_size;
		size_type									_capacity;

	public:
//coplien:
		vector(const allocator_type& alloc=allocator_type())
		:allocator(alloc),data(0), _size(0), _capacity(0){}
		
		template <typename _Val, template< typename > class  _InputIterator>
		vector(_InputIterator <_Val> first, _InputIterator <_Val> last,
					const allocator_type& alloc = allocator_type())
		{
			allocator = alloc;
			_capacity = last - first;
			_size = _capacity;
			data = allocator.allocate(_capacity);
			for(int i = 0; first != last; i++)
			{
				allocator.construct(&data[i], *first);
				++first;
			}
		}

		vector(size_type count, const_reference value = value_type(),
				const allocator_type& alloc = allocator_type())
		: allocator(alloc)
		, data(allocator.allocate(count))
		, _size(count)
		, _capacity(count)
		{
			while(count--)
				allocator.construct(&data[count], value);
		}
		
		vector(const vector& other)
		: allocator(other.allocator)
		, _size(other._size)
		, _capacity(other._capacity)
		{
			if (_capacity)
				data = allocator.allocate(_capacity);
			for(size_t i = 0; i < _size; i++)
				allocator.construct(&data[i], other.data[i]);
		}


		~vector()
		{
			clear();
			if (_capacity)
				allocator.deallocate(data, _capacity);
			_capacity = 0;
			_size = 0;
		}
		
		vector &operator=(const vector& other)
		{
			if (this == &other)
				return *this;
			if (_capacity)
				this->~vector();
			data = allocator.allocate(other._capacity);
			for(size_t i = 0; i < other._size; i++)
				allocator.construct(&data[i], other.data[i]);
			_size = other._size;
			_capacity = other._capacity;
			return(*this);
		}
		
		allocator_type get_allocator() const
		{
			return(allocator);
		}
//iterators:

		template <template <typename> class const_iterator>
		operator const_iterator<const value_type>() 
		{
			return const_iterator<const value_type>(data);
		}
		
		iterator begin()
		{
			return (data);
		}
		
		const_iterator begin() const
		{
			return (data);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(!_size ? 0 : end());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(!_size ? 0 : end());
		}	
		iterator end()
		{
			return(data + _size);
		}
		
		const_iterator end() const
		{
			return(data + _size);
		}

		reverse_iterator rend()
		{
			return reverse_iterator(data - 1);
		}
		
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(data - 1);
		}
//capcity:
		size_type size(void) const
		{
			return(_size);
		}
		
		size_type capacity(void) const
		{
			return(_capacity);
		}

		size_type max_size(void)
		{
			return(allocator.max_size());
		}
		
		void resize(size_type n, value_type val = value_type())
		{
			if (n >= max_size())
				throw std::length_error("vector");
			while (n < _size)
				allocator.destroy(&data[--_size]);
			if (n > _size)
			{
				reserve(n);
				for (size_type i = _size; i < n; i++)
					allocator.construct(&data[i], val);
				_size = n;
			}
		}
		
		void reserve(size_type n)
		{
			if (n >= max_size())
				throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
			if (_capacity < n)
			{
				pointer tmp = allocator.allocate(n);
				if (_size)
					std::memcpy(tmp, data, sizeof(value_type) * _size);
				allocator.deallocate(data, _capacity);
				_capacity = n;
				data = tmp;
			}
		}
		
		bool empty(void) const
		{
			return (!_size);
		}
		
//Element access:
		reference operator[] (size_type n)
		{
			return(data[n]);
		}
		
		const_reference operator[] (size_type n) const
		{
			return(data[n]);
		}
		
		reference at(size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("vector");
			return(data[n]);
		}

		const_reference at(size_type n) const
		{
			return(at(n));
		}

		reference front(void)
		{
			return(data[0]);
		}

		const_reference front(void) const
		{
			return(data[0]);
		}
		
		reference back(void)
		{
			return(data[_size - 1]);
		}

		const_reference back(void) const
		{
			return(data[_size - 1]);
		}

//Modifiers:

		template <typename _Val, template< typename > class  _InputIterator>
		void assign(_InputIterator <_Val> first, _InputIterator <_Val> last)
		{
			size_type new_size = last - first;
			if (new_size > _capacity)
			{
				this->~vector();
				if (new_size > max_size())
					throw std::length_error("vector");
				data = allocator.allocate(new_size);
				_capacity = new_size;
			}
			pointer tmp = allocator.allocate(1);
			for(int i = 0; first + i != last; i++)
			{
				tmp[0] = data[i];
				allocator.construct(&data[i], *(first + i));
				allocator.destroy(&tmp[0]);
			}
			allocator.deallocate(tmp, 1);
			_size = new_size;
		}

		void assign (size_type n, const value_type& val)
		{
			if (_capacity)
				this->~vector();
			reserving(n);
			for(size_type i = 0; i < _size; i++)
				allocator.destroy(&data[i]);
			_size = n;
			while(n--)
				allocator.construct(&data[n], val);
		}

		void push_back(const value_type val)
		{
			if (_capacity == _size && _capacity)
				reserve(_capacity * 2);
			else if (_capacity == _size)
				reserve(1);
			allocator.construct(&data[_size++], val);
		}
		
		void pop_back(void)
		{
			allocator.destroy(&data[--_size]);
		}

		void clear(void)
		{
			while(_size)
				allocator.destroy(&data[--_size]);
		}

	private:
		void reserving(size_type n)
		{
			if (2 * _capacity <= _size + n)
				reserve(n + _size);
			else if (2 * _capacity > _size + n && _capacity < _size + n)
				reserve(2 * _capacity);
			if (_capacity < n)
				reserve(n);
			if (!n)
				reserve(1);
		}

		void shifting(iterator position, size_type range)
		{
			size_type n_shift = end() - position;
			std::memmove(&*(position + range), &*position, n_shift * sizeof(value_type));
		}
		
	public:		
		iterator insert (iterator position, const value_type val)
		{
			size_type position_shift = position - begin();
			if (position == end())
			{
				push_back(val);
				position = begin() + position_shift;
			}
			else if (position < end())
			{
				reserving(_size);
				position = begin() + position_shift;
				shifting(position, 1);
				*position = val;
				_size++;
			}
			return (position);
		}

		void insert (iterator position, size_type n, const value_type val)
		{
			size_type position_shift = position - begin();
			reserving(n);
			position = begin() + position_shift;
			if (position == end())
			{
				for (size_type i = 0; i < n; i++)
					allocator.construct(&*position + i, val);
			}
			else if (position < end())
			{
				shifting(position, n);
				for (size_type i = 0; i < n; i++)
					allocator.construct(&*position + i, val);
			}
			_size += n;
		}

		template <typename _Val, template< typename > class  _InputIterator>
    	void insert (iterator position, _InputIterator <_Val> first, _InputIterator <_Val>  last)
		{
			size_type range = last - first;
			size_type position_shift = position - begin();
			if (last > first && first >= begin() && last <= end())
			{
				pointer tmp = allocator.allocate(range);
				for (size_type i = 0; i != range; i++)
					allocator.construct(&*tmp + i, *(first + i));
				first = tmp;
				last = tmp + range;
			}
			reserving(range);
			position = begin() + position_shift;
			if (position == end())
			{
				for (size_type i = 0; i != range; i++)
					allocator.construct(&*position + i, *(first + i));
			}
			else if (position < end())
			{
				shifting(position,range);
				for (size_type i = 0; i != range; i++)
					allocator.construct(&*position + i, *(first + i));
			}
			_size += range;
		}

		iterator erase(iterator position)
		{
			allocator.destroy(&*position);
			size_type position_shift = end() - position - 1;
			std::memmove(&*position, &*position + 1, position_shift * sizeof(value_type));
			--_size;
			return(position);
		}

		iterator erase(iterator first, iterator last)
		{
			size_type range = last - first;
			for (size_type i = 0; i < range; i++)
				allocator.destroy(&*(first + i));
			std::memmove(&*first, &*last, (end() - last) * sizeof(value_type));
			_size -= range;
			return(first);
		}

		void swap (vector& x)
		{
			allocator_type	tmp_allocator = x.allocator;
			size_type	tmp__size = x._size;
			size_type	tmp__capacity = x._capacity;
			pointer	tmp_data = x.data;
			
			x.allocator = allocator;
			x._size = _size;
			x._capacity = _capacity;
			x.data = data;
			
			allocator = tmp_allocator;
			_size = tmp__size;
			_capacity = tmp__capacity;
			data = tmp_data;
		}

		friend bool operator!=(const vector& l, const vector& r)
		{
			if (l._size - r._size)
				return true;
			for (size_type i = 0; i < l._size; i++)
				if (l[i] != r[i])
					return true;
			return false;
		}
		
		friend bool operator==(const vector& l, const vector& r)
		{
			if (l._size - r._size)
				return false;
			for (size_type i = 0; i < l._size; i++)
				if (l[i] != r[i])
					return false;
			return true;
		}

		friend bool operator>=(const vector& l, const vector& r)
		{
			for (size_type i = 0; (i != l._size && i != r._size); i++) {
				if (l[i] > r[i]) return true;
				if (r[i] > l[i]) return false;
			}
			return (l._size >= r._size);
		}

		friend bool operator<=(const vector& l, const vector& r)
		{
			for (size_type i = 0; (i != l._size && i != r._size); i++) {
				if (l[i] < r[i]) return true;
				if (r[i] < l[i]) return false;
			}
			return (l._size <= r._size);
		}
		
		friend bool operator>(const vector& l, const vector& r)
		{
			for (size_type i = 0; (i != l._size && i != r._size); i++) {
				if (l[i] > r[i]) return true;
				if (r[i] > l[i]) return false;
			}
			return (l._size > r._size);
		}
		
		friend bool operator<(const vector& l, const vector& r)
		{
			for (size_type i = 0; (i != l._size && i != r._size); i++) {
				if (l[i] < r[i]) return true;
				if (r[i] < l[i]) return false;
			}
			return (l._size < r._size);
			// Iterator<const value_type> first_l = l.begin();
			// Iterator<const value_type> first_r = r.begin();
		
			// for (; (first_l != l.end()) && (first_r != r.end()); ++first_l, (void) ++first_r ) {
			// 	if (*first_l < *first_r) return true;
			// 	if (*first_r < *first_l) return false;
			// }
			// return (first_l != l.end()) && (first_r == r.end());
		}

	};
	
	template <class T, class Alloc>
 	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}
}