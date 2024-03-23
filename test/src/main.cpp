#include <iostream>

using namespace std;


class Circle{
private:
	int radius;
public:
	Circle();
	Circle(int r);
	void print_radius()	{cout<<radius<<endl;}
};

Circle::Circle(){
	radius = 1;
}
Circle::Circle(int r){
	radius = r;
}


int main(){
	Circle waffle(5);
	waffle.print_radius();

	return 0;
}
