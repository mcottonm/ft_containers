/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 15:33:13 by mcottonm          #+#    #+#             */
/*   Updated: 2021/03/31 20:34:37 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <vector>
# include "ft_map_iterator.hpp"
// # include "b-r_tree_engine.hpp"

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
        typedef std::less<T>								value_compare;
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
        
    private:
    
        allocator_type										allocator;
        node_alloc											_node_alloc;
        key_compare											_key_cmp;
        node_type*											_root;
        node_type*                                          _nest;
        node_type*											_ground;
        size_type                                           _size;
    
    //TREEE:
    private:
        // node_type* grandp (node_type* n);
		// static node_type* uncle (node_type* n);
		// static void adopt (node_type* n, node_type* pivot);
		// static void rotate_left (node_type* n);
		// static void rotate_right (node_type* n);
		// static void insert_case5 (node_type* n);
		// static void insert_case4 (node_type* n);
		// static void insert_case3 (node_type* n);
		// static void insert_case2 (node_type* n);
		// static void insert_case1 (node_type* n);
		// static node_type* sibling (node_type* n);
		// static void replace_node (node_type* n, node_type* child);
		// static bool is_leaf (node_type* n);
		// static void delete_case6 (node_type *n);
		// static void delete_case5 (node_type *n);
		// static void delete_case4 (node_type* n);
		// static void delete_case3 (node_type *n);
		// static void delete_case2 (node_type* n);
		// static void delete_case1 (node_type* n);
		// static void delete_one_child (node_type* n);
    private:
        
        node_type* _new_empty_node() 
        {
            node_type* tmp = _node_alloc.allocate(1);
            tmp->_parent = NULL;
            tmp->_left = NULL;
            tmp->_right = NULL;
            tmp->color = RED;
            return tmp;
        }
        
        node_type* _new_node(const value_type& val)
        {
            node_type* tmp = _node_alloc.allocate(1);
            tmp->_parent = NULL;
            tmp->_left = NULL;
            tmp->_right = NULL;
            tmp->color = RED;
            allocator.construct(&tmp->value,val);
            return tmp;
        }
    
        bool insert_n(node_type* root, node_type* in)
        {
            if (_key_cmp(in->value.first, root->value.first))
            {
                if (!(root->_left))
                {
                    root->_left = in;
                    in->_parent = root;
                    insert_case1(in);
                }
                else
                    return (insert_n(root->_left, in));
            }
            else if (root->value.first == in->value.first)
                return false;
            else
            {
                if (!(root->_right))
                {
                    root->_right = in;
                    in->_parent = root;
                    insert_case1(in);
                }
                else
                    return (insert_n(root->_right, in));
            }
            return true;
        }
        
        pair<iterator,bool> put_in(const value_type& val)
        {
            pair<iterator,bool> p;
            node_type* in = _new_node(val);
            if (_nest == _ground)
            {
                _root = in;
				_nest = in;
				_ground->_parent = in;
				in->_right = _ground;
                insert_case1(_root);
                p.second = true;
            }
            else
			{
				_ground->_parent->_right = NULL;
                p.second = insert_n(_root, in);
				if (_key_cmp(in->value.first, _nest->value.first))
					_nest = in;
				if (!_key_cmp(in->value.first, _ground->_parent->value.first)
				&& in->value.first != _ground->_parent->value.first)
				{
					_ground->_parent = in;
					in->_right = _ground;
				}
			}
            p.first = in;
            return (p);
        }
        
        void nest()
        {
            node_type* _n = _root;
            while(_n->_left)
                _n = _n->_left;
            _nest = _n;
        }

        void ground()
        {
            node_type* _n = _root;
            while(_n->_right)
                _n = _n->_right;
            _n->_right = _ground;
            _ground->_parent = _n;
        }
        
    public:
        
        explicit map(const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type())
        : allocator(alloc)
        , _key_cmp(comp)
        , _root(NULL)
		, _nest(_new_empty_node())
        , _ground(_nest)
        , _size(0)
        {
        }

        template <typename _Val, template<typename> class InputIterator>
            map (InputIterator<_Val> first, InputIterator<_Val> last,
               const key_compare& comp = key_compare(),
                  const allocator_type& alloc = allocator_type())
        : allocator(alloc)
        , _key_cmp(comp)
        , _root(NULL)
		, _nest(_new_empty_node())
        , _ground(_nest)
        {
            while (first != last)
            {
                put_in(*first++);
                _size++;
            }
        }

        map(const map& x)
		{
			
		}

        map& operator= (const map& x);

        iterator begin()
        {
            // nest();
            ground();
            return(_nest);
        }
        
        const_iterator begin() const;
        
        iterator end()
        {
            // nest();
            // ground();
            return(_ground);
        }
        
        iterator rend();
        const_iterator rend() const;

        bool empty() const;

        size_type size() const;

        size_type max_size() const;

        mapped_type& operator[] (const key_type& k);

        pair<iterator,bool> insert (const value_type& val)
        {
            return(put_in(val));
        }


        iterator insert (iterator position, const value_type& val);
        
        template <class InputIterator>
        void insert (InputIterator first, InputIterator last);
        
        void erase (iterator position);

        size_type erase (const key_type& k);

        void erase (iterator first, iterator last);

        void swap (map& x);
        
        void clear();

        key_compare key_comp() const;

        value_compare value_comp() const;

	private:
	    
        node_type* finder(node_type* _n, const key_type& k)
        {
            if (_n->value.key == k)
                return (_n);
            else if (_key_cmp(_n->value.key, k))
            {
                if (!_n->left)
                    return(_ground);
                return (finder(_n->_left, k));
            }
            else
            {
                if (!_n->_right)
                    return(_ground);
                return (finder(_n->_right, k));
            }
        }
		
    public:
	 
        iterator find (const key_type& k)
        {
            node_type* _n = _root;
            return(iterator(finder(_n, k)));
        }
        
        const_iterator find (const key_type& k) const;

        size_type count (const key_type& k) const;

        iterator lower_bound (const key_type& k);
        
        const_iterator lower_bound (const key_type& k) const;

        iterator upper_bound (const key_type& k);
        
        const_iterator upper_bound (const key_type& k) const;

        pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
        
        pair<iterator,iterator>             equal_range (const key_type& k);


    // template< class Key, class T, class Compare, class Alloc >
	// class map;

	// template< class Key, class T, class Compare, class Alloc >
	typename map<Key,T,Compare,Alloc>::node_type*
			grandp(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		if (n && n->_parent)
			return n->_parent->_parent;
		else
			return NULL;
	}

	// template< class Key, class T, class Compare, class Alloc >
	typename map<Key,T,Compare,Alloc>::node_type*
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

	// template< class Key, class T, class Compare, class Alloc >
	void adopt(typename map<Key,T,Compare,Alloc>::node_type* n
				, typename map<Key,T,Compare,Alloc>::node_type* pivot)
	{
		pivot->_parent = n->_parent;
        if (!pivot->_parent)
            this->_root = pivot;
		if(n->_parent)
		{
			if (n->_parent->_left == n)
				n->_parent->_left = pivot;
			else
				n->_parent->_right = pivot;
		}
	}

	// template< class Key, class T, class Compare, class Alloc >
	void rotate_left(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		typename map<Key,T,Compare,Alloc>::node_type* pivot = n->_right;
		adopt(n, pivot);
		
		n->_right = pivot->_left;
		if (pivot->_left)
			pivot->_left->_parent = n;
		
		n->_parent = pivot;
		pivot->_left = n;
	}

	// template< class Key, class T, class Compare, class Alloc >
	void rotate_right(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		typename map<Key,T,Compare,Alloc>::node_type* pivot = n->_left;
		adopt(n, pivot);

		n->_left = pivot->_right;
		if (pivot->_right)
			pivot->_right->_parent = n;
		
		n->_parent = pivot;
		pivot->_right = n;
	}

	// template< class Key, class T, class Compare, class Alloc >
	void insert_case5(typename map<Key,T,Compare,Alloc>::node_type* n)	
	{
		typename map<Key,T,Compare,Alloc>::node_type* g = grandp(n);
		
		n->_parent->color = BLACK;
		g->color = RED;
		if (n == n->_parent->_left && n->_parent == g->_left)
			rotate_right(g);
		else
			rotate_left(g);
	}
	
	// template< class Key, class T, class Compare, class Alloc >
	void insert_case4(typename map<Key,T,Compare,Alloc>::node_type* n)
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

	// template< class Key, class T, class Compare, class Alloc >
	void insert_case3(typename map<Key,T,Compare,Alloc>::node_type* n)
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

	// template< class Key, class T, class Compare, class Alloc >
	void insert_case2(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		if (n->_parent->color == BLACK)
			return;
		else
			insert_case3(n);
	}
	
	// template< class Key, class T, class Compare, class Alloc >
	void insert_case1(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		if (n->_parent == NULL)
			n->color = BLACK;
		else
			insert_case2(n);
	}

	// template< class Key, class T, class Compare, class Alloc >
	typename map<Key,T,Compare,Alloc>::node_type*
			sibling(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		if (n == n->_parent->_left)
			return n->_parent->_right;
		else
			return n->_parent->_left;
	}

	// template< class Key, class T, class Compare, class Alloc >
	void 
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

	// template< class Key, class T, class Compare, class Alloc >
	bool is_leaf(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		return (n->_left || n->_right);
	}

	// template< class Key, class T, class Compare, class Alloc >
	void delete_case6(typename map<Key,T,Compare,Alloc>::node_type* n)
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
	
	// template< class Key, class T, class Compare, class Alloc >
	void delete_case5(typename map<Key,T,Compare,Alloc>::node_type* n)
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

	// template< class Key, class T, class Compare, class Alloc >
	void delete_case4(typename map<Key,T,Compare,Alloc>::node_type* n)
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

	// template< class Key, class T, class Compare, class Alloc >
	void delete_case3(typename map<Key,T,Compare,Alloc>::node_type* n)
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

	// template< class Key, class T, class Compare, class Alloc >
	void delete_case2(typename map<Key,T,Compare,Alloc>::node_type* n)
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


	// template< class Key, class T, class Compare, class Alloc >
	void delete_case1(typename map<Key,T,Compare,Alloc>::node_type* n)
	{
		if (n->_parent != NULL)
			delete_case2(n);
	}

	// template< class Key, class T, class Compare, class Alloc >
	void delete_one_child(typename map<Key,T,Compare,Alloc>::node_type* n)
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
    };
}