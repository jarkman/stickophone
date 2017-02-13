


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
      // static, leant back

      setSpeed(0.5);
      addPoint(0,-30);
      addPoint(0,-31);
      addPoint(0,-29);

      break;
      
  case GESTURE_SOMEBODY_HOME:
      // figure-8

      setSpeed(1.0);
      
      addPoint(0,0);
      addPoint(10,5);
      addPoint(10,-5);
      addPoint(0,0);
      addPoint(-10,5);
      addPoint(-10,-5);

      break;
      
  case GESTURE_WANT_TO_SPEAK:

      setSpeed(1.5);
      
      addPoint(0,30);
      addPoint(-30,30);
      addPoint(30,30);
      addPoint(-30,30);
      addPoint(30,30);
      addPoint(0,30);
     
      break;
      
  case GESTURE_OI:

      setSpeed(3.0);
      
      addPoint(0,85);
      addPoint(0,70);
      addPoint(0,85);
      addPoint(0,70);
      addPoint(0,85);
      break;
      
   case GESTURE_HELLO:

     setSpeed(1.0);
     
     addPoint(0,20);
     addPoint(20,20);
     addPoint(-20,20);
     addPoint(20,20);
     addPoint(-20,20);
     addPoint(0,20);
      break;


 case GESTURE_LEAVING:

      setSpeed(1.0);

     
     addPoint(0,-20);
     addPoint(20,-20);
     addPoint(-20,-20);
     addPoint(20,-20);
     addPoint(-20,-20);
     addPoint(0,-20);

      break;
      
  case GESTURE_BORED:
      setSpeed(0.5);

     
     addPoint(0,-20);
     addPoint(0,-5);
     addPoint(0,-30);
     addPoint(0,-10);
     addPoint(0,-30);
     addPoint(0,-5);
     
     break;
      
  case GESTURE_INTERESTED:
      setSpeed(1.5);

     
     addPoint(0,30);
     addPoint(0,-5);
     
     break;
      
  case GESTURE_LOOKING_ROUND:
      setSpeed(1.5);

     
     addPoint(-60,0);
     addPoint(-60,40);
     addPoint(60,40);
     addPoint(-60,40);
     addPoint(60,40);
     addPoint(60,0);
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

