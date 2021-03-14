/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 20:37:27 by mcottonm          #+#    #+#             */
/*   Updated: 2021/03/19 22:03:10 by mcottonm         ###   ########.fr       */
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
# include "ft_be_iterator.hpp"

namespace ft
{
	template <class T, class Allocator=std::allocator<T> >
	class list
	{
	public:
		typedef Allocator						allocator_type;
		typedef T								value_type;
		typedef size_t							size_type;
		typedef value_type&						reference;
		typedef const value_type&				const_reference;
		typedef value_type*						pointer;
		typedef const value_type*				const_pointer;
		typedef _list_node<T>					node_type;
		typedef typename allocator_type::template
			rebind<node_type>::other 			node_alloc;
		typedef BidirectionalIterator<value_type>			iterator;
		typedef BidirectionalIterator<const value_type>	const_iterator;
		
	private:
		allocator_type	allocator;
		size_type		_size;
		node_type*		_head;
		node_type*		_tail;
		node_alloc		_node_alloc;

	private:
		node_type* _new_empty_node() {
			node_type* tmp = _node_alloc.allocate(1);
			tmp->_next = NULL;
			tmp->_prev = NULL;
			return tmp;
		}

		inline void _node_add_front(node_type* node)
		{
			node->_next = _head;
			node->_prev = _tail;
			_head->_prev = node;
			_tail->_next = node;
			_head = node;
		}

		inline void _node_add_back(node_type* node)
		{
			if (_head == _tail)
				_node_add_front(node);
			else
			{
				_tail->_prev->_next = node;
				node->_prev = _tail->_prev;
				node->_next = _tail;
				_tail->_prev = node;
			}
		}

		template <typename _Val, template< typename > class  _InputIterator>
		static size_type distance(_InputIterator <_Val> first, _InputIterator <_Val> last)
		{
			size_type dist = 0;
			
			while (first++ != last) ++dist;
   			return dist;
		}

	public:
		
		list(const allocator_type& alloc = allocator_type())
		:allocator(alloc)
		,_head(_new_empty_node())
		,_tail(_head)
		,_size(0)
		{
		}
		
		list (size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type())
		:allocator(alloc)
		,_head(_new_empty_node())
		,_tail(_head)
		,_size(n)
		{
			node_type*	node;
			while(n--)
			{
				node = _new_empty_node();
				allocator.construct(node->valptr(), val);
				_node_add_back(node);
			}
		}

		template <typename _Val, template< typename > class  _InputIterator>
		list(_InputIterator <_Val> first, _InputIterator <_Val> last,
					const allocator_type& alloc = allocator_type())
		{
			_size = distance(first, last);
			node_type* node;
			
			while(first != last)
			{
				node = _new_empty_node();
				allocator.construct(node->valptr(), *first++);
				_node_add_back(node);
			}
		}

	};
}

