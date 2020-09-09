  #include "abstractdb.hpp"
  #include "vectordb.hpp"
  #include <iostream>
  #include <string>
  #include <cstdio>
  #include <cstdlib>
  #include <vector>

  using namespace nwen;
  using namespace std;

  #define TOTAL_RECORD 100

  // allocating memory space for 100 records in the constractor 
  VectorDbTable::VectorDbTable(){
  }

  //Destructor
  VectorDbTable::~VectorDbTable(){
    
  }

  // function that return the entire rows
  int VectorDbTable::rows(){ return movies.size();}

  //show all the records
  bool VectorDbTable::show(const int row){
    // the vector that contain all records
    printf("\n Showing the %d row of record:\n",row);
    // show all the records
    if(0 <= row && row < movies.size()){
      cout << "Row " << row << endl;
      cout << "ID              : " << movies[row].id << endl;
      cout << "Title           : " << movies[row].title << endl;
      cout << "Year            : " << movies[row].year << endl;
      cout << "director        : " << movies[row].director << endl;
      // true for successed
      return true;
      }
      //false for failed
      return false;
  }
  movie* VectorDbTable::get(const int row){
    //get the index of the row which is less than the size of the movies
    if(row < movies.size()){ 
      return  &movies[row];
    }
    //then return null pointer
    return 0x0;  
  }

  // function that able to add movies
  bool VectorDbTable::add(movie &t){
    if(movies.size()==TOTAL_RECORD){
      return false;
    }
    for(int i = 0; i<movies.size();i++){
      if(movies[i].id == t.id){
        return false;
      }
    }
    
    try{movies.push_back(t);
    }catch (exception &e) { 
     return false; //if out of space then false
    }
    return true;

  }

  // function that able to remove the movies
  bool VectorDbTable::remove(unsigned long id){
    //check within the movies and get the movie id that matches the input id
    for(int i = 0; i<movies.size();i++){
      if(movies[i].id == id){
        movies.erase(movies.begin()+i);  //delete it
        return true;
      }
    }
    return false;
  }

  //function that do update
  bool VectorDbTable ::update(int row, struct movie m){
    //check the row positions
    if(0 <= row && row < movies.size()){
      movies[row]=m;  //if matches, assign to the new one
      return true;
    }

  return false;
  }

