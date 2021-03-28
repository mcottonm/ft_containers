/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 15:33:13 by mcottonm          #+#    #+#             */
/*   Updated: 2021/03/28 17:50:35 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <vector>
# include "ft_map_iterator.hpp"
# include "b-r_tree_engine.hpp"

namespace ft
{
	template < class Key, class T,
           class Compare = std::less<Key>,
           class Alloc = std::allocator<pair<const Key,T> > >
	class map
	{
	public:
	
		typedef Key 										key_type;
		typedef T 											mapped_type;
		typedef pair<const key_type, mapped_type> 			value_type;
		typedef Compare 									key_compare;
		typedef Alloc 										allocator_type;
		typedef size_t										size_type;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;
		typedef value_type*									pointer;
		typedef const value_type*							const_pointer;
		typedef _tree_node<value_type>							node_type;
		typedef typename allocator_type::template
			rebind<node_type>::other 						node_alloc;
		typedef BiMapIterator<const value_type>				const_iterator;
		typedef BiMapIterator<value_type>					iterator;
		// typedef reversBiIterator<const_iterator>			const_reverse_iterator;
		// typedef reversBiIterator<iterator>					reverse_iterator;
		
	// private:
	
		allocator_type										allocator;
		node_alloc											_node_alloc;
		node_type*											_root;
		node_type*											_ground;
		key_compare											_key_cmp;
	
	private:
		
		node_type* _new_empty_node() 
		{
			node_type* tmp = _node_alloc.allocate(1);
			tmp->_parent = NULL;
			tmp->_left = NULL;
			tmp->_right = NULL;
			return tmp;
		}
		
		node_type* _new_node(const value_type& val)
		{
			node_type* tmp = _node_alloc.allocate(1);
			tmp->_parent = NULL;
			tmp->_left = NULL;
			tmp->_right = NULL;
			allocator.construct(&tmp->value,val);
			return tmp;
		}
	
		void insert_n(node_type* root, const value_type& value)
		{
			if (_key_cmp(root->value._key, value._key))
			{
				if (!(root->_left))
				{
					node_type* in = _new_node(value);
					root->_left = in;
					in->_parent = root;
					node_type::insert_case1(in);
				}
				else
					insert_n(root->_left, value);
			}
			else
			{
				if (!(root->_right))
				{
					node_type* in = _new_node(value);
					root->_right = in;
					in->_parent = root;
					node_type::insert_case1(in);
				}
				else
					insert_n(root->_right, value);
			}
		}
		
	public:
		
		explicit map(const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type())
		: allocator(alloc)
		, _root(_new_empty_node())
		, _ground(_root)
		, _key_cmp(comp)
		{
		}
		
		void insert(const value_type& val)
		{
			_root->_parent = NULL;
			if (_root == _ground)
			{
				_root = _new_node(val);
				node_type::insert_case1(_root);
			}
			insert_n(_root, val);
			while (_root->_parent)
				_root = _root->_parent;
			_root->_parent = _ground;
			_ground->_left = _root;
		}
	};
}