void setup(){
    
    Spark.function("my-main", myMain);  
    
    //RGB.control(true);
    RGB.color(255, 255, 255);  //cyan
    RGB.brightness(255);    // 1=very low light, 255 = max
    pinMode(A0, INPUT);
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    
    pinMode(D3, OUTPUT);
    pinMode(D4, OUTPUT);
    pinMode(D5, OUTPUT);
    
    pinMode(D6, OUTPUT);
}

void loop(){
    
    if (analogRead(A0) >200){
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

    // Block sets pinNumber for digital 0-7 or analog 10-17 from the number
    int mySetWrite = 0;
    int pinNumber = myCode.charAt(1) - '0';
    if (pinNumber< 0 || pinNumber >7) return -1; 
    if (myCode.startsWith("A")){pinNumber = pinNumber+10;}  //+10 is for analog numbers
    
    String  myActivity = myCode.substring(3,7);     // take 4 characters starting at the 3rd.
     
    String myOptional = myCode.substring(8);      
    if(myOptional == "HIGH") {mySetWrite = 1;}
        else if(myOptional == "LOW") {mySetWrite = 0; }
            else if(myOptional == "ON") {mySetWrite = 1;}
                else if(myOptional == "OFF") {mySetWrite = 0; }
                   else {mySetWrite = myOptional.toInt();  }  // sets  write value
   
    if (pinNumber < 9) {   // digital pins activated
   
        if (myActivity == "READ"){    //digital read
            pinMode(pinNumber, INPUT_PULLDOWN);
            return digitalRead(pinNumber);
        }
        
        if (myActivity == "SEND"){    //digital write
            pinMode(pinNumber, OUTPUT);
            digitalWrite(pinNumber, mySetWrite);
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
