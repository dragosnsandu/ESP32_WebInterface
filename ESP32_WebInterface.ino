#include <FastLED.h>
#include <WiFi.h>
#include "esp_system.h"

const char* ssid = "*****";
const char* password = "*****";
const char* host = "api.thingspeak.com";
const char* streamId = "....................";
const char* privateKey = "....................";

#define DATA_PIN 3
#define NUM_LEDS 16
CRGB leds[NUM_LEDS];

unsigned int brightness = 10;
unsigned int numberofLEDs = 16;

WiFiClient client;

void setup()
{
	FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
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
			char lineContent[20];
			char * token;
			char BrightnessValue[4];
			char NoLValue[3];

			line.toCharArray(lineContent, 20);
			
			token = strtok(lineContent, ",");
			strcpy(BrightnessValue, token);
			brightness = atoi(BrightnessValue);

			token = strtok(NULL, ",");
			strcpy(NoLValue,token);
			numberofLEDs = atoi(NoLValue);

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
		}
		lineNumber++;
	}
	
	Serial.println("closing connection");
}
