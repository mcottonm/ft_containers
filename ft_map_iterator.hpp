/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 15:38:25 by mcottonm          #+#    #+#             */
/*   Updated: 2021/04/14 16:06:53 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# define RED 0
# define BLACK 1

namespace ft
{	
	template <class _Tp> struct remove_const            {typedef _Tp type;};
	template <class _Tp> struct remove_const<const _Tp> {typedef _Tp type;};
		
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

	public:	
		static node_type* iter_finder1(node_type* _n)
        {
            if (_n->_left)
                return iter_finder1(_n->_left);
            return _n;
        }

        static node_type* iter_finder2(node_type* _n)
        {
            if (_n->_parent && _n->_parent->_left == _n)
                return(_n->_parent);
            else if (_n->_parent)
                return iter_finder2(_n->_parent);
            return _n;
        }

        static node_type* iter_finder(node_type* _n)
        {
            if (_n->_right)
                return iter_finder1(_n->_right);
            return iter_finder2(_n);
        }

		static node_type* iter_finder1_rev(node_type* _n)
        {
            if (_n->_right)
                return iter_finder1_rev(_n->_right);
            return _n;
        }
		
		static node_type* iter_finder2_rev(node_type* _n)
        {
            if (_n->_parent && _n->_parent->_right == _n)
                return(_n->_parent);
            else if (_n->_parent)
                return iter_finder2_rev(_n->_parent);
            return _n;
        }
		
		static node_type* iter_finder_rev(node_type* _n)
		{
			if (_n->_left)
				return iter_finder1_rev(_n->_left);
			return iter_finder2_rev(_n);
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

		template <template <typename> class iterator>
		operator iterator<typename remove_const<value_type>::type>()
		{
			return iterator<typename remove_const<value_type>::type>((_tree_node<typename remove_const<value_type>::type>*)_node);
		}
		
		static node_type* get_node(const BiMapIterator& iterator)
		{
			return(iterator._node);
		}

		reference operator*() const { return *&_node->value; }
		pointer operator->() const { return &_node->value; }
		self_type& operator++() { _node = iter_finder(_node); return *this; }
      	self_type operator++(int) { self_type __tmp = *this; _node = iter_finder(_node); return __tmp; }
		self_type& operator--() { _node = iter_finder_rev(_node); return *this; }
      	self_type operator--(int) { self_type __tmp = *this; _node = iter_finder_rev(_node); return __tmp; }
		bool operator==(const self_type& __x) const { return _node == __x._node; }
      	bool operator!=(const self_type& __x) const { return _node != __x._node; }
	};

	template <typename Iter>
	class reversBiMapIterator
	{
		typedef typename Iter::self_type		self_type;
		typedef typename Iter::value_type		value_type;
		typedef typename Iter::difference_type  difference_type;
		typedef typename Iter::pointer			pointer;
		typedef typename Iter::reference		reference;
		typedef typename Iter::node_type		node_type;
		typedef typename Iter::const_node_type		const_node_type;

	private:
		node_type*					_node;	

	public:
	
		reversBiMapIterator(): _node() {}
		reversBiMapIterator(const Iter& other): _node(Iter::get_node(other)) {}
		reversBiMapIterator(const reversBiMapIterator& other): _node(other._node) {}
		reversBiMapIterator(node_type* node): _node(node) {}
		reversBiMapIterator(const_node_type* node): _node(node) {}
		reversBiMapIterator & operator= (const reversBiMapIterator& other) { _node = other._node; return *this; }
		
		template <template <typename> class const_iterator>
		operator const_iterator<const value_type>()
		{
			return const_iterator<const value_type >((_tree_node<const value_type>*)_node);
		}
		
		template <template <typename> class iterator>
		operator iterator<typename remove_const<value_type>::type>()
		{
			return iterator<typename remove_const<value_type>::type>((_tree_node<typename remove_const<value_type>::type>*)_node);
		}

		static node_type* get_node(const reversBiMapIterator& iterator)
		{
			return(iterator._node);
		}

		reference operator*() const { return *&_node->value; }
		pointer operator->() const { return &_node->value; }
		reversBiMapIterator& operator++() { _node = Iter::iter_finder_rev(_node); return *this; }
      	reversBiMapIterator operator++(int) { reversBiMapIterator __tmp = *this; _node = Iter::iter_finder_rev(_node); return __tmp; }
		reversBiMapIterator& operator--() { _node = Iter::iter_finder(_node); return *this; }
      	reversBiMapIterator operator--(int) { reversBiMapIterator __tmp = *this; _node = Iter::iter_finder(_node); return __tmp; }
		friend bool operator!=(const reversBiMapIterator& l, const reversBiMapIterator& r)
		{
			return l._node != r._node;
		}
		
		friend bool operator==(const reversBiMapIterator& l, const reversBiMapIterator& r)
		{
			return l._node == r._node;
		}		
	};
}