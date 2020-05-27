#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <cmath>

using namespace std;

string& trim(string& word){
	word.erase(0, word.find_first_not_of(" "));
	word.erase(word.find_last_not_of(" ") + 1);
	return word;
}

class attribute{
	string key;
	string value;
public:
	attribute(){}

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

	~attribute(){}
};

class Figure{
	int x;
	int y;
	string name;
protected:
	list<attribute*> attributes;

	void set_x(int x_){
		x = x_;
	}

	void set_y(int y_){
		y = y_;
	}

public:
	Figure(){}

	Figure(int x_, int y_){
		x = x_;
		y = y_;
	}

	void set_name(string name_){
		name = name_;
	}

	string get_name(){
		return name;
	}

	int get_x(){
		return x;
	}

	int get_y(){
		return y;
	}

	void translate(int v, int h){
		x+=h;
		y+=v;
	}

	void add_attribute(string atr){
		string key;
		string value;
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

	virtual void fix() = 0;
	virtual void printFigure() = 0;
	virtual void write_in_file(ofstream& stream) = 0;
	virtual bool within(Figure* f) = 0;

	virtual ~Figure(){
		for(attribute* a : attributes){
			delete a;
		}
		attributes.clear();
	}
};

class Circle : public Figure{
	int r;
public: 
	Circle():Figure(){
		set_name("circle");
	}

	Circle(int cx, int cy, int r_):Figure(cx,cy),r(r_){
		set_name("circle");
	}

	void fix(){
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

	void write_in_file(ofstream& stream){
		stream << "  <" << get_name() << " " << "cx=\""<< get_x() << "\" cy=\"" << get_y() << "\" r=\"" << r << "\" ";
		for (attribute* a : attributes)
		{
			stream << a->get_key() << "=\"" << a->get_value() << "\" ";
		}
		stream << "/>" << endl;
	}

	void printFigure(){
		cout << get_name() << " " << get_x() << " " << get_y() << " " << r << " ";
		for (attribute* a : attributes)
		{
			cout << a->get_value() << " ";
		}
	}

	bool within(Figure* f){
		int x_ = abs(f->get_x() - get_x());
		int y_ = abs(f->get_y() - get_y());
		if((double)sqrt((x_*x_) + (y_*y_)) > r){
			return false;
		}else{
			return true;
		}
	}

	~Circle(){}
};
class Rectangle : public Figure{
	int width;
	int height;
	int x2;
	int y2;
public:
	Rectangle():Figure(){
		set_name("rect");
	}

	Rectangle(int x, int y, int width_, int height_):Figure(x,y),width(width_),height(height_){
		x2 = x + width;
		y2 = y + height;
		set_name("rect");
	}

	void fix(){
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

	void write_in_file(ofstream& stream){
		stream << "  <" << get_name() << " " << "x=\""<< get_x() << "\" y=\"" << get_y() << "\" width=\"" << width << "\" height=\"" << height << "\" ";
		for (attribute* a : attributes)
		{
			stream << a->get_key() << "=\"" << a->get_value() << "\" ";
		}
		stream << "/>" << endl;
	}

	void printFigure(){
		cout << get_name() << " " << get_x() << " " << get_y() << " " << width << " " << height << " ";
		for (attribute* a : attributes)
		{
			cout << a->get_value() << " ";
		}
	}

	bool within(Figure* f){
		int x_ = abs(f->get_x() - get_x());
		int y_ = abs(f->get_y() - get_y());
		if(get_x() <= x_ && x_  <= x2 && get_y() <= y_ && y_  <= y2){
			return true;
		}else{
			return false;
		}
	}

	~Rectangle(){}
};
class Line : public Figure{
	int x2;
	int y2;
public:
	Line():Figure(){
		set_name("line");
	}

	Line(int x, int y, int x2_, int y2_):Figure(x,y),x2(x2_),y2(y2_){
		set_name("line");
	}

