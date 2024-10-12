#include "network.h"

int main() {
  char *HTMLResponse = "HTTP/1.1 200 OK\r\n\r\n<html><head><title>An Example Page</title></head><body>Hello World, this is a very simple HTML document.</body></html>\r\n";
  socketif_t sockfd;
  FILE *connfd, *fptr1;
  long length=0;
  char request[MTU], method[10], c;
  
  sockfd = createTCPServer(8000);
  if (sockfd < 0) {
    printf("[SERVER] Errore: %i\n", sockfd);
    return -1;
  }
  
  while(true) {
    connfd = acceptConnectionFD(sockfd);
    
    fgets(request, sizeof(request), connfd);
    printf("%s", request);
    strcpy(method,strtok(request," "));
    while(request[0]!='\r') {
      fgets(request, sizeof(request), connfd);
      printf("%s", request);
      if(strstr(request, "Content-Length:")!=NULL)  {
        length = atol(request+15);
        //printf("length %ld\n", length);
      }
    }
    
    if(strcmp(method, "POST")==0)
    {
      // filename to rcv
      char filename[100] = "";
      // flag used to obtain the filename string
      bool flag = 1;
 
      while(true)
      {
        // take a letter
        c = fgetc(connfd);
        printf("%c", c);
        
        // verify if it's filename
        if (flag == 1 && c == ';')
        {
          // read  (space)
          c = fgetc(connfd);
          printf("%c", c);
          
          // read f
          c = fgetc(connfd);
          printf("%c", c);
          if (c == 'f')
          // jump to the end of the word...
          for (int j = 0; j < 7; j++)
          {
            c = fgetc(connfd);
            printf("%c", c);
          }
          // ...and verify if it is an 'e'
          if (c == 'e')
          {
            // read =
            c = fgetc(connfd);
            printf("%c", c);
            

            c = fgetc(connfd);
            printf("%c", c);
            
            /* read name of file */
            while (true)
            {
              c = fgetc(connfd);
              printf("%c", c);
              // read until there is a letter or other
              if (c == '"')
              {
                flag = 0;
                break;
              }
              else
              // build filename
              strncat(filename, &c, 1);
            }
          }
        }
        
        // verify if it's the start of file contents
        if (c == '\r')
        {
          // read \n
          c = fgetc(connfd);
          printf("%c", c);
          if (c == '\n')
          {
            // read another \r
            c = fgetc(connfd);
            printf("%c", c);
            if (c == '\r')
            {
              // read another \n
              c = fgetc(connfd);
              printf("%c", c);
              if (c == '\n')
              {
                // INSIDE THE FILE
                // Create local file
                fptr1 = fopen(filename, "w");
                if (fptr1 == NULL)
                {
                  printf("Cannot open file %s \n", filename);
                  exit(-1);
                }
                
                // read every letter inside the file and 
                // write it in the new file
                c = fgetc(connfd);
                // until last boundary
                while (c != '\r')
                {
                  printf("%c", c);
                  fputc(c, fptr1);
                  fflush(fptr1);
                  c = fgetc(connfd);
                }
                fclose(fptr1);
                
                // read \r
                c = fgetc(connfd);
                
                // read \n
                c = fgetc(connfd);
                
                // clean the pipe of connection
                while (c != '\n')
                c = fgetc(connfd);
                // exit
                break;
              }
              
            }
          }
        }
      }
    }
    fputs(HTMLResponse, connfd);
    fclose(connfd);
    
    printf("\n\n[SERVER] sessione HTTP completata\n\n");
  }
  
  closeConnection(sockfd);
  return 0;
}
