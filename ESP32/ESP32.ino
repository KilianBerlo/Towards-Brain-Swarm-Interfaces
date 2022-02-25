#include "WiFi.h"

char ssid[] = "";          //  your network SSID (name) 2.4ghz
char pass[] = "";          //  your network password

char servername[]= "";     // IP address of the server
int port = 1234;

WiFiClient client;

void setup() {
  //Short delay to prevent power spike
  delay(100);
  //Setup led to show when we are connected
  pinMode (LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  //Setup serial communication
  Serial.begin(115200);
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  //Start the wifi conncection
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED){
    Serial.println("Connecting to wifi...");
    delay(500);
  }
  
  //If you get a connection, connect to server:
  Serial.println("Connecting to server");
  while (!client.connect(servername, port)) {
    Serial.println("Connecting to server...");
    delay(500);
  }

  //We are now connected to the Raspberry Pi server
  Serial.println("Succefully connected");
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  // if there are incoming bytes available
  // from the server, read them and print them to the serial:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if there are incoming bytes available
  // from the serial, read them and print them to the server:
  if (Serial.available()) {
    char c = Serial.read();
    client.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    for(;;)
      ;
  }
}
