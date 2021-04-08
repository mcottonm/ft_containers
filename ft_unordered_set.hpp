/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unordered_set.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 18:12:07 by mcottonm          #+#    #+#             */
/*   Updated: 2021/04/08 19:46:33 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <unordered_map>
# include "forward_iterator.hpp"

namespace ft
{
	template < class Key,
           class Hash = std::hash<Key>,
           class Pred = std::equal_to<Key>,
           class Alloc = std::allocator<Key>
           > 
	class unordered_set
	{
	public:
	
		typedef Key		value_type;
		typedef Hash	hasher;
		typedef Pred	key_equal;
		typedef Alloc	allocator_type;
		typedef size_t	size_type;
        typedef value_type&		reference;
        typedef const value_type&	const_reference;
        typedef value_type*		pointer;
        typedef const value_type*	const_pointer;
		typedef Node<value_type>	node_type;
		typedef typename allocator_type::template
			rebind<node_type>::other node_alloc;
		typedef typename allocator_type::template
			rebind<node_type*>::other hash_alloc;
		typedef FIterator<value_type> iterator;
	
	private:
	
		allocator_type	allocator;
		node_alloc		n_alloc;
		hash_alloc		hsss_alloc;
		size_type		_size;
		size_type		bucket_count;
		node_type**		_cashT;
		hasher			hsss;
		key_equal		eq;
		

	private:
	
		size_type constrain_hash(size_t __h, size_t __bc)
		{
			return !(__bc & (__bc - 1)) ? __h & (__bc - 1) :
				(__h < __bc ? __h : __h % __bc);
		}
		
		node_type* new_node()
		{
			node_type* n = n_alloc.allocate(1);
			n->next = NULL;
			return n;
		}

		void push_back(node_type** field, node_type* in)
		{
			node_type* tmp = *field;
			if (!tmp)
			{
				tmp = in;
				return ;
			}
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = in;
		}
		
	public:
	
		explicit unordered_set ( size_type n = 8,
							const hasher& hf = hasher(),
							const key_equal& eql = key_equal(),
							const allocator_type& alloc = allocator_type() )
		: allocator(alloc)
		, _size(0)
		, bucket_count(n)
		, _cashT(hsss_alloc.allocate(n))
		, hsss(hf)
		{
			for(size_type i = 0; i < bucket_count; ++i)
				_cashT[i] = NULL;
		}
		
		~unordered_set()
		{
			for(size_type i = 0; i < bucket_count; ++i)
			{
				for(node_type* tmp = _cashT[i]; tmp; _cashT[i] = tmp)
				{
					tmp = tmp->next;
					allocator.destroy(&_cashT[i]->value);
					n_alloc.deallocate(_cashT[i], 1);
				}
			}
			hsss_alloc.deallocate(_cashT, bucket_count);
		}

		void rehash(size_type n)
		{
			if (bucket_count >= n)
				return ;
			size_type new_count = bucket_count * 2 < n ? n : bucket_count * 2;
			node_type** new_cashT = hsss_alloc.allocate(new_count);
			for (size_type i = 0; i < new_count; ++i)
				new_cashT[i] = NULL;
			for (size_type i = 0; i < bucket_count; ++i)
			{
				while(_cashT[i])
				{
					node_type* tmp = _cashT[i];
					size_type j = constrain_hash(hsss(_cashT[i]->value), new_count);
					push_back(&new_cashT[j], _cashT[i]);
					n_alloc.deallocate(_cashT[i], 1);
					_cashT[i] = tmp->next;
				}
			}
			hsss_alloc.deallocate(_cashT, bucket_count);
			_cashT = new_cashT;
			bucket_count = new_count;
		}

		bool Add(const value_type& value)
		{
			if (_size + 1 >= bucket_count)
				rehash(bucket_count * 2);
			size_type i = constrain_hash(hsss(value), bucket_count);
			node_type* tmp = _cashT[i];
			if (tmp)
			{
				for(;tmp->next; tmp = tmp->next)
					if (eq(tmp->value,value))
						return false;
				if (eq(tmp->value,value))
						return false;
				node_type* n = new_node();
				allocator.construct(&n->value, value);
				tmp->next = n;
			}
			else
			{
				node_type* n = new_node();
				allocator.construct(&n->value, value);
				_cashT[i] = n;
			}
			++_size;
			return true;
		}

		iterator begin()
		{
			size_type i = 0;
			while (!_cashT[i])
				++i;
			return(iterator(&_cashT[i], _cashT[i]));
		}		
	};
}