#! /bin/zsh

  clang++ ft_list_test.cpp -o user_bin_for_leaks &&
  valgrind ./user_bin_for_leaks
