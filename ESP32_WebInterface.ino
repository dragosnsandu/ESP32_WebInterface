#include <FastLED.h>
//#include <ESP32WebServer.h>
#include <WiFi.h>
#include "esp_system.h"

//String getMacAddress() {
//	uint8_t baseMac[6];
//	// Get MAC address for WiFi station
//	esp_read_mac(baseMac, ESP_MAC_WIFI_STA);
//	char baseMacChr[18] = { 0 };
//	sprintf(baseMacChr, "%02X:%02X:%02X:%02X:%02X:%02X", baseMac[0], baseMac[1], baseMac[2], baseMac[3], baseMac[4], baseMac[5]);
//	return String(baseMacChr);
//}

const char* ssid = "*****";
const char* password = "*****";
const char* host = "api.thingspeak.com";
const char* streamId = "....................";
const char* privateKey = "....................";

#define DATA_PIN 3
#define NUM_LEDS 16
CRGB leds[NUM_LEDS];
//byte mac[6];

unsigned int brightness = 10;
unsigned int numberofLEDs = 16;

//ESP32WebServer server(80);
WiFiClient client;


//void handleRoot()
//{
//	server.send(200, "text/plain", "Hai noroc, sa vedem daca merge!");
//	//server.send(200, "text/html", "/index.html");
//}

//void handleSettings()
//{
//	//digitalWrite(pinLED, !digitalRead(pinLED));
//	//server.send(204, "");
//	//if (server.arg("Brightness") == "")
//	//{
//	//	server.send(200, "text/html", "Nu am gasit parametrul corect");
//	//}
//	else
//	{
//		//Serial.println(brightness);
//		brightness = server.arg("Brightness").toInt();
//
//		FastLED.setBrightness(brightness);
//
//		for (int i = 0; i < NUM_LEDS; i++)
//		{
//			leds[i] = CRGB::White;
//			FastLED.show();
//		}
//
//		//Serial.println("Brightnessafter:" + brightness);
//		server.send(200, "text/plain", "OK");
//	}
//	//server.send(204, "");
//
//}

void setup()
{
	FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
	//pinMode(PixelPin, OUTPUT);
	Serial.begin(115200);
	WiFi.begin(ssid, password);
	Serial.println("");

	/* Wait for connection */
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.print("Connected to ");
	Serial.println(ssid);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

	//Serial.println(getMacAddress());

	//server.on("/", handleRoot);
	//server.on("/settings", handleSettings);

	//server.begin();

	//strip.Begin();
	//strip.SetBrightness(10);
	//strip.Show();
	//Serial.println(strip.GetBrightness());
	FastLED.setBrightness(brightness);

	for (int i = 0; i < NUM_LEDS; i++)
	{
		leds[i] = CRGB::Black;
		FastLED.show();
	}
	//digitalWrite(ringLEDPIN, HIGH);
	Serial.println(brightness);

}

void loop()
{
	//server.handleClient();
	delay(5000);

	if (!client.connect(host, 80))
	{
		Serial.println("Conectare esuata");
		return;
	}

	// We now create a URI for the request
	String url = "/apps/thinghttp/send_request?api_key=BCB9OUP00A35PHKO&headers=false";

	// This will send the request to the server
	client.print(String("GET ") + url + " HTTP/1.0\r\n" +
		"Host: " + host + "\r\n" +
		"Connection: close\r\n\r\n");
	unsigned long timeout = millis();
	while (client.available() == 0) {
		if (millis() - timeout > 5000) {
			Serial.println(">>> Client Timeout !");
			client.stop();
			return;
		}
	}

	// Read all the lines of the reply from server and print them to Serial
	int lineNumber = 1;
	while (client.available()) {
		String line = client.readStringUntil('\r');
		Serial.print(line);
		if (lineNumber == 15)
		{
			//Serial.println("a intrat");

			char lineContent[20];
			char * token;
			char BrightnessValue[4];
			char NoLValue[3];

			line.toCharArray(lineContent, 20);
			
			token = strtok(lineContent, ",");
			strcpy(BrightnessValue, token);
			brightness = atoi(BrightnessValue);

			token = strtok(NULL, ",");
			//token = strtok(lineContent, ",");
			//token = strtok(NULL, ",");
			strcpy(NoLValue,token);
			numberofLEDs = atoi(NoLValue);
			//Serial.println("TEST");
			//Serial.println(numberofLEDs);

			//brightness = line.toInt();
			FastLED.setBrightness(brightness);

			for (int i = 0; i < numberofLEDs; i++)
			{
				leds[i] = CRGB::White;
				FastLED.show();
			}

			for (int i = numberofLEDs; i < NUM_LEDS; i++)
			{
				leds[i] = CRGB::Black;
				FastLED.show();
			}


			//Serial.println(line.toInt());
		}
		lineNumber++;
	}
	
	Serial.println("closing connection");
}
