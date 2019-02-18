#include <Wire.h>
#include <MPU6050.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(9,10);
MPU6050 sensor ;
int16_t ax, ay, az ;
int16_t gx, gy, gz ;
int hotwire = 8;


#include <TinyGPS.h>
float lat = 28.721356,lon = 77.141240; 
SoftwareSerial gpsSerial(5,4);//rx,tx

TinyGPS gps; // create gps object
void setup ( )
{ 
pinMode(hotwire, INPUT);  
pinMode(LED_BUILTIN, OUTPUT);
Wire.begin ( );
Serial.begin  (9600);
mySerial.begin(9600); 
Serial.println  ( "Initializing the sensor" ); 
sensor.initialize( ); 
Serial.println (sensor.testConnection ( ) ? "Successfully Connected" : "Connection failed"); 
delay (1000); 
Serial.println ( "Taking Values from the sensor" );
delay (1000);

Serial.println("The GPS Received Signal:");
//gpsSerial.begin(9600); // connect gps sensor


}




void loop ( ) 
{
  int hotwirestate = digitalRead(hotwire);

digitalWrite(LED_BUILTIN, LOW);
sensor.getMotion6 (&ax, &ay, &az, &gx, &gy, &gz);

ax = map (ax, -17000, 17000, 0, 90) ;

Serial.println (ax);
if(ax<65)
{
  Serial.println("CRASH HAS OCCURED, PLEASE MARK YOURSELF SAFE BY TURNING OFF YOUR BIKE IN TWO MINUTES OR A DISTRESS CALL WILL BE SENT");
  digitalWrite(LED_BUILTIN, HIGH);
  

  if(hotwirestate == HIGH)
  {
  Serial.println("Sending message");
  Serial.print("THE RIDER HAS MET WITH AN ACCIDENT AT COORDINATES,\nLAT: ");
  Serial.println(lat);
  Serial.print("LON: ");
  Serial.println(lon);
  Serial.println("Track the user using this link: https://maps.app.goo.gl/kHgkwUuh1rSRezLE3");
  Serial.println("Message sent to Police Station, Hospital and Relative");
  SendMessage();
  delay (30000);
  }




}
}

void SendMessage()
{

  mySerial.println("AT+CMGF=1");    
  delay(1000);  
  mySerial.println("AT+CMGS=\"+919354493228\"\r"); 
  delay(1000);
  mySerial.println("THE RIDER HAS MET WITH AN ACCIDENT");
  delay(100);
  mySerial.println("HERE IS THE LOCATION WHERE HE MET WITH AN ACCIDENT");
  delay(100);
  location();
  String latitude = String(lat,6);
  String longitude = String(lon,6);
  mySerial.println("Lat: "+ latitude+"; Long: "+longitude);
  delay(100);
  mySerial.println((char)26);
  delay(1000);
}
void location(){



    while(gpsSerial.available()){ 
    if(gps.encode(gpsSerial.read()))
    { 
    gps.f_get_position(&lat,&lon); 
    
    Serial.print("Position: ");
    Serial.print("Latitude:");
    Serial.print(lat,6);
    Serial.print(";");
    Serial.print("Longitude:");
    Serial.println(lon,6); 
    
    Serial.print(lat);
    Serial.print(" ");
    
   }
}
  
 
  
 
  

 // }
