//#include <NewSoftSerial.h>


#include <Servo.h> 
 
#define  DO_LOGGING


int numPoints = 0;
boolean pathWorking = true;

boolean motionWorking = false;

float max_servo_speed = 0.0;
float sum_servo_speed = 0.0;
float num_servo_speed = 1.0;

void moveTo( float x0, float y0, boolean s = true );
boolean addPoint( int x, int y );

#define GESTURE_NOBODY_HOME 0
#define GESTURE_SOMEBODY_HOME 1
#define GESTURE_WANT_TO_SPEAK 2
#define GESTURE_OI 3
#define GESTURE_HELLO 4

int currentGesture = -1;
boolean someoneIsHome = false;
long gestureStartMillis = 0;
long eventStartMillis = 0;


void setup() 
{ 
  
  
  #ifdef DO_LOGGING
  Serial.begin (9600); // for debugging

  Serial.print ("setup\n");
  #endif

  setupPosition();
  setupMotion();

  turnOnServos();

  startGesture(GESTURE_NOBODY_HOME);
}




float z = 0;
boolean wasOff = false;


void loop() 
{ 

  int newGesture = checkForEvents(); // change this function so it delivers a gesture number when the person on the call want to perform a gesture
  
  boolean done = ! loopPath();

   if( newGesture != -1 )
   {
      // Serial.println("a");
      startGesture(newGesture);  // something kicked off a new gesture, we'll just do it once then go back to repeating GESTURE_SOMEBODY_HOME
   }
   else if( done )
   { 
      // finished a thing, go to a neutral gesture
      if( someoneIsHome )
      {
          Serial.println("nobody home");
        startGesture(GESTURE_NOBODY_HOME);
      }
      else
      {
        
          Serial.println("soembody home");
        startGesture(GESTURE_SOMEBODY_HOME);
      }
   }
   // else just keep running the current motion
      
   loopMotion();   
}


int eventGesture = GESTURE_WANT_TO_SPEAK - 1;

int checkForEvents()
{
  // see if something happened that mean we ought to start a gesture, for now just use a timer

  long now = millis();

  if( now - eventStartMillis > 10000 )  // run through the gesture, one every 10 secs
  {
    eventStartMillis = now;

    eventGesture = eventGesture + 1;
    
    if( eventGesture > GESTURE_HELLO )
      eventGesture = GESTURE_WANT_TO_SPEAK;
    
    
       #ifdef DO_LOGGING
         Serial.print ("next gesture ");
         Serial.println (eventGesture);
      #endif
      return eventGesture;
    

    
  }

  return -1;
}


