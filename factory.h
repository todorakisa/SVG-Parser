#ifndef FACTORY_H_
#define FACTORY_H_

#include "figures.h"
#include <iostream>
#include <string>
#include <list>

class Factory{
public: 
	static Figure* make_empty(std::string type);
	static Figure* make_with_values(std::string type, std::list<int> values);
};

#endif