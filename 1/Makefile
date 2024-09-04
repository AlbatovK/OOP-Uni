test:
	g++ test.cpp Car.cpp CarSerializer.cpp TestValidator.cpp CarTomlValidator.cpp ValidationException.cpp IOException.cpp -o test -lgtest -lgmock
	valgrind ./test

build:
	g++ main.cpp Car.cpp CarSerializer.cpp TestValidator.cpp CarTomlValidator.cpp ValidationException.cpp IOException.cpp -o main -lgtest -lgmock
	valgrind ./main
