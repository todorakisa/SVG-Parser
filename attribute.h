#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

#include <iostream>
#include <string>

class attribute{
	std::string key;
	std::string value;
public:
	attribute();
	attribute& operator=(attribute& other);
	void set_key(std::string key_);
	void set_value(std::string value_);
	std::string get_key();
	std::string get_value();
	~attribute();
};


#endif