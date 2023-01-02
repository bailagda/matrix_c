CC=gcc
CFLAGS= -Wall -Wextra -Werror -pedantic -std=c11 -g
FLAGS_TEST_LIBS = -lcheck -lm -lpthread
#
SRC=s21_matrix.c

HEADER=s21_matrix.h
NAME=s21_matrix.a
OBJ=$(patsubst %.c, %.o, $(SRC))
OS = $(shell uname)

.PHONY: all build s21_matrix test gcov_report clean m

all: build

build: $(NAME)

s21_matrix: build

$(NAME) : $(OBJ) $(HEADER)
	ar rcs $(NAME) $?
%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

test: build unit_test.c
	$(CC) $(CFLAGS) -c unit_test.c -o unit_test.o
	$(CC) unit_test.o $(NAME) $(FLAGS_TEST_LIBS) -o unit_test
	./unit_test

gcov_report: clean build
	$(CC) $(CFLAGS) --coverage unit_test.c $(SRC) $(NAME) $(FLAGS_TEST_LIBS) -o gcov_test
	chmod +x *
	./gcov_test
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info
	open ./report/index.html

check: test
	@cp ../materials/linters/CPPLINT.cfg .
	@python3 ../materials/linters/cpplint.py --extensions=c *.c *.h
	@rm -rf CPPLINT.cfg
	@cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config *.c *.h
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./unit_test
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./unit_test
endif

clean:
	rm -rf *.gch *.out *.o *.a m *.gcda *.gcdo *.gcno *.dSYM s21_test_matrix gcov_test unit_test gcov_test.info ./report

m: build
	@ $(CC) m.c $(NAME) -g
	@./a.out
