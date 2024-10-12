#include "network.h"
#include <string.h>
#include <stdbool.h>

int main() {
    char *HTTPResponse_header = "HTTP/1.1 200 OK\r\n";
    socketif_t sockfd;
    FILE *connfd;
    FILE *file;
    long length = 0;
    char request[MTU], method[10];

    sockfd = createTCPServer(8000);
    if (sockfd < 0) {
        printf("[SERVER] Errore: %i\n", sockfd);
        return -1;
    }

    while (true) {
        connfd = acceptConnectionFD(sockfd);
        if (connfd == NULL) {
            printf("[SERVER] Errore nell'accettare la connessione\n");
            continue;
        }
        printf("\nNew Connection Answer:\n");
        fgets(request, sizeof(request), connfd);
        printf("Request: %s\n", request);

        // Parse request line to get HTTP method and request URI
        strcpy(method, strtok(request, " "));
        char *requestURI = strtok(NULL, " ");
        printf("uri: %s\n", requestURI);

        // Check if the request URI is not NULL and starts with "/"
        if (requestURI != NULL && requestURI[0] == '/') {
            // Get the file path from the request URI (remove leading "/")
            char *filePath = requestURI + 1;

            printf("Requested file: %s\n", filePath);

            // Open the file in read o readbinary (rb) mode 
            file = fopen(filePath, "r"); 
            if (file == NULL) {
                printf("Failed to open file: %s\n", filePath);
                // Send 404 Not Found response
                fputs("HTTP/1.1 404 Not Found\r\n\r\n", connfd);
            } else {
                
                // Get the file length
                fseek(file, 0, SEEK_END);
                length = ftell(file);
                printf("dimensione file: %ld\n", length);
                fseek(file, 0, SEEK_SET);

                // Send HTTP response header
                fputs(HTTPResponse_header, connfd);

                
                fputs("Connection: close\r\n\r\n", connfd);

                // Send file content to the client
                char buffer[MTU];
                size_t bytesRead;
                while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
                    fwrite(buffer, 1, bytesRead, connfd);
                }

                fclose(file);
            }
        } else {
            printf("Invalid request URI\n");
        }

        fclose(connfd);
        printf("[SERVER] HTTP session completed\n\n");
    }

    closeConnection(sockfd);
    return 0;
}
