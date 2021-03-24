/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 20:34:34 by mcottonm          #+#    #+#             */
/*   Updated: 2021/03/24 05:48:53 by mcottonm         ###   ########.fr       */
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
#include <queue>

class A
{
public:
	int c;
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
		printf("destructor A\n");
	}
};

template<typename _Container>
void put_collection(_Container& container, std::string container_name = "default")
{
	container_name += ": {";
	typename _Container::iterator first = container.begin();
	typename _Container::iterator last = container.end();
	
	std::cout << container_name;
	while (first != last) {
		std::cout << " " << *first++;
	}
	std::cout << " }" << std::endl;
}

bool comp(int a, int b)
{
	return (a > b);
}

void foo()
{
	ft::list<int> a(2, 8);
	// ft::list<int> b(a.begin(), a.end());
	ft::list<int> b(2);
	ft::list<int> c(2, 10);
	ft::list<int> d;
	// d = c;
	// put_collection(b, "b");
	// d.assign(3, 4);
	// ft::list<int>::iterator it1 = c.begin();
	// ft::list<int>::iterator it2 = c.end();
	// ft::list<int>::iterator it = a.end();
	a.merge(c,comp);
	a.merge(b,comp);
	// a.reverse();
	// printf("%d\n", a == a);
	// a.splice(--it, c, it1, it2);
	// a.insert(it, 7);
	// a.assign(it2, it1);
	put_collection(a, "a");
	// // //*--it1 = 8;
	put_collection(c, "c");
	// put_collection(d, "d");
	// printf("%lu\n", d.max_size());
	// d.insert(it1,3);
}

int main()
{
	foo();
	while (1)
	{
		;
	}
}