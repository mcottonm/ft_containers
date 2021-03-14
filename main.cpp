/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 20:34:34 by mcottonm          #+#    #+#             */
/*   Updated: 2021/03/19 21:59:31 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdint.h>
#include <iostream>
#include <malloc/malloc.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include "ft_vector.hpp"
#include "ft_list.hpp"
#include <list>

class A
{
public:
	char *c;
	A()
	{
		printf("constructor A\n");
	}

	A(const A&)
	{
		printf("copy constructor A\n");
	}

	~A()
	{
		if (malloc_size(c))
			free(c);
		printf("destructor A\n");
	}
};

void foo()
{
	ft::list<A> a(3);
		
	// std::list<A> b(3);
	// ft::list<A>::iterator it1 = a.begin();
	// *it1 = 5;
	// *it1 = 99;
	// for (int i = 0; i < 13; ++i)
	// 	printf("%d\n", *it1++);
}

int main()
{
	foo();
	while (1)
	{
		;
	}
}