
#include "../test.hpp"       // class Test;
#include "../../ft_map.hpp"
#include "../../ft_vector.hpp"
#include "../../ft_list.hpp"
#include "../../ft_stack.hpp"
#include <queue>
#include <list>
#include <vector>

#define lib std
#define con queue

void queue_out(lib::con<Test>& x)
{
	std::cout << "empty() : " << x.empty()    << std::endl;
	std::cout << "size    : " << x.size()     << std::endl;
	std::cout << "arr     :" << std::endl;
	while (!x.empty())
	{
		std::cout << x.front().some_ << " ";
		x.pop();
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void construct_test()
{
	std::cout << "\nconstruct_test\n" << std::endl;
	lib::con<Test,lib::list<Test> > ls;
	lib::con<Test> def1;
	lib::list<Test> l(10, 8);
	lib::con<Test,lib::list<Test> > lss(l);

	queue_out(def1);

	std::cout << "empty() : " << lss.empty()    << std::endl;
	std::cout << "size    : " << lss.size()     << std::endl;
	std::cout << "arr     :" << std::endl;
	while (!lss.empty())
	{
		std::cout << lss.front().some_ << " ";
		lss.pop();
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void queue_in(lib::con<Test>& x)
{
	for(int i = 0; i < 11; ++i)
		x.push(i);
}

void el_action()
{
	std::cout << "\nel_action\n" << std::endl;
	lib::con<Test> def;
	queue_in(def);
	std::cout << def.front().some_ << std::endl;
	std::cout << std::endl;
	queue_out(def);

	queue_in(def);
	std::cout << "empty() : " << def.empty()    << std::endl;
	std::cout << "size    : " << def.size()     << std::endl;
	std::cout << "arr     :" << std::endl;
	while (!def.empty())
	{
		std::cout << def.back().some_ << " ";
		def.pop();
	}
	std::cout << std::endl;
	std::cout << std::endl;
}


void relation_test()
{
	lib::con<int> rcit;
	for(int i = 0; i < 11; ++i)
		rcit.push(i);
	lib::con<int> rcit2;
	std::cout << (rcit > rcit2) << std::endl;
	std::cout << (rcit < rcit2) << std::endl;
	std::cout << (rcit >= rcit2) << std::endl;
	std::cout << (rcit <= rcit2) << std::endl;
	std::cout << (rcit == rcit2) << std::endl;
	std::cout << std::endl;
}

int main()
{
	construct_test();
	el_action();
	relation_test();
}