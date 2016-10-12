#include <iostream>
#include <string>
#include <vector>

class DrawInYellow {
public:
	void draw() {
		std::cout << "Draw in Yellow" << std::endl;
	}
};

class DrawInRed {
public:
	void draw() {
		std::cout << "Draw in Red" << std::endl;
	}
};

class GeometricObjectInterface {
public:
	virtual void draw() = 0;
};

template <class T_HOW_TO_DRAW>
class GeometricObjectInColor : public GeometricObjectInterface {
public:
	void draw() {
		T_HOW_TO_DRAW draw_in_color;
		draw_in_color.draw();
	}
};

int main() {
	std::vector<GeometricObjectInterface*> obj_list;

	obj_list.push_back(new GeometricObjectInColor<DrawInYellow>);
	obj_list.push_back(new GeometricObjectInColor<DrawInRed>);

	for (auto itr : obj_list)
		itr->draw();

	//GeometricObjectInColor<DrawInYellow> go_yellow; //class를 template받았다.
	//GeometricObjectInColor<DrawInRed> go_red;
	//go_yellow.draw();
	//go_red.draw();

	return 0;
}