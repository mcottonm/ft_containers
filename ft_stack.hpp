/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:20:58 by mcottonm          #+#    #+#             */
/*   Updated: 2021/04/14 16:42:56 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include "ft_list.hpp"

namespace ft
{
	template <typename T, class Container = list<T> >
	class stack
	{
	public:
	
		typedef T	value_type;
      	typedef size_t	size_type;
      	typedef Container	container_type;

	private:

		container_type c;
		
	public:
		
		explicit stack (const container_type& ctnr = container_type())
		: c(ctnr)
		{
		}
		
		bool empty() const
		{
			return c.empty();
		}

		size_type size() const
		{
			return c.size();
		}

		value_type& top()
		{
			return c.back();
		}
		
		const value_type& top() const
		{
			return c.back();
		}

		void push (const value_type& val)
		{
			c.push_back(val);
		}

		void pop()
		{
			c.pop_back();
		}
		
		
		bool operator== (const stack<T,Container>& rhs)
		{
			return(c == rhs.c);
		}
		
		
		bool operator!= (const stack<T,Container>& rhs)
		{
			return(c != rhs.c);
		}
		
		
		bool operator<  (const stack<T,Container>& rhs)
		{
			return(c < rhs.c);
		}
		
		
		bool operator<= (const stack<T,Container>& rhs)
		{
			return(c <= rhs.c);
		}

		
		bool operator>  (const stack<T,Container>& rhs)
		{
			return(c > rhs.c);
		}
		
		
		bool operator>= (const stack<T,Container>& rhs)
		{
			return(c >= rhs.c);
		}
	};

}