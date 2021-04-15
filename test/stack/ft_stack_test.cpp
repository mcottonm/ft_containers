
#include "../test.hpp"       // class Test;
#include "../../ft_map.hpp"
#include "../../ft_vector.hpp"
#include "../../ft_list.hpp"
#include "../../ft_stack.hpp"
#include <stack>
#include <list>
#include <vector>

#define lib ft
#define con stack

void stack_out(lib::con<Test>& x)
{
	std::cout << "empty() : " << x.empty()    << std::endl;
	std::cout << "size    : " << x.size()     << std::endl;
	std::cout << "arr     :" << std::endl;
	while (!x.empty())
	{
		std::cout << x.top().some_ << " ";
		x.pop();
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void construct_test()
{
	std::cout << "\nconstruct_test\n" << std::endl;
	lib::con<Test,lib::list<Test> > ls;
	lib::con<Test,lib::vector<Test> > vs;
	lib::con<Test> def1;
	lib::list<Test> l(10, 8);
	lib::vector<Test> v(10, 8);
	lib::con<Test,lib::list<Test> > lss(l);
	lib::con<Test,lib::vector<Test> > vss(v);

	stack_out(def1);
	std::cout << "empty() : " << vss.empty()    << std::endl;
	std::cout << "size    : " << vss.size()     << std::endl;
	std::cout << "arr     :" << std::endl;
	while (!vss.empty())
	{
		std::cout << vss.top().some_ << " ";
		vss.pop();
	}
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "empty() : " << lss.empty()    << std::endl;
	std::cout << "size    : " << lss.size()     << std::endl;
	std::cout << "arr     :" << std::endl;
	while (!lss.empty())
	{
		std::cout << lss.top().some_ << " ";
		lss.pop();
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void stack_in(lib::con<Test>& x)
{
	for(int i = 0; i < 11; ++i)
		x.push(i);
}

void el_action()
{
	std::cout << "\nel_action\n" << std::endl;
	lib::con<Test> def;
	stack_in(def);
	std::cout << def.top().some_ << std::endl;
	std::cout << std::endl;
	stack_out(def);

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