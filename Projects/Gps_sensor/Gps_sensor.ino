#include <TinyGPS++.h>        // include TinyGPS++ library
#include <TimeLib.h>          // include Time library
#include <SoftwareSerial.h>   // include Software serial library
#include <ESP8266WiFi.h>      // include WiFi library
//***********************************************************************
const char* ssid = "Fedora_Link_2G";                          // replace with your SSID
const char* password = "Muhammed1984$";// and Password
#define time_offset   10800                         // define a clock offset of 10800 seconds (3 hours) ==> UTC + 3
static const double WAYPOINT_LAT = 51.508131, WAYPOINT_LON = -0.128002; // change the waypoint coordinates
// variables
char Time[]  = "00:00:00";
char Date[]  = "00-00-2000";
byte last_second, Second, Minute, Hour, Day, Month;
int Year;
String Longitude, Latitude, alt, sat, fixage, speed1, course1, header;
unsigned long distanceKmToWaypoint;
double courseToWaypoint;

WiFiServer server(80);                              // set web server port number to 80
TinyGPSPlus gps;                                    // The TinyGPS++ object
SoftwareSerial SoftSerial(4, 5);                    // configure SoftSerial library (RX pin, TX pin)

void setup()
{
  Serial.begin(9600);      // initialise serial communication at 9600 bps
  SoftSerial.begin(9600);  // initialize software serial at 9600 bps
  Serial.println();         // print empty line
  Serial.print("Connecting to "); // print text in Serial Monitor
  Serial.println(ssid);           // print text in Serial Monitor
  WiFi.begin(ssid, password);     // connect to Wi-Fi network with SSID and password
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  // print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
  server.begin();
            
}

