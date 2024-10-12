#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h> 


float calcolaSomma(float val1, float val2)  {
   return (val1 + val2);
}

int* numeriPrimi(int a, int b, int* count) {
    int i, j;
    int primeCount = 0; // Counter for the number of prime numbers found

    // Initially, there are no prime numbers, so the size of the array is 0
    int* primes = (int *)malloc(primeCount * sizeof(int));

    if (primes == NULL) {
        printf("Memory allocation error\n");
        return NULL;
    }

    for (i = a; i <= b; i++) {
        if (i == 1 || i == 0)
            continue;

        int isPrime = 1;

        for (j = 2; j <= i / 2; ++j) {
            if (i % j == 0) {
                isPrime = 0;
                break;
            }
        }

        if (isPrime) {
            primeCount++;
            int* temp = (int*)realloc(primes, primeCount * sizeof(int));

            if (temp == NULL) {
                printf("Memory reallocation error\n");
                free(primes); // Free the previously allocated memory to avoid memory leaks
                return NULL;
            }

            primes = temp;
            primes[primeCount - 1] = i;
        }
    }

    *count = primeCount;
    return primes;
}



int main() {
    char *HTMLResponse = "HTTP/1.1 200 OK\r\n\r\n";
    socketif_t sockfd;
    FILE* connfd;
    int res, i;
    long length = 0;
    char request[MTU], url[MTU], method[10], c;

    // Create TCP connection
    sockfd = createTCPServer(8000);
    if (sockfd < 0) {
        printf("[SERVER] Error: %i\n", sockfd);
        return -1;
    }

    while (1) {
        connfd = acceptConnectionFD(sockfd);

        fgets(request, sizeof(request), connfd);
        printf("\nInitial connection text: %s\n", request);
        strcpy(method, strtok(request, " "));
        strcpy(url, strtok(NULL, " "));
        printf("\nurl: %s\n\n", url);
        while (request[0] != '\r') {
            fgets(request, sizeof(request), connfd);
            if (strstr(request, "Content-Length:") != NULL) {
                length = atol(request + 15);
            }
        }

        // POST METHOD
        if (strcmp(method, "POST") == 0) {
            // Read the body of the POST request
            char *body = malloc(length + 1);
            if (body == NULL) {
                printf("Errore di allocazione memoria\n");
                fclose(connfd);
                continue;
            }
            fread(body, 1, length, connfd);
            body[length] = '\0';
            printf("Body: %s\n", body);

            fprintf(connfd,
                    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/plain\r\n"
                    "\r\n"
                    "Valori salvati\r\n");           
        }


        // API
        if (strstr(url, "calcola-somma") != NULL) {
            printf("Calling sum function\n");

            char *function, *op1, *op2;
            float somma, val1, val2;

            // Skeleton: decode (deserialize) the parameters
            function = strtok(url, "?&");
            op1 = strtok(NULL, "?&");
            op2 = strtok(NULL, "?&");
            strtok(op1, "=");
            val1 = atof(strtok(NULL, "="));
            strtok(op2, "=");
            val2 = atof(strtok(NULL, "="));

            // Call business logic
            somma = calcolaSomma(val1, val2);

            // Skeleton: encode (serialize) the result
            fprintf(connfd,
                    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: application/json\r\n"
                    "\r\n"
                    "{\r\n"
                    "    \"somma\": %.2f\r\n"
                    "}\r\n",
                    somma);
        } else if (strstr(url, "numeri-primi") != NULL) {
            printf("Calling prime number function\n");

            char *function, *op1, *op2;
            int val1, val2, size;
            int count = 0;
            int* primes;

            // Skeleton: decode (deserialize) the parameters
            function = strtok(url, "?&");
            op1 = strtok(NULL, "?&");
            op2 = strtok(NULL, "?&");
            strtok(op1, "=");
            val1 = atoi(strtok(NULL, "="));
            strtok(op2, "=");
            val2 = atoi(strtok(NULL, "="));

            // Call business logic
            primes = numeriPrimi(val1, val2, &count);

            if (primes == NULL) {
                fprintf(connfd, "HTTP/1.1 500 Internal Server Error\r\n");
                fprintf(connfd, "Content-Type: application/json\r\n");
                fprintf(connfd, "\r\n");
                fprintf(connfd, "{\r\n");
                fprintf(connfd, "    \"error\": \"Memory allocation error\"\r\n");
                fprintf(connfd, "}\r\n");
                
            } else {
                fprintf(connfd, "HTTP/1.1 200 OK\r\n");
                fprintf(connfd, "Content-Type: application/json\r\n");
                fprintf(connfd, "\r\n");
                fprintf(connfd, "{\r\n");
                fprintf(connfd, "    \"numeri-primi\": [");

                // Iterate over the prime numbers and format as JSON
                for (int i = 0; i < count; i++) {
                    if (i < count - 1) {
                        fprintf(connfd, "%d, ", primes[i]);
                    } else {
                        fprintf(connfd, "%d", primes[i]);
                    }
                }

                // Close the JSON array
                fprintf(connfd, "]\r\n}\r\n");

                // Free the allocated memory
                free(primes);
            }
        } else {
            fprintf(connfd, "HTTP/1.1 200 OK\r\n\r\n{\r\n    \"error\": \"Unknown function\"\r\n}\r\n");
        }

        fclose(connfd);
        printf("\n\n[SERVER] HTTP session completed\n\n");
    }

    closeConnection(sockfd);
    return 0;
}