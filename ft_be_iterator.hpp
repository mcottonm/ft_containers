/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_be_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 18:28:19 by mcottonm          #+#    #+#             */
/*   Updated: 2021/03/19 22:06:58 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>

namespace ft
{
	template<typename T>
	struct _list_node
	{
		struct _list_node *_next;
		struct _list_node *_prev;
		T _value;

		_list_node(struct _list_node* prev = NULL, struct _list_node* next = NULL, const T& val = T())
			: _prev(prev), _next(next), _value(val) {}

		_list_node(struct _list_node& other):_prev(other->prev), _next(other->next), _value(other._value) {}

		T* valptr() { return &_value; }
		const T* valptr() const { return &_value; }
	};

	template <typename T>
	class BidirectionalIterator
	{
	public:
		typedef BidirectionalIterator<T>	self_type;
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef value_type*					pointer;
		typedef value_type&					reference;
		typedef _list_node<T>				node_type;
		
	private:
		node_type*					_node;
		
	public:
	
		BidirectionalIterator(): _node() {}
		BidirectionalIterator(const BidirectionalIterator& other): _node(other._node) {}
		BidirectionalIterator(node_type* node): _node(node) {}
		BidirectionalIterator & operator= (const BidirectionalIterator& other) { _node = other._node; return *this; }
		reference operator*() const { return *_node->valptr(); }
		pointer operator->() const { return _node->valptr(); }
		self_type& operator++() { _node = _node->_next; return *this; }
      	self_type operator++(int) { self_type __tmp = *this; _node = _node->_next; return __tmp; }
		self_type& operator--() { _node = _node->_prev; return *this; }
      	self_type operator--(int) { self_type __tmp = *this; _node = _node->_prev; return __tmp; }
		bool operator==(const self_type& __x) const { return _node == __x._node; }
      	bool operator!=(const self_type& __x) const { return _node != __x._node; }
	};
}