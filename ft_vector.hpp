/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 20:23:54 by mcottonm          #+#    #+#             */
/*   Updated: 2021/03/13 18:07:04 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <vector>
# include <cstring>
# include "ft_iterator.hpp"

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
		typedef iterator<value_type>				iterator;
		typedef const iterator						const_iterator;

	private:
		allocator_type								allocator;
		size_type									_size;
		size_type									_capacity;
		pointer										data;
	public:
//coplien:
		vector(const allocator_type& alloc=allocator_type())
		:allocator(alloc),data(0), _size(0), _capacity(0){}
		
		template <typename _Val, template< typename > class  _InputIterator>
		vector(_InputIterator <_Val> first, _InputIterator <_Val> last,
					const allocator_type& alloc = allocator_type())
		{
			_capacity = last - first;
			_size = _capacity;
			data = allocator.allocate(_capacity);
			for(int i = 0; first != last; i++)
			{
				allocator.construct(&data[i], *first);
				++first;
			}
		}

		// template <class _InputIterator, typename SAFETY = typename _InputIterator::value_type >
		// vector(_InputIterator first, _InputIterator last,
		// 			const allocator_type& alloc = allocator_type())
		// {
		// 	_capacity = last - first;
		// 	_size = _capacity;
		// 	data = allocator.allocate(_capacity);
		// 	int i = 0;
		// 	while(first != last)
		// 	{
		// 		allocator.construct(&data[i], *first);
		// 		++first;
		// 		++i;
		// 	}
		// }

		vector(size_type count, const_reference value,
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
		:allocator(other.allocator)
		, _size(other._size)
		, _capacity(other._capacity)
		, data(allocator.allocate(_capacity))
		{
			for(size_t i = 0; i < _size; i++)
				allocator.construct(&data[i], other.data[i]);
		}


		~vector()
		{
			clear();
			allocator.deallocate(data, _capacity);
		}
		
		vector &operator=(const vector& other)
		{
			if (_capacity)
				this->~vector();
			data = allocator.allocate(other._capacity);
			for(size_t i = 0; i < other._size; i++)
				allocator.construct(&data[i], other.data[i]);
			_size = other._size;
			_capacity = other._capacity;
			return(*this);
		}
//iterators:

		iterator begin()
		{
			return(data);
		}

		iterator end()
		{
			return(data + _size);
		}

//capcity:
		size_type size(void)
		{
			return(_size);
		}
		
		size_type capacity(void)
		{
			return(_capacity);
		}

		size_type max_size(void)
		{
			return(allocator.max_size());
		}
		
		void resize(size_type n, value_type val = value_type())
		{
			while (n < _size--)
			{
				allocator.destroy(&data[_size]);
				_size = n;
			}
			if (n > _size)
			{
				reserve(n);
				for (size_type i = _size + 1; i < n; i++)
					allocator.construct(&data[i], val);
				_size = n;
			}
		}
		
		void reserve(size_type n)
		{
			if (n >= max_size())
				throw std::length_error("Out of max size.");
			if (_capacity < n)
			{
				pointer tmp = allocator.allocate(n);
				if (_size)
					std::memcpy(tmp, data, sizeof(value_type) * _size);
				clear();
				allocator.deallocate(data, _capacity);
				_capacity = n;
				data = tmp;
			}
		}
		
		bool empty(void) const
		{
			return (_size);
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
				throw std::out_of_range("Out of size.\n");
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
				data = allocator.allocate(new_size);
				_capacity = new_size;
			}
			else
				for(size_type i = 0; i < _size; i++)
					allocator.destroy(&data[i]);
			_size = new_size;
			for(int i = 0; first != last; i++)
			{
				allocator.construct(&data[i], *first);
				++first;
			}
		}

		void assign (size_type n, const value_type& val)
		{
			if (n > _capacity)
			{
				this->~vector();
				data = allocator.allocate(n);
				_capacity = n;
			}
			else
				for(size_type i = 0; i < _size; i++)
					allocator.destroy(&data[i]);
			_size = n;
			while(n--)
				allocator.construct(&data[n], val);
		}

		void push_back(const value_type& val)
		{
			if (_capacity == _size && _capacity)
				reserve(_capacity * 2);
			else if (_capacity == _size)
				reserve(1);
			data[_size++] = val;
		}
		
		void pop_back(void)
		{
			allocator.destroy(&data[--_size]);
		}

		void clear(void)
		{
			for (size_type i = 0; i < _size; i++)
				allocator.destroy(&data[i]);
		}

		iterator insert (iterator position, const value_type& val)
		{
			if (position == end())
			{
				size_type position_shift = position - begin();
				push_back(val);
				position = begin() + position_shift;
			}
			else if (position < end())
			{
				size_type n = end() - position;
				pointer shift = allocator.allocate(n);
				std::memcpy(shift, &*position, n * sizeof(value_type));
				*position = val;
				std::memcpy(&*position + 1, shift, n * sizeof(value_type));
				for (size_type i = 0; i < n; i++)
					allocator.destroy(&shift[i]);
				allocator.deallocate(shift, n);
				_size++;
			}
			return (position);
		}

		void insert (iterator position, size_type n, const value_type& val)
		{
			if (position == end())
			{
				if (2 * _capacity < _size + n)
					reserve(n + _size);
				else if (2 * _capacity > _size + n && _capacity < _size + n)
					reserve(2 * _capacity);
				for (size_type i = 0; n != i; i++)
					allocator.construct(&*position, val);
			}
			else if (position < end())
			{
				size_type position_shift = position - begin();
				size_type n_shift = end() - position;
				if (2 * _capacity < _size + n)
					reserve(n + _size );
				else if (2 * _capacity > _size + n && _capacity < _size + n)
					reserve(2 * _capacity);
				position = begin() + position_shift;
				pointer shift = allocator.allocate(n_shift);
				std::memcpy(shift, &*position, sizeof(value_type) * n_shift);
				*position = val;
				std::memcpy(&*position + n, shift, n_shift * sizeof(value_type));
				for (size_type i = 0; i < n; i++)
					allocator.construct(&*position + i, val);
				for (size_type i = 0; i < n_shift; i++)
					allocator.destroy(&shift[i]);
				allocator.deallocate(shift, n_shift);
				_size += n;
			}
		}
	};
}