#include <iostream>
#include <string>
#include <sstream>
#include "fileSVG.h"

using namespace std;

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