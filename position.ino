
// position.pde


 
// limits of servo motion for our rig
int minServoPos = 0;
int maxServoPos = 180;


#define STATUS_LED 13 // lights up for bad positions



Servo s0;
Servo s1;


boolean servosAttached = false;


 boolean transformToServoAngle( float &theta );
void servoWriteFloat( Servo *s, float angle);
void servoWriteCalibrated( Servo *s, float angle);
boolean uSForAngle( float angle, int*result) ;





void setupPosition()
{
   pinMode(STATUS_LED, OUTPUT);
   
  turnOnServos();
   
  
   servoWriteCalibrated( &s0, 0 );
   servoWriteCalibrated( &s1, 0 );
   
   delay(2000); 
   

  
}

void turnOnServos()
{
  if( ! servosAttached )
  {
   s0.attach(8);
   s1.attach(9);
  
  }
  
   servosAttached = true;
}
void turnOffServos()
{
  if( servosAttached )
  {
  s0.detach();
  s1.detach();

  }
  servosAttached = false;
  
}

int goTo( float x0, float y0 ) // 0 is vertical, range is -90 to +90
{
   float theta1;
   float theta2;
   float theta3;
   
   static float last_theta1;
   static float last_theta2;
   
  
    static float tLast = 0;
   
   
     
  theta1 = x0;
  theta2 = y0;
  
 
  /*
   #ifdef DO_LOGGING
    Serial.print ("Pos: ");
    Serial.print (x0);
    Serial.print (", ");
    Serial.print (y0);
   
    Serial.print ("\n");
     #endif
   */
  
  boolean success = true; 
  int u1;
  int u2;
  
  
   success &=  uSForAngle( theta1, &u1);
   success &=  uSForAngle( theta2, &u2);
    
 
  if( ! success )
  {
  #ifdef DO_LOGGING
    Serial.print ("Unreachable servo angle\n");
  #endif
   return 0;
  }
  
  digitalWrite(STATUS_LED,! success);
  
  s0.writeMicroseconds( u1 );
  s1.writeMicroseconds( u2 );

  float tNow = millis();

  last_theta1 = theta1;
  last_theta2 = theta2;
  
  tLast = tNow;
  return 1;
}

  


void servoWriteCalibrated( Servo *s, float angle)
{
  int uSecs;
  if( uSForAngle( angle, &uSecs))
    s->writeMicroseconds(uSecs);
}

// Use writeMicroseconds instead of write() to get more servo resolution, copy conversion formula from Arduino Servo lib source
// This gets us something like ten times the resolution, so we get much smoother motion.
// This version is uncalibrated and is replaced by servoWriteCalibrated above.

void servoWriteFloat( Servo *s, float angle)
{  

  float servoCal = -10.0;
  
  angle -= servoCal;
  
  if(angle < 0) 
    angle = 0;
    
    
  if(angle > 180) 
    angle = 180;
    
   int uS = MIN_PULSE_WIDTH + angle * ( MAX_PULSE_WIDTH - MIN_PULSE_WIDTH ) / 180.0;      

  s->writeMicroseconds(uS);
}


boolean uSForAngle( float angle, int*result) // expect angle  in geometry frame, 0 is vertical, range is -90 to +90
{  


   int uS = MIN_PULSE_WIDTH + (angle+90.0) * ( MAX_PULSE_WIDTH - MIN_PULSE_WIDTH ) / 180.0;
   
  if( uS < MIN_PULSE_WIDTH  )
    return false;
    
  if( uS > MAX_PULSE_WIDTH  )
    return false;

  *result = uS;
  return true;
  
}



  

