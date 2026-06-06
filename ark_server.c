#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

// La structure de l'Ark
typedef struct {
    int oxygen_level;
    int energy_level;
    int countdown;
} ArkStatus;

#define PORT 8080

int main() {
    int server_fd = -1, pv_socket =-1;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    // Initialisation des datas Ark
    ArkStatus ark = {100, 100, 60}; // 100% O2, 100% Énergie, 60 secondes avant le crash

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {
        perror("Échec de la création du socket");
        exit(EXIT_FAILURE);
    }

    // Config
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(PORT);

    // link du socket au port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Échec du Bind");
        exit(EXIT_FAILURE);
    }

    //  L'Ark se met en mode écoute (attend Raven)
    if (listen(server_fd, 1) < 0) {
        perror("Échec du Listen");
        exit(EXIT_FAILURE);
    }

    printf("[ARK] Système en ligne. En attente du terminal de Raven Reyes sur le port %d...\n", PORT);

    // Accepter la connexion du terminal de Raven
    if ((pv_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Échec du Accept");
        exit(EXIT_FAILURE);
    }

    printf("[ARK] Connexion établie avec le terminal de Raven !\n");

    // Boucle de simulation de crise 
    while (ark.oxygen_level > 0 && ark.countdown > 0) {
        
        ark.oxygen_level -= 2; 
        ark.energy_level -= 5;  
        ark.countdown -= 1;

        if (ark.oxygen_level < 0) ark.oxygen_level = 0;

        // ENVOI dans pv_socket les datas stocké depuis l'ark + la taille necessaire des datas

        send(pv_socket, &ark, sizeof(ArkStatus), 0);
        printf("[ARK] Données envoyées -> O2: %d%% | Énergie: %d%% | Crash dans: %ds\n", 
               ark.oxygen_level, ark.energy_level, ark.countdown);

        sleep(1); 
    }

    printf("[ARK] FIN DE LA SIMULATION.\n");
    close(pv_socket);
    close(server_fd);
    return 0;
}