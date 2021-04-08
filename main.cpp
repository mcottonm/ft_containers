/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 20:34:34 by mcottonm          #+#    #+#             */
/*   Updated: 2021/04/08 19:48:58 by mcottonm         ###   ########.fr       */
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
	std::unordered_set<std::string> a;
	std::unordered_set<std::string> myset;
	
	// a.Add("office");
	// a.Add("office");
	// a.Add("house");
	// a.Add("gym");
	// a.Add("parking");
	// a.Add("highway");
	// a.insert("highway");
	a.insert("house");
	a.insert("office");
	// a.insert("office");
	// a.insert("gym");
	// a.insert("parking");
	std::unordered_set<std::string>::iterator it = a.begin();
	std::cout << *++it << std::endl;
}

int main()
{
	foo();
	while (1)
	{
		;
	}
}