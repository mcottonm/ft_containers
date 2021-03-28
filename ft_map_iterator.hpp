/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 15:38:25 by mcottonm          #+#    #+#             */
/*   Updated: 2021/03/28 17:39:04 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "b-r_tree_engine.hpp"

namespace ft
{
	template <typename T1, typename T2>
	struct pair
	{
		T1 _key;
		T2 _content;
		
		pair(const T1& a = T1(), const T2& b = T2())
		: _key(a)
		, _content(b)
		{
		}
		
		template<class U, class V> pair (const pair<U,V>& pr)
		: _key(pr._key)
		, _content(pr._content)
		{
		}
	};

	template <typename T>
	class BiMapIterator
	{
	public:
		typedef BiMapIterator<T>		self_type;
		typedef 	T			value_type;
		typedef ptrdiff_t					difference_type;
		typedef value_type*					pointer;
		typedef value_type&					reference;
		typedef _tree_node<value_type>		node_type;
		typedef const _tree_node<const value_type> const_node_type;
		
	private:
		node_type*					_node;
		
	public:
	
		BiMapIterator(): _node() {}
		BiMapIterator(const BiMapIterator& other): _node(other._node) {}
		BiMapIterator(node_type* node): _node(node) {}
		BiMapIterator(const_node_type* node): _node(node) {}
		BiMapIterator & operator= (const BiMapIterator& other) { _node = other._node; return *this; }
		
		// template <template <typename> class const_iterator>
		// operator const_iterator<const value_type>()
		// {
		// 	return const_iterator<const value_type >((_list_node<const value_type>*)_node);
		// }

		// static node_type* get_node(const BiMapIterator& iterator)
		// {
		// 	return(iterator._node);
		// }

		// reference operator*() const { return *_node->valptr(); }
		// pointer operator->() const { return _node->valptr(); }
		// self_type& operator++() { _node = _node->_next; return *this; }
      	// self_type operator++(int) { self_type __tmp = *this; _node = _node->_next; return __tmp; }
		// self_type& operator--() { _node = _node->_prev; return *this; }
      	// self_type operator--(int) { self_type __tmp = *this; _node = _node->_prev; return __tmp; }
		// bool operator==(const self_type& __x) const { return _node == __x._node; }
      	// bool operator!=(const self_type& __x) const { return _node != __x._node; }
	};
}