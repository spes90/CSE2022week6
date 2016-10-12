#include <iostream>

class MyObject
{
public:
	void draw() {
		std::cout << "MyObject::draw()" << std::endl;
	}
	friend std::ostream& operator<<(std::ostream& os, const MyObject& vec) {
		//os << vec.x_ << " " << vec.y_;
		return os;
	}
};

template<class T_OBJECT>
void draw(T_OBJECT& obj) {
	obj.draw();
}

template<class T>
class Vector {
public:
	T x_, y_;

	friend std::ostream& operator<<(std::ostream& os, const Vector& vec) {
		os << vec.x_ << " " << vec.y_;
		return os;
	}
	friend Vector operator + (Vector lhs, const Vector& rhs) {
		lhs.x_ += rhs.x_;
		lhs.y_ += rhs.y_;
	}
};

template <class T_CLASS>
void print(const T_CLASS& input) {
	std::cout << input << std::endl;
}

int main() {
	Vector<MyObject> my_vector;
	print(my_vector);

	/*Vector<int> my_vector, my_vector2, my_vector3;
	my_vector.x_ = 1.0f;
	my_vector.y_ = 2.0f;

	my_vector2.x_ = 3.0f;
	my_vector2.y_ = 13.0f;

	my_vector3 = my_vector + my_vector2;

	print(my_vector3);
*/
	return 0;
}