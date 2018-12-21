/*
  Basic Web Server

 A simple web server that replies with nothing, but prints the client's request
 and the server IP address.

 Circuit:
 * MKR NB 1500 board
 * Antenna

 created
 by David Cuartielles
 modified 21 Nov 2012
 by Tom Igoe
*/
#include <MKRNB.h>

#include "arduino_secrets.h" 
// Please enter your sensitive data in the Secret tab or arduino_secrets.h
// PIN Number
const char PINNUMBER[]     = SECRET_PINNUMBER;

// initialize the library instance
GPRS gprs;
NB nbAccess;     // include a 'true' parameter for debug enabled
NBServer server(80); // port 80 (http default)

// timeout
const unsigned long __TIMEOUT__ = 10 * 1000;

void setup() {
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  Serial.println("starting,..");
  // connection state
  boolean connected = false;

  // Start module
  // If your SIM has PIN, pass it as a parameter of begin() in quotes
  while (!connected) {
    if ((nbAccess.begin(PINNUMBER) == NB_READY) &&
        (gprs.attachGPRS() == GPRS_READY)) {
      connected = true;
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }

  Serial.println("Connected to GPRS network");

  // start server
  server.begin();

  //Get IP.
  IPAddress LocalIP = gprs.getIPAddress();
  Serial.println("Server IP address=");
  Serial.println(LocalIP);
}

void loop() {
  NBClient client = server.available();

  if (client) {
    if (client.available()) {
      Serial.write(client.read());
    }
  }
}
