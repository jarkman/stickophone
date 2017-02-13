


void startGesture( int gesture )
{
  currentGesture = gesture;

  clearPath();

  switch( currentGesture )
  {
    case GESTURE_NOBODY_HOME:
      // static, leant back
      addPoint(0,-30);
      break;
      
  case GESTURE_SOMEBODY_HOME:
      // figure-8
      addPoint(0,0);
      addPoint(20,10);
      addPoint(20,-10);
      addPoint(0,0);
      addPoint(-20,10);
      addPoint(20,-10);

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
      addPoint(0,90);
      addPoint(0,70);
      addPoint(0,90);
      addPoint(0,70);
      addPoint(0,90);
      break;
      
   case GESTURE_HELLO:
      addPoint(0,20);
     addPoint(20,20);
     addPoint(-20,20);
     addPoint(20,20);
     addPoint(-20,20);
     addPoint(0,20);
      break;
      
  }

  gestureStartMillis = millis();
  startPath();
}

