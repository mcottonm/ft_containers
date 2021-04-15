#include <iostream>
#include <map>
#include <ctime>
#include <unistd.h>

#include "../test.hpp"       // class Test;
#include "../../ft_map.hpp"

#define lib std
#define con map



// =============================================================================

std::string keys[10] = {
	"I",
	"don't",
	"want",
	"it",
	"anymore?",
	"ABC",
	"ZYX",
	"",
	"\n",
	"?"
};

void map_out(lib::con<std::string, Test> x)
{
	std::cout << "empty() : " << x.empty()    << std::endl;
	std::cout << "size    : " << x.size()     << std::endl;
	std::cout << "arr     :" << std::endl;
	for (lib::con<std::string, Test>::const_iterator i = x.begin(); i != x.end(); ++i) {
		std::cout << (*i).first << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void constructors_test()
{
	std::cout << "\ndefoult_constructor\n" << std::endl;

	lib::con<std::string, Test> useles;

	map_out(useles);

	for (int i = 0; i < 10; ++i) {
		lib::pair<std::string, Test> ps(keys[i], i);
		useles.insert(ps);
	}

	map_out(useles);

	lib::con<std::string, Test> copy(useles);

	map_out(copy);

	lib::con<std::string, Test> iter(copy.begin(), copy.end());

	map_out(iter);
}

void operator_assignment()
{
	std::cout << "\noperator_assignment\n" << std::endl;

	lib::con<std::string, Test> mymap;
	for (int i = 9; i >= 0; --i) {
		lib::pair<std::string, Test> ps(keys[i], i);
		mymap.insert(ps);
	}
	
	lib::con<std::string, Test> not_mymap;
	not_mymap = mymap;

	map_out(not_mymap);

	std::cout << "\nMAX_SIZE: " << std::endl;
	std::cout << not_mymap.max_size() << std::endl;
}

void el_access_test()
{
	std::cout << "\nel_access_test\n" << std::endl;

	lib::con<std::string, Test> mymap;
	for (int i = 9; i >= 0; --i) {
		lib::pair<std::string, Test> ps(keys[i], i);
		mymap.insert(ps);
	}

	std::cout << mymap[""].some_ << std::endl;
	std::cout << mymap["\n"].some_ << std::endl;
	std::cout << mymap["I"].some_ << std::endl;
	std::cout << mymap[""].some_ << std::endl;
	std::cout << mymap["anymore?"].some_ << std::endl;
}

void map_insert()
{
	std::cout << "\ninsert\n" << std::endl;

	lib::con<std::string, Test> mymap;
	for (int i = 0; i < 10; ++i) {
		lib::pair<std::string, Test> ps(keys[i], i);
		mymap.insert(ps);
	}

	lib::pair<std::string, Test> test1("yyy", 99);
	lib::pair<std::string, Test> test2("I", 0);

	std::cout << (*(mymap.insert(test1).first)).first << std::endl;
	std::cout << mymap.insert(test1).second << std::endl;

	lib::pair<std::string, Test> test3("xyz", 99);
	lib::con<std::string, Test>::iterator it = mymap.begin();
	lib::con<std::string, Test>::iterator itt = mymap.begin();

	std::cout << (*(mymap.insert(++++it, test3))).first << std::endl;
	map_out(mymap);

	lib::con<std::string, Test> not_mymap;
	for (int i = 0; i < 2; ++i) {
		lib::pair<std::string, Test> ps(keys[i], i);
		not_mymap.insert(ps);
	}

	it = mymap.begin();
	itt = mymap.end();
	not_mymap.insert(++it, --itt);
	map_out(not_mymap);
}

void erase_test()
{
	std::cout << "\nerise\n" << std::endl;

	lib::con<std::string, Test> mymap;
	for (int i = 0; i < 10; ++i) {
		lib::pair<std::string, Test> ps(keys[i], i);
		mymap.insert(ps);
	}

	lib::con<std::string, Test>::iterator it1 = mymap.begin();
	mymap.erase(it1);
	it1 = mymap.begin();
	mymap.erase(++++it1);

	map_out(mymap);

	std::cout << mymap.erase("I") << std::endl;
	std::cout << mymap.erase("I") << std::endl;
	std::cout << std::endl;

	it1 = mymap.end();
	mymap.erase(mymap.begin(), ----it1);

	map_out(mymap);
}

void swap_test()
{
	std::cout << "\nswap_test\n" << std::endl;
	lib::con<std::string, Test> mymap;
	for (int i = 0; i < 5; ++i) {
		lib::pair<std::string, Test> ps(keys[i], i);
		mymap.insert(ps);
	}

	lib::con<std::string, Test> not_mymap;
	for (int i = 5; i < 10; ++i) {
		lib::pair<std::string, Test> ps(keys[i], i);
		not_mymap.insert(ps);
	}
	mymap.swap(not_mymap);

	map_out(mymap);

	map_out(not_mymap);
}

void clear_test()
{
	std::cout << "\nclear_test\n" << std::endl;
	lib::con<std::string, Test> mymap;
	mymap.clear();

	for (int i = 0; i < 10; ++i) {
		lib::pair<std::string, Test> ps(keys[i], i);
		mymap.insert(ps);
	}
	map_out(mymap);
	mymap.clear();
	map_out(mymap);
}

void observers_test()
{
	std::cout << "\nkey_comp\n" << std::endl;
	lib::con<std::string, Test> mymap;
	for (int i = 0; i < 10; ++i) {
		lib::pair<std::string, Test> ps(keys[i], i);
		mymap.insert(ps);
	}
	std::string c("I");
	std::cout << mymap.key_comp()("I", (*(mymap.find("I"))).first) << std::endl;
	std::cout << mymap.key_comp()("I", (*(mymap.find("anymore?"))).first) << std::endl;

	std::cout << "\nvalue_comp\n" << std::endl;
	lib::pair<std::string, Test> p("", 8);
	std::cout << mymap.value_comp()(p, *(mymap.find(""))) << std::endl;
	std::cout << mymap.value_comp()(p, *(mymap.find("I"))) << std::endl;
}

void find_test()
{
	std::cout << "\nfind\n" << std::endl;
	lib::con<std::string, Test> mymap;
	for (int i = 0; i < 10; ++i) {
		lib::pair<std::string, Test> ps(keys[i], i);
		mymap.insert(ps);
	}

	std::cout << (*(mymap.find("it"))).first << std::endl;
	std::cout << (mymap.find("OOOOOOO") == mymap.end()) << std::endl;
}

void count_test()
{
	std::cout << "\ncount_test\n" << std::endl;
	lib::con<std::string, Test> mymap;
	for (int i = 0; i < 10; ++i) {
		lib::pair<std::string, Test> ps(keys[i], i);
		mymap.insert(ps);
	}

	std::cout << mymap.count("ABC") << std::endl;
	std::cout << mymap.count("sdfsdfABCasdfasdf") << std::endl;
}

void bounds_test()
{
	lib::con<std::string, Test> mymap;
	for (int i = 0; i < 10; ++i) {
		lib::pair<std::string, Test> ps(keys[i], i);
		mymap.insert(ps);
	}

	std::cout << "\nlower_bound\n" << std::endl;
	std::cout << (*(mymap.lower_bound("it"))).first << std::endl;
	std::cout << (*(mymap.lower_bound(""))).first << std::endl;

	std::cout << "\nupper_bound\n" << std::endl;
	std::cout << (*(mymap.upper_bound("it"))).first << std::endl;
	std::cout << (*(mymap.upper_bound(""))).first << std::endl;
}

void iterator_test()
{
	lib::con<std::string, Test> mymap;
	for (int i = 0; i < 10; ++i) {
		lib::pair<std::string, Test> ps(keys[i], i);
		mymap.insert(ps);
	}
	lib::pair<std::string, Test> pr("r", 9);
	lib::con<std::string, Test>::iterator it = mymap.begin();
	lib::con<std::string, Test>::const_iterator it_same(it);
	lib::con<std::string, Test>::reverse_iterator it_rev1(it);
	--it_rev1;
	it_rev1 = mymap.rbegin();
	std::cout << (it != it) << std::endl;
	std::cout << (it == it_same) << std::endl;

	// *it_same = pr;
	while (it_rev1 != mymap.rend())
		std::cout << (*(it_rev1++)).first << std::endl;
	std::cout << std::endl;
	while (it != mymap.end())
		std::cout << (*(it++)).first << std::endl;
}

int main(void)
{
	constructors_test();
	operator_assignment();

	el_access_test();

	map_insert();
	erase_test();
	swap_test();
	clear_test();

	observers_test();
	find_test();
	count_test();
	bounds_test();

	iterator_test();
	return 0;
}