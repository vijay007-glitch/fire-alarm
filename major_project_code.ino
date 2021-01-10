#include <DHT.h>  
#include <ThingSpeak.h> 
#include <ESP8266WiFi.h>  
#include <WiFiClient.h> 
#define DHTPIN 5
#define DHTTYPE DHT11
int smokePin = A0;
int flamePin = D1
DHT dht(DHTPIN, DHTTYPE);
const char* ssid = "phoenix";  
const char* password = "madhav0505"; 
WiFiClient client;  
unsigned long myChannelNumber = 1249274;  
const char * myWriteAPIKey = "AQSXKX9643NJ45Q1";
uint8_t temperature, humidity;
void setup() 
{
  pinMode(smokePin, INPUT);
  pinMode(flamePin, INPUT);
  Serial.begin(115200);  
  dht.begin();  
  delay(10);  
  // Connect to WiFi network  
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("WiFi connected");  
  // Print the IP address  
  Serial.println(WiFi.localIP());   
  ThingSpeak.begin(client);

}

void loop() {
  int gasLevels = analogRead(smokePin);
  int flame = digitalRead(flamePin);
  temperature = dht.readTemperature();  
  humidity = dht.readHumidity();  
  Serial.print("Temperature Value is :");  
  Serial.print(temperature);  
  Serial.println("C");  
  Serial.print("Humidity Value is :");  
  Serial.print(humidity);  
  Serial.println("%");   
  Serial.println("Uploading Values");  
  ThingSpeak.writeField(myChannelNumber, 1, temperature, myWriteAPIKey);  
  ThingSpeak.writeField(myChannelNumber, 2, humidity, myWriteAPIKey);    
  ThingSpeak.writeField(myChannelNumber, 4, gasLevels, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 3, flame, myWriteAPIKey);  
  delay(500); 
} 
