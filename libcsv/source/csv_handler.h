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

#ifndef __csv_handler_h__
#define __csv_handler_h__

#include <deque>
#include <string>
#include "../headers/csv.h"

using std::deque;
using std::string;

namespace csv {

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

#endif
