#include <SoftwareSerial.h>

SoftwareSerial mySerial(4, 5); // RX, TX of arduino serial communication 

void setup() {
   Serial.begin(115200);  // begin Serial monitor
   mySerial.begin(9600); // Serial of OPENMV
   pinMode(LED_BUILTIN, OUTPUT); // LED PIN
}

void loop(){
   char buffer [63+1];  // get chars from buffer
   int max_len = 63;   // max length of characters 
   buffer[0] = 0x00;  // conver bytes
   getline(buffer, max_len);  // get the value , and max length
   Serial.println(buffer); // print out the value
   
   digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
   
   if (buffer[0] == 'H' ) {
     digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
     delay(500);
     digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
     delay(500);

     digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
     delay(500);
     digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
     delay(500);
     delay(5000);
   }
   
   if (buffer[0] == 'S') {
     digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
     delay(500);
     digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
     delay(500);
     delay(5000);
   }
}

//get values from bytes 
void getline(char *buffer, int max_len)
{
   uint8_t idx = 0;
   char c;
   do
   {
     if(idx >= max_len)
       return;
     buffer[idx] = '0'; // NEED THIS for Cleanup

     c = mySerial.read();
     buffer[idx++] = c;
   }
   while (c != '\n' && c != '\r');
   if(idx >= max_len) return;
   buffer[idx] = 0;
}
