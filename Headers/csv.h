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

#ifndef CSV_H_
#define CSV_H_

#include <deque>
#include <fstream>
#include <string>

using std::deque;
using std::ifstream;
using std::ofstream;
using std::string;

namespace csv {

template<typename T>
class csv_parser {
private:
	deque<T> line;
public:
	template<typename S>
	friend csv_parser<S>& operator>> (ifstream& input, csv_parser<S>& parser); //file input stream operator
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
	ofstream& operator>>(ofstream& output); //file output operator
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

}

#endif /* CSV_H_ */
