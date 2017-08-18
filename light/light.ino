

// Import required libraries
#include <ESP8266WiFi.h>
#include <aREST.h>
#include <aREST_UI.h> 

// Create aREST instance
aREST_UI rest = aREST_UI();

// WiFi parameters
const char* ssid = "ArcadiaIoT";
const char* password = "Unlock1234";
const int bulbPin = 14;


// The port to listen for incoming TCP connections 
#define LISTEN_PORT           80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Variables to be exposed to the API
int temperature;
float humidity;

void setup(void)
{  
  // Start Serial
  Serial.begin(115200);
  pinMode(5,OUTPUT);
  pinMode(bulbPin,OUTPUT);
  bulbOff("");
  // Create button to control pin 5
  rest.button(5);
//  rest.button(14);
  
  // Init variables and expose them to REST API
  temperature = 22;
  humidity = 39.1;
  rest.variable("temperature",&temperature);
  rest.variable("humidity",&humidity);

  // Function to be exposed
  rest.function("bulb_on",bulbOn);
  rest.function("bulb_off",bulbOff);
    
  // Give name and ID to device
  rest.set_id("1");
  rest.set_name("esp8266");
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
  
  // Print the IP address
  Serial.println(WiFi.localIP());
  
}

void loop() {

    while (WiFi.status() != WL_CONNECTED) {
    bulbOn("");
    delay(1000);
    bulbOff("");
    Serial.print(".");
  }
  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);
 
}

int ledControl(String command) {
  
  Serial.println(command);
  
  // Get state from command
  int state = command.toInt();
 
  digitalWrite(5,state);
  return 1;
}

int bulbOn(String command) {
  
//  Serial.println(command);
//  
//  // Get state from command
//  int state = command.toInt();
 
  digitalWrite(bulbPin,LOW);
  return 1;
}

int bulbOff(String command) {
  
//  Serial.println(command);
//  
//  // Get state from command
//  int state = command.toInt();
 
  digitalWrite(bulbPin,HIGH);
  return 1;
}




