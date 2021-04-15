/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unordered_set.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 18:12:07 by mcottonm          #+#    #+#             */
/*   Updated: 2021/04/10 15:19:18 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <unordered_map>
# include <algorithm>
# include "forward_iterator.hpp"

namespace ft
{
	int HashFunctionHorner(const std::string& s)
	{
		int hash_result = 0;
		for (int i = 0; i != s.size(); ++i)
			hash_result = ((std::numeric_limits<int>::max() - 1) * hash_result + s[i]) % std::numeric_limits<int>::max();
		hash_result = (hash_result * 2 + 1);
		return hash_result;
	}
		
	class func
	{
	public:
		int operator()(const std::string& s) const
		{
			return HashFunctionHorner(s);
		}
	};
	
	template < class Key,
           class Hash = func,
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
		size_type		_bucket_count;
		node_type**		_cashT;
		node_type*		_last;
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
	
		explicit unordered_set ( size_type n = 0,
							const hasher& hf = hasher(),
							const key_equal& eql = key_equal(),
							const allocator_type& alloc = allocator_type() )
		: allocator(alloc)
		, _size(0)
		, _bucket_count(n)
		, _cashT(hsss_alloc.allocate(n))
		, _last(NULL)
		, hsss(hf)
		{
			for(size_type i = 0; i < _bucket_count; ++i)
				_cashT[i] = NULL;
		}
		
		~unordered_set()
		{
			while (_last)
			{
				node_type* tmp = _last;
				_last = _last->next;
				allocator.destroy(&tmp->value);
				n_alloc.deallocate(tmp, 1);
			}
			hsss_alloc.deallocate(_cashT, _bucket_count);
		}

		void rehash(size_type n)
		{
			if (_bucket_count >= n)
				return ;
			size_type new_count = _bucket_count * 2 < n ? n : _bucket_count * 2;
			node_type** new_cashT = hsss_alloc.allocate(new_count);
			for (size_type i = 0; i < new_count; ++i)
				new_cashT[i] = NULL;
			node_type* tmp = _last;
			while(tmp)
			{
				size_type j = constrain_hash(hsss(tmp->value), new_count);
				new_cashT[j] = tmp;
				tmp = tmp->next;
			}
			hsss_alloc.deallocate(_cashT, _bucket_count);
			_cashT = new_cashT;
			_bucket_count = new_count;
		}

		bool insert(const value_type& value)
		{
			if (_size + 1 >= _bucket_count)
				rehash(_bucket_count + 1);
			size_type i = constrain_hash(hsss(value), _bucket_count);
			std::cout << value << " " << i <<std::endl;
			node_type* tmp = _cashT[i];
			if (tmp)
			{
				for(;tmp->next && constrain_hash(hsss(tmp->next->value), _bucket_count) == i; tmp = tmp->next)
					if (eq(tmp->value,value))
						return false;
				if (eq(tmp->value,value))
						return false;
				node_type* n = new_node();
				allocator.construct(&n->value, value);
				n->next = tmp->next;
				tmp->next = n;
			}
			else
			{
				node_type* n = new_node();
				allocator.construct(&n->value, value);
				_cashT[i] = n;
				n->next = _last;
				_last = n;
			}
			++_size;
			return true;
		}

		
		iterator begin()
		{
			return(_last);
		}

		size_type size() const
		{
			return _size;
		}

		size_type bucket_count() const
		{
			return _bucket_count;
		}
	};
}