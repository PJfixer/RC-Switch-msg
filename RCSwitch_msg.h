#ifndef RCSWITCH_MSG_H
#define RCSWITCH_MSG_H

#include "RCSwitch.h"
#include <stdint.h>  // Pour utiliser uint8_t

class RCSwitch_msg {
public:
    // Constructeur pour transmettre uniquement
    RCSwitch_msg(int transmitPin);

    // Constructeur pour recevoir uniquement
    RCSwitch_msg(int receivePin, bool isReceiver);

    // Constructeur pour transmettre et recevoir
    RCSwitch_msg(int transmitPin, int receivePin);

    // Méthode pour envoyer un message de 24 bits (3 octets)
    void sendMessage(uint8_t* buffer, size_t length);

    // Méthode pour recevoir un message de 24 bits (3 octets)
    bool receiveMessage(uint8_t* buffer);

private:
    RCSwitch rcSwitch;  // L'objet RCSwitch encapsulé
};

#endif // RCSWITCH_MSG_H
