#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFFERSIZE 1024
#define PORT 5566

int main()
{
    int sock;

    struct sockaddr_in serv_addr;

    char buffer[BUFFERSIZE];
    int bytes_received;

    /* Create socket */
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0)
    {
        perror("Socket creation failed");
        return 1;
    }

    /* Configure server address */
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(PORT);

    /* Connect to server */
    if (connect(sock,
                (struct sockaddr *)&serv_addr,
                sizeof(serv_addr)) < 0)
    {
        perror("Connection failed");
        close(sock);
        return 1;
    }

    /* Keep receiving messages */
    while (1)
    {
        memset(buffer, 0, BUFFERSIZE);

        bytes_received = recv(
            sock,
            buffer,
            BUFFERSIZE - 1,
            0
        );

        if (bytes_received <= 0)
        {
            break;
        }

        buffer[bytes_received] = '\0';

        /* Check for exit command */
        if (strcmp(buffer, "exit\n") == 0)
        {
            break;
        }

        /* Print exactly what the server sent */
        write(STDOUT_FILENO, buffer, bytes_received);
    }

    /* Close connection */
    close(sock);

    return 0;
}