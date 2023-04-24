

all := $(shell find ./ -iname "*.c" )
test_f := $(shell find ./tests/ -iname "*.c" )

all: ${all} 
	gcc -g -Wall -Werror -Wextra $^ -o main.a -lm

test: ${all}
	gcc -g -Wall -Werror -Wextra -fprofile-arcs -ftest-coverage --coverage $^ -o $@.a -lcheck -lgcov -lpthread -lm -lsubunit
	./$@.a
	
gcov_report: test
	gcov ${all} || true
	# rm -rf test*.gcda test*.gcno main.gcda main.gcno
	find ./ -type f -iname '*.gcda'
	lcov --directory ./ --capture --output-file postgresql.info
	mkdir cov-report || true
	genhtml -o ./cov-report/ postgresql.info

cppcheck: $(all) 
	cppcheck $^;

format: $(all)
	cp ../materials/linters/.clang-format .
	clang-format -i -style=google $^;
	rm .clang-format

clean: 
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./test && rm -rf ./cov-report
	-rm -rf ./report/ && rm -rf test.dSYM
	-rm -rf lib* && rm -rf test
	-rm -rf test_*
