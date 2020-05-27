#ifndef FILESVG_CPP_
#define FILESVG_CPP_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "figures.h"
#include "fileSVG.h"
#include "factory.h"

void FileSVG::_clearContent(){
	for (Figure* f : figures)
	{
		delete f;
	}
	figures.clear();
	filled = false;
};

FileSVG::FileSVG():filled(false){}

void FileSVG::set_name(std::string name_){
	name = name_;
}	

std::string FileSVG::get_name(){
	return name;
}

bool FileSVG::is_filled(){
	return filled;
};

std::string& FileSVG::trim(std::string& word){
	word.erase(0, word.find_first_not_of(" "));
	word.erase(word.find_last_not_of(" ") + 1);
	return word;
}

bool FileSVG::fill_content(){
	if(this->name.size() == 0){
		return filled;
	}
	std::ifstream original_file(this->name);
	if(!original_file){
		std::ofstream new_file(this->name);
		new_file.close();
		filled = false;
	}else if(original_file.is_open()){	

		std::string line;
		bool svg_mode = false;

		while(getline(original_file,line)){
			trim(line);
			if(line.compare("</svg>") == 0){
				svg_mode = false;
			}
			if(svg_mode){
				Figure* figure = nullptr;
				std::istringstream fig(line);
				std::string word;
				bool first = true;
				while(fig >> word){
					if(first){
						first = false;
						word.erase(word.begin());
						figure = Factory::make_empty(word);
					}else if(word.compare("/>") != 0){
						figure->add_attribute(word);
					}
				}
				figure->fix();
				figures.push_back(figure);
			}
			if(line.compare("<svg>") == 0){
				svg_mode = true;
			}
		}

		filled = true;
	}else{
		std::cout << "The file cannot be opened" << std::endl;
		original_file.close();
		filled = false;
	}
	original_file.close();
	return filled;
}

void FileSVG::print(){
	int i = 1;
	for(Figure* f : figures){
		std::cout << i << ". "; i++;
		f->printFigure();
		std::cout << std::endl;
	}
}

void FileSVG::create(std::string name, std::list<int> values,std::string fill){
	Figure* figure = Factory::make_with_values(name, values);
	if(figure == nullptr){
		std::cout << "Invalid command!" << std::endl;
		return;
	}
	if(fill.size() > 0){
		figure->add_attribute("fill=\"" + fill + "\"");
	}
	figures.push_back(figure);
	std::cout << "Successfully created "<< figure->get_name() << " (" << figures.size() << ")" << std::endl;
}

void FileSVG::erase(int index){
	if(index > figures.size()){
		std::cout << "There is no figure number " << index << "!" << std::endl;
		return;
	}
	std::cout << "Erased a "<< (*(figures.begin()+index-1))->get_name() <<" (" << index << ")" << std::endl;
	delete (*(figures.begin()+index-1));
	figures.erase(figures.begin()+index-1);
}

void FileSVG::translate(int index, std::list<std::string> params){
	int vertical;
	int horizontal;
	for(std::string s : params){
		if(s.substr(0,8).compare("vertical") == 0){
			vertical = stoi(s.substr(9));
		}else if(s.substr(0,10).compare("horizontal") == 0){
			horizontal = stoi(s.substr(11));
		}
	}
	if(index == -1){
		for (Figure* f : figures)
		{
			f->translate(vertical,horizontal);
		}
		std::cout << "Translated all figures!" << std::endl;
		return;
	}
	(*(figures.begin()+index-1))->translate(vertical,horizontal);
	std::cout << "Translated " << (*(figures.begin()+index-1))->get_name() << " (" << index << ")!" << std::endl;
}

void FileSVG::within(std::string name, std::list<int> values){
	Figure* figure = Factory::make_with_values(name, values);
	int i = 1;
	int has_figure = false;
	for(Figure* f : figures){
		if(figure->within(f)){
			has_figure = true;
			std::cout << i << ". "; i++;
			f->printFigure();
			std::cout << std::endl;
		}
	}
	if(!has_figure){
		std::cout << "No figures are located within ";
		figure->printFigure();
		std::cout << std::endl;
	}
}

void FileSVG::save_as(std::string name_){
	if(name.compare(name_) == 0){
		char name__[name.size()+1];
		name.copy(name__,name.size()+1);
		name__[name.size()+1] = '\0';
		remove(name__);
	}
	std::ofstream new_file(name_);
	new_file << "<?xml version=\"1.0\" standalone=\"no\"?>" << std::endl;
	new_file << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">" << std::endl;
	new_file << "<svg>" << std::endl;
	for (Figure* f : figures)
	{
		f->write_in_file(new_file);
	}
	new_file << "</svg>" << std::endl;
	new_file.close();
}

void FileSVG::empty_content(){
	_clearContent();
}

FileSVG::~FileSVG(){
	_clearContent();
}

#endif