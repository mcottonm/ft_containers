/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 20:37:27 by mcottonm          #+#    #+#             */
/*   Updated: 2021/03/27 17:37:00 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <cstring>
# include <string>
# include <cassert>
# include <utility>
# include <type_traits>
# include <algorithm>
# include "ft_bi_iterator.hpp"

namespace ft
{

	// template <bool expr, typename T = void>
	// struct bubka {};

	// template <typename T>
	// struct bubka<true, T> { typedef T type; };

	template <class T, class Allocator=std::allocator<T> >
	class list
	{
	public:
		typedef Allocator									allocator_type;
		typedef T											value_type;
		typedef size_t										size_type;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;
		typedef value_type*									pointer;
		typedef const value_type*							const_pointer;
		typedef _list_node<T>								node_type;
		typedef typename allocator_type::template
			rebind<node_type>::other 						node_alloc;
		typedef BidirectionalIterator<const value_type>		const_iterator;
		typedef BidirectionalIterator<value_type>			iterator;
		typedef reversBiIterator<const_iterator>			const_reverse_iterator;
		typedef reversBiIterator<iterator>					reverse_iterator;
		
	private:
		allocator_type	allocator;
		size_type		_size;
		node_type*		_head;
		node_type*		_tail;
		node_alloc		_node_alloc;

	private:
	
		inline void init()
		{
			_head = _new_empty_node();
			_tail = _head;
		}
		
		node_type* _new_empty_node() {
			node_type* tmp = _node_alloc.allocate(1);
			tmp->_next = tmp;
			tmp->_prev = tmp;
			return tmp;
		}

		inline void _node_add_front(node_type* node)
		{
			node->_next = _head;
			node->_prev = _tail;
			_head->_prev = node;
			_tail->_next = node;
			_head = node;
		}

		inline void _node_add_back(node_type* node)
		{
			if (_head == _tail)
				_node_add_front(node);
			else
			{
				_tail->_prev->_next = node;
				node->_prev = _tail->_prev;
				node->_next = _tail;
				_tail->_prev = node;
			}
		}

		template <typename _InputIterator>
		static size_type distance(_InputIterator first, _InputIterator last)
		{
			size_type dist = 0;
			
			while (first++ != last) 
				++dist;
   			return dist;
		}
		
		static bool my_comp(const T& a, const T& b)
		{
			return (a < b);
		}

	public:
			
		explicit list(const allocator_type& alloc = allocator_type())
		:allocator(alloc)
		,_head(_new_empty_node())
		,_tail(_head)
		,_size(0)
		{
		}
		
		explicit list (size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type())
		:allocator(alloc)
		,_head(_new_empty_node())
		,_tail(_head)
		,_size(n)
		{
			node_type*	node;
			while(n--)
			{
				node = _new_empty_node();
				allocator.construct(node->valptr(), val);
				_node_add_back(node);
			}
		}

		// template <typename _InputIterator>
		// list(_InputIterator first, _InputIterator last, const allocator_type& alloc = allocator_type(),
		// 	typename bubka<std::__is_input_iterator<_InputIterator>::value >::type * = 0)
		template <typename _Val, template< typename > class  _InputIterator>
		list(_InputIterator <_Val> first, _InputIterator <_Val> last,
						const allocator_type& alloc = allocator_type())
		:allocator(alloc)
		,_head(_new_empty_node())
		,_tail(_head)
		,_size(0)
		{
			_size = distance(first, last);
			node_type* node;
			for(size_type i = 0; i < _size; ++i)
			{
				node = _new_empty_node();
				allocator.construct(node->valptr(), *first++);
				_node_add_back(node);
			}
		}
		
		list(const list& other)
		:allocator(other.allocator)
		,_head(_new_empty_node())
		,_tail(_head)
		,_size(other._size)
		{
			node_type* new_node;
			node_type* cped_node = other._head;
			for(size_type i = 0; i < _size; ++i)
			{
				new_node = _new_empty_node();
				allocator.construct(new_node->valptr(), cped_node->_value);
				_node_add_back(new_node);
				cped_node = cped_node->_next;
			}
		}
		
		~list()
		{
			node_type* _tmp = _head;
			while (_tmp != _tail)
			{
				_head = _head->_next;
				allocator.destroy(_tmp->valptr());
				_node_alloc.deallocate(_tmp, 1);
				_tmp = _head;
			}
			_node_alloc.deallocate(_tmp, 1);
			_size = 0;
		}

		list& operator=(const list& other)
		{
			this->~list();
			allocator = other.allocator;
			init();
			_size = other._size;
			node_type* new_node;
			node_type* cped_node = other._head;
			for(size_type i = 0; i < _size; ++i)
			{
				new_node = _new_empty_node();
				allocator.construct(new_node->valptr(), cped_node->_value);
				_node_add_back(new_node);
				cped_node = cped_node->_next;
			}
			return(*this);
		}
		
		template <typename _Val, template <typename> class _Iter>
		void assign(_Iter<_Val> first, _Iter<_Val> last)
		{
			this->~list();
			init();
			size_type i = distance(first, last);
			for (; i ; --i)
				push_back(*first++);
		}
		
		void assign( size_type count, const value_type& val )
		{
			this->~list();
			init();
			while (count)
			{
				push_back(val);
				--count;
			}
		}
		
//iterators:
		iterator begin() { return iterator(_head); }
		iterator end() { return iterator(_tail); }

		const_iterator begin() const { return reinterpret_cast<_list_node<const value_type>*>(_head); }
		const_iterator end() const { return reinterpret_cast<_list_node<const value_type>*>(_tail); }

		reverse_iterator rbegin() { return reverse_iterator(!_size ? _tail : _tail->_prev); }
		reverse_iterator rend() { return _tail; }

		const_reverse_iterator rbegin() const { return const_reverse_iterator(!_size ? _tail : _tail->_prev); }
		const_reverse_iterator rend() const { return _tail; }

//element access:
		reference front()
		{
			return(_head->_value);
		}

		const_reference front() const
		{
			return(_head->_value);
		}

		reference back()
		{
			return(_tail->_prev->_value);
		}
		
		const_reference back() const
		{
			return(_tail->_prev->_value);
		}
		
//capacity:
		bool empty() const
		{
			return(!_size);
		}

		size_type size() const
		{
			return(_size);
		}

		size_type max_size() const
		{
			return(_node_alloc.max_size());
		}

//modifiers:
		void push_back(const value_type& val)
		{
			++_size;
			node_type* new_node = _new_empty_node();
			allocator.construct(new_node->valptr(), val);
			_node_add_back(new_node);
		}
		
		void clear()
		{
			this->~list();
			init();
		}
		
		iterator insert(iterator pos, const value_type& value)
		{
			list<value_type> l(1,value);
			
			splice(pos, l, l.begin(), l.end());
			return --pos;
		}

		void insert(iterator pos, size_type count, const value_type& value)
		{
			list<value_type> l(count, value);
			
			splice(pos, l, l.begin(), l.end());
		}
		
		template< typename _Val, template <typename> class _Iter>
		void insert(iterator pos, _Iter<_Val> first, _Iter<_Val> last)
		{
			list<value_type> l(first, last);
			
			splice(pos, l, l.begin(), l.end());
		}

		iterator erase(iterator pos)
		{
			if (pos == end())
				return pos;
			node_type* p = (node_type*)iterator::get_node(pos);
			++pos;
			if (p == _head)
				_head = p->_next;
			p->_next->_prev = p->_prev;
			p->_prev->_next = p->_next;
			allocator.destroy(p->valptr());
			_node_alloc.deallocate(p, 1);
			--_size;
			return(pos);
		}

		iterator erase(iterator first, iterator last)
		{
			if (first == end())
				return first;
			_size -= distance(first, last);
		
			node_type* f = (node_type*)iterator::get_node(first);
			node_type* l = (node_type*)iterator::get_node(last);
			
			f->_prev->_next = l;
			l->_prev = f->_prev;
			
			if (f == _head)
				_head = l->_next;

			node_type* _tmp;
			while (f != l)
			{
				_tmp = f;
				f = f->_next;
				allocator.destroy(_tmp->valptr());
				_node_alloc.deallocate(_tmp, 1);
			}
			return(last);
		}
		
		void pop_back()
		{
			iterator a = end();
			erase(--a);
		}

		void push_front(const value_type& value)
		{
			insert(begin(), value);
		}
		
		void pop_front()
		{
			iterator a = begin();
			erase(a);
		}

		void resize(size_type count, value_type value = value_type())
		{
			if (count == _size)
				return ;
			while (count > _size)
				push_back(value);
			while (_size > count)
				pop_back();
		}
		
		void swap(list& other)
		{
			node_type* tmp_head = _head;
			node_type* tmp_tail = _tail;
			size_type tmp_size = _size;

			_head = other._head;
			_tail = other._tail;
			_size = other._size;
			
			other._head = tmp_head;
			other._tail = tmp_tail;
			other._size = tmp_size;
		}

//Opeartions:

		void splice(const_iterator pos, list& other)
		{
			splice(pos, other, other.begin(), other.end());
		}

		void splice(const_iterator pos, list& other, const_iterator it)
		{	
			node_type* p = (node_type*)const_iterator::get_node(pos);
			node_type* f = (node_type*)const_iterator::get_node(it);
			if(f == other._tail)
				return ;

			if(f == other._head)
				other._head = f->_next;
			if (_head == p)
				_head = f;
			f->_prev->_next = f->_next;
			f->_next->_prev = f->_prev;
			
			p->_prev->_next = f;
			f->_prev = p->_prev;
			p->_prev = f;
			f->_next = p;
			++_size;
			--other._size;
		}
		
		void splice(const_iterator pos, list& other,
             const_iterator first, const_iterator last)
		{
			if (first != last)
			{
				node_type* p = (node_type*)const_iterator::get_node(pos);
				node_type* f = (node_type*)const_iterator::get_node(first);
				node_type* l = (node_type*)const_iterator::get_node(last);
				
				size_type range = distance(first, last);
				l = l->_prev;
				
				if(f == other._head)
					other._head = l->_next;
				if (_head == p)
					_head = f;

				other._size -= range;
				_size += range;

				f->_prev->_next = l->_next;
				l->_next->_prev = f->_prev;
				
				f->_prev = p->_prev;
				l->_next = p;
				
				p->_prev->_next = f;
				p->_prev = l;
			}
		}

	private:

		template <class Compare>
		node_type* sorted(node_type* a, node_type* b, Compare comp)
		{
			node_type* tmp;
			
			if (a == _tail)
				return b;
			else if (b == _tail)
				return a;
			if(comp(a->_value, b->_value))
			{
				tmp = a;
				tmp->_next = sorted(a->_next, b, comp);
			}
			else
			{
				tmp = b;
				tmp->_next = sorted(a, b->_next, comp);
			}
			return tmp;
		}

		void split_list(node_type* new_head, node_type** a, node_type** b)
		{
			node_type* fast = new_head->_next;
			node_type* slow = new_head;

			while (fast != _tail)
			{
				fast = fast->_next;
				if(fast != _tail)
				{
					slow = slow->_next;
					fast = fast->_next;
				}
			}
			*a = new_head;
			*b = slow->_next;
			slow->_next = _tail;
		}
		
		template <class Compare>
		void _merge_sort(node_type** head, Compare comp)
		{
			node_type* new_head = *head;
			node_type* a;
			node_type* b;
			
			if(new_head->_next == _tail || new_head == _tail)
				return ;
			split_list(new_head, &a, &b);
			_merge_sort(&a, comp);
			_merge_sort(&b, comp);
			*head = sorted(a, b, comp);
		}

		void avsb(node_type** a, node_type** b, node_type **c)
		{
			node_type* tmpa = (*a)->_next;
			node_type* tmpb = (*b)->_next;

			(*c)->_next = (*a);
			(*a)->_prev = (*c);
			(*a)->_next = (*b);
			(*b)->_prev = (*a);
			(*c) = (*b);
			*a = tmpa;
			*b = tmpb;
		}

	public:
	
		template <class Compare>
		void merge(list& other, Compare comp)
		{
			if (other._head == _head)
				return ;
			_size += other._size;
			node_type* new_list = _tail;
			
			while (_head != _tail && other._head != other._tail)
			{
				if (comp(_head->_value, other._head->_value))
					avsb(&_head, &(other._head), &new_list);
				else
					avsb(&(other._head), &_head, &new_list);
				new_list->_next = _head;
			}
			_head = _tail->_next;
			if (other._head != other._tail)
			{
				new_list->_next = other._head;
				other._head->_prev = new_list;
				other._tail->_prev->_next = _tail;
				_tail->_prev = other._tail->_prev;
			}
			other._tail->_next = other._tail;
			other._tail->_prev = other._tail;
			other._head = other._tail;
			other._size = 0;
		}

		void merge(list& other)
		{
			merge(other, my_comp);
		}
		
		template <class Predicate>
		void remove_if(Predicate pred)
		{
			iterator pos = begin();
			
			while (pos != end())
			{
				if (pred(*pos))
					pos = erase(pos);
				else
					++pos;
			}
		}
		
		void remove(const value_type& val)
		{
			iterator pos = begin();

			while (pos != end())
			{
				if (*pos == val)
					pos = erase(pos);
				else
					++pos;
			}
		}

		void unique()
		{
			iterator pos1 = begin();
			iterator pos2;

			while (pos1 != end())
			{
				pos2 = pos1;
				if (*pos1 == *++pos2 && pos2 != end())
					pos1 = erase(pos1);
				else
					++pos1;
			}			
		}
		
		template <class BinaryPredicate>
  		void unique (BinaryPredicate binary_pred)
		{
			iterator pos1 = begin();
			iterator pos2;

			while (pos1 != end())
			{
				pos2 = pos1;
				if (binary_pred(*pos1,*++pos2) && pos2 != end())
					pos1 = erase(pos1);
				else
					++pos1;
			}			
		}

		void sort()
		{
			sort(my_comp);
		}

		template <class Compare>
  		void sort (Compare comp)
		{
			node_type* tmp = _head;
			_merge_sort(&_head, comp);
			while (tmp != _tail)
			{
				tmp->_next->_prev = tmp;
				tmp = tmp->_next;
			}
		}

		void reverse()
		{
			list<value_type> a;
			
			iterator it = end();
			while (--it != end())
				a.push_back(*it);
			this->~list();
			init();
			merge(a);
		}
		
//relational operators:

		// friend bool operator==(const list& lhs, const list& rhs)
		// {
		// 	const_iterator first_l = lhs.begin();
		// 	const_iterator first_r = rhs.begin();
		
		// 	for (; (first_l != lhs.end()) && (first_r != rhs.end()); ++first_l, (void) ++first_r ) {
		// 		if (*first_l < *first_r) return true;
		// 		if (*first_r < *first_l) return false;
		// 	}
		// 	return (first_l != lhs.end()) && (first_r == rhs.end());
		// }

	};

//Non-member function overloads:

	template <class T, class Alloc>
  	void swap (list<T,Alloc>& x, list<T,Alloc>& y)
	{
		x.swap(y);
	}
	
	template <class T, class Alloc>
  	bool operator== (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		// typedef typename const list<T,Alloc>::const_iterator const_iterator;
		// const_iterator first_l = lhs.begin();
		// const_iterator first_r = rhs.begin();
		typename list<T,Alloc>::const_iterator first_l = lhs.begin();
		typename list<T,Alloc>::const_iterator first_r = rhs.begin();
	
		for (; (first_l != lhs.end()) && (first_r != rhs.end()); ++first_l, (void) ++first_r ) {
			if (*first_l != *first_r) return false;
		}
		return (lhs.size() == rhs.size());
	}
	
	template <class T, class Alloc>
  	bool operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		typedef typename list<T,Alloc>::const_iterator const_iterator;
		const_iterator first_l = lhs.begin();
		const_iterator first_r = rhs.begin();
	
		for (; (first_l != lhs.end()) && (first_r != rhs.end()); ++first_l, (void) ++first_r ) {
			if (*first_l != *first_r) return true;
		}
		return (lhs.size() != rhs.size());
	}

	template <class T, class Alloc>
  	bool operator< (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		typedef typename list<T,Alloc>::const_iterator const_iterator;
		const_iterator first_l = lhs.begin();
		const_iterator first_r = rhs.begin();
	
		for (; (first_l != lhs.end()) && (first_r != rhs.end()); ++first_l, (void) ++first_r ) {
			if (*first_l < *first_r) return true;
			if (*first_r < *first_l) return false;
		}
		return (lhs.size() < rhs.size());
	}

	template <class T, class Alloc>
  	bool operator> (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		typedef typename list<T,Alloc>::const_iterator const_iterator;
		const_iterator first_l = lhs.begin();
		const_iterator first_r = rhs.begin();
	
		for (; (first_l != lhs.end()) && (first_r != rhs.end()); ++first_l, (void) ++first_r ) {
			if (*first_l > *first_r) return true;
			if (*first_r > *first_l) return false;
		}
		return (lhs.size() > rhs.size());
	}

	template <class T, class Alloc>
	bool operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		typedef typename list<T,Alloc>::const_iterator const_iterator;
		const_iterator first_l = lhs.begin();
		const_iterator first_r = rhs.begin();
	
		for (; (first_l != lhs.end()) && (first_r != rhs.end()); ++first_l, (void) ++first_r ) {
			if (*first_l > *first_r) return true;
			if (*first_r > *first_l) return false;
		}
		return (lhs.size() >= rhs.size());
	}

	template <class T, class Alloc>
	bool operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		typedef typename list<T,Alloc>::const_iterator const_iterator;
		const_iterator first_l = lhs.begin();
		const_iterator first_r = rhs.begin();
	
		for (; (first_l != lhs.end()) && (first_r != rhs.end()); ++first_l, (void) ++first_r ) {
			if (*first_l > *first_r) return true;
			if (*first_r > *first_l) return false;
		}
		return (lhs.size() <= rhs.size());
	}
}

