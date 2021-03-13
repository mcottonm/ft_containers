/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 20:34:34 by mcottonm          #+#    #+#             */
/*   Updated: 2021/03/13 18:03:10 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdint.h>
#include <iostream>
#include <malloc/malloc.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include "ft_vector.hpp"
#include <list>

class A
{
public:
	A()
	{
		printf("constructor A\n");
	}
	~A()
	{
		printf("destructor A\n");
	}
};

void foo()
{
	// char *a;
	// char *b;
	// a = (char*)malloc(100);
	// b = (char*)malloc(100);
	A a;
	ft::vector<char> v1;
	for (char i = 0; i < 11; ++i)
		v1.push_back(i);
	for (char i = 0; i < v1.size(); ++i)
		std::cout<< (int)v1[i];
	std::cout<< std::endl;
	ft::vector<char>::iterator it1 = v1.begin();
	// ft::vector<A> v2(4,a);
	// ft::vector<A>::iterator it2 = v2.end();
	// printf("%p\n", &it1);
	v1.insert(++it1, 3, 3);
	for (char i = 0; i < v1.size(); ++i)
		std::cout<< (int)v1[i];
	std::cout<< std::endl;
	// v2.insert(it2, a);
	// v1.pop_back();
	// v1.reserve(0);
	printf("E%lu\n", v1.capacity());
	printf("E%lu\n", v1.size());
}

int main()
{
	foo();
	while (1)
	{
		;
	}
	
}