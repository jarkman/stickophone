


void startGesture( int gesture )
{
   #ifdef DO_LOGGING
    Serial.print ("startGesture ");
    Serial.println (gesture);
   #endif
    
  currentGesture = gesture;

  clearPath();
  // hard-coded coordinates for the gestures
 
  switch( currentGesture )
  {
    case GESTURE_NOBODY_HOME:
      Serial.println ("GESTURE_NOBODY_HOME");
      // static, leant back

      setSpeed(0.5);
      addPoint(0,-30);
      addPoint(0,-31);
      addPoint(0,-29);
      someoneIsHome = 0;

      break;
      
  case GESTURE_SOMEBODY_HOME:
      // figure-8
      Serial.println ("GESTURE_SOMEBODY_HOME");

      setSpeed(0.1);

      int r1;
      r1 = (int)random(10);
      for (int i = 0; i <= r1; i++){
         long r2 = random(2);
         long r3 = random(5);
         addPoint(r2,r3);
         if(delayMotion > 0){
            for (int j = 0; j <= delayMotion; j++){
               addPoint(r2,r3);
            }
         }         
      }
      someoneIsHome == 1;
/*
        addPoint(0,0);
        addPoint(5,2);
        addPoint(5,-2);
        addPoint(0,0);
        addPoint(-5,2);
        addPoint(-5,-2);
      
      addPoint(0,0);
      addPoint(10,5);
      addPoint(10,-5);
      addPoint(0,0);
      addPoint(-10,5);
      addPoint(-10,-5);
*/
      someoneIsHome = 1;
      break;
      
  case GESTURE_WANT_TO_SPEAK:
      Serial.println ("GESTURE_WANT_TO_SPEAK");

      setSpeed(1.5);
      someoneIsHome == 1;
      addPoint(0,30);
      addPoint(-30,30);
      addPoint(30,30);
      addPoint(-30,30);
      addPoint(30,30);
      addPoint(0,30);
     
      break;
      
  case GESTURE_OI:
      Serial.println ("GESTURE_OI");

      setSpeed(3.0);
      someoneIsHome == 1;
      addPoint(0,85);
      addPoint(0,70);
      addPoint(0,85);
      addPoint(0,70);
      addPoint(0,85);
      break;
      
   case GESTURE_HELLO:
     Serial.println ("GESTURE_HELLO");

     setSpeed(1.0);
     someoneIsHome == 1;
     addPoint(0,20);
     addPoint(20,20);
     addPoint(-20,20);
     addPoint(20,20);
     addPoint(-20,20);
     addPoint(0,20);
      break;


 case GESTURE_LEAVING:
     Serial.println ("GESTURE_LEAVING");

     setSpeed(1.0);

     
     addPoint(0,-20);
     addPoint(20,-20);
     addPoint(-20,-20);
     addPoint(20,-20);
     addPoint(-20,-20);
     addPoint(0,-20);
      someoneIsHome = 0;

      break;
      
  case GESTURE_BORED:
     Serial.println ("GESTURE_BORED");

     setSpeed(0.1);

     addPoint(0,-10);
     addPoint(0,-5);
     addPoint(0,-30);
//     addPoint(0,-10);
  //   addPoint(0,-30);
     //addPoint(0,-5);
     someoneIsHome = 2;
  
     break;

  case GESTURE_STAY_BORED:
     Serial.println ("GESTURE_STAY_BORED");

     setSpeed(0.1);

      if(delayMotion > 0){
         delay(delayMotion);
      }

      int r4;
      r4 = (int)random(3);
      for (int i = 0; i <= r4; i++){
         long r5 = random(24,30);
         addPoint(0,-r5);
         if(delayMotion > 0){
            for (int j = 0; j <= delayMotion; j++){
               addPoint(0,-r5);
            }
         } 
      }

     someoneIsHome = 2;
  
     break;
      
  case GESTURE_INTERESTED:
     Serial.println ("GESTURE_INTERESTED");

     setSpeed(1.5);

     someoneIsHome == 1;
     addPoint(0,30);
     addPoint(0,-5);
     
     break;
      
  case GESTURE_LOOKING_ROUND:
      Serial.println ("GESTURE_LOOKING_ROUND");

      setSpeed(1.5);

     
     addPoint(-60,0);
     addPoint(-60,40);
     addPoint(60,40);
     addPoint(-60,40);
     addPoint(60,40);
     addPoint(60,0);
     someoneIsHome == 1;
     break;

  case GESTURE_REVOLVE_ALL_LEFT:
     Serial.println ("GESTURE_REVOLVE_ALL_LEFT");
     //stepper1.moveTo(-200);
     stepper1.moveTo(stepper1.currentPosition() - 200);
     break;

  case GESTURE_REVOLVE_ALL_RIGHT:
     Serial.println ("GESTURE_REVOLVE_ALL_RIGHT");
     stepper1.moveTo(stepper1.currentPosition() + 200);
     break;

   default:
     #ifdef DO_LOGGING
      Serial.print ("bad gesture ");
      Serial.println (gesture);
     #endif
     break;
      
  }

  gestureStartMillis = millis();
  startPath();
}

