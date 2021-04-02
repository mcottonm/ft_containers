/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 15:33:13 by mcottonm          #+#    #+#             */
/*   Updated: 2021/04/02 20:16:26 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <vector>
# include "ft_map_iterator.hpp"

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
    
        node_type* grandp (node_type* n);
		node_type* uncle (node_type* n);
		void adopt (node_type* n, node_type* pivot);
		void rotate_left (node_type* n);
		void rotate_right (node_type* n);
		void insert_case5 (node_type* n);
		void insert_case4 (node_type* n);
		void insert_case3 (node_type* n);
		void insert_case2 (node_type* n);
		void insert_case1 (node_type* n);
		node_type* sibling (node_type* n);
		void replace_node (node_type* n, node_type* child);
		bool is_leaf (node_type* n);
		void delete_case6 (node_type *n);
		void delete_case5 (node_type *n);
		void delete_case4 (node_type* n);
		void delete_case3 (node_type *n);
		void delete_case2 (node_type* n);
		void delete_case1 (node_type* n);
		void delete_one_child (node_type* n);
        
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
					_ground->_parent = in;
                _ground->_parent->_right = _ground;
			}
            p.first = in;
            _size++;
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

        node_type* max_left(node_type* n)
        {
            if (n->_right)
                return max_left(n->_right);
            return n;
        }
        
        node_type* min_right(node_type* n)
        {
            if (n->_left)
                return  min_right(n->_left);
            return n;
        }
        
        node_type* find_swch(node_type* n)
        {
            if (n->_left)
                return max_left(n->_left);
            if (n->_right)
                return min_right(n->_right);
            return n;
        }
        
        void replace_n(node_type* n, node_type* swch)
        {
            node_type* tmp = _new_empty_node();
            tmp->color = n->color;
            tmp->_left = n->_left;
            tmp->_right = n->_right;
            tmp->_parent = n->_parent;

            if (n->_parent)
            {
                if (n->_parent->_left == n)
                    n->_parent->_left = swch;
                else
                    n->_parent->_right = swch;
            }
            if (n->_right)
                n->_right->_parent = swch;
            if (n->_left)
                n->_left->_parent = swch;
                
            n->color = swch->color;
            n->_left = swch->_left;
            n->_right = swch->_right;
            n->_parent = swch->_parent;
            
            if (n->_parent)
            {
                if (n->_parent->_left == swch)
                    n->_parent->_left = n;
                else
                    n->_parent->_right = n;
            }
            if (n->_right)
                n->_right->_parent = n;
            if (n->_left)
                n->_left->_parent = n;
            
            swch->color = tmp->color;
            if (tmp->_left == swch)
                swch->_left = n;
            else
                swch->_left = tmp->_left;
            if (tmp->_right == swch)
                swch->_right = n;
            else
                swch->_right = tmp->_right;
            swch->_parent = tmp->_parent;
            if (n == _root)
                _root = swch;
            if (n == _nest)
                _nest = swch;
            _node_alloc.deallocate(tmp,1);
        }

        void delete_n(node_type* n)
        {
            node_type* swch = find_swch(n);
            if (n != swch)
                replace_n(n, swch);
            delete_one_child(n);
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
        , _size(0)
        {
            while (first != last)
                put_in(*first++);
        }

        map(const map& x)
        : allocator(x.allocator)
        , _key_cmp(x._key_cmp)
        , _root(NULL)
        , _nest(_new_empty_node())
        , _ground(_nest)
        , _size(0)
		{
            const_iterator it = x.begin();
		    while (it != x.end())
                put_in(*it++);
		}

        ~map()
        {
            while (_size--)
                delete_n(_root);
            _node_alloc.deallocate(_nest, 1);
        }

        map& operator= (const map& x)
        {
            this->~map();
            _size = 0;
            _nest = _new_empty_node();
            _ground = _nest;
            _root = NULL;
            const_iterator it = x.begin();
		    while (it != x.end())
                put_in(*it++);
            return *this;
        }

        iterator begin()
        {
            // nest();
            // ground();
            return(_nest);
        }
        
        const_iterator begin() const
        {
            return(reinterpret_cast<_tree_node<const value_type>*>(_nest));
        }
        
        iterator end()
        {
            // nest();
            // ground();
            return(_ground);
        }
        
        const_iterator end() const
        {
            // nest();
            // ground();
            return(reinterpret_cast<_tree_node<const value_type>*>(_ground));
        }
        
        iterator rend();
        const_iterator rend() const;

        bool empty() const;

        size_type size() const
        {
            return(_size);
        }

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
	};
}

# include "b-r_tree_engine.hpp"