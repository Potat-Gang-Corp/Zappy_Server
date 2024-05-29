#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_ADDRESS "127.0.0.1"  // Adresse du serveur
#define SERVER_PORT 1234  // Port du serveur
#define BUFFER_SIZE 1024  // Taille du tampon pour les messages

void error_handling(const char *message) {
    perror(message);
    exit(1);
}

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    char message[BUFFER_SIZE];
    int str_len;
    int response_count = 0;

    // Création du socket
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    serv_addr.sin_port = htons(SERVER_PORT);

    // Connexion au serveur
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("connect() error");
    }

    printf("Connecté au serveur %s sur le port %d\n", SERVER_ADDRESS, SERVER_PORT);

    // Envoi de la commande initiale "team1\r\n"
    char *initial_command = "team1\r\n";
    if (write(sock, initial_command, strlen(initial_command)) == -1) {
        error_handling("write() error");
    }

    // Boucle de lecture des réponses du serveur
    while (1) {
        str_len = read(sock, message, BUFFER_SIZE - 1);
        if (str_len == -1) {
            error_handling("read() error");
        } else if (str_len == 0) {
            // Si la lecture renvoie 0, cela signifie que le serveur a fermé la connexion
            printf("La connexion au serveur a été fermée.\n");
            break;
        }

        message[str_len] = '\0';
        printf("Réponse du serveur : %s\n", message);
        response_count++;

        // Envoyer "bonjour" après avoir reçu les trois réponses
        if (response_count == 3) {
            char *bonjour = "bonjour\r\n";
            if (write(sock, bonjour, strlen(bonjour)) == -1) {
                error_handling("write() error");
            }
            response_count = 0; // Réinitialiser le compteur si vous voulez envoyer "bonjour" après chaque trois réponses
        }
    }

    // Fermeture du socket
    close(sock);

    return 0;
}

