/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 20:34:34 by mcottonm          #+#    #+#             */
/*   Updated: 2021/03/28 17:56:19 by mcottonm         ###   ########.fr       */
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
// #include "tree.hpp"
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

	ft::map<int,int> m;
	ft::pair<int,int> l(0,6);
	ft::pair<int,int> ll(1,2);
	ft::pair<int,int> lll(2,2);
	m.insert(l);
	m.insert(ll);
	m.insert(lll);
	printf("%d %d\n", m._root->value._key, m._root->value._content);
	// std::pair<int, int> i1(4,2);
	// std::pair<int, int> i2(1,0);
	// std::pair<int, int> i3(9,10);
	// std::pair<int,int> out;
	// std::map<int, int> l;
	
	// l.insert(i1);
	// l.insert(i2);
	// l.insert(i3);

	// std::map<int,int>::iterator it = l.end();
	// out = *--it;
	// std::cout << out.first << std::endl;
	// std::cout << out.second << std::endl;
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