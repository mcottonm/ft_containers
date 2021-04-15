/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 20:34:34 by mcottonm          #+#    #+#             */
/*   Updated: 2021/04/13 14:19:14 by mcottonm         ###   ########.fr       */
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
#include "ft_deque.hpp"
#include <list>
#include <queue>
#include "ft_map.hpp"
#include <map>
#include <unordered_set>
#include "ft_unordered_set.hpp"
#include "forward_iterator.hpp"
#include <stack>
#include "ft_stack.hpp"

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
	ft::vector<int> a;
	ft::vector<int>::const_iterator it = a.begin();
	ft::vector<int>::iterator it2 = a.begin();
	a.insert(it, 20);
	std::cout << (it != it2) << std::endl;
	
}

int main()
{
	foo();
	while (1)
	{
		;
	}
}