#include <stdio.h>
#include <stdint.h>  // Pour uint8_t
#include <string.h>  // Pour strlen
#include "RCSwitch_msg.h"

// you can test this code in loopback mode by connecting TX on RX 

int main(int argc, char *argv[]) {
    printf("Starting msg demo\n");
    int RECV_PIN = 25;
    int TX_PIN = 17;

    // Initialiser WiringPi
    if (wiringPiSetup() == -1) {
        printf("ERROR WIRING PI SETUP \n");
        return 1;
    }

    // Créer une instance de RCSwitch_msg
    RCSwitch_msg my_msg(TX_PIN, RECV_PIN);

    // Message à envoyer
    const char* message = "HELLO_WORLD";  // Utiliser const char* pour les chaînes de caractères
    size_t msg_length = strlen(message);    // Obtenir la longueur du message

    // Créer un buffer statique pour le message à envoyer
    uint8_t send_buffer[3] = { 0 }; // Buffer pour envoyer 3 octets

    // Créer un buffer statique pour recevoir un message
    uint8_t received_buffer[3] = { 0 }; // Pour recevoir 3 octets

    while (1) {
        // Remplir le send_buffer avec les valeurs des octets (par exemple en utilisant ASCII)
        for (size_t i = 0; i < 3 && i < msg_length; i++) {
            send_buffer[i] = message[i]; // Copier les premiers 3 caractères
        }

        // Envoyer le message
        my_msg.sendMessage(send_buffer, sizeof(send_buffer));
        delay(500);  // Attendre 500 ms

        // Recevoir le message
        if (my_msg.receiveMessage(received_buffer)) {
            // Afficher les octets reçus
            printf("Message reçu : ");
            for (int i = 0; i < 3; i++) {
                printf("%c", received_buffer[i]); // Afficher les caractères reçus
            }
            printf("\n");
        } else {
            printf("Aucun message reçu.\n");
        }

        delay(1000);  // Attendre 1 seconde avant de renvoyer
    }

    return 0;
}
