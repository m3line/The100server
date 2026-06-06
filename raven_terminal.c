#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

//  même struct pr savoir comment lire les données reçues!!!!!!
typedef struct {
    int oxygen_level;
    int energy_level;
    int countdown;
} ArkStatus;

#define PORT 8080

int main() {
    int sock = -1;
    struct sockaddr_in serv_addr;
    ArkStatus current_status;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Erreur de création du socket \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    // Conversion de l'adresse IP locale 127.0.0.1 w  inet_pton ( = internet presentation(human) to network)

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\n Adresse invalide \n");
        return -1;
    }

    // Connexion à l'Ark
    printf("[RAVEN] Tentative de connexion aux systèmes de l'Ark...\n");
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\n Connexion échouée. L'Ark est-elle allumée ? \n");
        return -1;
    }

    // Boucle de réception des données
    // > 0 : tant qu'on reçoit des datas
    while (recv(sock, &current_status, sizeof(ArkStatus), 0) > 0 ) {
        
        // Efface le terminal pour un effet dynamique "écran de contrôle"
        system("clear"); 

        // (Code couleur ANSI vert \033[0;32m)
        printf("\033[0;32m");
        printf("==================================================\n");
        printf("           TERMINAL DE RECONNEXION - REYES R.      \n");
        printf("==================================================\n\n");
        
        printf("  [!] SYSTÈME CRITIQUE DE L'ARK EN PERDITION [!]\n\n");
        printf("  Niveau d'Oxygène : [ %d%% ]\n", current_status.oxygen_level);
        printf("  Niveau d'Énergie : [ %d%% ]\n", current_status.energy_level);
        printf("  Temps avant destruction : %ds\n\n", current_status.countdown);
        
        if (current_status.oxygen_level < 20) {
            printf("\033[0;31m  [ALERTE] ASPHYXIE IMMINENTE !\033[0;32m\n");
        }
        printf("==================================================\n");

        if (current_status.energy_level < 50) {
            printf("\033[0;31m  [ALERTE] NIVEAU D'ENERGIE EN CHUTE !\033[0;32m\n");
        }
        printf("==================================================\n");
    }

    printf("\033[0m"); // Réinitialise les couleurs du terminal
    printf("\n[RAVEN] Connexion interrompue avec l'Ark.\n");
    close(sock);
    return 0;
}