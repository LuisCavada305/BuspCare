#include <ESP8266WiFi.h>
#include <PubSubClient.h>


const char* ssid     = "CAVADA";      
const char* password = "paocomlin";  
const char* mqtt_server = "lprot.pea.usp.br";
#define mqtt_port         7883
#define MQTT_USER         ""
#define MQTT_PASSWORD     ""
#define MQTT_SERIAL_PUBLISH_CH   "/Intengele/Grupo_A_Tx"
#define MQTT_SERIAL_RECEIVER_CH  "/Intengele/Grupo_A_Rx" 

WiFiClient wifiClient;
PubSubClient client(wifiClient);


void setup_wifi() {
    delay(10);
    Serial.println();
    Serial.println("## ExemploMQTT started");
    Serial.print("## Connecting to ");
    Serial.print(ssid);
    Serial.print("-");
    Serial.print(password);
    Serial.print(" ");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    randomSeed(micros());
    Serial.println("");
    Serial.println("## WiFi connected");
    
}

void reconnect() {
  
  while (!client.connected()) {
    
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    Serial.print("## Client Id = [");
    Serial.print(clientId.c_str()); Serial.println("]");

    
    Serial.println("## Attempting MQTT connectiont to broker");
    if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("## Client connected");
      
      
      client.publish(MQTT_SERIAL_PUBLISH_CH, "Testando 1 2 3\n");
      
      
      client.subscribe(MQTT_SERIAL_RECEIVER_CH);
      
      Serial.println("## Connected ok. Published and subscribed OK");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("## Trying again in 5 seconds");
      
      delay(5000);
    }
  }
}


void callback(char* topic, byte *payload, unsigned int length) {
    Serial.print("<< new message from broker. Topic:[");
    Serial.print(topic);
    Serial.print("] data length:");
    Serial.print(length);
    Serial.println(". Data follows...");
    Serial.write(payload, length);
    Serial.println(" ");
}


void setup() {
  Serial.begin(9600);     
  Serial.setTimeout(500);   
  setup_wifi();
  Serial.print("## MQTT Broker at [");
  Serial.print(mqtt_server);
  Serial.print(":");
  Serial.print(mqtt_port);
  Serial.println("]");
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  reconnect();
}


int    len = 0;     
long   counter = 0; 
long   eventcnt = 0;
void loop() {
   counter++;
   
   client.loop(); 
   
   
   if (Serial.available() > 0) {
     char bfr[501];
     memset(bfr,0, 501);
     len = Serial.readBytesUntil( '\n',bfr,500);
     if (!client.connected()) {
        Serial.println("## Broker not connected. Reconnecting");
        reconnect();
     }
     client.publish(MQTT_SERIAL_PUBLISH_CH, bfr);

     bfr[len]=0;
     Serial.print(">> Published to topic: [");
     Serial.print(MQTT_SERIAL_PUBLISH_CH);
     Serial.print("] Data: [");
     Serial.print(bfr);
     Serial.println("]");
   }
   
   if(counter>100000) 
   {
    if (!client.connected()) {
      Serial.println("## Broker not connected. Reconnecting");
      reconnect();
    }
    char bfr[501];
    
    
   }
 }
 