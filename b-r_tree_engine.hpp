/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b-r_tree_engine.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 16:41:41 by mcottonm          #+#    #+#             */
/*   Updated: 2021/04/07 14:49:22 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

# include <iostream>
# define RED 0
# define BLACK 1

namespace ft
{
	template< class Key, class T, class Compare, class Alloc >
	class map;

	template< class Key, class T, class Compare, class Alloc >
	typename map<Key,T,Compare,Alloc>::node_type*
			map<Key,T,Compare,Alloc>::grandp(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		if (n && n->_parent)
			return n->_parent->_parent;
		else
			return NULL;
	}

	template< class Key, class T, class Compare, class Alloc >
	typename map<Key,T,Compare,Alloc>::node_type*
			map<Key,T,Compare,Alloc>::uncle(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		typename map<Key,T,Compare,Alloc>::node_type* g = grandp(n);
		if (!g)
			return NULL;
		if (n->_parent == g->_left)
			return g->_right;
		else
			return g->_left;
	}

	template< class Key, class T, class Compare, class Alloc >
	void map<Key,T,Compare,Alloc>::adopt(typename map<Key,T,Compare,Alloc>::node_type* n
				, typename map<Key,T,Compare,Alloc>::node_type* pivot)
	{
		pivot->_parent = n->_parent;
        if (!pivot->_parent)
            map<Key,T,Compare,Alloc>::_root = pivot;
		if(n->_parent)
		{
			if (n->_parent->_left == n)
				n->_parent->_left = pivot;
			else
				n->_parent->_right = pivot;
		}
	}

	template< class Key, class T, class Compare, class Alloc >
	void map<Key,T,Compare,Alloc>::rotate_left(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		typename map<Key,T,Compare,Alloc>::node_type* pivot = n->_right;
		adopt(n, pivot);
		
		n->_right = pivot->_left;
		if (pivot->_left)
			pivot->_left->_parent = n;
		
		n->_parent = pivot;
		pivot->_left = n;
	}

	template< class Key, class T, class Compare, class Alloc >
	void map<Key,T,Compare,Alloc>::rotate_right(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		typename map<Key,T,Compare,Alloc>::node_type* pivot = n->_left;
		adopt(n, pivot);

		n->_left = pivot->_right;
		if (pivot->_right)
			pivot->_right->_parent = n;
		
		n->_parent = pivot;
		pivot->_right = n;
	}

	template< class Key, class T, class Compare, class Alloc >
	void map<Key,T,Compare,Alloc>::insert_case5(typename map<Key,T,Compare,Alloc>::node_type* n)	
	{
		typename map<Key,T,Compare,Alloc>::node_type* g = grandp(n);
		
		n->_parent->color = BLACK;
		g->color = RED;
		if (n == n->_parent->_left && n->_parent == g->_left)
			rotate_right(g);
		else
			rotate_left(g);
	}
	
	template< class Key, class T, class Compare, class Alloc >
	void map<Key,T,Compare,Alloc>::insert_case4(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		typename map<Key,T,Compare,Alloc>::node_type* g = grandp(n);

		if (n == n->_parent->_right && n->_parent == g->_left)
		{
			rotate_left(n->_parent);
			n = n->_left;
		}
		else if (n == n->_parent->_left && n->_parent == g->_right)
		{
			rotate_right(n->_parent);
			n = n->_right;
		}
		insert_case5(n);
	}

	template< class Key, class T, class Compare, class Alloc >
	void map<Key,T,Compare,Alloc>::insert_case3(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		typename map<Key,T,Compare,Alloc>::node_type* u = uncle(n), *g;

		if ((u != NULL) && (u->color == RED)) 
		{
			n->_parent->color = BLACK;
			u->color = BLACK;
			g = grandp(n);
			g->color = RED;
			insert_case1(g);
		} 
		else 
			insert_case4(n);
	}

	template< class Key, class T, class Compare, class Alloc >
	void map<Key,T,Compare,Alloc>::insert_case2(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		if (n->_parent->color == BLACK)
			return;
		else
			insert_case3(n);
	}
	
	template< class Key, class T, class Compare, class Alloc >
	void map<Key,T,Compare,Alloc>::insert_case1(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		if (n->_parent == NULL)
			n->color = BLACK;
		else
			insert_case2(n);
	}

	template< class Key, class T, class Compare, class Alloc >
	typename map<Key,T,Compare,Alloc>::node_type*
			map<Key,T,Compare,Alloc>::sibling(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		if (n->_parent)
		{
			if (n == n->_parent->_left)
				return n->_parent->_right;
			else
				return n->_parent->_left;
		}
		return NULL;
	}

	template< class Key, class T, class Compare, class Alloc >
	void 
			map<Key,T,Compare,Alloc>::replace_node(typename map<Key,T,Compare,Alloc>::node_type* n
					, typename map<Key,T,Compare,Alloc>::node_type* child)
	{
		child->_parent = n->_parent;
		if (n->_parent)
		{
			if (n == n->_parent->_left) 
				n->_parent->_left = child;
			else
				n->_parent->_right = child;
		}
	}

	template< class Key, class T, class Compare, class Alloc >
	bool map<Key,T,Compare,Alloc>::is_leaf(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		return (!n);
	}

	template< class Key, class T, class Compare, class Alloc >
	void map<Key,T,Compare,Alloc>::delete_case6(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		typename map<Key,T,Compare,Alloc>::node_type* s = sibling(n);

		s->color = n->_parent->color;
		n->_parent->color = BLACK;

		if (n == n->_parent->_left)
		{
			if (s->_right)
				s->_right->color = BLACK;
			rotate_left(n->_parent);
		} 
		else 
		{
			if (s->_left)
				s->_left->color = BLACK;
			rotate_right(n->_parent);
		}
	}
	
	template< class Key, class T, class Compare, class Alloc >
	void map<Key,T,Compare,Alloc>::delete_case5(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		typename map<Key,T,Compare,Alloc>::node_type* s = sibling(n);

		if  (s->color == BLACK) 
		{ 
			if (n == n->_parent->_left && ((s->_right &&
				s->_right->color == BLACK) || !s->_right) && s->_left &&
				s->_left->color == RED)
			{
				s->color = RED;
				s->_left->color = BLACK;
				rotate_right(s);
			} 
			else if (n == n->_parent->_right && ((s->_left &&
				s->_left->color == BLACK) || !s->_left) && s->_right &&
				s->_right->color == RED)
			{
				s->color = RED;
				s->_right->color = BLACK;
				rotate_left(s);
			}
		}
		delete_case6(n);
	}

	template< class Key, class T, class Compare, class Alloc >
	void map<Key,T,Compare,Alloc>::delete_case4(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		typename map<Key,T,Compare,Alloc>::node_type* s = sibling(n);

		if ((n->_parent->color == RED) &&
			(s->color == BLACK) && s->_left &&
			(s->_left->color == BLACK) && s->_right &&
			(s->_right->color == BLACK))
		{
			s->color = RED;
			n->_parent->color = BLACK;
		} 
		else
			delete_case5(n);
	}

	template< class Key, class T, class Compare, class Alloc >
	void map<Key,T,Compare,Alloc>::delete_case3(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		typename map<Key,T,Compare,Alloc>::node_type* s = sibling(n);

		if ((n->_parent->color == BLACK) &&
			(s->color == BLACK) && 
			((s->_left && s->_left->color == BLACK && s->_right &&
			s->_right->color == BLACK) || (!s->_right && !s->_left)
			|| (!s->_left && s->_right && s->_right->color == BLACK)
			|| (!s->_right && s->_left && s->_left->color == BLACK)))
		{
			s->color = RED;
			delete_case1(n->_parent);
		} 
		else
			delete_case4(n);
	}

	template< class Key, class T, class Compare, class Alloc >
	void map<Key,T,Compare,Alloc>::delete_case2(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		typename map<Key,T,Compare,Alloc>::node_type* s = sibling(n);

		if (s->color == RED)
		{
			n->_parent->color = RED;
			s->color = BLACK;
			if (n == n->_parent->_left)
				rotate_left(n->_parent);
			else
				rotate_right(n->_parent);
		}
		delete_case3(n);
	}


	template< class Key, class T, class Compare, class Alloc >
	void map<Key,T,Compare,Alloc>::delete_case1(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		if (n->_parent != NULL)
		{
			delete_case2(n);
		}
	}

	template< class Key, class T, class Compare, class Alloc >
	void map<Key,T,Compare,Alloc>::delete_one_child(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		typename map<Key,T,Compare,Alloc>::node_type* child = is_leaf(n->_right) ? n->_left : n->_right;
		
		if (child)
		{
			if (n == _nest)
				_nest = child;
			replace_node(n, child);
			if (n->color == BLACK)
			{
				if (child->color == RED)
					child->color = BLACK;
				else
					delete_case1(child);
			}
		}
		else
		{
			typename map<Key,T,Compare,Alloc>::node_type* s = sibling(n);
			if (!s && n->_parent && n->_parent->color == RED && n->color == BLACK)
				n->_parent->color = BLACK;
			else if (n->color == BLACK)
				delete_case1(n);
			if (n->_parent)
			{
				if (n->_parent->_left == n)
					n->_parent->_left = 0;
				else
					n->_parent->_right = 0;
			}
		}
		allocator.destroy(&(n->value));
		_node_alloc.deallocate(n, 1);
	}
	
	template< class Key, class T, class Compare, class Alloc >
	class map;
}