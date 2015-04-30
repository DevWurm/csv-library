/*
	 * License
	 
	 * Copyright 2015 DevWurm
	
	 * This file is part of csv_library.

	 *  csv_library is free software: you can redistribute it and/or modify
	    it under the terms of the GNU General Public License as published by
	    the Free Software Foundation, either version 3 of the License, or
	    (at your option) any later version.
	
	    csv_library is distributed in the hope that it will be useful,
	    but WITHOUT ANY WARRANTY; without even the implied warranty of
	    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	    GNU General Public License for more details.
	
	    You should have received a copy of the GNU General Public License
	    along with csv_library.  If not, see <http://www.gnu.org/licenses/>.
	
	    Diese Datei ist Teil von csv_library.
	
	    csv_library ist Freie Software: Sie können es unter den Bedingungen
	    der GNU General Public License, wie von der Free Software Foundation,
	    Version 3 der Lizenz oder (nach Ihrer Wahl) jeder späteren
	    veröffentlichten Version, weiterverbreiten und/oder modifizieren.
	
	    csv_library wird in der Hoffnung, dass es nützlich sein wird, aber
	    OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
	    Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
	    Siehe die GNU General Public License für weitere Details.
	
	    Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
	    Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*/

#ifndef LIBCSV_H_
#define LIBCSV_H_

#include <deque>
#include <ostream>
#include <istream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>

using std::deque;
using std::istream;
using std::ostream;
using std::string;
using std::stringstream;
using std::getline;
using std::copy;
using std::back_inserter;

namespace csv {

template<typename T>
class csv_parser {
private:
	deque<T> line;
public:
	template<typename S>
	friend csv_parser<S>& operator>> (istream& input, csv_parser<S>& parser); //file input stream operator
	deque<T>& operator>> (deque<T>& target); //data output operator
	deque<T> get_line(); //get parsed line
	void set_line(string input);  //set line and parse
};

template<typename T>
class csv_creator {
private:
	string line;
public:
	template<typename S>
	friend csv_creator<S>& operator>>(deque<S>& input, csv_creator<S>& creator); //data input stream operator
	ostream& operator>>(ostream& output); //file output operator
	string get_line(); //set data and create csv
	void set_line(deque<T>& input); //get created csv
};

template<typename T>
class csv_handler: public csv_parser<T>, public csv_creator<T> {
private:
public:
	deque<T> get_parsed_line();
	void set_csv_line(string input);
	string get_csv_line();
	void set_parsed_line(deque<T>& input);
};

//csv_parser
template<typename T>
csv_parser<T>& operator>> (istream& input, csv_parser<T>& parser) {
	parser.line.clear(); //clear the data
	T buffer;
	string line;
	stringstream converter;

	getline(input, line); //get one line from csv file

	while (line.size() > 0) { //get field from csv line and delete this segment until
							  //input line is empty
		if (line.find_first_of(",") != -1) { //(not the last segment [one ',' left])
			converter << line.substr(0, line.find_first_of(",")); //add segment to converter
			converter >> buffer; //convert segment to T type
			converter.clear(); //clear flags of converter (normally EOF flag is set
								//after converting), so writing in converter is enabled again
			parser.line.push_back(buffer); //write segment into data
			line.erase(0, line.find_first_of(",")+1); //delete segment from input line
		}
		else { //(last segment in line)
			converter << line.substr(0, line.length()); //get rest of the line
			converter >> buffer; //convert segment to T type
			converter.clear(); //clear flags of converter (normally EOF flag is set
							   //after converting), so writing in converter is enabled again
			parser.line.push_back(buffer);//write segment into data
			line.erase(0, line.length()); //delete rest of input string
		}
	}
	return parser;
}

template<typename T>
void csv_parser<T>::set_line(string input) {
	line.clear();
	T buffer;
	stringstream converter;

	while (input.size() > 0) { //get field from input and delete this segment until
							  //input is empty
		if (input.find_first_of(",") != -1) { //(not the last segment [one ',' left])
			converter << input.substr(0, input.find_first_of(",")); //add segment to converter
			converter >> buffer; //convert segment to T type
			converter.clear(); //clear flags of converter (normally EOF flag is set
								//after converting), so writing in converter is enabled again
			line.push_back(buffer); //write segment into data
			input.erase(0, input.find_first_of(",")+1); //delete segment from input
		}
		else { //(last segment in line)
			converter << input.substr(0, input.length()); //get rest of the input
			converter >> buffer; //convert segment to T type
			converter.clear(); //clear flags of converter (normally EOF flag is set
							   //after converting), so writing in converter is enabled again
			line.push_back(buffer);//write segment into data
			input.erase(0, input.length()); //delete rest of input
		}
	}
}

template<typename T>
deque<T>& csv_parser<T>::operator>>(deque<T>& target) {//write parsed data into target
	target.clear();
	target.assign(line.begin(), line.end());
	line.clear();
	return target;
}

template<typename T>
deque<T> csv_parser<T>::get_line(){ //return data
	deque<T> buffer = line; //copy data into buffer
	line.clear(); //delete data
	return buffer; //return buffer
}

//csv_creator
template<typename T>
ostream& csv_creator<T>::operator>>(ostream& output) {
	output << line; // stream csv line into output
	return output;
}

template<typename T>
csv_creator<T>& operator>>(deque<T>& input, csv_creator<T>& creator) {
	stringstream converter;
	for (int i = 0; i <= input.size()-1; i++) { //add values to converter, separated by ','
		if (i != input.size()-1) {
			converter << input.at(i) << ','; //add ',' behind value if value is not last value
		}
		else {
			converter << input.at(i);
		}
	}
	creator.line = converter.str(); //get string from converter
	return creator;
}

template<typename T>
string csv_creator<T>::get_line() {
	return line; //return data
}

template<typename T>
void csv_creator<T>::set_line (deque<T>& input) {
	stringstream converter;
	for (int i = 0; i <= input.size()-1; i++) { //add values to converter, separated by ','
		if (i != input.size()-1) {
			converter << input.at(i) << ','; //add ',' behind value if value is not last value
		}
		else {
			converter << input.at(i);
		}
	}
	line = converter.str(); //get string from converter
}

//csv_handler
template<typename T>
deque<T> csv_handler<T>::get_parsed_line() {
	return csv_parser<T>::get_line(); //get parsed line (from parent class element csv_parser<T>::line)
}

template<typename T>
void csv_handler<T>::set_csv_line(string input) {
	csv_parser<T>::set_line(input); //set csv line and parse (into parent class element csv_parser<T>::line)
}

template<typename T>
string csv_handler<T>::get_csv_line() {
	return csv_creator<T>::get_line(); //get csv line (from parent class element csv_creator<T>::line)
}

template<typename T>
void csv_handler<T>::set_parsed_line(deque<T>& input) {
	csv_creator<T>::set_line(input); //set parsed line and create csv (into parent class element csv_creator<T>::line)
}


}

#endif /* LIBCSV_H_ */
