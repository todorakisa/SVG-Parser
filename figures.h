#ifndef FIGURES_H_
#define FIGURES_H_

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include "attribute.h"

class Figure{
	int x;
	int y;
	std::string name;
protected:
	std::list<attribute*> attributes;

	void set_x(int x_);
	void set_y(int y_);
public:
	Figure();
	Figure(int x_, int y_);
	void set_name(std::string name_);
	std::string get_name();
	int get_x();
	int get_y();
	void translate(int v, int h);
	void add_attribute(std::string atr);
	virtual void fix() = 0;
	virtual void printFigure() = 0;
	virtual void write_in_file(std::ofstream& stream) = 0;
	virtual bool within(Figure* f) = 0;
	virtual ~Figure();
};

class Circle : public Figure{
	int r;
public: 
	Circle();
	Circle(int cx, int cy, int r_);
	void fix();
	void write_in_file(std::ofstream& stream);
	void printFigure();
	bool within(Figure* f);
	~Circle();
};

class Rectangle : public Figure{
	int width;
	int height;
	int x2;
	int y2;
public:
	Rectangle();	
	Rectangle(int x, int y, int width_, int height_);
	void fix();
	void write_in_file(std::ofstream& stream);
	void printFigure();
	bool within(Figure* f);
	~Rectangle();
};

class Line : public Figure{
	int x2;
	int y2;
public:
	Line();
	Line(int x, int y, int x2_, int y2_);
	void fix();
	void write_in_file(std::ofstream& stream);
	void printFigure();
	bool within(Figure* f);
	~Line();
};

#endif