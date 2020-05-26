#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class attribute{
	string key;
	string value;
public:

	attribute& operator=(attribute& other){
		if(this!=&other){
			key = other.key;
			value = other.value;
		}
		return *this;
	}

	void set_key(string key_){
		key = key_;
	}

	void set_value(string value_){
		value = value_;
	}

	string get_key(){
		return key;
	}

	string get_value(){
		return value;
	}
};

class Figure{
	int x;
	int y;
	attribute* attributes;
public:
	Figure(){}
	~Figure(){}
};

class Circle{};
class Rectangle{};
class Line{};

class FileSVG{
	bool filled;
	string name;
	int size_figures;
	Figure* figures;

	void _clearContent(){
		delete[] figures;
		size_figures = 0;
		figures = nullptr;
		name.clear();
	};

public:
	FileSVG():figures(nullptr){}
	void set_name(string name_){
		name = name_;
	}	
	string get_name(){
		return name;
	}
	bool is_filled();
	bool fill_content(){
		return true;
	}
	void print(){

	}
	void save_as(std::string name_){
		if(name.compare(name_) == 0){
			char name__[name.size()+1];
			name.copy(name__,name.size()+1);
			name__[name.size()+1] = '\0';
			remove(name__);
		}
		ofstream new_file(name_);
		new_file << "<?xml version=\"1.0\" standalone=\"no\"?>" << endl;
		new_file << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">" << endl;
		new_file << "<svg>" << endl;
		new_file << "</svg>" << endl;
		//write_in_file(new_file,tree,0);
		new_file.close();
	}
	//void write_in_file(std::ofstream& stream, elementXML* elem, int spaces);
	void empty_content(){
		_clearContent();
	}

	~FileSVG(){
		_clearContent();
	}
};

int main(){

	string command;
	bool active = true;
	FileSVG file;

	while(active){

		cout << ">";
		getline(cin,command);

		if(command.compare(0,5,"open ") == 0){
			//if(file.is_filled()){
				//cout << "You must close the opened file first" << endl;
			//}else{
				string file_name = command.substr(5);
				cout << file_name << endl;
				file.set_name(file_name);
				if(file.fill_content()){
					cout << "Successfully opened " << file.get_name() << endl;
				}
			//}	
		}

		if(command.compare(0,7,"saveas ") == 0){
			//if(file.is_filled()){
				string file_name = command.substr(7);
				file.save_as(file_name);
				cout << "Successfully saved as " << file_name << endl;	
			//}else{
				//cout << "You must open a file first" << endl;
			//}
		}

		if(command.compare("help") == 0){
			cout << "-------------------------------------------------------" << endl;
			cout << "The following commands are supported:" << endl;
			cout << "-------------------------------------------------------" << endl;
			cout << "open <file>     opens <file>, if there is not such file it creates one!" << endl;
			cout << "close           closes currently opened file" << endl;
			cout << "save            saves the currently open file" << endl;
			cout << "saveas <file>   saves the currently open file in <file>" << endl;
			cout << "help            prints this information" << endl;
			cout << "exit            exits the program" << endl;
			cout << "-------------------------------------------------------" << endl;
			cout << "SVG Functionalyties:" << endl;
			cout << "-------------------------------------------------------" << endl;
			cout << "print                    prints all figures from the file" << endl;
			cout << "create                   creates a figure, arguments depend on figure" << endl;
			cout << "erase <n>                deletes figure with number n" << endl;
			cout << "translate [<n>]          translates a figure with number n or all figures if n is not given" << endl;
			cout << "within <option>          prints all figures in a region" << endl;
			cout << "-------------------------------------------------------" << endl;
		}

		if(command.compare("exit") == 0){
			file.empty_content();
			cout << "Exiting the program..." << endl;
			active = false;
		}	
	}
}