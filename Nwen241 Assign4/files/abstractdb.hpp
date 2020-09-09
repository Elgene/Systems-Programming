    #ifndef __ABSTRACT_DB_HPP__
    #define __ABSTRACT_DB_HPP__
    #include <vector>

    /**
     * You will need to add the necessary class declaration for Task 4 in this
     * file.
     */

    using namespace std;

    namespace nwen 
    {
        struct movie {
            unsigned long id;
                char title[50];
            unsigned short year;
            char director[50];
        };


    class AbstractDbTable {
        public:
            virtual int rows() = 0;
            virtual bool show(const int row) = 0;
            virtual movie* get(const int row) = 0;
            virtual bool add(movie &m) = 0;
            virtual bool update(int row, struct movie m) = 0;
            virtual bool remove(unsigned long id) = 0;
            bool loadCSV(const char* file);
            
        };
    }

    #endif /* __ABSTRACT_DB_HPP__ */
