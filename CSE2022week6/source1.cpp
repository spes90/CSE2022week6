#include <iostream>
#include <string>

//generic function

template <class T_OBJECT>

void print(const T_OBJECT& i) {
	std::cout << i << std::endl;
}

int main() {
	print(1);
	print(2.345f);
	print("Hello World");

	return 0;
}