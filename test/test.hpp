#ifndef TEST_HPP
# define TEST_HPP
#include <cstdlib>
#include <iostream>

class Test {
public:
	Test() : some_(0) {
		this->str_ = (char*)malloc(20);
	}

	Test(int s) : some_(s) {
		this->str_ = (char*)malloc(20);
	}

	Test(Test const & x) : some_(x.some_) {
		this->str_ = (char*)malloc(20);
	}

	~Test() {
		if (this->str_ != 0)
			free(this->str_);
		this->some_ = 0;
		this->str_  = 0;
	}

	Test &operator=(Test const & x) {
		if (this == &x)
			return (*this);
		this->str_ = (char*)malloc(20);
		this->some_ = x.some_;
		return (*this);
	}

	int   some_;
	std::string o;
	char* str_;

};

#endif
