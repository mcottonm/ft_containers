/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forward_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:49:47 by mcottonm          #+#    #+#             */
/*   Updated: 2021/04/08 19:48:04 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>

namespace ft
{
	template <typename T>
    struct Node
    {
        T value;
        bool state;
        Node(const T& value_) : value(value_), state(true) {}
        Node* next;
    };

    template <typename T>
    class FIterator
    {
	public:
		typedef FIterator<T>	self_type;
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef value_type*					pointer;
		typedef value_type&					reference;
		typedef Node<value_type>		node_type;
		typedef const Node<const value_type> const_node_type;
		
	private:
		node_type**					_cashT;
		node_type*                  _node;
	public:
	
		FIterator(): _node(), _cashT() {}
		FIterator(const FIterator& other): _node(other._node), _cashT(other._cashT) {}
		//FIterator(const reversBiIterator<FIterator>& other): _node(reversBiIterator<FIterator>::get_node(other)) {}
		FIterator(node_type** cashT, node_type* node): _cashT(cashT), _node(node) {}
		FIterator(const_node_type** cashT, const_node_type* node): _cashT(cashT), _node(node) {}
		FIterator & operator= (const FIterator& other) { _cashT = other._cashT; _node = other._node; return *this; }
		
		template <template <typename> class const_iterator>
		operator const_iterator<const value_type>()
		{
			return const_iterator<const value_type >((Node<const value_type>*)_node);
		}

		static node_type* get_node(const FIterator& iterator)
		{
			return(iterator._node);
		}

		reference operator*() const { return *&_node->value; }
		pointer operator->() const { return *_node->value; }
		self_type& operator++()
        {
            if (!_node->next)
            {
                while (!*++_cashT)
                    ;
                _node = *_cashT;
            }
            else
                _node = _node->next;
            return *this;
        }
      	self_type operator++(int) 
        {
            self_type __tmp = *this; 
            if (!_node->next)
            {
                while (!*++_cashT)
                    ;
                _node = *_cashT;
            }
            else
                _node = _node->next;
            return __tmp;
        }
		bool operator==(const self_type& __x) const { return _node == __x._node; }
      	bool operator!=(const self_type& __x) const { return _node != __x._node; }
    };
}