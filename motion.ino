// motion.pde

// manages motion control for a 2-servo stick
// implements maximum speed and maximum acceleration limits
// decelerates to a stop at the end of each motion



float currX = 0;
float currY = 0;

float currT = millis();
float paperDelta = 0;

float targetX = 0;
float targetY = 0;

boolean stopAtEnd = true;

float maxSpeed = 0.050; // mm / millisec - 0.600 is good
float acceleration = 0.001; // mm / millisec / millisec - 0.002 keeps the current rig pretty calm, 0.004 starts to be wobbly

float minSpeed = 0.001;
float currSpeed= 0;


float totalDistance = 0;
int  totalSteps =0; 
int  totalMillis  =0;

void setupMotion()
{
  currX = 0;
  currY = 0;

  currT = millis();
  currSpeed = 0;

  targetX = 0;
  targetY = 0;

 
  motionWorking = false;
}

boolean loopMotion() // move one increment towards targetXYZ at constant speed
{
  float dx,dy, dt, scale, distance, now;
  
   
   if( ! motionWorking )
    return false;
  
   
  dx = targetX - currX;
  dy = targetY - currY;

  
  distance = sqrt( (dx*dx) + (dy*dy));
  
 
  if( distance < 1 ) // arrived
  {
   motionWorking = false; 
 
    return false;
  }

 
  now = millis();
  
  dt =  now - currT;
  
   if( stopAtEnd && inBrakingZone(distance))
  {
    currSpeed -= acceleration * dt;
    if( currSpeed < minSpeed )
      currSpeed = minSpeed;
  }
  else if( currSpeed < maxSpeed )
  {
    currSpeed += acceleration * dt;
    
    if( currSpeed > maxSpeed )
      currSpeed = maxSpeed;
  }
  
  scale = dt * currSpeed / distance;
  
  dx = scale * dx;
  dy = scale * dy;

  
  currX += dx;
  currY += dy;

   

    
  currT = now;
  
  
  totalDistance +=  sqrt( dx*dx + dy*dy );
  totalSteps ++; 
  totalMillis += dt;
  
  #ifdef DO_LOGGING
  /*
    Serial.print ("goTo ");
    Serial.print (currX);
    Serial.print (", ");

    Serial.print (currY);
    
    Serial.print ("\n");
  */  
    #endif
  
  if( ! goTo( currX, currY ))
  {
      #ifdef DO_LOGGING
  
    Serial.print ("Failed goTo: ");
    Serial.print (currX);
    Serial.print (", ");

    Serial.print (currY);

    
    Serial.print ("\n");
    
    #endif
    // if we couldn't go there, keep track of where we really are to stop the motion control going mad
      currX -= dx;
      currY -= dy;
      
      motionWorking = false; 
 
      return false;

  }
  
  
  return true;
}

boolean inBrakingZone( float distance )
{
  // s = 0.5 a t^2
  // s = 0.5 v t
  // => s = v^2 / 2a
  
  float s = currSpeed * currSpeed * 0.5 / acceleration;
  
  return distance < s;
}

void moveTo( float x0, float y0, boolean s)
{
  #ifdef DO_LOGGING
  /*
    Serial.print ("moveto ");
    Serial.print (x0);
    Serial.print (", ");

    Serial.print (y0);

    
    Serial.print ("\n");
    */
    #endif
  
  s = true; // always stop at end  
  motionWorking = true;
  targetX = x0;
  targetY = y0;

  if( stopAtEnd )
  {
    currSpeed = 0;
    currT = millis();
  }
  stopAtEnd = s;

}


