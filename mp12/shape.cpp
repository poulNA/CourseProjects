#include "shape.hpp"
#define PI 3.14159265359


//Base class
//Please implement Shape's member functions
//constructor, getName()
//
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable 
Shape::Shape(string name){
	name_ = name;
}

string Shape::getName(){
	return name_;
}


//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Rectangle::Rectangle(double a, double b):Shape("Rectangle"){
	width_ = a;
	length_ = b;
}

double Rectangle::getArea()const{
	return width_ * length_;
}

double Rectangle::getVolume()const{
	return 0;
}

Rectangle Rectangle::operator+(const Rectangle& R1) {
	double w = getWidth() + R1.getWidth();
	double l = getLength() + R1.getLength();
	
	Rectangle R3(w, l);
	return R3;
}
Rectangle Rectangle::operator-(const Rectangle& R1) {
	double w = std::max(0.0, getWidth() - R1.getWidth());
	double l = std::max(0.0, getLength() - R1.getLength());
	
	Rectangle R3(w, l);
	return R3;
}

double Rectangle::getWidth()const{return width_;}
double Rectangle::getLength()const{return length_;}




//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Circle::Circle(double r):Shape("Circle"){
	radius_ = r;
}

double Circle::getArea()const{
	return radius_*radius_ * PI; 
}

double Circle::getVolume()const{
	return 0;
}

Circle Circle::operator+(const Circle& C1) {
	double c = C1.getRadius() + getRadius();
	
	Circle C3(c);
	return C3;
}

Circle Circle::operator-(const Circle& C1) {
	double c = std::max(0.0, getRadius() - C1.getRadius());
	
	Circle C3(c);
	return C3;
}

double Circle::getRadius()const{return radius_;}

//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Sphere::Sphere(double s):Shape("Sphere"){
	radius_ = s;
}

double Sphere::getVolume()const{return (4.0/3.0)*getRadius()*getRadius()*getRadius()*PI;}

double Sphere::getArea()const{
	return radius_*radius_ * 4 * PI;
}

Sphere Sphere::operator+(const Sphere& S1) {
	double s = S1.getRadius() + getRadius();
	
	Sphere S3(s);
	return S3;
}

Sphere Sphere::operator-(const Sphere& S1) {
	double s = std::max(0.0, getRadius() - S1.getRadius());
	
	Sphere S3(s);
	return S3;
}

double Sphere::getRadius()const{return radius_;}

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
RectPrism::RectPrism(double width, double length, double height):Shape("RectPrism") {
	width_ = width;
	length_ = length;
	height_ = height;
}

double RectPrism::getVolume()const{return getWidth()*getHeight()*getLength();}
double RectPrism::getArea()const{return 2*(getLength()*getWidth()+getLength()*getHeight()+getWidth()* getHeight());}

RectPrism RectPrism::operator+(const RectPrism& R1) {
	double w = getWidth() + R1.getWidth();
	double l = getLength() + R1.getLength();
	double h = getHeight() + R1.getHeight();
	RectPrism R3(w, l, h);
	return R3;
}
RectPrism RectPrism::operator-(const RectPrism& R1) {
	double w = std::max(0.0, getWidth() - R1.getWidth());
	double l = std::max(0.0, getLength() - R1.getLength());
	double h = std::max(0.0, getHeight() - R1.getHeight());
	RectPrism R3(w, l, h);
	return R3;
}

double RectPrism::getWidth()const{return width_;}
double RectPrism::getHeight()const{return height_;}
double RectPrism::getLength()const{return length_;}


 
// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
vector<Shape*> CreateShapes(char* file_name){
	//@@Insert your code here
	ifstream file (file_name, std::ifstream::in);
	
	int size;
	string shape;
	double x, y, z;
	file >> size;

	vector<Shape *> vect;

	for (int i = 0; i < size; i++) {
		file >> shape;
		Shape *newShape;

		if (shape == "Rectangle") {
			file >> x >> y;
			newShape = new Rectangle(x, y);
		}
		if (shape == "Circle") {
			file >> x;
			newShape = new Circle(x);
		}
		if (shape == "Sphere") {
			file >> x;
			newShape = new Sphere(x);
		}
		if (shape == "RectPrism") {
			file >> x >> y >> z;
			newShape = new RectPrism(x, y, z);
		}

		vect.push_back(newShape);
		
	}
	return vect; // please remeber to modify this line to return the correct value
}

// call getArea() of each object 
// return the max area
double MaxArea(vector<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
	int size = shapes.size();
	for (int i = 0; i < size; i++) {
		if (shapes[i]->getArea() > max_area) {
			max_area = shapes[i]->getArea();
		}
	}
	return max_area;
}


// call getVolume() of each object 
// return the max volume
double MaxVolume(vector<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
	int size = shapes.size();
	for (int i = 0; i < size; i++) {
		if (shapes[i]->getVolume() > max_volume) {
			max_volume = shapes[i]->getVolume();
		}
	}
	
	return max_volume;
}