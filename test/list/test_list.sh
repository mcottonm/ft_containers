#! /bin/zsh

rm -rf logs
mkdir logs

  clang++ -Wall -Wextra -Werror -fsanitize=address -std=c++98 ft_list_test.cpp -o logs/user_bin &&
  ./logs/user_bin > logs/user.output &&
  clang++ -Wall -Wextra -Werror -fsanitize=address -std=c++98 std_list_test.cpp -o logs/bin &&
  ./logs/bin > logs/std.output &&
  diff logs/user.output logs/std.output
