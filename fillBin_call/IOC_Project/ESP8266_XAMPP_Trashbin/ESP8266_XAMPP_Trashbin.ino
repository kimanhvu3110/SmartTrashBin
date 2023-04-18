#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include "HC_SR.h" 

const char* ssid = "MINH";
const char* password = "123456789";
String ipAddress = "192.168.177.35"; 
const int httpPort = 8080;

const unsigned long eventInterval = 5000;
unsigned long previousTime = 0;

String UserID;
String weight1;
String weight2;

WiFiClient client;
void setup() {
    Serial.println("============ Setup ============");  
    Serial.begin(115200);
    delay(100); 
    // ------------- Connect to WiFi network
    Serial.print("Connecting to ");
    Serial.println(ssid);
  
    WiFi.begin(ssid, password); 
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected");
 
    // Make GET request
    Serial.println("Making GET request..."); 
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }
}

void doGet(String get_command){ 
    Serial.println("~~~~~~~ doGet ~~~~~~~");
    //a.Connect
    if (!client.connect(ipAddress, httpPort)) {
        Serial.println("Connection failed");
        return;
    } 
    //b.doGet 
    client.print(get_command);
    //delay(500);
    String host = "Host: " + ipAddress + "\r\n";
    client.print(host); 
    //c.Close Connection
    client.print("Connection: close\r\n\r\n");
    while (client.connected()) {
        String line = client.readStringUntil('\n');
        Serial.println(line);
    } 
    Serial.print("get_command: "); Serial.println(get_command);
    Serial.println("Closing connection"); 
    Serial.println("~~~~~~~ doGet ~~~~~~~");
}
 
void get_data_esp(){ 
    Serial.println("~~~~~~~ get_data_esp ~~~~~~~");
    if (Serial.available() > 0) {    
        String received = Serial.readString();       
        //Code to split each elements from received string
        int first = 0;
        int last = 0;
        int index = 0;
        while (last >= 0) {
            last = received.indexOf('/', first);
            if (last >= 0) {
                String part = received.substring(first, last);
//                Serial.println(part);Serial.print(",");
                if (index == 0) {
                    UserID = part;
                } else if (index == 1) {
                    weight1 = part;
                } 
                first = last + 1;
                index++;
            }
        } 
        
        weight2 = received.substring(first);
        delay(1000);
//        Serial.print("UserID: ");
        Serial.println(UserID); 
//        Serial.print("weight1: ");
        Serial.println(weight1);  
//        Serial.print("weight2: ");
        Serial.println(weight2); 
        String doGet_history2 = String("GET /IOC_Project/update_history.php?")
                    +  String("&UserID=") + String(UserID)
                    +  String("&OrganicWaste_kg=") + String(weight1) 
                    +  String("&InorganicWaste_kg=") + String(weight2) 
                    +  " HTTP/1.1\r\n";     
        doGet(doGet_history2);
    }
} 

void update_fillLevel(){ 
    float bin_height = 26.00;
    float level1 = trash_level(trigPin, echoPin);
    float fill_percentage = 100-((level1/bin_height)*100);
    
    //Serial.print("level1: ");Serial.println(level1); 
    Serial.print("fill_percentage: ");Serial.println(fill_percentage); 
    
    // Update fill level table // 
    String doGet_fillLevel = String("GET /IOC_Project/update_Fill_Level.php?")
                    +  String("&BinID=") + String("1")
                    +  String("&Fill_Level=") + String(fill_percentage) //fill_percentage
                    +  " HTTP/1.1\r\n";                
    doGet(doGet_fillLevel);       
    // Update fill pct table // -- show avg of month of BinID '1'
    String doGet_fill_percentage = String("GET /IOC_Project/update_fill_pct.php?") 
                    +  String("&BinID=") + String("1")
                    +  String("&fill_percentage=") + String(fill_percentage) 
                    +  " HTTP/1.1\r\n";                
    doGet(doGet_fill_percentage);  
}


  
void loop(){  
    update_fillLevel();
    get_data_esp();     
    Serial.println("########################################################################");  
    delay(5000);
}



/************************
Loop: Every 5 sec,
- update_fillLevel() |delay: 0
- get_data_esp |delay: 0
***********************/
