

all := $(shell find ./ -iname "*.c" )
TEST_FILES := array_stack_help.c calculate.c string_edit.c tests/main.c tests/test.c validate.c
	
all: install 
	../build/Smartcalc

install:
	mkdir -p ../build
	cmake -S . -B ../build || true
	cmake open ../build/ || true
	cmake --build ../build --target all || true

uninstall:
	rm -rf ../build

test: ${TEST_FILES}
	gcc -g -fprofile-arcs -ftest-coverage --coverage $^ -o $@.a -lcheck -lgcov -lpthread -lm 
	./$@.a 
	
dvi:
	open readme.html

dist:
	git archive --format=tar.gz -o C7_SmartCalc_v1.0-1.tar.gz --prefix=my-repo/ develop

gcov_report: test
	gcov ${all} || true
	find ./ -type f -iname '*.gcda'
	lcov --directory ./ --capture --output-file postgresql.info || true
	mkdir cov-report || true
	genhtml -o ./cov-report/ postgresql.info

cppcheck: $(all) 
	cppcheck  $^;

format: $(all)
	cp ../materials/linters/.clang-format .
	clang-format -i -style=google $^;
	rm .clang-format

clean: 
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./test && rm -rf ./cov-report
	-rm -rf ./report/ && rm -rf test.a.* && rm -rf main.a*
	-rm -rf lib* && rm -rf test
	-rm -rf test_*
	-rm -rf *tar.gz
