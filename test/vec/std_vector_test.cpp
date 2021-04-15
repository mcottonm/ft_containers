#include <iostream>
#include <vector>

#include "../test.hpp"       // class Test;
#include "../../ft_vector.hpp"

#define lib std
#define con vector

// Constructors ================================================================

void ft_constructors_capacity_test() {
	std::cout << "\ndefoult_constructor\n" << std::endl;
	lib::con<Test> useles;

	std::cout << "empty() : " << useles.empty()    << std::endl;
	std::cout << "size    : " << useles.size()     << std::endl;
	std::cout << "capacity: " << useles.capacity() << std::endl;
	std::cout << "arr     :" << std::endl;
	for (size_t i = 0; i < useles.size(); ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << useles[i].some_ << " ";
	}
	std::cout << std::endl;

	std::cout << "\nn_constructor\n" << std::endl;
	lib::con<Test> sus(20);
	for (size_t i = 0; i < sus.size(); ++i) {
		sus[i].some_ = i;
	}

	std::cout << "empty() : " << sus.empty()    << std::endl;
	std::cout << "size    : " << sus.size()     << std::endl;
	std::cout << "capacity: " << sus.capacity() << std::endl;
	std::cout << "arr     :" << std::endl;
	for (size_t i = 0; i < sus.size(); ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << sus[i].some_ << " ";
	}
	std::cout << std::endl;

	std::cout << "\nn_val_constructor\n" << std::endl;
	lib::con<Test> useless(128, 2);

	std::cout << "size    : " << useless.size()     << std::endl;
	std::cout << "capacity: " << useless.capacity() << std::endl;
	std::cout << "arr     :" << std::endl;
	for (size_t i = 0; i < useless.size(); ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << useless[i].some_ << " ";
	}
	std::cout << std::endl;


	std::cout << "\ncopy_constructor\n" << std::endl;
	lib::con<Test> base(128);
	for (size_t i = 0; i < base.size(); ++i) {
		base[i].some_ = i;
	}

	lib::con<Test> copy(base);

	std::cout << "size    : " << copy.size()     << std::endl;
	std::cout << "capacity: " << copy.capacity() << std::endl;
	std::cout << "arr     :" << std::endl;
	for (size_t i = 0; i < copy.size(); ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << copy[i].some_ << " ";
	}
	std::cout << std::endl;

	std::cout << "\nresize_test\n" << std::endl;
	lib::con<Test> mouse(128);
	for (size_t i = 0; i < mouse.size(); ++i) {
		mouse[i].some_ = i;
	}
	lib::con<Test> big_empty(mouse);
	lib::con<Test> small_mouse(mouse);
	lib::con<Test> big_mouse(mouse);

	std::cout << "size    : " << mouse.size()     << std::endl;
	std::cout << "capacity: " << mouse.capacity() << std::endl;
	std::cout << "arr     :" << std::endl;
	for (size_t i = 0; i < mouse.size(); ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << mouse[i].some_ << " ";
	}
	std::cout << std::endl;
	std::cout << (*mouse.begin()).some_      << std::endl;
	std::cout << (*(mouse.end() - 1)).some_  << std::endl;
	std::cout << (*mouse.rbegin()).some_     << std::endl;
	std::cout << (*(mouse.rend() - 1)).some_ << std::endl;

	big_empty.resize(64, 7);
	std::cout << "size    : " << big_empty.size()     << std::endl;
	std::cout << "capacity: " << big_empty.capacity() << std::endl;
	std::cout << "arr     :" << std::endl;
	for (size_t i = 0; i < big_empty.size(); ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << big_empty[i].some_ << " ";
	}
	std::cout << std::endl;

	try {
		big_mouse.resize(big_mouse.max_size() + 10);

	} catch(std::exception & e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "size    : " << big_mouse.size()     << std::endl;
	std::cout << "capacity: " << big_mouse.capacity() << std::endl;
	std::cout << "arr     :" << std::endl;
	for (size_t i = 0; i < big_mouse.size(); ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << big_mouse[i].some_ << " ";
	}
	std::cout << std::endl;

	std::cout << "\nreserve_test\n" << std::endl;
	lib::con<Test> mouses(128);
	lib::con<Test> empty;
	for (size_t i = 0; i < mouses.size(); ++i) {
		mouses[i].some_ = i;
	}

	std::cout << "size    : " << mouses.size()     << std::endl;
	std::cout << "capacity: " << mouses.capacity() << std::endl;
	std::cout << "arr     :" << std::endl;
	for (size_t i = 0; i < mouses.size(); ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << mouses[i].some_ << " ";
	}
	std::cout << std::endl;

	std::cout << "size    : " << empty.size()     << std::endl;
	std::cout << "capacity: " << empty.capacity() << std::endl;
	std::cout << "arr     :" << std::endl;
	for (size_t i = 0; i < empty.size(); ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << empty[i].some_ << " ";
	}

	try {
		mouses.reserve(mouses.max_size() + 10);

	} catch(std::exception & e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "size    : " << mouses.size()     << std::endl;
	std::cout << "capacity: " << mouses.capacity() << std::endl;
	std::cout << "arr     :" << std::endl;
	for (size_t i = 0; i < mouses.size(); ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << mouses[i].some_ << " ";
	}
	std::cout << std::endl;

	std::cout << "size    : " << empty.size()     << std::endl;
	std::cout << "capacity: " << empty.capacity() << std::endl;
	std::cout << "arr     :" << std::endl;
	for (size_t i = 0; i < empty.size(); ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << empty[i].some_ << " ";
	}
	std::cout << std::endl;
}

// =============================================================================

// Operator '=' ================================================================

void ft_operator_assignment() {
	std::cout << "\noperator_assignment\n" << std::endl;
	lib::con<Test> base(128);
	for (size_t i = 0; i < base.size(); ++i) {
		base[i].some_ = i;
	}

	lib::con<Test> copy;
	copy = base;

	std::cout << "size    : " << copy.size()     << std::endl;
	std::cout << "capacity: " << copy.capacity() << std::endl;
	std::cout << "arr     :" << std::endl;
	for (size_t i = 0; i < copy.size(); ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << copy[i].some_ << " ";
	}
	std::cout << std::endl;

}

// =============================================================================

// Iterators ===================================================================

void ft_iterator_test() {
	std::cout << "\niterator_test\n" << std::endl;
	lib::con<Test> mouse(128);
	for (size_t i = 0; i < mouse.size(); ++i) {
		mouse[i].some_ = i;
	}

	std::cout << "size    : " << mouse.size()     << std::endl;
	std::cout << "capacity: " << mouse.capacity() << std::endl;
	std::cout << "arr     :" << std::endl;
	for (size_t i = 0; i < mouse.size(); ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << mouse[i].some_ << " ";
	}
	std::cout << std::endl;
	std::cout << (*mouse.begin()).some_      << std::endl;
	std::cout << (*(mouse.end() - 1)).some_  << std::endl;
	std::cout << (*mouse.rbegin()).some_     << std::endl;
	std::cout << (*(mouse.rend() - 1)).some_ << std::endl;
}

// =============================================================================

// Element access ==============================================================

void ft_el_access_test() {
	std::cout << "\nel_access_test\n" << std::endl;
	lib::con<Test> one(1, 2);
	lib::con<Test> mouse(128);
	for (size_t i = 0; i < mouse.size(); ++i) {
		mouse[i].some_ = i;
	}

	std::cout << "size    : " << mouse.size()     << std::endl;
	std::cout << "capacity: " << mouse.capacity() << std::endl;
	std::cout << "arr     :" << std::endl;
	for (size_t i = 0; i < mouse.size(); ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << mouse.at(i).some_ << " ";
	}
	std::cout << std::endl;

	try {
		std::cout << mouse.at(1042).some_ << std::endl;

	} catch(std::exception & e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << one.front().some_   << std::endl;
	std::cout << mouse.front().some_ << std::endl;

	std::cout << one.back().some_   << std::endl;
	std::cout << mouse.back().some_ << std::endl;
}

// =============================================================================

// Modifiers ===================================================================

void ft_assign_test() {
	std::cout << "\nassign_iter_iter\n" << std::endl;
	lib::con<Test> mouse(128);
	lib::con<Test> empty;

	empty.assign(mouse.begin() + 5, mouse.end() - 5);

	std::cout << "size    : " << empty.size()     << std::endl;
	std::cout << "capacity: " << empty.capacity() << std::endl;
	std::cout << "arr     :" << std::endl;
	for (size_t i = 0; i < empty.size(); ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << empty.at(i).some_ << " ";
	}
	std::cout << std::endl;

	std::cout << "size    : " << mouse.size()     << std::endl;
	std::cout << "capacity: " << mouse.capacity() << std::endl;
	std::cout << "arr     :" << std::endl;
	for (size_t i = 0; i < mouse.size(); ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << mouse.at(i).some_ << " ";
	}
	std::cout << std::endl;
}

void ft_push_back_test() {
	std::cout << "\npush_back\n" << std::endl;
	lib::con<Test> empty;

	empty.push_back(8);

	std::cout << "size    : " << empty.size()     << std::endl;
	std::cout << "capacity: " << empty.capacity() << std::endl;
	std::cout << "arr     :" << std::endl;
	for (size_t i = 0; i < empty.size(); ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << empty.at(i).some_ << " ";
	}
	std::cout << std::endl;
}

void ft_pop_back_test() {
	std::cout << "\npop_back\n" << std::endl;
	lib::con<Test> mouse(128);
	for (size_t i = 0; i < mouse.size(); ++i) {
		mouse[i].some_ = i;
	}

	for (size_t i = 0; i < 10; ++i) {
		mouse.pop_back();
	}

	std::cout << "size    : " << mouse.size()     << std::endl;
	std::cout << "capacity: " << mouse.capacity() << std::endl;
	std::cout << "arr     :" << std::endl;
	for (size_t i = 0; i < mouse.size(); ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << mouse.at(i).some_ << " ";
	}
	std::cout << std::endl;
}

void ft_insert_iter_val_test() {
	std::cout << "\ninsert_iter_val\n" << std::endl;
	lib::con<Test> mouse(128);
	lib::con<Test> small_mouse(11);
	lib::con<Test> big_empty;
	big_empty.reserve(2023);
	for (size_t i = 0; i < mouse.size(); ++i) {
		mouse[i].some_ = i;
	}

	mouse.insert(mouse.begin(), 100);

	std::cout << "size    : " << mouse.size()     << std::endl;
	std::cout << "capacity: " << mouse.capacity() << std::endl;
	std::cout << "arr     :" << std::endl;
	for (size_t i = 0; i < mouse.size(); ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << mouse.at(i).some_ << " ";
	}
	std::cout << std::endl;
}

void ft_insert_iter_n_val_test() {
	std::cout << "\ninsert_iter_n_val\n" << std::endl;
	lib::con<Test> mouse(128);
	for (size_t i = 0; i < mouse.size(); ++i) {
		mouse[i].some_ = i;
	}

	mouse.insert(mouse.begin(), 20, 100);

	std::cout << "size    : " << mouse.size()     << std::endl;
	std::cout << "capacity: " << mouse.capacity() << std::endl;
	std::cout << "arr     :" << std::endl;
	for (size_t i = 0; i < mouse.size(); ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << mouse.at(i).some_ << " ";
	}
	std::cout << std::endl;
}

void ft_insert_iter_iter_iter_test() {
	std::cout << "\niter_iter_iter\n" << std::endl;
	lib::con<Test> mouse(128);
	lib::con<Test> empty;

	empty.insert(empty.begin(), mouse.begin() + 5, mouse.end() - 5);

	std::cout << "size    : " << empty.size()     << std::endl;
	std::cout << "capacity: " << empty.capacity() << std::endl;
	std::cout << "arr     :" << std::endl;
	for (size_t i = 0; i < empty.size(); ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << empty.at(i).some_ << " ";
	}
	std::cout << std::endl;
}

void ft_erase_test() {
	std::cout << "erase_test" << std::endl;
	lib::con<Test> mouse(129);
	for (size_t i = 0; i < mouse.size(); ++i) {
		mouse[i].some_ = i;
	}
	lib::con<Test> big_mouse(1023);
	for (size_t i = 0; i < big_mouse.size(); ++i) {
		big_mouse[i].some_ = i + 1000;
	}

	std::cout << mouse.erase(mouse.begin())->some_ << std::endl;

	std::cout << "size    : " << mouse.size()     << std::endl;
	std::cout << "capacity: " << mouse.capacity() << std::endl;
	std::cout << "arr     :" << std::endl;
	for (size_t i = 0; i < mouse.size(); ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << mouse.at(i).some_ << " ";
	}
	std::cout << std::endl;

	mouse.erase(mouse.end() - 1);
}

void ft_swap_test() {
	std::cout << "swap_test" << std::endl;
	lib::con<Test> mouse(129);
	for (size_t i = 0; i < mouse.size(); ++i) {
		mouse[i].some_ = i;
	}
	lib::con<Test> big_mouse(1023);
	for (size_t i = 0; i < big_mouse.size(); ++i) {
		big_mouse[i].some_ = i + 1000;
	}

	big_mouse.swap(mouse);

	std::cout << "size    : " << mouse.size()     << std::endl;
	std::cout << "capacity: " << mouse.capacity() << std::endl;
	std::cout << "arr     :" << std::endl;
	for (size_t i = 0; i < mouse.size(); ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << mouse.at(i).some_ << " ";
	}
	std::cout << std::endl;
}

void ft_clear_test() {
	std::cout << "clear_test" << std::endl;

	lib::con<Test> big_mouse(1023);
	for (size_t i = 0; i < big_mouse.size(); ++i) {
		big_mouse[i].some_ = i + 1000;
	}

	std::cout << "size    : " << big_mouse.size()     << std::endl;
	std::cout << "capacity: " << big_mouse.capacity() << std::endl;
	std::cout << "arr     :" << std::endl;
	for (size_t i = 0; i < big_mouse.size(); ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << big_mouse.at(i).some_ << " ";
	}
	std::cout << std::endl;

	big_mouse.clear();

	std::cout << "size    : " << big_mouse.size()     << std::endl;
	std::cout << "capacity: " << big_mouse.capacity() << std::endl;
	std::cout << "arr     :" << std::endl;
	for (size_t i = 0; i < big_mouse.size(); ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << big_mouse.at(i).some_ << " ";
	}
	std::cout << std::endl;
}

void ft_relational_operators() {
	std::cout << "relational_operators" << std::endl;
	lib::con<int> empty;
	lib::con<int> big_empty;
	lib::con<int> mouse(129);
	for (size_t i = 0; i < mouse.size(); ++i) {
		mouse[i] = i;
	}
	lib::con<int> big_mouse(1023);
	for (size_t i = 0; i < big_mouse.size(); ++i) {
		big_mouse[i] = i + 1000;
	}
	big_empty.reserve(190);
	std::cout << (empty     == empty)     << std::endl;
	std::cout << (big_empty == big_empty) << std::endl;
	std::cout << (mouse     == mouse)     << std::endl;
	std::cout << (big_mouse == big_mouse) << std::endl;

	std::cout << (empty     != empty)     << std::endl;
	std::cout << (big_empty != big_empty) << std::endl;
	std::cout << (mouse     != mouse)     << std::endl;
	std::cout << (big_mouse != big_mouse) << std::endl;

	std::cout << (empty     > big_empty)     << std::endl;
	std::cout << (big_empty > empty) << std::endl;
	std::cout << (mouse     > big_mouse)     << std::endl;
	std::cout << (big_mouse > mouse) << std::endl;

	std::cout << (empty     < big_empty)     << std::endl;
	std::cout << (big_empty < empty) << std::endl;
	std::cout << (mouse     < big_mouse)     << std::endl;
	std::cout << (big_mouse < mouse) << std::endl;

	std::cout << (empty     >= big_empty)     << std::endl;
	std::cout << (big_empty >= empty) << std::endl;
	std::cout << (mouse     >= big_mouse)     << std::endl;
	std::cout << (big_mouse >= mouse) << std::endl;

	std::cout << (empty     <= big_empty)     << std::endl;
	std::cout << (big_empty <= empty) << std::endl;
	std::cout << (mouse     <= big_mouse)     << std::endl;
	std::cout << (big_mouse <= mouse) << std::endl;
}

void const_iterators() {
	std::cout << "const_iterators" << std::endl;
	lib::con<int> src;
	for (int i = 0; i < 20; ++i) {
		src.push_back(i);
	}
	lib::con<const int>                 def(src.begin(), src.end());
	lib::con<const int>::const_iterator cit(def.begin());

	while (cit != def.end()) {
		std::cout << *cit << " ";
		++cit;
	}
	std::cout << std::endl;
//	*cit = 6; // DOES NOT COMPILE

	--cit;
	lib::con<const int>::const_iterator cit2(def.begin());
	std::cout << (cit > cit2) << std::endl;
	std::cout << (cit >= cit2) << std::endl;
	std::cout << (cit < cit2) << std::endl;
	std::cout << (cit <= cit2) << std::endl;
	std::cout << (cit == cit2) << std::endl;

	lib::con<int>::const_iterator cit_src(src.begin());
	while (cit_src != src.end()) {
		std::cout << *cit_src << " ";
		++cit_src;
	}
	std::cout << std::endl;
	// *cit_src = 6; // DOES NOT COMPILE
}

void reverse_iterators() {
	std::cout << "reverse_iterators" << std::endl;
	lib::con<int> src;
	for (int i = 0; i < 20; ++i) {
		src.push_back(i);
	}
	lib::con<const int>                         def(src.begin(), src.end());
	lib::con<const int>::const_reverse_iterator rcit(def.rbegin());

	while (rcit != def.rend()) {
		std::cout << *rcit << " ";
		++rcit;
	}
	std::cout << std::endl;
//	*rcit = 6; // DOES NOT COMPILE

	--rcit;
	lib::con<const int>::const_reverse_iterator rcit2(def.rbegin());
	std::cout << (rcit > rcit2) << std::endl;
	std::cout << (rcit < rcit2) << std::endl;
	std::cout << (rcit >= rcit2) << std::endl;
	std::cout << (rcit <= rcit2) << std::endl;
	std::cout << (rcit == rcit2) << std::endl;

	lib::con<int>::const_reverse_iterator rcit_src(src.end());
	while (rcit_src != src.rend()) {
		std::cout << *rcit_src << " ";
		++rcit_src;
	}
	std::cout << std::endl;
	// *rcit_src = 6; // DOES NOT COMPILE
}

void relational_operators() {
	std::cout << "relational_operators" << std::endl;
	lib::con<int> def;
	for (int i = 0; i < 10; i += 2) {
		def.push_back(2);
	}
	lib::con<int> def2;
	for (int i = 1; i < 20; i += 2) {
		def2.push_back(2);
	}
	std::cout << (def >  def2) << std::endl;
	std::cout << (def >= def2) << std::endl;
	std::cout << (def <  def2) << std::endl;
	std::cout << (def <= def2) << std::endl;
	std::cout << (def == def2) << std::endl;
	std::cout << (def != def2) << std::endl;
}

void const_iter_with_iter() {
	std::cout << "const_iter_with_iter" << std::endl;
	lib::con<int> def;
	for (int i = 0; i < 10; i += 2) {
		def.push_back(2);
	}
	lib::con<int>::iterator       it(def.begin());
	lib::con<int>::const_iterator cit(def.begin());

	std::cout << (it >  cit) << std::endl;
	std::cout << (it <  cit) << std::endl;
	std::cout << (it >= cit) << std::endl;
	std::cout << (it <= cit) << std::endl;
	std::cout << (it != cit) << std::endl;
	std::cout << (it == cit) << std::endl;

	lib::con<int>::reverse_iterator       rit(def.begin());
	lib::con<int>::const_reverse_iterator rcit(def.begin());

	std::cout << (rit >  rcit) << std::endl;
	std::cout << (rit <  rcit) << std::endl;
	std::cout << (rit >= rcit) << std::endl;
	std::cout << (rit <= rcit) << std::endl;
	std::cout << (rit != rcit) << std::endl;
	std::cout << (rit == rcit) << std::endl;
}

// =============================================================================

int main(void)
{
	ft_constructors_capacity_test();
	ft_operator_assignment();
	ft_el_access_test();

	ft_assign_test();
	ft_pop_back_test();
	ft_push_back_test();
	ft_insert_iter_val_test();
	ft_insert_iter_n_val_test();
	ft_insert_iter_iter_iter_test();

	ft_erase_test();
	ft_swap_test();
	ft_clear_test();
	ft_relational_operators();

	ft_iterator_test();
	relational_operators();
	const_iterators();
	reverse_iterators();
	const_iter_with_iter();
	return 0;
}