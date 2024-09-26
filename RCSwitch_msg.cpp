#include "RCSwitch_msg.h"
#include <iostream>





// Constructeur pour transmettre uniquement
RCSwitch_msg::RCSwitch_msg(int transmitPin) {
    rcSwitch = RCSwitch();  // Initialisation de l'objet RCSwitch
    rcSwitch.enableTransmit(transmitPin);  // Initialiser la transmission
    rcSwitch.setProtocol(5);
    rcSwitch.setRepeatTransmit(0);
    std::cout << "Transmission activée sur la pin " << transmitPin << std::endl;
}

// Constructeur pour recevoir uniquement
RCSwitch_msg::RCSwitch_msg(int receivePin, bool isReceiver) {
    rcSwitch = RCSwitch();  // Initialisation de l'objet RCSwitch
    rcSwitch.enableReceive(receivePin);  // Initialiser la réception
    std::cout << "Réception activée sur la pin " << receivePin << std::endl;
}

// Constructeur pour transmettre et recevoir
RCSwitch_msg::RCSwitch_msg(int transmitPin, int receivePin) {
    rcSwitch = RCSwitch();  // Initialisation de l'objet RCSwitch
    rcSwitch.enableTransmit(transmitPin);  // Initialiser la transmission
    rcSwitch.enableTransmit(transmitPin);  // Initialiser la transmission
    rcSwitch.setProtocol(5);
    rcSwitch.setRepeatTransmit(0);
    rcSwitch.enableReceive(receivePin);    // Initialiser la réception
    std::cout << "Transmission activée sur la pin " << transmitPin << std::endl;
    std::cout << "Réception activée sur la pin " << receivePin << std::endl;
}

// Méthode pour envoyer un message de 24 bits (3 octets)
void RCSwitch_msg::sendMessage(uint8_t* buffer, size_t length) {
    for (size_t i = 0; i < length; i += 3) {
        if (i + 2 < length) {
            // Combiner 3 octets en un entier 24 bits
            uint32_t data = (buffer[i] << 16) | (buffer[i + 1] << 8) | buffer[i + 2];
            rcSwitch.send(data, 24);  // Envoyer 24 bits
            PRINT("Message envoyé: " << std::hex << data);
        }
    }
}

// Méthode pour recevoir un message de 24 bits (3 octets)
bool RCSwitch_msg::receiveMessage(uint8_t* buffer) {
    if (rcSwitch.available()) {
        uint32_t receivedValue = rcSwitch.getReceivedValue();  // Lire 24 bits (3 octets)
        if (receivedValue <= 0xFFFFFF) {  // Vérifier que la valeur tient sur 24 bits
            // Décomposer l'entier 24 bits en 3 octets et les stocker dans le buffer
            buffer[0] = (receivedValue >> 16) & 0xFF;
            buffer[1] = (receivedValue >> 8) & 0xFF;
            buffer[2] = receivedValue & 0xFF;
            PRINT("Message reçu: " << std::hex << receivedValue);
            return true;
        }
    }
    return false;
}
