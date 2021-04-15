#include <iostream>
#include <list>

#include "../../ft_list.hpp"
#include "../test.hpp" // class Test;

// Constructors ================================================================

void ft_constructors_capacity_test() {
	std::cout << "\nstd_default_constructor\n" << std::endl;
	ft::list<Test> useles;

	std::cout << "empty() : " << useles.empty()    << std::endl;
	std::cout << "size    : " << useles.size()     << std::endl;
	std::cout << "\nstd_n_val_constructor\n" << std::endl;
	ft::list<Test> useless(10, 8);

	std::cout << "empty() : " << useless.empty()    << std::endl;
	std::cout << "size    : " << useless.size()     << std::endl;

	ft::list<Test>::iterator first = useless.begin();

	for (size_t i = 0; first != useless.end(); ++i, ++first) {
		if (i % 32 == 0 && i != 0)
			std::cout << std::endl;
		std::cout << first->some_ << " ";
	}
	std::cout << std::endl;

	std::cout << "\nstd_iter_iter_constructor\n" << std::endl;
	ft::list<Test>           s(20);
	ft::list<Test>::iterator s_iter;
	size_t                   i = 0;

	for (s_iter = s.begin(); s_iter != s.end(); ++s_iter, ++i) {
		s_iter->some_ = i;
	}

	ft::list<Test> uselesss(s.begin(), s.end());
	first = uselesss.begin();

	std::cout << "empty() : " << uselesss.empty()    << std::endl;
	std::cout << "size    : " << uselesss.size()     << std::endl;
	for (i = 0; first != uselesss.end(); ++i, ++first) {
		if (i % 32 == 0 && i != 0)
			std::cout << std::endl;
		std::cout << first->some_ << " ";
	}
	std::cout << std::endl;

	std::cout << "\nstd_copy_constructor\n" << std::endl;
	ft::list<Test>           src(20);
	ft::list<Test>::iterator src_iter;
	i = 0;

	for (src_iter = src.begin(); src_iter != src.end(); ++src_iter, ++i) {
		src_iter->some_ = i;
	}

	ft::list<Test> usele(src);
	first = usele.begin();

	std::cout << "empty() : " << usele.empty()    << std::endl;
	std::cout << "size    : " << usele.size()     << std::endl;
	for (i = 0; first != usele.end(); ++i, ++first) {
		if (i % 32 == 0 && i != 0)
			std::cout << std::endl;
		std::cout << first->some_ << " ";
	}
	std::cout << std::endl;
}

// =============================================================================

// Iterator ====================================================================

void ft_iterator_test() {
	std::cout << "\niterator_test()\n" << std::endl;
	ft::list<int>           mouse(10, 5);
	ft::list<int>           fat_mouse(1000, 9);
	ft::list<int>::iterator begin;
	ft::list<int>::iterator fat_end;

	begin    = mouse.begin();
	fat_end  = fat_mouse.end();

	std::cout << (begin++ == begin)     << std::endl;
	std::cout << (begin   == ++begin)   << std::endl;
	std::cout << (begin   == --fat_end) << std::endl;

	std::cout << (begin   != begin)     << std::endl;
	std::cout << (begin   != begin--)   << std::endl;
	std::cout << (--begin != begin)     << std::endl;
	std::cout << (begin   != --fat_end) << std::endl;

	std::cout << *begin << std::endl;
}

// =============================================================================

// Element access ==============================================================

void ft_element_access_test() {
	std::cout << "\nelement_access_test()\n" << std::endl;
	ft::list<int>           small_mouse(1);
	ft::list<int>           mouse(10);
	ft::list<int>::iterator iter;

	for (iter = small_mouse.begin(); iter != small_mouse.end(); ++iter) {
		*iter = 123;
	}
	std::cout << small_mouse.front() << std::endl;
	std::cout << small_mouse.back()  << std::endl;

	size_t i = 900;
	for (iter = mouse.begin(); iter != mouse.end(); ++iter) {
		*iter = i++;
	}

	std::cout << mouse.front() << std::endl;
	std::cout << mouse.back()  << std::endl;
}

// =============================================================================

// Modifiers ===================================================================

void ft_push_front_test() {
	std::cout << "\npush_front_test()\n" << std::endl;
	ft::list<int>           empty_mouse;
	ft::list<int>           small_mouse(1);
	ft::list<int>           mouse(10);
	ft::list<int>::iterator iter;
	size_t                  i = 0;

	// empty_mouse
	for (i = 0; i < 19 ; ++i) {
		empty_mouse.push_front(i + 50);
	}
	std::cout << "empty() : " << empty_mouse.empty() << std::endl;
	std::cout << "size    : " << empty_mouse.size()  << std::endl;
	i = 0;
	for (iter = empty_mouse.begin(); iter != empty_mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << *iter << " ";
	}
	std::cout << std::endl;

	// small_mouse
	for (i = 0; i < 27 ; ++i) {
		small_mouse.push_front(i + 20);
	}
	std::cout << "empty() : " << small_mouse.empty() << std::endl;
	std::cout << "size    : " << small_mouse.size()  << std::endl;
	i = 0;
	for (iter = small_mouse.begin(); iter != small_mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << *iter << " ";
	}
	std::cout << std::endl;

	// mouse
	for (i = 0; i < 27 ; ++i) {
		mouse.push_front(i + 900);
	}
	std::cout << "empty() : " << mouse.empty() << std::endl;
	std::cout << "size    : " << mouse.size()  << std::endl;
	i = 0;
	for (iter = mouse.begin(); iter != mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << *iter << " ";
	}
	std::cout << std::endl;
}

