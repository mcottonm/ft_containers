/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b-r_tree_engine.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 16:41:41 by mcottonm          #+#    #+#             */
/*   Updated: 2021/03/31 17:03:23 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

# include <iostream>
# define RED 0
# define BLACK 1

/*namespace ft
{
	template< class Key, class T, class Compare, class Alloc >
	class map;

	template< class Key, class T, class Compare, class Alloc >
	typename map<Key,T,Compare,Alloc>::node_type*
			grandp(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		if (n && n->_parent)
			return n->_parent->_parent;
		else
			return NULL;
	}

	template< class Key, class T, class Compare, class Alloc >
	static typename map<Key,T,Compare,Alloc>::node_type*
			uncle(typename map<Key,T,Compare,Alloc>::node_type* n)
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
	static void adopt(typename map<Key,T,Compare,Alloc>::node_type* n
				, typename map<Key,T,Compare,Alloc>::node_type* pivot)
	{
		pivot->_parent = n->_parent;
		if(n->_parent)
		{
			if (n->_parent->_left == n)
				n->_parent->_left = pivot;
			else
				n->_parent->_right = pivot;
		}
	}

	template< class Key, class T, class Compare, class Alloc >
	static void rotate_right(typename map<Key,T,Compare,Alloc>::node_type* n)
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
	static void rotate_left(typename map<Key,T,Compare,Alloc>::node_type* n)
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
	static void insert_case5(typename map<Key,T,Compare,Alloc>::node_type* n)	
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
	static void insert_case4(typename map<Key,T,Compare,Alloc>::node_type* n)
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
	static void insert_case3(typename map<Key,T,Compare,Alloc>::node_type* n)
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
	static void insert_case2(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		if (n->_parent->color == BLACK)
			return;
		else
			insert_case3(n);
	}
	
	template< class Key, class T, class Compare, class Alloc >
	static void insert_case1(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		if (n->_parent == NULL)
			n->color = BLACK;
		else
			insert_case2(n);
	}

	template< class Key, class T, class Compare, class Alloc >
	static typename map<Key,T,Compare,Alloc>::node_type*
			sibling(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		if (n == n->_parent->_left)
			return n->_parent->_right;
		else
			return n->_parent->_left;
	}

	template< class Key, class T, class Compare, class Alloc >
	static void 
			replace_node(typename map<Key,T,Compare,Alloc>::node_type* n
					, typename map<Key,T,Compare,Alloc>::node_type* child)
	{
		child->_parent = n->_parent;
		if (n == n->_parent->_left) 
		{
			n->_parent->_left = child;
		} 
		else 
		{
			n->_parent->_right = child;
		}
	}

	template< class Key, class T, class Compare, class Alloc >
	static bool is_leaf(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		return (n->_left || n->_right);
	}

	template< class Key, class T, class Compare, class Alloc >
	static void delete_case6(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		typename map<Key,T,Compare,Alloc>::node_type* s = sibling(n);

		s->color = n->_parent->color;
		n->_parent->color = BLACK;

		if (n == n->_parent->_left) 
		{
			s->_right->color = BLACK;
			rotate_left(n->_parent);
		} 
		else 
		{
			s->_left->color = BLACK;
			rotate__right(n->_parent);
		}
	}
	
	template< class Key, class T, class Compare, class Alloc >
	static void delete_case5(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		typename map<Key,T,Compare,Alloc>::node_type* s = sibling(n);

		if  (s->color == BLACK) 
		{ 
			if ((n == n->_parent->_left) &&
				(s->_right->color == BLACK) &&
				(s->_left->color == RED))
			{
				s->color = RED;
				s->_left->color = BLACK;
				rotate__right(s);
			} 
			else if ((n == n->_parent->_right) &&
					(s->_left->color == BLACK) &&
					(s->_right->color == RED)) 
			{
				s->color = RED;
				s->_right->color = BLACK;
				rotate_left(s);
			}
		}
		delete_case6(n);
	}

	template< class Key, class T, class Compare, class Alloc >
	static void delete_case4(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		typename map<Key,T,Compare,Alloc>::node_type* s = sibling(n);

		if ((n->_parent->color == RED) &&
			(s->color == BLACK) &&
			(s->_left->color == BLACK) &&
			(s->_right->color == BLACK)) 
		{
			s->color = RED;
			n->_parent->color = BLACK;
		} 
		else
				delete_case5(n);
	}

	template< class Key, class T, class Compare, class Alloc >
	static void delete_case3(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		typename map<Key,T,Compare,Alloc>::node_type* s = sibling(n);

		if ((n->_parent->color == BLACK) &&
			(s->color == BLACK) &&
			(s->_left->color == BLACK) &&
			(s->_right->color == BLACK)) 
		{
			s->color = RED;
			delete_case1(n->_parent);
		} 
		else
			delete_case4(n);
	}

	template< class Key, class T, class Compare, class Alloc >
	static void delete_case2(typename map<Key,T,Compare,Alloc>::node_type* n)
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
	static void delete_case1(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		if (n->_parent != NULL)
			delete_case2(n);
	}

	template< class Key, class T, class Compare, class Alloc >
	static void delete_one_child(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		typename map<Key,T,Compare,Alloc>::node_type* child = is_leaf(n->_right) ? n->_left : n->_right;
		
		replace_node(n, child);
		if (n->color == BLACK)
		{
			if (child->color == RED)
				child->color = BLACK;
			else
				delete_case1(child);
		}
		free(n);
	}
}/*