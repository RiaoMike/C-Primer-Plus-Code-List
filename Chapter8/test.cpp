#include<iostream>
#include<string>
using namespace std;
class Rui{
	private:
		string name;
		double tall;
		double height;
		double money;
	public:
		Rui(double a, double b, double c);
		void play();
		void show();

};
Rui::Rui(double a, double b, double c) {
	tall = a;
	height = b;
	money = c;
}

void Rui::play() {
	cout << "rui is now play wangzhe" << endl;
}

void Rui::show() {
	cout << "tall: " << tall << endl;
	cout << "height: " << height << endl;
	cout << "rui is now have " << money << " money" << endl;
}

int main() {
	Rui rui(32, 12.3, 10000);
	rui.play();
	rui.show();
	return 0;
}
