/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 15:42:49 by mcottonm          #+#    #+#             */
/*   Updated: 2021/04/14 14:40:37 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include "ft_list.hpp"

namespace ft
{
	template <typename T, class Container = list<T> >
	class queue
	{
	public:
	
		typedef T	value_type;
      	typedef size_t	size_type;
      	typedef Container	container_type;

	private:

		container_type c;
		
	public:
	
		explicit queue (const container_type& ctnr = container_type())
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
		
		value_type& front()
		{
			return c.front();
		}
		
		const value_type& front() const
		{
			return c.front();
		}
		
		value_type& back()
		{
			return c.back();
		}
		
		const value_type& back() const
		{
			return c.back();
		}

		void push (const value_type& val)
		{
			c.push_back(val);
		}

		void pop()
		{
			c.pop_front();
		}
		
		bool operator== (const queue<T,Container>& rhs)
		{
			return(c == rhs.c);
		}
		
		
		bool operator!= (const queue<T,Container>& rhs)
		{
			return(c != rhs.c);
		}
		
		
		bool operator<  (const queue<T,Container>& rhs)
		{
			return(c < rhs.c);
		}
		
		
		bool operator<= (const queue<T,Container>& rhs)
		{
			return(c <= rhs.c);
		}

		
		bool operator>  (const queue<T,Container>& rhs)
		{
			return(c > rhs.c);
		}
		
		
		bool operator>= (const queue<T,Container>& rhs)
		{
			return(c >= rhs.c);
		}
	};
}