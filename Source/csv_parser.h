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

#include "../Headers/csv.h"
#include <deque>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using std::deque;
using std::ifstream;
using std::stringstream;
using std::string;
using std::getline;
using std::copy;

namespace csv {

template<typename T>
csv_parser<T>& operator>> (ifstream& input, csv_parser<T>& parser) {
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
	target.assign(line.begin(), line.end()); //copy data into target
	line.clear(); //delete data
	return target;
}

template<typename T>
deque<T> csv_parser<T>::get_line(){ //return data
	deque<T> buffer = line; //copy data into buffer
	line.clear(); //delete data
	return buffer; //return buffer
}

}



