/**
 * Source file for Assignment 3
 * Full Name:Elgene Menon Leo Anthony
 * Student ID:3002604
 *
 * You will need to modify this file to perform Tasks 4-5. See the
 * handout for more details.
 *
 * You may also use this as base code to perform Task 6. See the 
 * handout for more details.
 */


#include <stdio.h>
#include <unistd.h> 
#include <string.h>
#include <stdlib.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 

#include <sys/socket.h>
#include <sys/wait.h>
#include <ctype.h>
#include <errno.h>


/**
 * Header file contains macros and user-defined types
 * needed in this program. Open server.h for more
 * details.
 */
#include "server.h"

/**
 * Load CSV database file. The implementation of this
 * function is provided so you do not need to implement
 * this.
 * 
 * @param fn CSV database filename
 * @param m Pointer to movie_t
 * @param mlen Number of elements in m
 * @return 0 if successful, -1 otherwise
 */ 
int db_loadfile(const char *fn, movie_t *m, int mlen);

/**
 * If you are implementing your own functions, declare
 * the function prototypes below. Document your function
 * prototypes using the format above in the prototype
 * declaration of db_loadfile.
 */


/**
 * Main function
 */
int main(void)
{
  int ret, sockfd, bindret, fd, client_fd;
  socklen_t addrlen;
  struct sockaddr_in server_addr, client_addr; //addresses of struct
  char incoming[DEFAULT_STRLEN];
  int receiving, sending;
  movie_t movies[CSVDB_RECORDS];

  addrlen = sizeof(client_addr);

  printf("Starting server...\n");

    /* Load CSV database file */
  ret = db_loadfile(CSVDB_FILENAME, movies, CSVDB_RECORDS);
  if(ret) {
    printf("Error: Failed to open %s\n", CSVDB_FILENAME);
    return 0;
  }

    /* Step 1 : create a socket with the socket() system call */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    printf("Error creating socket\n");
    exit(1);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(DB_SERVER_PORT);

   /* Step 2 : Bind the socket to an address using the bind() system call */
  bindret = bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr));
  if (bindret < 0) {
    printf("Error binding socket\n");
    exit(1);
  }

  /* Step 3 : Listen for connections with the listen() system call */
  if (listen(sockfd,SOMAXCONN) < 0){
    printf("Error listening for connections\n");
    exit(1);
  }

  /* Step 4 : Accept a connection with the accept() system call */
  
  client_fd = accept(sockfd, (struct sockaddr *)&client_addr, &addrlen);
  if (client_fd < 0) {
   printf("Error accepting connection\n");
   exit(1);
 }
 char msg[] = "HELLO\n";
 send(client_fd,msg,strlen(msg), 0);
 
 int row_number, row;

 while(1){
    /*reset the incoming*/
  memset(incoming, 0, DEFAULT_STRLEN);

    /* Step 5 : Send and receive data */
  receiving = recv(client_fd,incoming,DEFAULT_STRLEN, 0);
  if (receiving < 0) {
   printf("Error receiving message");
   exit(1);
 }

 printf("Received message: %s\n",incoming);
 char temp[DEFAULT_STRLEN];
 row_number = sscanf(incoming, "%s %d", temp, &row);

 if(row_number == 1){
      //BYE
  if ((strcasecmp(temp, "BYE") == 0) || (strcasecmp(incoming, "BYE\n") == 0) ){
    printf("Closing connection with client.\n");
    close(client_fd);
    close(sockfd);
    exit(1);
  }

      //GET
  if(strcasecmp(temp, "GET") == 0){
    printf("Sent all database\n");
    for(int i = 0; i < CSVDB_RECORDS; i++){
      snprintf(incoming, 5*DEFAULT_STRLEN, "%d: %s, %s, %d, %d, %s\r\n", i ,
        movies[i].title,movies[i].director,movies[i].year,movies[i].oscars_won,movies[i].origin_country);
      sending = send(client_fd, incoming, strlen(incoming),0);
     }
   }
 }
    //get particular row
 else if(row_number == 2){
   if(strcasecmp(temp, "GET") == 0){
    if(row < 0 || row > CSVDB_RECORDS){
      printf("Error:The index is out of bound\n");
      char errorOutOfBound[] = "Error:The index is out of bound\n";
      send(client_fd,errorOutOfBound , strlen(errorOutOfBound),0);

    }
    else{
      snprintf(incoming, 5*DEFAULT_STRLEN, "%d: %s, %s, %d, %d, %s\r\n", row,
       movies[row].title, movies[row].director, movies[row].year, movies[row].oscars_won, movies[row].origin_country);
      sending = send(client_fd, incoming, strlen(incoming), 0);
    }
  }
}
      /* Step 5 : Send and receive data */
      if (sending < 0) { //if failed
       printf("Error sending message\n");
       exit(1);
     }
   }
   return 0;
   
 }
/**
 * Implementation of db_loadfile function
 */
 int db_loadfile(const char *fn, movie_t *movies, int mlen)
 {
    // Input file stream to read csv
  FILE *csv = fopen("scifi.csv", "r");
  if(!csv) {
    return -1;
  }

    // Read csv file line by line and scan for input
  int i = 0;
  while(!feof(csv) && i < mlen) {
   fscanf(csv, "%[^,],%[^,],%d,%d,%[^\n]%*c", 
     movies[i].title, movies[i].director, &movies[i].year, 
     &movies[i].oscars_won, movies[i].origin_country);
   i++;
 }

    // Close file after reading
 fclose(csv);

 return 0;
}





