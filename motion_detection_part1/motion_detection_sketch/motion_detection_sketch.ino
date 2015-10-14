#include<Arduino.h>
#include<HardwareSerial.h>

#define ssid "" //write your ssid
#define PASS "" //write your pass
#define IP "" //write your server IP

#define pirPin 2

int calibrationTime = 30;

long unsigned int lowIn;

long unsigned int pause = 5000;

boolean lockLow = true;
boolean takeLowTime;


void setup(){
	Serial.begin(9600);
	Serial1.begin(115200);
	pinMode(pirPin, INPUT);
	digitalWrite(pirPin, LOW);

	Serial1.println("AT");
	delay(5000);
	if (Serial1.find("OK")){
		Serial.println("ESP8266 OK");
		if (connectWiFi()) {
			Serial.println("WIFI OK");
		}
	}

	Serial.print("calibrating sensor ");
	for (int i = 0; i < calibrationTime; i++){
		Serial.print(".");
		delay(1000);
	}
	Serial.println(" done");
	Serial.println("SENSOR ACTIVE");
	delay(50);
}

void loop(){
	String rezultat = connTest("GET /motion_detection/det_serv.php", true);
	if (rezultat.indexOf("TUON") >= 0) {
		if (digitalRead(pirPin) == HIGH){
			if (lockLow){
				lockLow = false;
				Serial.println("---");
				Serial.print("motion detected at ");
				Serial.print(millis() / 1000);
				Serial.println(" sec");
				connTest("GET /motion_detection/is_detected.php?yes=yes", false);
				delay(50);
			}
			takeLowTime = true;
		}

		if (digitalRead(pirPin) == LOW){

			if (takeLowTime){
				lowIn = millis();          
				takeLowTime = false;       
			}
			if (!lockLow && millis() - lowIn > pause){
				lockLow = true;
				Serial.print("motion ended at ");      
				Serial.print((millis() - pause) / 1000);
				Serial.println(" sec");
				connTest("GET /motion_detection/is_detected.php?no=no", false);
				delay(50);
			}
		}
	}
}

boolean connectWiFi(){
	Serial1.println("AT+CWMODE=1");
	delay(2000);
	String cmd = "AT+CWJAP=\"";
	cmd += ssid;
	cmd += "\",\"";
	cmd += PASS;
	cmd += "\"";
	Serial1.println(cmd);
	delay(5000);
	if (Serial1.find("OK")){
		return true;
		Serial.print("ETO");
	}
	else{
		return false;
	}
}

String connTest(String GET, bool wait){
	String izlaz = "";
	String cmd = "AT+CIPSTART=\"TCP\",\"";
	cmd += IP;
	cmd += "\",80";
	Serial1.println(cmd);
	delay(2000);
	if (Serial1.find("Error")){
		return "";
	}
	cmd = GET;
	cmd += "\r\n";
	Serial1.print("AT+CIPSEND=");
	Serial1.println(cmd.length());
	if (Serial1.find(">")){
		Serial1.print(cmd);
		if (wait == true) delay(2000);
		if (Serial1.available()>0)
		{
			while (Serial1.available()>0)
			{
				izlaz += char(Serial1.read());
			}
			Serial.println(izlaz);
		}
	}
	else{
		Serial1.println("AT+CIPCLOSE");
	}
	return izlaz;
}

