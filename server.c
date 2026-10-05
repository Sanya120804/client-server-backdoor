#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFERSIZE 1024
#define PORT 5566

int main()
{
    int serv_sock, clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;

    socklen_t clnt_addr_size = sizeof(clnt_addr);

    char message[BUFFERSIZE];

    /* Create socket */
    serv_sock = socket(AF_INET, SOCK_STREAM, 0);

    if (serv_sock < 0)
    {
        perror("Socket creation failed");
        return 1;
    }

    /* Configure server address */
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(PORT);

    /* Bind socket */
    if (bind(serv_sock,
             (struct sockaddr *)&serv_addr,
             sizeof(serv_addr)) < 0)
    {
        perror("Bind failed");
        close(serv_sock);
        return 1;
    }

    /* Listen */
    if (listen(serv_sock, 5) < 0)
    {
        perror("Listen failed");
        close(serv_sock);
        return 1;
    }

    printf("Server waiting for client...\n");

    /* Accept client */
    clnt_sock = accept(
        serv_sock,
        (struct sockaddr *)&clnt_addr,
        &clnt_addr_size
    );

    if (clnt_sock < 0)
    {
        perror("Accept failed");
        close(serv_sock);
        return 1;
    }

    printf("Client connected!\n");

    /* Keep sending messages */
    while (1)
    {
        printf("Type message: ");

        if (fgets(message, BUFFERSIZE, stdin) == NULL)
        {
            break;
        }

        /* Remove Enter key */
        message[strcspn(message, "\n")] = '\0';

        /* Exit command */
        if (strcmp(message, "exit") == 0)
        {
            send(clnt_sock, "exit\n", 5, 0);
            break;
        }

        /* Add newline as message delimiter */
        strcat(message, "\n");

        /* Send message */
        if (send(clnt_sock, message, strlen(message), 0) < 0)
        {
            perror("Send failed");
            break;
        }
    }

    /* Close connection */
    close(clnt_sock);
    close(serv_sock);

    printf("Connection closed.\n");

    return 0;
}