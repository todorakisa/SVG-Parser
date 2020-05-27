#ifndef FIGURES_CPP_
#define FIGURES_CPP_

#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "figures.h"
#include "attribute.h"

void Figure::set_x(int x_){
	x = x_;
}

void Figure::set_y(int y_){
	y = y_;
}

Figure::Figure(){}

Figure::Figure(int x_, int y_):x(x_),y(y_){}

void Figure::set_name(std::string name_){
	name = name_;
}

std::string Figure::get_name(){
	return name;
}

int Figure::get_x(){
	return x;
}

int Figure::get_y(){
	return y;
}

void Figure::translate(int v, int h){
	x+=h;
	y+=v;
}

void Figure::add_attribute(std::string atr){
	std::string key;
	std::string value;
	int index = 0;
	while(atr[index] != '='){
		key+= atr[index];
		index++;
	}
	for (int i = index+2; i < atr.size()-1; ++i)
	{
		value+=atr[i];
	}

	attribute* attribute_ = new attribute();
	attribute_->set_key(key);
	attribute_->set_value(value);
	attributes.push_back(attribute_);
}

Figure::~Figure(){
	for(attribute* a : attributes){
		delete a;
	}
	attributes.clear();
}


Circle::Circle():Figure(){
	set_name("circle");
}

Circle::Circle(int cx, int cy, int r_):Figure(cx,cy),r(r_){
	set_name("circle");
}

void Circle::fix(){
	if(attributes.front()->get_key().compare("cx") == 0){
		set_x(stoi(attributes.front()->get_value()));
		delete attributes.front();
		attributes.pop_front();
	}
	if(attributes.front()->get_key().compare("cy") == 0){
		set_y(stoi(attributes.front()->get_value()));
		delete attributes.front();
		attributes.pop_front();
	}
	if(attributes.front()->get_key().compare("r") == 0){
		r = stoi(attributes.front()->get_value());
		delete attributes.front();
		attributes.pop_front();
	}
}

void Circle::write_in_file(std::ofstream& stream){
	stream << "  <" << get_name() << " " << "cx=\""<< get_x() << "\" cy=\"" << get_y() << "\" r=\"" << r << "\" ";
	for (attribute* a : attributes)
	{
		stream << a->get_key() << "=\"" << a->get_value() << "\" ";
	}
	stream << "/>" << std::endl;
}

void Circle::printFigure(){
	std::cout << get_name() << " " << get_x() << " " << get_y() << " " << r << " ";
	for (attribute* a : attributes)
	{
		std::cout << a->get_value() << " ";
	}
}

bool Circle::within(Figure* f){
	int x_ = abs(f->get_x() - get_x());
	int y_ = abs(f->get_y() - get_y());
	return ((double)sqrt((x_*x_) + (y_*y_)) <= r);
}

Circle::~Circle(){}

Rectangle::Rectangle():Figure(){
	set_name("rect");
}

Rectangle::Rectangle(int x, int y, int width_, int height_):Figure(x,y),width(width_),height(height_){
	x2 = x + width;
	y2 = y + height;
	set_name("rect");
}

void Rectangle::fix(){
	if(attributes.front()->get_key().compare("x") == 0){
		set_x(stoi(attributes.front()->get_value()));
		delete attributes.front();
		attributes.pop_front();
	}
	if(attributes.front()->get_key().compare("y") == 0){
		set_y(stoi(attributes.front()->get_value()));
		delete attributes.front();
		attributes.pop_front();
	}
	if(attributes.front()->get_key().compare("width") == 0){
		width = stoi(attributes.front()->get_value());
		delete attributes.front();
		attributes.pop_front();
	}
	if(attributes.front()->get_key().compare("height") == 0){
		height = stoi(attributes.front()->get_value());
		delete attributes.front();
		attributes.pop_front();
	}
	x2 = get_x() + width;
	y2 = get_y() + height;
}

void Rectangle::write_in_file(std::ofstream& stream){
	stream << "  <" << get_name() << " " << "x=\""<< get_x() << "\" y=\"" << get_y() << "\" width=\"" << width << "\" height=\"" << height << "\" ";
	for (attribute* a : attributes)
	{
		stream << a->get_key() << "=\"" << a->get_value() << "\" ";
	}
	stream << "/>" << std::endl;
}

void Rectangle::printFigure(){
	std::cout << get_name() << " " << get_x() << " " << get_y() << " " << width << " " << height << " ";
	for (attribute* a : attributes)
	{
		std::cout << a->get_value() << " ";
	}
}

bool Rectangle::within(Figure* f){
	int x_ = abs(f->get_x() - get_x());
	int y_ = abs(f->get_y() - get_y());
	return (get_x() <= x_ && x_  <= x2 && get_y() <= y_ && y_  <= y2);
}

Rectangle::~Rectangle(){}

Line::Line():Figure(){
	set_name("line");
}

Line::Line(int x, int y, int x2_, int y2_):Figure(x,y),x2(x2_),y2(y2_){
	set_name("line");
}

void Line::fix(){
	if(attributes.front()->get_key().compare("x1") == 0){
		set_x(stoi(attributes.front()->get_value()));
		delete attributes.front();
		attributes.pop_front();
	}
	if(attributes.front()->get_key().compare("y1") == 0){
		set_y(stoi(attributes.front()->get_value()));
		delete attributes.front();
		attributes.pop_front();
	}
	if(attributes.front()->get_key().compare("x2") == 0){
		x2 = stoi(attributes.front()->get_value());
		delete attributes.front();
		attributes.pop_front();
	}
	if(attributes.front()->get_key().compare("y2") == 0){
		y2 = stoi(attributes.front()->get_value());
		delete attributes.front();
		attributes.pop_front();
	}
}

void Line::write_in_file(std::ofstream& stream){
	stream << "  <" << get_name() << " " << "x1=\""<< get_x() << "\" y1=\"" << get_y() << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" ";
	for (attribute* a : attributes)
	{
		stream << a->get_key() << "=\"" << a->get_value() << "\" ";
	}
	stream << "/>" << std::endl;
}

void Line::printFigure(){
	std::cout << get_name() << " " << get_x() << " " << get_y() << " " << x2 << " " << y2 << " ";
	for (attribute* a : attributes)
	{
		std::cout << a->get_value() << " ";
	}
}

bool Line::within(Figure* f){
	return false;
}

Line::~Line(){}

#endif