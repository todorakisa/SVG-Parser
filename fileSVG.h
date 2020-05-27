#ifndef FILESVG_H_
#define FILESVG_H_

#include <iostream>
#include <string>
#include <vector>
#include "figures.h"

class FileSVG{
	bool filled;
	std::string name;
	std::vector<Figure*> figures;

	void _clearContent();

public:
	FileSVG();
	void set_name(std::string name_);
	std::string get_name();
	bool is_filled();
	std::string& trim(std::string& word);
	bool fill_content();
	void print();
	void create(std::string name, std::list<int> values,std::string fill);
	void erase(int index);
	void translate(int index, std::list<std::string> params);
	void within(std::string name, std::list<int> values);
	void save_as(std::string name_);
	void empty_content();
	~FileSVG();
};

#endif