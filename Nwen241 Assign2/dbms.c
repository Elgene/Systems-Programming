        //Name:Elgene Menon Leo Anthony
        //username:leoanelge
        //student id: 300492604
        #include <stdlib.h>
        #include <string.h>
        #include <stdio.h>
        #include <string.h>
        #include <stdlib.h>

        #include "dbms.h"

        // Task 6
        int db_show_row(struct db_table *db, unsigned int row)
        {
        //if it doesnt not exist 
         if (row > db->rows_used )
         {
            return 0;
         }else if(db+row)
         {
           struct album *a = (db->table) + row;

           printf("........Information......................\n");
           printf("%ld Id: \n", a->id);
           printf("%s Title: \n", a->title);
           printf("%d Year: \n", a->year);
           printf("%s Artist: \n", a->artist);

           return 1;
        }
           return 0;
        }

        // Task 7
        int db_add_row(struct db_table *db, struct album *a)
        { 
        struct album *newtable;
        //check the content of the table
        if(db-> table==NULL){
        printf("Empty table");
        } 
        //if theres space in the table then more rows with album
        if(db-> rows_used < db-> rows_total){
        int more_rows = db-> rows_used;
        *((db->table)+more_rows)=*a; //add new rows to the album

        db->rows_used++; //increment the rows 
        return 1;  //for doing the adding of rows well
        }
        else if(db-> rows_total == db-> rows_used){//need to create extra space 
         if(db->rows_total == 0){//this is for the first time
            newtable= (struct album*) calloc(5,sizeof(struct album));

            if(newtable!=NULL){//making sure that the new table is not empty
            	db-> table = newtable;
            }
        }
        else{
            //increase the size by 5 and reallocating the memory space
        	newtable= (struct album*) realloc(db->table,sizeof(struct album) * db->rows_total+5);
            if(newtable!=NULL){//making sure that the new table is not empty
            	db-> table = newtable;
            }
        }
            int more_rows = db-> rows_used;
            *((db->table)+more_rows)=*a; //add new rows to the album

            db->rows_used++;
            db->rows_total += 5;
            return 1;
            }
            return 0;
        }


        // Task 8
        int db_remove_row(struct db_table *db, unsigned long id)
            {           
            int  row = -1;
           for(int i=0; i < db-> rows_used; i++){
            if(((db->table+i))->id == id){
                row=i;
                db->rows_used--;
                break;
            }
           }  
               if(row!=-1){
                for(int i=row; i < db-> rows_used; i++){  
               if(((db->table)+(i+1))!=NULL){
                *((db->table)+i) = *((db->table )+(i+ 1)); 
            }
                }
                if (db->rows_used < db->rows_total && db->rows_total > 5){
            struct album *temp ;
            temp = (struct album*)realloc(db->table, (db->rows_total-5) * sizeof(struct album));

            //check if memory allocation succeed
            if(temp)
                db->table = temp;

            db->rows_total -= 5;
        }
             
         return 1;
           }
           return 0;
        }



