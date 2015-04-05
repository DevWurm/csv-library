# csv_library
A simple stream or object based csv parsing and creating library for C++.
With the library you can stream an CSV File into an object or you add 
a CSV line as string into the object and get a deque object with the parsed data.
The data can get streamed out of the object or yout get a copy of the data from a member function.
The same way you can stream or add a deque with data into an object and get a CSV string.

##Librarys
Because the code is template based it is completly written in Header files. All needed source data and headers are
copied into the file lib/libcsv.h. When includeing this file into the source files where you need the library, you
can use all the provided interfaces.

##How to use

    #include "libcss.h" //include the header
    #include <iostream>
    #include <fstream>
    #include <deque>
    #include <stream>
    int main() {
      csv::csv_handler<int>handler;** //ceate a handler object for int 
									 //(from namespace csv)
      std::ifstream input("file.csv"); //open input file
      std::ofstream output("file2.csv"); //open output file
      std::deque<int> data; //deque object to store data (is used like vector)
      std::stream buffer;
      
      //stream version
      input >> handler >> data; //read one line from input and store
						       //parsed data in data
      data >> handler >> output; //write the data from data into on one
								 //line of output
      
      //possible [but not very useful]: stream one line from input through data
      //into output and add a newline
      input >> handler >> data >> handler >> output << std::endl; 
      
      //member function version
      getline(input, buffer); //read one line from input into buffer
      handler.set_csv_line(buffer); //put CSV string into handler (and parse)
      data = handler.get_parsed_line(); //get parsed data and store in data
      handler.set_parsed_line(data); //put parsed data into handler 
									//(and create CSV string)
      buffer =  handler.get_csv_line(); //get CSV Sttring and store into buffer
      output << buffer //write buffer into file
      
    	return 0;
    }


You can use the CSV Handler object as an 'tunnel' between a stream and a variable or another stream, or you can set
and get data in and from the Handler over public member functions. You can also mix those two ways (conversion is always
done at setting data/streaming data into object).<br>
You can also use seperate objects for input/conversion do deque and output/conversion to string (here use ::set_line(DATA)
and DATA ::getline():

    csv::csv_parser<type> parser;
    input >> parser >> data;
    getline(input, buffer);
    parser.set_line(buffer);
    data = parser.get_line();
    
    csv::csv_creator<type> creator;
    data >> creator >> output;
    parser.set_line(data);
    buffer = parser.get_line();
    output << buffer;
The data stored in the csv object are deleted from there after get()ting them or streaming them out of the object.

##License
Copyright 2015 DevWurm<br>
'csv_library' is offered under GPL 3 License (Read ./license/gpl-3.0.txt)

##Documentation
Documentation will be offered soon. (Email me if you have any questions)

##Setup
<b>Building:</b><br>
Because the objects are templates, all souces are written in Header files. There is a 'real Header' (/Headers/csv.h) and
several 'source header' (/Source/*.h), because the code is more structured in this way. For using all declarations, 
definitions and dependencies are 'copyed together' in a 'library header' (/lib/libcsv.h'). You can use this header
or copy the suorces together yourself (make sure all includes and usings are given in the output file once and then copy
all the sources into one namespace definition).
<b>Using:</b><br>
Include the libcsv.h header file into your source file(s)
<pre><code>#include "libcsv.h"</code></pre>
Then you can use the objects and their members.
<br>
All the Element functions are showed in the how to use section.

##Authors
DevWurm<br>
Email: <a href='mailto:devwurm@gmx.net'>devwurm@gmx.net</a><br>
Feel free to contact me, if you have any questions or ideas about the project :)

##Collaborating
You can use the GitHub issue tracker for bugs and feature requests or create a pull request to submit 
changes and forks are welcome, too.
If you don't want to use these possibilities, you can also write me an email at 
<a href='mailto:devwurm@gmx.net'>devwurm@gmx.net</a>.

