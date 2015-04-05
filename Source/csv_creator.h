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
#include <ostream>
#include <sstream>
#include <string>

using std::deque;
using std::ostream;
using std::stringstream;
using std::string;

namespace csv {

template<typename T>
ostream& csv_creator<T>::operator>>(ostream& output) {
	output << line; // stream csv line into file
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

}