void ft_pop_front_test() {
	std::cout << "\npop_front_test()\n" << std::endl;
	ft::list<Test>           small_mouse(1, 10);
	ft::list<Test>           mouse(18, 8);
	ft::list<Test>::iterator iter;
	size_t                   i;

	small_mouse.pop_front();
	std::cout << "empty() : " << small_mouse.empty() << std::endl;
	std::cout << "size    : " << small_mouse.size()  << std::endl;
	i = 0;
	for (iter = small_mouse.begin(); iter != small_mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;

	i = 10;
	while (i--) {
		mouse.pop_front();
	}
	std::cout << "empty() : " << mouse.empty() << std::endl;
	std::cout << "size    : " << mouse.size()  << std::endl;
	i = 0;
	for (iter = mouse.begin(); iter != mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;
}

void ft_erase_position_test() {
	std::cout << "\nerase_position_test()\n" << std::endl;
	ft::list<Test>           small_mouse(1, 10);
	ft::list<Test>           mouse;
	ft::list<Test>::iterator iter;
	size_t                   i;

	for (i = 0; i < 10; ++i) {
		mouse.push_back(i + 10);
	}

	small_mouse.erase(small_mouse.begin());
	std::cout << "empty() : " << small_mouse.empty() << std::endl;
	std::cout << "size    : " << small_mouse.size()  << std::endl;
	i = 0;
	for (iter = small_mouse.begin(); iter != small_mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;

	iter = mouse.begin();
	++iter;
	++iter;
	++iter;
	mouse.erase(iter);
	std::cout << "empty() : " << mouse.empty() << std::endl;
	std::cout << "size    : " << mouse.size()  << std::endl;
	i = 0;
	for (iter = mouse.begin(); iter != mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;

	iter = mouse.end();
	--iter;
	mouse.erase(iter);
	std::cout << "empty() : " << mouse.empty() << std::endl;
	std::cout << "size    : " << mouse.size()  << std::endl;
	i = 0;
	for (iter = mouse.begin(); iter != mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;
}

void ft_erase_iter_iter_test() {
	std::cout << "\nerase_iter_iter_test()\n" << std::endl;
	ft::list<Test>           small_mouse(1, 10);
	ft::list<Test>           mouse;
	ft::list<Test>::iterator iter;
	ft::list<Test>::iterator iter2;
	size_t                    i;

	for (i = 0; i < 10; ++i) {
		mouse.push_back(i + 10);
	}

	small_mouse.erase(small_mouse.begin(), small_mouse.end());
	std::cout << "empty() : " << small_mouse.empty() << std::endl;
	std::cout << "size    : " << small_mouse.size()  << std::endl;
	i = 0;
	for (iter = small_mouse.begin(); iter != small_mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;

	iter  = mouse.begin();
	iter2 = mouse.begin();
	i = 3;
	while (i--) {
		++iter;
	}
	i = 6;
	while (i--) {
		++iter2;
	}
	mouse.erase(iter, iter2);
	std::cout << "empty() : " << mouse.empty() << std::endl;
	std::cout << "size    : " << mouse.size()  << std::endl;
	i = 0;
	for (iter = mouse.begin(); iter != mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;

	mouse.erase(mouse.begin(), mouse.end());
	std::cout << "empty() : " << mouse.empty() << std::endl;
	std::cout << "size    : " << mouse.size()  << std::endl;
	i = 0;
	for (iter = mouse.begin(); iter != mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;
}

void ft_swap_test() {
	std::cout << "\nswap_test()\n" << std::endl;
	ft::list<Test>           mouse;
	ft::list<Test>           fat_mouse;
	ft::list<Test>::iterator iter;
	size_t                    i;

	for (i = 0; i < 10; ++i) {
		mouse.push_back(i + 10);
	}
	i = 0;
	for (i = 0; i < 1000; ++i) {
		fat_mouse.push_back(i + 100);
	}
	mouse.swap(fat_mouse);
	std::cout << "empty() : " << mouse.empty() << std::endl;
	std::cout << "size    : " << mouse.size()  << std::endl;
	i = 0;
	for (iter = mouse.begin(); iter != mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;

	std::cout << "empty() : " << fat_mouse.empty() << std::endl;
	std::cout << "size    : " << fat_mouse.size()  << std::endl;
	i = 0;
	for (iter = fat_mouse.begin(); iter != fat_mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;
}

void ft_resize_test() {
	std::cout << "\nresize_test()\n" << std::endl;
	std::list<Test>           mouse;
	std::list<Test>           fat_mouse;
	std::list<Test>::iterator iter;
	size_t                    i;

	for (i = 0; i < 10; ++i) {
		mouse.push_back(i + 10);
	}
	i = 0;
	for (i = 0; i < 1000; ++i) {
		fat_mouse.push_back(i + 100);
	}

	mouse.resize(50, 2);
	std::cout << "empty() : " << mouse.empty() << std::endl;
	std::cout << "size    : " << mouse.size()  << std::endl;
	i = 0;
	for (iter = mouse.begin(); iter != mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;

	fat_mouse.resize(100, 8);
	std::cout << "empty() : " << fat_mouse.empty() << std::endl;
	std::cout << "size    : " << fat_mouse.size()  << std::endl;
	i = 0;
	for (iter = fat_mouse.begin(); iter != fat_mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;
}

void ft_clear_test() {
	std::cout << "\nclear_test()\n" << std::endl;
	ft::list<Test>           empty_mouse;
	ft::list<Test>           mouse;
	ft::list<Test>           fat_mouse;
	ft::list<Test>::iterator iter;
	size_t                    i;

	for (i = 0; i < 10; ++i) {
		mouse.push_back(i + 10);
	}
	i = 0;
	for (i = 0; i < 1000; ++i) {
		fat_mouse.push_back(i + 100);
	}

	empty_mouse.clear();
	std::cout << "empty() : " << empty_mouse.empty() << std::endl;
	std::cout << "size    : " << empty_mouse.size()  << std::endl;
	i = 0;
	for (iter = empty_mouse.begin(); iter != empty_mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;

	mouse.clear();
	std::cout << "empty() : " << mouse.empty() << std::endl;
	std::cout << "size    : " << mouse.size()  << std::endl;
	i = 0;
	for (iter = mouse.begin(); iter != mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;

	fat_mouse.clear();
	std::cout << "empty() : " << fat_mouse.empty() << std::endl;
	std::cout << "size    : " << fat_mouse.size()  << std::endl;
	i = 0;
	for (iter = fat_mouse.begin(); iter != fat_mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;
}

void ft_insert_iter_val_test() {
	std::cout << "\ninsert_iter_val_test()\n" << std::endl;
	ft::list<Test>           empty_mouse;
	ft::list<Test>           mouse;
	ft::list<Test>           fat_mouse;
	ft::list<Test>::iterator iter;
	size_t                    i;

	for (i = 0; i < 10; ++i) {
		mouse.push_back(i + 10);
	}
	i = 0;
	for (i = 0; i < 1000; ++i) {
		fat_mouse.push_back(i + 100);
	}

	std::cout << empty_mouse.insert(empty_mouse.begin(), 7)->some_ << std::endl;

	std::cout << "empty() : " << empty_mouse.empty() << std::endl;
	std::cout << "size    : " << empty_mouse.size()  << std::endl;
	i = 0;
	for (iter = empty_mouse.begin(); iter != empty_mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;

	iter = mouse.begin();
	i = 5;
	while (i--) {
		++iter;
	}
	std::cout << mouse.insert(iter, 7)->some_ << std::endl;
	std::cout << "empty() : " << mouse.empty() << std::endl;
	std::cout << "size    : " << mouse.size()  << std::endl;
	i = 0;
	for (iter = mouse.begin(); iter != mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;

	iter = fat_mouse.end();
	std::cout << fat_mouse.insert(iter, 7)->some_ << std::endl;
	std::cout << "empty() : " << fat_mouse.empty() << std::endl;
	std::cout << "size    : " << fat_mouse.size()  << std::endl;
	i = 0;
	for (iter = fat_mouse.begin(); iter != fat_mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;
}

void ft_insert_iter_n_val_test() {
	std::cout << "\ninsert_iter_val_test()\n" << std::endl;
	ft::list<Test>           empty_mouse;
	ft::list<Test>           mouse;
	ft::list<Test>           fat_mouse;
	ft::list<Test>::iterator iter;
	size_t                    i;

	for (i = 0; i < 10; ++i) {
		mouse.push_back(i + 10);
	}
	i = 0;
	for (i = 0; i < 1000; ++i) {
		fat_mouse.push_back(i + 100);
	}

	empty_mouse.insert(empty_mouse.begin(), 2, 7);

	std::cout << "empty() : " << empty_mouse.empty() << std::endl;
	std::cout << "size    : " << empty_mouse.size()  << std::endl;
	i = 0;
	for (iter = empty_mouse.begin(); iter != empty_mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;

	iter = mouse.begin();
	i = 5;
	while (i--) {
		++iter;
	}
	mouse.insert(iter, 10, 7);;
	std::cout << "empty() : " << mouse.empty() << std::endl;
	std::cout << "size    : " << mouse.size()  << std::endl;
	i = 0;
	for (iter = mouse.begin(); iter != mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;

	iter = fat_mouse.end();
	fat_mouse.insert(iter, 7, 7);
	std::cout << "empty() : " << fat_mouse.empty() << std::endl;
	std::cout << "size    : " << fat_mouse.size()  << std::endl;
	i = 0;
	for (iter = fat_mouse.begin(); iter != fat_mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;
}

void ft_insert_iter_iter_iter_test() {
	std::cout << "\ninsert_iter_iter_iter_test()\n" << std::endl;
	ft::list<Test>           empty_mouse;
	ft::list<Test>           mouse;
	ft::list<Test>           fat_mouse;
	ft::list<Test>::iterator iter;
	ft::list<Test>::iterator iter2;
	size_t                    i;

	for (i = 0; i < 10; ++i) {
		mouse.push_back(i + 10);
	}
	i = 0;
	for (i = 0; i < 1000; ++i) {
		fat_mouse.push_back(i + 100);
	}

	empty_mouse.insert(empty_mouse.begin(), mouse.begin(), mouse.end());

	std::cout << "empty() : " << empty_mouse.empty() << std::endl;
	std::cout << "size    : " << empty_mouse.size()  << std::endl;
	i = 0;
	for (iter = empty_mouse.begin(); iter != empty_mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;

	iter = mouse.begin();
	i = 5;
	while (i--) {
		++iter;
	}
	iter2 = mouse.end();
	iter2--;
	mouse.insert(iter, iter, iter2);
	std::cout << "empty() : " << mouse.empty() << std::endl;
	std::cout << "size    : " << mouse.size()  << std::endl;
	i = 0;
	for (iter = mouse.begin(); iter != mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;

	iter = mouse.begin();
	i = 5;
	while (i--) {
		++iter;
	}
	iter2 = mouse.end();
	iter2--;

	fat_mouse.insert(fat_mouse.end(), iter, iter2);
	std::cout << "empty() : " << fat_mouse.empty() << std::endl;
	std::cout << "size    : " << fat_mouse.size()  << std::endl;
	i = 0;
	for (iter = fat_mouse.begin(); iter != fat_mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;
}

void ft_assign_iter_iter_test() {
	std::cout << "\nassign_iter_iter_test()\n" << std::endl;
	ft::list<Test>           empty_mouse;
	ft::list<Test>           mouse;
	ft::list<Test>           fat_mouse;
	ft::list<Test>::iterator iter;
	ft::list<Test>::iterator iter2;
	size_t                    i;

	for (i = 0; i < 10; ++i) {
		mouse.push_back(i + 10);
	}
	i = 0;
	for (i = 0; i < 1000; ++i) {
		fat_mouse.push_back(i + 100);
	}

	empty_mouse.assign(mouse.begin(), mouse.end());

	std::cout << "empty() : " << empty_mouse.empty() << std::endl;
	std::cout << "size    : " << empty_mouse.size()  << std::endl;
	i = 0;
	for (iter = empty_mouse.begin(); iter != empty_mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;

	iter = fat_mouse.begin();
	i = 5;
	while (i--) {
		++iter;
	}
	iter2 = fat_mouse.end();
	iter2--;
	mouse.assign(iter, iter2);
	std::cout << "empty() : " << mouse.empty() << std::endl;
	std::cout << "size    : " << mouse.size()  << std::endl;
	i = 0;
	for (iter = mouse.begin(); iter != mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;

	iter = mouse.begin();
	i = 5;
	while (i--) {
		++iter;
	}
	iter2 = mouse.end();
	iter2--;

	fat_mouse.assign(mouse.begin(), mouse.end());
	std::cout << "empty() : " << fat_mouse.empty() << std::endl;
	std::cout << "size    : " << fat_mouse.size()  << std::endl;
	i = 0;
	for (iter = fat_mouse.begin(); iter != fat_mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;
}

void ft_assign_n_val_test() {
	std::cout << "\nassign_iter_iter_test()\n" << std::endl;
	ft::list<Test>           empty_mouse;
	ft::list<Test>           mouse;
	ft::list<Test>           fat_mouse;
	ft::list<Test>::iterator iter;
	size_t                   i;

	for (i = 0; i < 10; ++i) {
		mouse.push_back(i + 10);
	}
	i = 0;
	for (i = 0; i < 1000; ++i) {
		fat_mouse.push_back(i + 100);
	}

	empty_mouse.assign(7, 10);

	std::cout << "empty() : " << empty_mouse.empty() << std::endl;
	std::cout << "size    : " << empty_mouse.size()  << std::endl;
	i = 0;
	for (iter = empty_mouse.begin(); iter != empty_mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;

	mouse.assign(3, 99);
	std::cout << "empty() : " << mouse.empty() << std::endl;
	std::cout << "size    : " << mouse.size()  << std::endl;
	i = 0;
	for (iter = mouse.begin(); iter != mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;

	fat_mouse.assign(21, 1);
	std::cout << "empty() : " << fat_mouse.empty() << std::endl;
	std::cout << "size    : " << fat_mouse.size()  << std::endl;
	i = 0;
	for (iter = fat_mouse.begin(); iter != fat_mouse.end() ; ++iter, ++i) {
		if (i != 0 && i % 32 == 0)
			std::cout << std::endl;
		std::cout << iter->some_ << " ";
	}
	std::cout << std::endl;
}

// =============================================================================

// Operations ==================================================================

void ft_merge_x_test() {
	std::cout << "\nmerge_x_test()\n" << std::endl;
	ft::list<int> mouse;
	mouse.push_back(10);
	mouse.push_back(20);
	mouse.push_back(60);
	mouse.push_back(90);
	mouse.push_back(200);
	mouse.push_back(-5);

	ft::list<int> copy_mouse(mouse);

	ft::list<int> fat_mouse;
	fat_mouse.push_back(205);
	fat_mouse.push_back(15);
	fat_mouse.push_back(25);
	fat_mouse.push_back(45);
	fat_mouse.push_back(75);
	fat_mouse.push_back(85);
	fat_mouse.push_back(105);
	fat_mouse.push_back(115);

	mouse.merge(fat_mouse);

	std::cout << "mouse:" << std::endl;
	std::cout << "size:"  << mouse.size()  << std::endl;
	std::cout << "empty:" << mouse.empty() << std::endl;
	for (ft::list<int>::iterator it = mouse.begin(); it != mouse.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	mouse.merge(copy_mouse);

	std::cout << "mouse:" << std::endl;
	std::cout << "size:"  << mouse.size()  << std::endl;
	std::cout << "empty:" << mouse.empty() << std::endl;
	for (ft::list<int>::iterator it = mouse.begin(); it != mouse.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	mouse.merge(mouse);

	std::cout << "mouse:" << std::endl;
	std::cout << "size:"  << mouse.size()  << std::endl;
	std::cout << "empty:" << mouse.empty() << std::endl;
	for (ft::list<int>::iterator it = mouse.begin(); it != mouse.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}


bool compare(int a, int b) {
	return a < b;
}

void ft_merge_x_compare_test() {
	std::cout << "\nmerge_x_test()\n" << std::endl;
	ft::list<int> mouse;
	mouse.push_back(10);
	mouse.push_back(20);
	mouse.push_back(60);
	mouse.push_back(90);
	mouse.push_back(200);
	mouse.push_back(-5);

	ft::list<int> copy_mouse(mouse);

	ft::list<int> fat_mouse;
	fat_mouse.push_back(5);
	fat_mouse.push_back(25);
	fat_mouse.push_back(45);
	fat_mouse.push_back(75);
	fat_mouse.push_back(85);
	fat_mouse.push_back(105);
	fat_mouse.push_back(115);
	fat_mouse.push_back(205);

	mouse.merge(fat_mouse, compare);

	std::cout << "mouse:" << std::endl;
	std::cout << "size:"  << mouse.size()  << std::endl;
	std::cout << "empty:" << mouse.empty() << std::endl;
	for (ft::list<int>::iterator it = mouse.begin(); it != mouse.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	mouse.merge(copy_mouse, compare);

	std::cout << "mouse:" << std::endl;
	std::cout << "size:"  << mouse.size()  << std::endl;
	std::cout << "empty:" << mouse.empty() << std::endl;
	for (ft::list<int>::iterator it = mouse.begin(); it != mouse.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	mouse.merge(mouse, compare);

	std::cout << "mouse:" << std::endl;
	std::cout << "size:"  << mouse.size()  << std::endl;
	std::cout << "empty:" << mouse.empty() << std::endl;
	for (ft::list<int>::iterator it = mouse.begin(); it != mouse.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

}

void ft_sort_test() {
    std::cout << "sort_test" << std::endl;
    ft::list<int> mouse;
    mouse.push_back(7);
    mouse.push_back(3);
    mouse.push_back(5);
    mouse.push_back(13);
    mouse.push_back(9);
    mouse.push_back(6);

    mouse.sort();
	std::cout << "mouse:" << std::endl;
	std::cout << "size:"  << mouse.size()  << std::endl;
	std::cout << "empty:" << mouse.empty() << std::endl;
    for (ft::list<int>::iterator it = mouse.begin(); it != mouse.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    ft::list<int> empty;

    empty.sort();
    for (ft::list<int>::iterator it = empty.begin(); it != empty.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    ft::list<int> reverse;
    reverse.push_back(10);
    reverse.push_back(9);
    reverse.push_back(8);
    reverse.push_back(7);
    reverse.push_back(6);
    reverse.push_back(5);

    reverse.sort();
    for (ft::list<int>::iterator it = reverse.begin(); it != reverse.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

bool comp(int a, int b) {
	return a < b;
}

void ft_sort_comp_test() {
	std::cout << "sort_comp_test" << std::endl;
	ft::list<int> mouse;
	mouse.push_back(7);
	mouse.push_back(3);
	mouse.push_back(5);
	mouse.push_back(13);
	mouse.push_back(9);
	mouse.push_back(6);

	mouse.sort(comp);
	for (ft::list<int>::iterator it = mouse.begin(); it != mouse.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	ft::list<int> empty;

	empty.sort(comp);
	for (ft::list<int>::iterator it = empty.begin(); it != empty.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	ft::list<int> reverse;
	reverse.push_back(10);
	reverse.push_back(9);
	reverse.push_back(8);
	reverse.push_back(7);
	reverse.push_back(6);
	reverse.push_back(5);

	reverse.sort(comp);
	for (ft::list<int>::iterator it = reverse.begin(); it != reverse.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	reverse.reverse();
	reverse.sort(comp);
	for (ft::list<int>::iterator it = reverse.begin(); it != reverse.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void ft_reverse_test() {
	ft::list<int> empty;
	ft::list<int> reverse;
	reverse.push_back(10);
	reverse.push_back(9);
	reverse.push_back(8);
	reverse.push_back(7);
	reverse.push_back(6);
	reverse.push_back(5);

	reverse.reverse();
	for (ft::list<int>::iterator it = reverse.begin(); it != reverse.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	std::cout << "mouse:" << std::endl;
	std::cout << "size:"  << reverse.size()  << std::endl;
	std::cout << "empty:" << reverse.empty() << std::endl;

	empty.reverse();
	for (ft::list<int>::iterator it = empty.begin(); it != empty.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	std::cout << "mouse:" << std::endl;
	std::cout << "size:"  << empty.size()  << std::endl;
	std::cout << "empty:" << empty.empty() << std::endl;
}

void ft_splice_pos_lst_test() {
	ft::list<Test>           empty;
	ft::list<Test>           mouse;
	ft::list<Test>           fat_mouse;
	ft::list<Test>::iterator it;
	for (int i = 0; i < 10; ++i) {
		mouse.push_back(i + 10);
	}
	for (int i = 0; i < 5; ++i) {
		fat_mouse.push_back(i + 100);
	}
	it = mouse.begin();
	++it; ++it;

	mouse.splice(it, fat_mouse);

	std::cout << "mouse:" << std::endl;
	std::cout << "size:"  << mouse.size()  << std::endl;
	std::cout << "empty:" << mouse.empty() << std::endl;
	for (it = mouse.begin(); it != mouse.end(); ++it) {
		std::cout << it->some_ << " ";
	}
	std::cout << std::endl;
	std::cout << "fat_mouse:" << std::endl;
	std::cout << "size:"  << fat_mouse.size()  << std::endl;
	std::cout << "empty:" << fat_mouse.empty() << std::endl;
	for (it = fat_mouse.begin(); it != fat_mouse.end(); ++it) {
		std::cout << it->some_ << " ";
	}
	std::cout << std::endl;

	for (int i = 0; i < 20; ++i) {
		fat_mouse.push_back(i + 100);
	}

	mouse.splice(mouse.begin(), fat_mouse);

	std::cout << "mouse:" << std::endl;
	std::cout << "size:"  << mouse.size()  << std::endl;
	std::cout << "empty:" << mouse.empty() << std::endl;
	for (it = mouse.begin(); it != mouse.end(); ++it) {
		std::cout << it->some_ << " ";
	}
	std::cout << std::endl;
	std::cout << "fat_mouse:" << std::endl;
	std::cout << "size:"  << fat_mouse.size()  << std::endl;
	std::cout << "empty:" << fat_mouse.empty() << std::endl;
	for (it = fat_mouse.begin(); it != fat_mouse.end(); ++it) {
		std::cout << it->some_ << " ";
	}
	std::cout << std::endl;

	for (int i = 0; i < 5; ++i) {
		fat_mouse.push_back(i + 100);
	}

	mouse.splice(mouse.end(), fat_mouse);

	std::cout << "mouse:" << std::endl;
	std::cout << "size:"  << mouse.size()  << std::endl;
	std::cout << "empty:" << mouse.empty() << std::endl;
	for (it = mouse.begin(); it != mouse.end(); ++it) {
		std::cout << it->some_ << " ";
	}
	std::cout << std::endl;
	std::cout << "fat_mouse:" << std::endl;
	std::cout << "size:"  << fat_mouse.size()  << std::endl;
	std::cout << "empty:" << fat_mouse.empty() << std::endl;
	for (it = fat_mouse.begin(); it != fat_mouse.end(); ++it) {
		std::cout << it->some_ << " ";
	}
	std::cout << std::endl;

	mouse.splice(mouse.begin(), empty);

	std::cout << "mouse:" << std::endl;
	std::cout << "size:"  << mouse.size()  << std::endl;
	std::cout << "empty:" << mouse.empty() << std::endl;
	for (it = mouse.begin(); it != mouse.end(); ++it) {
		std::cout << it->some_ << " ";
	}
	std::cout << std::endl;
}

void ft_splice_pos_lst_i_test() {
	ft::list<Test>           mouse;
	ft::list<Test>           fat_mouse;
	ft::list<Test>::iterator it;
	for (int i = 0; i < 10; ++i) {
		mouse.push_back(i + 10);
	}
	for (int i = 0; i < 5; ++i) {
		fat_mouse.push_back(i + 100);
	}
	it = mouse.begin();
	++it; ++it;

	mouse.splice(it, fat_mouse, fat_mouse.begin());

	std::cout << "mouse:" << std::endl;
	std::cout << "size:"  << mouse.size()  << std::endl;
	std::cout << "empty:" << mouse.empty() << std::endl;
	for (it = mouse.begin(); it != mouse.end(); ++it) {
		std::cout << it->some_ << " ";
	}
	std::cout << std::endl;
	std::cout << "fat_mouse:" << std::endl;
	std::cout << "size:"  << fat_mouse.size()  << std::endl;
	std::cout << "empty:" << fat_mouse.empty() << std::endl;
	for (it = fat_mouse.begin(); it != fat_mouse.end(); ++it) {
		std::cout << it->some_ << " ";
	}
	std::cout << std::endl;

	for (int i = 0; i < 20; ++i) {
		fat_mouse.push_back(i + 100);
	}

	mouse.splice(mouse.begin(), fat_mouse, fat_mouse.begin());

	std::cout << "mouse:" << std::endl;
	std::cout << "size:"  << mouse.size()  << std::endl;
	std::cout << "empty:" << mouse.empty() << std::endl;
	for (it = mouse.begin(); it != mouse.end(); ++it) {
		std::cout << it->some_ << " ";
	}
	std::cout << std::endl;
	std::cout << "fat_mouse:" << std::endl;
	std::cout << "size:"  << fat_mouse.size()  << std::endl;
	std::cout << "empty:" << fat_mouse.empty() << std::endl;
	for (it = fat_mouse.begin(); it != fat_mouse.end(); ++it) {
		std::cout << it->some_ << " ";
	}
	std::cout << std::endl;

	for (int i = 0; i < 5; ++i) {
		fat_mouse.push_back(i + 100);
	}

	mouse.splice(mouse.end(), fat_mouse, fat_mouse.begin());

	std::cout << "mouse:" << std::endl;
	std::cout << "size:"  << mouse.size()  << std::endl;
	std::cout << "empty:" << mouse.empty() << std::endl;
	for (it = mouse.begin(); it != mouse.end(); ++it) {
		std::cout << it->some_ << " ";
	}
	std::cout << std::endl;
	std::cout << "fat_mouse:" << std::endl;
	std::cout << "size:"  << fat_mouse.size()  << std::endl;
	std::cout << "empty:" << fat_mouse.empty() << std::endl;
	for (it = fat_mouse.begin(); it != fat_mouse.end(); ++it) {
		std::cout << it->some_ << " ";
	}
	std::cout << std::endl;
}

void ft_splice_pos_lst_first_last_test() {
	ft::list<Test>           mouse;
	ft::list<Test>           fat_mouse;
	ft::list<Test>::iterator it;
	ft::list<Test>::iterator it2;
	for (int i = 0; i < 10; ++i) {
		mouse.push_back(i + 10);
	}
	for (int i = 0; i < 5; ++i) {
		fat_mouse.push_back(i + 100);
	}
	it = mouse.begin();
	++it; ++it;
	it2 = fat_mouse.end();
	--it2; --it2;

	mouse.splice(it, fat_mouse, fat_mouse.begin(), it2);

	std::cout << "mouse:" << std::endl;
	std::cout << "size:"  << mouse.size()  << std::endl;
	std::cout << "empty:" << mouse.empty() << std::endl;
	for (it = mouse.begin(); it != mouse.end(); ++it) {
		std::cout << it->some_ << " ";
	}
	std::cout << std::endl;
	std::cout << "fat_mouse:" << std::endl;
	std::cout << "size:"  << fat_mouse.size()  << std::endl;
	std::cout << "empty:" << fat_mouse.empty() << std::endl;
	for (it = fat_mouse.begin(); it != fat_mouse.end(); ++it) {
		std::cout << it->some_ << " ";
	}
	std::cout << std::endl;

	for (int i = 0; i < 20; ++i) {
		fat_mouse.push_back(i + 100);
	}

	mouse.splice(mouse.begin(), fat_mouse, fat_mouse.begin(), fat_mouse.end());

	std::cout << "mouse:" << std::endl;
	std::cout << "size:"  << mouse.size()  << std::endl;
	std::cout << "empty:" << mouse.empty() << std::endl;
	for (it = mouse.begin(); it != mouse.end(); ++it) {
		std::cout << it->some_ << " ";
	}
	std::cout << std::endl;
	std::cout << "fat_mouse:" << std::endl;
	std::cout << "size:"  << fat_mouse.size()  << std::endl;
	std::cout << "empty:" << fat_mouse.empty() << std::endl;
	for (it = fat_mouse.begin(); it != fat_mouse.end(); ++it) {
		std::cout << it->some_ << " ";
	}
	std::cout << std::endl;

	for (int i = 0; i < 5; ++i) {
		fat_mouse.push_back(i + 100);
	}
	it2 = fat_mouse.end();
	--it2; --it2;

	mouse.splice(mouse.end(), fat_mouse, fat_mouse.begin(), it2);

	std::cout << "mouse:" << std::endl;
	std::cout << "size:"  << mouse.size()  << std::endl;
	std::cout << "empty:" << mouse.empty() << std::endl;
	for (it = mouse.begin(); it != mouse.end(); ++it) {
		std::cout << it->some_ << " ";
	}
	std::cout << std::endl;
	std::cout << "fat_mouse:" << std::endl;
	std::cout << "size:"  << fat_mouse.size()  << std::endl;
	std::cout << "empty:" << fat_mouse.empty() << std::endl;
	for (it = fat_mouse.begin(); it != fat_mouse.end(); ++it) {
		std::cout << it->some_ << " ";
	}
	std::cout << std::endl;
}

void ft_remove_val_test() {
	ft::list<int>           empty;
	ft::list<int>           mouse;
	ft::list<int>           fat_mouse;
	ft::list<int>::iterator it;
	ft::list<int>::iterator it2;
	for (int i = 0; i < 10; ++i) {
		if (i % 2 == 0) {
			mouse.push_back(1000);
		} else {
			mouse.push_back(i + 10);
		}
	}
	for (int i = 0; i < 100; ++i) {
		if (i % 2 == 1) {
			fat_mouse.push_back(1000);
		} else {
			fat_mouse.push_back(i + 10);
		}
	}

	empty.remove(10);

	std::cout << "empty:" << std::endl;
	std::cout << "size:"  << empty.size()  << std::endl;
	std::cout << "empty:" << empty.empty() << std::endl;
	for (it = empty.begin(); it != empty.end(); ++it) {
		std::cout << *it << " ";
	}

	mouse.remove(1000);

	std::cout << "mouse:" << std::endl;
	std::cout << "size:"  << mouse.size()  << std::endl;
	std::cout << "empty:" << mouse.empty() << std::endl;
	for (it = mouse.begin(); it != mouse.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	fat_mouse.remove(1000);

	std::cout << "fat_mouse:" << std::endl;
	std::cout << "size:"  << fat_mouse.size()  << std::endl;
	std::cout << "empty:" << fat_mouse.empty() << std::endl;
	for (it = fat_mouse.begin(); it != fat_mouse.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

bool pred(const int & val) {
	return val == 1000;
}

void ft_remove_if_test() {
	ft::list<int>           empty;
	ft::list<int>           mouse;
	ft::list<int>           fat_mouse;
	ft::list<int>::iterator it;
	ft::list<int>::iterator it2;
	for (int i = 0; i < 10; ++i) {
		if (i % 2 == 0) {
			mouse.push_back(1000);
		} else {
			mouse.push_back(i + 10);
		}
	}
	for (int i = 0; i < 100; ++i) {
		if (i % 2 == 1) {
			fat_mouse.push_back(1000);
		} else {
			fat_mouse.push_back(i + 10);
		}
	}

	empty.remove_if(pred);

	std::cout << "empty:" << std::endl;
	std::cout << "size:"  << empty.size()  << std::endl;
	std::cout << "empty:" << empty.empty() << std::endl;
	for (it = empty.begin(); it != empty.end(); ++it) {
		std::cout << *it << " ";
	}

	mouse.remove_if(pred);

	std::cout << "mouse:" << std::endl;
	std::cout << "size:"  << mouse.size()  << std::endl;
	std::cout << "empty:" << mouse.empty() << std::endl;
	for (it = mouse.begin(); it != mouse.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	fat_mouse.remove_if(pred);

	std::cout << "fat_mouse:" << std::endl;
	std::cout << "size:"  << fat_mouse.size()  << std::endl;
	std::cout << "empty:" << fat_mouse.empty() << std::endl;
	for (it = fat_mouse.begin(); it != fat_mouse.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void ft_unique_test() {
	ft::list<int>           empty;
	ft::list<int>           mouse;
	ft::list<int>           fat_mouse;
	ft::list<int>::iterator it;
	ft::list<int>::iterator it2;
	for (int i = 0; i < 10; ++i) {
		if (i % 2 == 0) {
			mouse.push_back(1000);
			mouse.push_back(1000);
		} else {
			mouse.push_back(i + 10);
		}
	}
	for (int i = 0; i < 100; ++i) {
		if (i % 2 == 1) {
			fat_mouse.push_back(1000);
			fat_mouse.push_back(1000);
		} else {
			fat_mouse.push_back(i + 10);
		}
	}

	empty.unique();

	std::cout << "empty:" << std::endl;
	std::cout << "size:"  << empty.size()  << std::endl;
	std::cout << "empty:" << empty.empty() << std::endl;
	for (it = empty.begin(); it != empty.end(); ++it) {
		std::cout << *it << " ";
	}

	mouse.unique();

	std::cout << "mouse:" << std::endl;
	std::cout << "size:"  << mouse.size()  << std::endl;
	std::cout << "empty:" << mouse.empty() << std::endl;
	for (it = mouse.begin(); it != mouse.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	fat_mouse.unique();

	std::cout << "fat_mouse:" << std::endl;
	std::cout << "size:"  << fat_mouse.size()  << std::endl;
	std::cout << "empty:" << fat_mouse.empty() << std::endl;
	for (it = fat_mouse.begin(); it != fat_mouse.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

}

bool pred2(int & a, int & b) {
	return (a == b);
}

void ft_unique_pred_test() {
	ft::list<int>           empty;
	ft::list<int>           mouse;
	ft::list<int>           fat_mouse;
	ft::list<int>::iterator it;
	ft::list<int>::iterator it2;
	for (int i = 0; i < 10; ++i) {
		if (i % 2 == 0) {
			mouse.push_back(100);
			mouse.push_back(100);
		} else {
			mouse.push_back(i + 10);
		}
	}
	for (int i = 0; i < 100; ++i) {
		if (i % 2 == 1) {
			fat_mouse.push_back(100);
			fat_mouse.push_back(100);
		} else {
			fat_mouse.push_back(i + 10);
		}
	}

	empty.unique(pred2);

	std::cout << "empty:" << std::endl;
	std::cout << "size:"  << empty.size()  << std::endl;
	std::cout << "empty:" << empty.empty() << std::endl;
	for (it = empty.begin(); it != empty.end(); ++it) {
		std::cout << *it << " ";
	}

	mouse.unique(pred2);

	std::cout << "mouse:" << std::endl;
	std::cout << "size:"  << mouse.size()  << std::endl;
	std::cout << "empty:" << mouse.empty() << std::endl;
	for (it = mouse.begin(); it != mouse.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	fat_mouse.unique(pred2);

	std::cout << "fat_mouse:" << std::endl;
	std::cout << "size:"  << fat_mouse.size()  << std::endl;
	std::cout << "empty:" << fat_mouse.empty() << std::endl;
	for (it = fat_mouse.begin(); it != fat_mouse.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

}

void rel_iter_test()
{
	std::cout << "\nrel_iter_test:\n" << std::endl;
	ft::list<int> def;
	for (int i = 0; i < 10; ++i) {
		def.push_back(i);
	}

	ft::list<int>::iterator       it(def.begin());
	ft::list<int>::const_iterator cit(def.begin());

	std::cout << (it != cit) << std::endl;
	std::cout << (it == cit) << std::endl;
}

void iter_test()
{
	std::cout << "\niter_test:\n" << std::endl;
	ft::list<int> def;
	for (int i = 0; i < 10; ++i) {
		def.push_back(i);
	}

	ft::list<int>::iterator cit(def.begin());
	while (cit != def.end())
		std::cout << *(cit++) << std::endl;

	ft::list<int>::reverse_iterator rcit(def.rbegin());
		while (rcit != def.rend())
	std::cout << *(rcit++) << std::endl;
	
}

// =============================================================================

int main() {
	ft_iterator_test();
	ft_constructors_capacity_test();
	ft_element_access_test();

	 // Modifiers

	ft_push_front_test();
	ft_pop_front_test();
	ft_erase_position_test();
	ft_erase_iter_iter_test();
	ft_swap_test();
	ft_resize_test();
	ft_clear_test();
	ft_insert_iter_val_test();
	ft_insert_iter_n_val_test();
	ft_insert_iter_iter_iter_test();
	ft_assign_iter_iter_test();
	ft_assign_n_val_test();

	//  ---------

	//  Operations

	 ft_merge_x_test();
	 ft_merge_x_compare_test();
	 ft_sort_test();
	 ft_sort_comp_test();
	 ft_reverse_test();
	 ft_splice_pos_lst_test();
	 ft_splice_pos_lst_i_test();
	 ft_splice_pos_lst_first_last_test();
	 ft_remove_val_test();
	 ft_remove_if_test();
	 ft_unique_test();
	 ft_unique_pred_test();
	rel_iter_test();
	iter_test();

	return 0;
}
