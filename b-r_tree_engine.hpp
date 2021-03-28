/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b-r_tree_engine.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 16:41:41 by mcottonm          #+#    #+#             */
/*   Updated: 2021/03/28 17:52:00 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

# include <iostream>

# define RED 0
# define BLACK 1

namespace ft
{
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
	
		typedef _tree_node<T> tree_node;

		static tree_node* grandp(tree_node* n)
		{
			if (n && n->_parent)
				return n->_parent->_parent;
			else
				return NULL;
		}

		static tree_node* uncle(tree_node* n)
		{
			tree_node*g = grandp(n);
			if (!g)
				return NULL;
			if (n->_parent == g->_left)
				return g->_right;
			else
				return g->_left;
		}

		static void adopt(tree_node* n, tree_node* pivot)
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

		static void rotate_left(tree_node* n)
		{
			tree_node* pivot = n->_right;

			adopt(n, pivot);

			n->_right = pivot->_left;
			if (pivot->_left)
				pivot->_left->_parent = n;
			
			n->_parent = pivot;
			pivot->_left = n;
		}

		static void rotate_right(tree_node* n)
		{
			tree_node* pivot = n->_right;

			adopt(n, pivot);

			n->_left = pivot->_right;
			if (pivot->_right)
				pivot->_right->_parent = n;
			
			n->_parent = pivot;
			pivot->_right = n;
		}

		static void insert_case5(tree_node* n)
		{
			tree_node* g = grandp(n);

			n->_parent->color = BLACK;
			g->color = RED;
			if (n == n->_parent->_left && n->_parent == g->_left)
				rotate_right(g);
			else
				rotate_left(g);
		}

		static void insert_case4(tree_node* n)
		{
			tree_node* g = grandp(n);

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

		static void insert_case3(tree_node* n)
		{
			tree_node *u = uncle(n), *g;

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

		static void insert_case2(tree_node* n)
		{
			if (n->_parent->color == BLACK)
				return;
			else
				insert_case3(n);
		}

		static void insert_case1(tree_node* n)
		{
			if (n->_parent == NULL)
				n->color = BLACK;
			else
				insert_case2(n);
		}

		static tree_node* sibling(tree_node* n)
		{
			if (n == n->_parent->_left)
				return n->_parent->_right;
			else
				return n->_parent->_left;
		}

		static void replace_node(tree_node* n, tree_node* child)
		{
			child->_parent = n->_parent;
			if (n == n->_parent->_left) {
				n->_parent->_left = child;
			} else {
				n->_parent->_right = child;
			}
		}

		static bool is_leaf(tree_node* n)
		{
			return (n->_left || n->_right);
		}

		static void delete_case6(tree_node *n)
		{
			tree_node *s = sibling(n);

			s->color = n->_parent->color;
			n->_parent->color = BLACK;

			if (n == n->_parent->_left) {
				s->_right->color = BLACK;
				rotate_left(n->_parent);
			} else {
				s->_left->color = BLACK;
				rotate__right(n->_parent);
			}
		}

		static void delete_case5(tree_node *n)
		{
			tree_node *s = sibling(n);

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

		static void delete_case4(tree_node* n)
		{
			tree_node* s = sibling(n);

			if ((n->_parent->color == RED) &&
				(s->color == BLACK) &&
				(s->_left->color == BLACK) &&
				(s->_right->color == BLACK)) {
				s->color = RED;
				n->_parent->color = BLACK;
			} else
				delete_case5(n);
		}


		static void delete_case3(tree_node *n)
		{
			tree_node *s = sibling(n);

			if ((n->_parent->color == BLACK) &&
				(s->color == BLACK) &&
				(s->_left->color == BLACK) &&
				(s->_right->color == BLACK)) {
				s->color = RED;
				delete_case1(n->_parent);
			} else
				delete_case4(n);
		}

		static void delete_case2(tree_node* n)
		{
			tree_node *s = sibling(n);

			if (s->color == RED) {
				n->_parent->color = RED;
				s->color = BLACK;
				if (n == n->_parent->_left)
					rotate_left(n->_parent);
				else
					rotate_right(n->_parent);
			} 
			delete_case3(n);
		}


		static void delete_case1(tree_node* n)
		{
			if (n->_parent != NULL)
				delete_case2(n);
		}

		static void delete_one_child(tree_node* n)
		{
			tree_node *child = is_leaf(n->_right) ? n->_left : n->_right;
			
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
	};
}