/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 20:34:34 by mcottonm          #+#    #+#             */
/*   Updated: 2021/04/02 20:18:33 by mcottonm         ###   ########.fr       */
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
	// std::list<int> a;
	// a.push_back(1);
	// a.push_back(2);
	// a.push_back(3);

	// ft::list<int>::iterator itr(a.end());
	// ft::list<int>::const_iterator it(a.begin());
	// // printf("%d\n", itr == it);
	// printf("%d\n", *itr);
	// printf("%d\n", *it);
	ft::pair<int, int> i1(5,2);
	ft::pair<int, int> i2(4,0);
	ft::pair<int, int> i3(2,10);
	ft::pair<int, int> i4(3,10);
	ft::pair<int, int> i5(6,10);
	ft::pair<int, int> i6(0,2);
	ft::pair<int,int> out1;
	ft::map<int, int> l;
	ft::pair<ft::map<int,int>::iterator, bool> out;
	
	l.insert(i1);
	l.insert(i2);
	l.insert(i3);
	l.insert(i4);
	l.insert(i5);
	l.insert(i6);
	// out = l.insert(i5);
	ft::map<int, int> t(l);
	ft::map<int, int> j;
	j = t;
	// ft::map<int,int>::const_iterator it = t.begin();
	// std::cout << (*(out.first)).first << std::endl;
	// std::cout << l.size() << std::endl;
	// it++++++;
	// std::cout << (*(it)).first << std::endl;
	// std::cout << (*(it)).second << std::endl;
	// tree_node* y = 0;

	// for(int i = 0; i < 9; i++)
	// {
	// 	if (!y)
	// 	{
	// 		y = new tree_node(i);
	// 		insert_case1(y);
	// 	}
	// 	else
	// 		insert(y,i, comp);
	// 	while (y->parent)
	// 		y = y->parent;
	// }
	// printf("%d\n", y->left->value);
	// printf("%d\n", y->left->color);
}

int main()
{
	foo();
	while (1)
	{
		;
	}
}