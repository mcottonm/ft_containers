/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 15:38:25 by mcottonm          #+#    #+#             */
/*   Updated: 2021/03/31 17:16:17 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
// # include "b-r_tree_engine.hpp"
// # include "ft_map.hpp"

# define RED 0
# define BLACK 1

namespace ft
{	
	template< class Key, class T, class Compare, class Alloc >
	class map;
	
	template <typename T>
	struct _tree_node
	{
	public:
		struct _tree_node *_parent;
		struct _tree_node *_left;
		struct _tree_node *_right;
		T value;
		int color;
	
		_tree_node(struct _tree_node* parent = NULL, struct _tree_node* left = NULL,
					struct _tree_node* right = NULL, const T& a = T())
		: _parent(parent)
		, _left(left)
		, _right(right)
		, value(a)
		, color(RED)
		{
		}

		_tree_node(struct _tree_node& other)
		: _parent(other->_parent)
		, _left(other->_left)
		, _right(other->_right)
		, value(other.value)
		, color(other.color)
		{
		}
	};

	template <typename T1, typename T2>
	struct pair
	{
		T1 first;
		T2 second;
		
		pair(const T1& a = T1(), const T2& b = T2())
		: first(a)
		, second(b)
		{
		}
		
		template<class U, class V> pair (const pair<U,V>& pr)
		: first(pr.first)
		, second(pr.second)
		{
		}

		pair& operator= (const pair& pr)
		{
			first = pr.first;
			second = pr.second;
			return (*this);
		}
	};
	
	template <class T1, class T2>
  	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs==rhs); }

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(rhs<lhs); }

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return rhs<lhs; }

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs<rhs); }

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
		
		node_type* iter_finder1(node_type* _n)
        {
            if (_n->_left)
                return iter_finder1(_n->_left);
            return _n;
        }

        node_type* iter_finder2(node_type* _n)
        {
            if (_n->_parent && _n->_parent->_left == _n)
                return(_n->_parent);
            else if (_n->_parent)
                return iter_finder2(_n->_parent);
            return _n;
        }

        node_type* iter_finder(node_type* _n)
        {
            if (_n->_right)
                return iter_finder1(_n->_right);
            return iter_finder2(_n);
        }
		
	public:
	
		BiMapIterator(): _node() {}
		BiMapIterator(const BiMapIterator& other): _node(other._node) {}
		BiMapIterator(node_type* node): _node(node) {}
		BiMapIterator(const_node_type* node): _node(node) {}
		BiMapIterator & operator= (const BiMapIterator& other) { _node = other._node; return *this; }
		
		template <template <typename> class const_iterator>
		operator const_iterator<const value_type>()
		{
			return const_iterator<const value_type >((_tree_node<const value_type>*)_node);
		}

		static node_type* get_node(const BiMapIterator& iterator)
		{
			return(iterator._node);
		}

		reference operator*() const { return *&_node->value; }
		pointer operator->() const { return &_node->value; }
		// template< class Key, class T1, class Compare, class Alloc >
		self_type& operator++() { _node = iter_finder(_node); return *this; }
		// template< class Key, class T1, class Compare, class Alloc >
      	self_type operator++(int) { self_type __tmp = *this; _node = iter_finder(_node); return __tmp; }
		self_type& operator--() { _node = _node->_prev; return *this; }
      	self_type operator--(int) { self_type __tmp = *this; _node = _node->_prev; return __tmp; }
		bool operator==(const self_type& __x) const { return _node == __x._node; }
      	bool operator!=(const self_type& __x) const { return _node != __x._node; }
	};
}