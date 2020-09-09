  #include "abstractdb.hpp"
  #include "vectordb.hpp"
  #include <iostream>
  #include <algorithm>
  #include <string.h>
  #include <cstdio>
  #include <cstdlib>
  #include <vector>
  #include <stdio.h>
  #include <sstream>
  #include <fstream>
  #include <cstring>


  using namespace nwen;
  using namespace std;

  //function that read and load data 
  bool AbstractDbTable::loadCSV(const char *file){
    // check for the file exist or not  
    if(file == NULL){ 
      return false;
    }
    //read the file
    ifstream infile;

    infile.open(file);

    //check whether the file can open or not
    if(!infile.is_open()) {
        printf("The file is failed to open %s\n",file);
        return false;
    }

    movie movie_info;

    // load the file
    while(!infile.eof()) {
        string text;

        if(!getline(infile, text, ',')){
        break;
        } //if no more lines then return 

        movie_info.id = strtoul(text.c_str(),NULL,10);

        if(!getline(infile, text, ',')){
        break;
        } //if no more lines then return 

        strncpy(movie_info.title, text.c_str(), text.length()+1);

        if(!getline(infile, text, ',')){
        break;
        } //if no more lines then return 

        movie_info.year = (unsigned short)strtoul(text.c_str(),NULL,10);

        if(!getline(infile, text, '\n')){
         break; 
        } //if no more lines then return 

        strncpy(movie_info.director, text.c_str(), text.length()+1);
      
          add(movie_info);
    }

    // Close the file
    infile.close();
    return true;
  }