void loop()
{
  while (SoftSerial.available() > 0)
  {
    if (gps.encode(SoftSerial.read()))
    {
      // get time from GPS module
      if (gps.time.isValid())
      {
        Minute = gps.time.minute();
        Second = gps.time.second();
        Hour   = gps.time.hour();
      }
      // get date drom GPS module
      if (gps.date.isValid())
      {
        Day   = gps.date.day();
        Month = gps.date.month();
        Year  = gps.date.year();
      }
      if (gps.location.isValid())
      {
        Longitude = String(gps.location.lng(), 7);
        Latitude = String(gps.location.lat(), 7);

          Serial.println(Latitude);
          Serial.println(Longitude);

  
      }
      if (gps.altitude.isValid())
      {
        alt = String(gps.altitude.meters(), 2);
      }
      if (gps.satellites.isValid())
      {
        sat = String(gps.satellites.value());
      }
      if (gps.location.isValid())
      {
        fixage = "OK";
      }
      if (gps.speed.isValid())
      {
        speed1 = String(gps.speed.kmph(), 2);
      }
      if (gps.course.isValid())
      {
        course1 = String(gps.course.deg(), 2);
      }
      if (gps.location.isValid())
      {
        distanceKmToWaypoint =
          (unsigned long)TinyGPSPlus::distanceBetween(
            gps.location.lat(),
            gps.location.lng(),
            WAYPOINT_LAT,
            WAYPOINT_LON) / 1000;
        courseToWaypoint =
          TinyGPSPlus::courseTo(
            gps.location.lat(),
            gps.location.lng(),
            WAYPOINT_LAT,
            WAYPOINT_LON);
      }
      if (last_second != gps.time.second()) // if time has changed
      {
        last_second = gps.time.second();        
        setTime(Hour, Minute, Second, Day, Month, Year);// set current UTC time        
        adjustTime(time_offset);                        // add the offset to get local time
                                                        // update time array
        Time[0]  = hour()   / 10 + '0';
        Time[1]  = hour()   % 10 + '0';
        Time[3]  = minute() / 10 + '0';
        Time[4] = minute() % 10 + '0';
        Time[6] = second() / 10 + '0';
        Time[7] = second() % 10 + '0';
                                                         // update date array
        Date[0]  =  day()   / 10 + '0';
        Date[1]  =  day()   % 10 + '0';
        Date[3]  =  month() / 10 + '0';
        Date[4] =  month() % 10 + '0';
        Date[8] = (year()  / 10) % 10 + '0';
        Date[9] =  year()  % 10 + '0';       
      }
    }
    WiFiClient client = server.available();   // Listen for incoming clients
    if (client) {                             // If a new client connects,
      Serial.println("New Client.");          // print a message out in the serial port
      String currentLine = "";                // make a String to hold incoming data from the client
      while (client.connected()) {            // loop while the client's connected
        if (client.available()) {             // if there's bytes to read from the client,
          char c = client.read();             // read a byte, then
          Serial.write(c);                    // print it out the serial monitor
          header += c;
          if (c == '\n') {                    // if the byte is a newline character
            // if the current line is blank, you got two newline characters in a row.
            // that's the end of the client HTTP request, so send a response:
            if (currentLine.length() == 0) {
              // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
              // and a content-type so the client knows what's coming, then a blank line:
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println("Connection: close");
              client.println();
              // Display the HTML web page
              client.println("<!DOCTYPE html><html>");
              client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
              client.println("<link rel=\"icon\" href=\"data:,\">");
              client.println("<title>GPS Web Server</title>");
              client.println("<style>a:link {text-decoration: none;} table, th, td {border: 1px solid black;} #map {display: block; background-color: grey; margin-left: auto; margin-right: auto; height: 400px; width: 600px;} </style>");
              client.println("<body><p ALIGN=CENTER style=""font-size:120%;""><b>GPS Web Server</b></p> <table ALIGN=CENTER style=width:50%>");
              client.println("<tr><th>Date</th><td ALIGN=CENTER >");
              client.println(Date);
              client.println("</td></tr>");
              client.println("<tr><th>Local time</th><td ALIGN=CENTER >");
              client.println(Time);
              client.println("</td></tr>");
              client.println("<tr><th>Latitude</th><td ALIGN=CENTER >");
              client.println(Latitude);
              client.println("</td></tr>");
              client.println("<tr><th>Longitude</th><td ALIGN=CENTER >");
              client.println(Longitude);
              client.println("</td></tr>");
              client.println("<tr><th>Altitude, m</th><td ALIGN=CENTER >");
              client.println(alt);
              client.println("</td></tr>");
              client.println("<tr><th>Satellites</th><td ALIGN=CENTER >");
              client.println(sat);
              client.println("</td></tr>");
              client.println("<tr><th>Fix age</th><td ALIGN=CENTER >");
              client.println(fixage);
              client.println("</td></tr>");
              client.println("<tr><th>Speed,km/h</th><td ALIGN=CENTER >");
              client.println(speed1);
              client.println("</td></tr>");
              client.println("<tr><th>Course,deg</th><td ALIGN=CENTER >");
              client.println(course1);
              client.println("</td></tr>");
              client.println("<tr><th>Distance to Waypoint, km</th><td ALIGN=CENTER >");
              client.println(distanceKmToWaypoint);
              client.println("</td></tr>");
              client.println("<tr><th>Heading to Waypoint, km</th><td ALIGN=CENTER >");
              client.println(courseToWaypoint);
              client.println("</td></tr></table>");
              client.println("<p align=center><a style=""color:RED;"" href=""http://maps.google.com/maps?&z=19&mrt=yp&t=k&q="+Latitude+"+"+Longitude+"&ll="+Latitude+"+"+Longitude+""">Click here</a> to see your location on Google maps.</p>");
              client.println("</body></html>");

              // The HTTP response ends with another blank line
              client.println();
              // Break out of the while loop
              break;
            } else { // if you got a newline, then clear currentLine
              currentLine = "";
            }
          } else if (c != '\r') {  // if you got anything else but a carriage return character,
            currentLine += c;      // add it to the end of the currentLine
          }
        }
      }
      // Clear the header variable
      header = "";
      // Close the connection
      client.stop();
      Serial.println("Client disconnected.");
      Serial.println("");

    }
  }
}
