


void startGesture( int gesture )
{
   #ifdef DO_LOGGING
    Serial.print ("startGesture ");
    Serial.println (gesture);
   #endif
    
  currentGesture = gesture;

  clearPath();

  // hard-coded coordinates for the gestures
  // we could also change max_speed here so that each gesture specified its own speed
  
  switch( currentGesture )
  {
    case GESTURE_NOBODY_HOME:
      // static, leant back
      addPoint(0,-30);
      addPoint(0,-31);
      addPoint(0,-29);

      break;
      
  case GESTURE_SOMEBODY_HOME:
      // figure-8
      addPoint(0,0);
      addPoint(10,5);
      addPoint(10,-5);
      addPoint(0,0);
      addPoint(-10,5);
      addPoint(-10,-5);

      break;
      
  case GESTURE_WANT_TO_SPEAK:
      addPoint(0,30);
      addPoint(-30,30);
      addPoint(30,30);
      addPoint(-30,30);
      addPoint(30,30);
      addPoint(0,30);
     
      break;
      
  case GESTURE_OI:
      addPoint(0,85);
      addPoint(0,70);
      addPoint(0,85);
      addPoint(0,70);
      addPoint(0,85);
      break;
      
   case GESTURE_HELLO:
      addPoint(0,20);
     addPoint(20,20);
     addPoint(-20,20);
     addPoint(20,20);
     addPoint(-20,20);
     addPoint(0,20);
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

