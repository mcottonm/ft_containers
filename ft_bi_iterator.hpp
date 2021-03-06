/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 18:28:19 by mcottonm          #+#    #+#             */
/*   Updated: 2021/04/14 16:24:46 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include "ft_map_iterator.hpp"
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

		_list_node(struct _list_node& other):_prev(other->_prev), _next(other->_next), _value(other._value) {}
		
		T* valptr() { return &_value; }
		const T* valptr() const { return &_value; }
	};

	template <typename Iter>
	class reversBiIterator;
	
	template <typename T>
	class BidirectionalIterator
	{
	public:
		typedef BidirectionalIterator<T>	self_type;
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef value_type*					pointer;
		typedef value_type&					reference;
		typedef _list_node<value_type>		node_type;
		typedef const _list_node<const value_type> const_node_type;
		
	private:
		node_type*					_node;
		
	public:
		
		BidirectionalIterator(): _node() {}
		BidirectionalIterator(const BidirectionalIterator& other): _node(other._node) {}
		BidirectionalIterator(const reversBiIterator<BidirectionalIterator>& other): _node(reversBiIterator<BidirectionalIterator>::get_node(other)) {}
		BidirectionalIterator(node_type* node): _node(node) {}
		BidirectionalIterator(const_node_type* node): _node(node) {}
		BidirectionalIterator & operator= (const BidirectionalIterator& other) { _node = other._node; return *this; }
		
		template <template <typename> class const_iterator>
		operator const_iterator<const value_type>()
		{
			return const_iterator<const value_type >((_list_node<const value_type>*)_node);
		}

		template <template <typename> class iterator>
		operator iterator<typename remove_const<T>::type>()
		{
			return iterator<typename remove_const<T>::type>((_list_node<typename remove_const<T>::type>*)_node);
		}
		
		static node_type* get_node(const BidirectionalIterator& iterator)
		{
			return(iterator._node);
		}

		reference operator*() const { return *_node->valptr(); }
		pointer operator->() const { return _node->valptr(); }
		self_type& operator++() { _node = _node->_next; return *this; }
      	self_type operator++(int) { self_type __tmp = *this; _node = _node->_next; return __tmp; }
		self_type& operator--() { _node = _node->_prev; return *this; }
      	self_type operator--(int) { self_type __tmp = *this; _node = _node->_prev; return __tmp; }
		bool operator==(const self_type& __x) const { return _node == __x._node; }
      	bool operator!=(const self_type& __x) const { return _node != __x._node; }
	};

	template <typename Iter>
	class reversBiIterator
	{
	public:
		typedef typename Iter::self_type		self_type;
		typedef typename Iter::value_type		value_type;
		typedef typename Iter::difference_type difference_type;
		typedef typename Iter::pointer		pointer;
		typedef typename Iter::reference	reference;
		typedef typename Iter::node_type	node_type;
		
	private:
		Iter					_node;
		
	public:
	
		reversBiIterator(): _node() {}
		reversBiIterator(const Iter& other): _node(other) {}
		reversBiIterator(const reversBiIterator& other): _node(other._node) {}

		static node_type* get_node(const reversBiIterator& iterator)
		{
			return(iterator._node);
		}
		
		template <template <typename> class const_iterator>
		operator const_iterator<const value_type>()
		{
			return const_iterator<const value_type >((_list_node<const value_type>*)_node);
		}

		reversBiIterator & operator= (const reversBiIterator& other) { _node = other; return *this; }
		reference operator*() const { return *_node; }
		pointer operator->() const { return _node->valptr(); }
		reversBiIterator& operator--() { ++_node; return *this; }
      	reversBiIterator operator--(int) { reversBiIterator __tmp = *this; ++_node; return __tmp; }
		reversBiIterator& operator++() { --_node; return *this; }
      	reversBiIterator operator++(int) { reversBiIterator __tmp = *this; --_node; return __tmp; }
		friend bool operator!=(const reversBiIterator& l, const reversBiIterator& r)
		{
			return l._node != r._node;
		}
		
		friend bool operator==(const reversBiIterator& l, const reversBiIterator& r)
		{
			return l._node == r._node;
		}
	};

}