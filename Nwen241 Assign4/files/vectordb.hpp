    #ifndef __VDB_HPP__
    #define __VDB_HPP__

    #include "abstractdb.hpp"
    #include <vector>

    using namespace std;
    using namespace nwen;

    namespace nwen{
        class VectorDbTable : public AbstractDbTable {
        public:
            int rows();
            bool show(const int row);
    	    movie* get(const int row);
            bool add(movie &m);
    	    bool update(int row, struct movie m);
            bool remove(unsigned long id);
            
            
            VectorDbTable();
            ~VectorDbTable();

        private:
    	int rowNumber;
            vector<movie> movies;
        };
    }

    #endif //__VDB_HPP__