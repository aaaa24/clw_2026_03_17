CXXFLAGS := -Wall -Wextra -std=c++14 -g -O0 -MMD

main: main.o
	$(CXX) $^ -o $@

-include main.d

valgrind: main
	valgrind --leak-check=full --show-leak-kinds=all ./main

clean:
	@$(RM) main.d main.o main
