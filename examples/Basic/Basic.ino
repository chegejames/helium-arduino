/*
 * Copyright 2017, Helium Systems, Inc.
 * All Rights Reserved. See LICENCE.txt for license information
 */

#include "Arduino.h"
#include "Board.h"
#include "Helium.h"

Helium  helium(&atom_serial);
Channel channel(&helium);

void
setup()
{
    Serial.begin(9600);
    Serial.println("Starting");

    // Begin communication with the Helium Atom
    // The baud rate differs per supported board
    // and is configured in Board.h
    helium.begin(HELIUM_BAUD_RATE);

    // Connect the Atom to the Helium Network
    Serial.print("Connecting - ");
    int status = helium.connect();
    if (helium_status_OK == status)
    {
        Serial.println("Succeeded");
    }
    else
    {
        Serial.println("Failed");
    }

    // Begin communicating with the channel. This should only need to
    // be done once.
    //
    // NOTE: Please ensure you've created a channel called "Helium
    // Cloud MQTT" called in the Helium Dashboard.
    int8_t result;
    Serial.print("Creating Channel - ");
    status = channel.begin("Helium Cloud MQTT", &result);
    if (helium_status_OK == status && result == 0)
    {
        Serial.println("Succeeded");
    }
    else
    {
        Serial.println("Failed");
    }
}

void
loop()
{
    const char * data = "Hello Helium!";

    // Send some data to the configured channel
    int8_t result;
    Serial.print("Sending - ");
    int    status = channel.send(data, strlen(data), &result);
    if (helium_status_OK == status && result == 0)
    {
        Serial.println("Succeeded");
    }
    else
    {
        Serial.println("Failed");
    }

    delay(5000);
}
