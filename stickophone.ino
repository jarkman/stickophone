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

  int newGesture = checkForEvents();
  
  boolean done = ! loopPath();

   if( newGesture != -1 )
   {
      startGesture(newGesture);
   }
   else if( done )
   { 
      // finished a thing, go to a neutral gesture
      if( someoneIsHome )
        startGesture(GESTURE_NOBODY_HOME);
      else
        startGesture(GESTURE_SOMEBODY_HOME);
   }
      
   loopMotion();   
}



int checkForEvents()
{
  // see if something happened that mean we ought to start a gesture, for now just use a timer

  long now = millis();

  if( now - eventStartMillis > 10000 )  // run through the gesture, one every 10 secs
  {
    eventStartMillis = now;

    if( ! someoneIsHome )
    {
      someoneIsHome = true;
      return -1;
    }

    int newGesture = currentGesture + 1;
    if( newGesture <= GESTURE_HELLO )
    {
      return newGesture;
    }
    else
    {
      someoneIsHome = false;
      return -1;
    }
    
  }

}


