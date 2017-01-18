

//please do not use this photon. it is currently being used for a project.



void setup(){
    
    Spark.function("my-main", myMain);  
    
    //PUT YOUR SETUP CODE HERE. Note: Only three more functions allowed!
    // test everything using the return int from a function!
      
  
    //RGB.control(true);
    RGB.color(255, 255, 255);  //cyan
    RGB.brightness(255);    // 1=very low light, 255 = max
    pinMode(A1, INPUT);
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    
    pinMode(D3, OUTPUT);
    pinMode(D4, OUTPUT);
    pinMode(D5, OUTPUT);
    
    pinMode(D6, OUTPUT);


}

void loop(){
    
    if (analogRead(A1) >200){
        digitalWrite(D6, HIGH);
        Particle.publish("streetlight-on"); 
        delay(400);
    } else {
        digitalWrite(D6, LOW);
        Particle.publish("streetlight-off"); 
    }
    
    

}

int myMain(String myCode) {
    
    myCode.toUpperCase();           // set argument to uppercase--remove for better security
    
    // used send instead of write since I needed it to be 4 characters long.
    

    // d7-send-1 or d7-send-high or d7-send-on    to turn on D7
    // d7-send-0   or d7-send-low  or d7-send-off to tuurn off D7
    // d5-read    read D5

    // a0-send-0     turn A0 off
    // a0-send-255   turn A0 maximum
    // a1-read       read A1
     
    // Block sets pinNumber for digital 0-7 or analog 10-17 from the number
    int mySetWrite = 0;
    int pinNumber = myCode.charAt(1) - '0';
    if (pinNumber< 0 || pinNumber >7) return -1; 
    if (myCode.startsWith("A")){pinNumber = pinNumber+10;}  //+10 is for analog numbers
    
    
  
    String  myActivity = myCode.substring(3,7);     // take 4 characters starting at the 3rd.
     
    
    //Following sets the 7 and on characters to integers
    String myOptional = myCode.substring(8);      
    if(myOptional == "HIGH") {mySetWrite = 1;}
        else if(myOptional == "LOW") {mySetWrite = 0; }
            else if(myOptional == "ON") {mySetWrite = 1;}
                else if(myOptional == "OFF") {mySetWrite = 0; }
                   else {mySetWrite = myOptional.toInt();  }  // sets  write value
    
    
    // myCode parsing complete
    
    
    if (pinNumber < 9) {   // digital pins activated
   
        if (myActivity == "READ"){    //digital read
            digitalWrite(D2, HIGH);
            digitalWrite(D3, HIGH);
            digitalWrite(D3, LOW);
            digitalWrite(D4, HIGH);
            delay(900);
            digitalWrite(D4, LOW);
            digitalWrite(D5, HIGH);
            delay(500);
            digitalWrite(D2, LOW);
            digitalWrite(D0, HIGH);
            return 1;
        }
        
        if (myActivity == "SEND"){    //digital write
        digitalWrite(D5, HIGH);
        digitalWrite(D0, HIGH);
        digitalWrite(D0, LOW);
        digitalWrite(D1, HIGH);
        delay(900);
        digitalWrite(D1, LOW);
        digitalWrite(D2, HIGH);
        delay(500);
        digitalWrite(D5, LOW);
        digitalWrite(D3, HIGH);
        
            return mySetWrite;
        }        
        
        
    }  else {      // analog pins activated
    
        if (myActivity == "READ"){    //Analog read
            pinMode(pinNumber, INPUT_PULLUP); // sets unknown to max 4095 analog read
            return analogRead(pinNumber);
        }
        
        if (myActivity == "SEND"){    //Analog Write
            pinMode(pinNumber, OUTPUT);
            analogWrite(pinNumber,  mySetWrite);
            return mySetWrite;
        }        
      }
    
}