	void fix(){
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

	void write_in_file(ofstream& stream){
		stream << "  <" << get_name() << " " << "x1=\""<< get_x() << "\" y1=\"" << get_y() << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" ";
		for (attribute* a : attributes)
		{
			stream << a->get_key() << "=\"" << a->get_value() << "\" ";
		}
		stream << "/>" << endl;
	}

	void printFigure(){
		cout << get_name() << " " << get_x() << " " << get_y() << " " << x2 << " " << y2 << " ";
		for (attribute* a : attributes)
		{
			cout << a->get_value() << " ";
		}
	}

	bool within(Figure* f){
		return false;
	}

	~Line(){}
};

class Factory{
public: 
	static Figure* make_empty(string type){
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

	static Figure* make_with_values(string type, list<int> values){
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
};

class FileSVG{
	bool filled;
	string name;
	vector<Figure*> figures;

	void _clearContent(){
		for (Figure* f : figures)
		{
			delete f;
		}
		figures.clear();
		filled = false;
	};

public:
	FileSVG():filled(false){}

	void set_name(string name_){
		name = name_;
	}	

	string get_name(){
		return name;
	}

	bool is_filled(){
		return filled;
	};

	bool fill_content(){
		if(this->name.size() == 0){
			return filled;
		}
		ifstream original_file(this->name);
		if(!original_file){
			ofstream new_file(this->name);
			new_file.close();
			filled = false;
		}else if(original_file.is_open()){	

			string line;
			bool svg_mode = false;

			while(getline(original_file,line)){
				trim(line);
				if(line.compare("</svg>") == 0){
					svg_mode = false;
				}
				if(svg_mode){
					Figure* figure = nullptr;
					istringstream fig(line);
					string word;
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
			cout << "The file cannot be opened" << endl;
			original_file.close();
			filled = false;
		}
		original_file.close();
		return filled;
	}

	void print(){
		int i = 1;
		for(Figure* f : figures){
			cout << i << ". "; i++;
			f->printFigure();
			cout << endl;
		}
	}

	void create(string name, list<int> values,string fill){
		Figure* figure = Factory::make_with_values(name, values);
		if(figure == nullptr){
			cout << "Invalid command!" << endl;
		}else{
			if(fill.size() > 0){
				figure->add_attribute("fill=\"" + fill + "\"");
			}
			figures.push_back(figure);
			cout << "Successfully created "<< figure->get_name() << " (" << figures.size() << ")" << endl;
		}
	}

	void erase(int index){
		if(index > figures.size()){
			cout << "There is no figure number " << index << "!" <<endl;
		}else{
			cout << "Erased a "<< (*(figures.begin()+index-1))->get_name() <<" (" << index << ")" << endl;
			figures.erase(figures.begin()+index-1);
		}
	}

	void translate(int index, list<string> params){
		int vertical;
		int horizontal;
		for(string s : params){
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
			cout << "Translated all figures!" << endl;
		}else{
			(*(figures.begin()+index-1))->translate(vertical,horizontal);
			cout << "Translated " << (*(figures.begin()+index-1))->get_name() << " (" << index << ")!" << endl;
		}
	}

	void within(string name, list<int> values){
		Figure* figure = Factory::make_with_values(name, values);
		int i = 1;
		int has_figure = false;
		for(Figure* f : figures){
			if(figure->within(f)){
				has_figure = true;
				cout << i << ". "; i++;
				f->printFigure();
				cout << endl;
			}
		}
		if(!has_figure){
			cout << "No figures are located within ";
			figure->printFigure();
			cout << endl;
		}
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
		for (Figure* f : figures)
		{
			f->write_in_file(new_file);
		}
		new_file << "</svg>" << endl;
		new_file.close();
	}

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
			if(file.is_filled()){
				cout << "You must close the opened file first" << endl;
			}else{
				string file_name = command.substr(5);
				file.set_name(file_name);
				if(file.fill_content()){
					cout << "Successfully opened " << file.get_name() << endl;
				}
			}	
		}

		if(command.compare("close") == 0){
			if(file.is_filled()){
				file.empty_content();
				cout << "Successfully closed " << file.get_name() << endl;
			}else{
				cout << "You must open a file first" << endl;
			}
		}

		if(command.compare("save") == 0){
			if(file.is_filled()){
				file.save_as(file.get_name());
				cout << "Successfully saved " << file.get_name() << endl;
			}else{
				cout << "You must open a file first" << endl;
			}	
		}

		if(command.compare(0,7,"saveas ") == 0){
			if(file.is_filled()){
				string file_name = command.substr(7);
				file.save_as(file_name);
				cout << "Successfully saved as " << file_name << endl;	
			}else{
				cout << "You must open a file first" << endl;
			}
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

		if(command.compare("print") == 0){
			if(file.is_filled()){
				file.print();
			}else{
				cout << "You must open a file first" << endl;
			}
		}

		if(command.compare(0,7,"create ") == 0){
			if(file.is_filled()){
				string part_of_command = command.substr(7);
				string word;
				string name;
				string fill;
				istringstream figure(part_of_command);
				list<int> values;
				bool first = true;
				while(figure >> word){
					if(first){
						first = false;
						name = word;
					}else if(word.find_first_not_of( "0123456789" ) == std::string::npos || word[0] == '-'){
						values.push_back(abs(stoi(word)));
					}else{
						fill = word;
					}
				}
				file.create(name,values,fill);
			}else{
				cout << "You must open a file first" << endl;
			}
		}

		if(command.compare(0,6,"erase ") == 0){
			if(file.is_filled()){
				int index = stoi(command.substr(6));
				file.erase(index);
			}else{
				cout << "You must open a file first" << endl;
			}
		}

		if(command.compare(0,10,"translate ") == 0){
			if(file.is_filled()){
				istringstream part_of_command(command.substr(10));
				string word;
				list<string> params;
				int index = -1;
				while(part_of_command >> word){
					if(word.find_first_not_of( "0123456789" ) == std::string::npos){
						index = abs(stoi(word));
					}else{
						params.push_back(word);
					}
				}
				file.translate(index,params);
			}else{
				cout << "You must open a file first" << endl;
			}
		}

		if(command.compare(0,7,"within ") == 0){
			if(file.is_filled()){
				string part_of_command = command.substr(7);
				string word;
				string name;
				istringstream figure(part_of_command);
				list<int> values;
				bool first = true;
				while(figure >> word){
					if(first){
						first = false;
						name = word;
					}else{
						values.push_back(abs(stoi(word)));
					}
				}
				file.within(name,values);
			}else{
				cout << "You must open a file first" << endl;
			}
		}
	}
}