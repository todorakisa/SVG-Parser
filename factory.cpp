#ifndef FACTORY_CPP_
#define FACTORY_CPP_

#include "figures.h"
#include "factory.h"
#include <iostream>
#include <string>
#include <list>

Figure* Factory::make_empty(std::string type){
    Figure* newFigure = nullptr;
    if(type.compare("rect") == 0){
        newFigure = new Rectangle();
    }else if(type.compare("circle") == 0){
        newFigure = new Circle();
    }else if(type.compare("line") == 0){
        newFigure = new Line();
    }
    return newFigure;
}

Figure* Factory::make_with_values(std::string type, std::list<int> values){
	Figure* newFigure = nullptr;
    if(type.compare("rect") == 0){
    	if(values.size() < 4){return newFigure;}
    	int x = values.front();values.pop_front();
    	int y = values.front();values.pop_front();
    	int width = values.front();values.pop_front();
    	int height = values.front();values.pop_front();
        newFigure = new Rectangle(x,y,width,height);
    }else if(type.compare("circle") == 0){
    	if(values.size() < 3){return newFigure;}
    	int x = values.front();values.pop_front();
    	int y = values.front();values.pop_front();
    	int r = values.front();values.pop_front();
        newFigure = new Circle(x,y,r);
    }else if(type.compare("line") == 0){
    	if(values.size() < 4){return newFigure;}
    	int x = values.front();values.pop_front();
    	int y = values.front();values.pop_front();
    	int x2 = values.front();values.pop_front();
    	int y2 = values.front();values.pop_front();
        newFigure = new Line(x,y,x2,y2);
    }
    return newFigure;
}

#endif