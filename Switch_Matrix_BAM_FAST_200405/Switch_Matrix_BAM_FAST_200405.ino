
// --------------------------------------------
/*  
INSTRUCTIONS:

This code will scan a 5x8 switch matrix and print the status of new switch states.


CODE FLOW:

  -  Set the first drive line output.
  -  Scan first input.
  -  If state was low, and now high, set new switch flag.
  -  Send message out to Serial Monitor (optional).
  -  Loop through all eight inputs.
  -  Loop through all five drive lines.
  -  Delay.
  -  Repeat.
  
For questions or comments, check the blog:
http://howtobuildapinballmachine.wordpress.com

*/


//  --------------------------
//  BUILD VARIABLES HERE
#define DEBOUNCE_MODE 1
#define SERIAL_MONITOR 0 //1 // ONLY USED WHEN DEBUGGING DEBUG 
#define OUTPUT_DIRECT 1

//  --------------------------
//  VARIABLES
unsigned char j = 0;	//
unsigned char i = 0;	//
unsigned char k = 0;	//

unsigned char flagLoops = 0;	//

//  --------------------------
//  SWITCHES (OLD, was x40)
//unsigned char switchStateNow[40];	// start no digit selected
//unsigned char switchStatePrev[40];	// start no digit selected
//unsigned char switchNew[40];	//
//unsigned char switchDebounce[40];
//  --------------------------
//  SWITCHES (NEW, now x48)
unsigned char switchStateNow[48];  // start no digit selected
unsigned char switchStatePrev[48];  // start no digit selected
unsigned char switchNew[48];  //
unsigned char switchDebounce[48];


//  --------------------------
//  DEFINE SWITCH NAMES HERE
//  optional for this test code, but good idea
//  if you are going to build on this as a game later.
enum  
{
  SWITCH_0,
  SWITCH_A, // was 1
  SWITCH_B, // was 2
  SWITCH_C, // was 3
  SWITCH_D, // was 4
  SWITCH_5,
  SWITCH_6,
  SWITCH_7,
  
  SWITCH_8,
  SWITCH_9,
  SWITCH_10,
  SWITCH_11,
  SWITCH_START,
  SWITCH_COIN,
  SWITCH_KICKER,
  SWITCH_ROLLOVER,
  
  SWITCH_LF_SPINNER, // 16
  SWITCH_LANE_DROP_1,
  SWITCH_LANE_DROP_2,
  SWITCH_LANE_DROP_3,  // kicker / shoot again
  SWITCH_LANE_TARGET,
  SWITCH_MID_TARGET,
  SWITCH_22,
  SWITCH_RT_SPINNER,
  
  SWITCH_THUMPER_1,        // BLACK - ORANGE
  SWITCH_THUMPER_2,        // BLACK - GREEN
  SWITCH_THUMPER_3,        // BLACK - BLUE

  SWITCH_LANE_R_1,
  SWITCH_LANE_E,
  SWITCH_LANE_T,
  SWITCH_LANE_R_2,
  SWITCH_LANE_O,
  
  SWITCH_SHOOT_LANE,
  SWITCH_LF_OUT_LANE,
  SWITCH_LF_RET_LANE,
  SWITCH_LF_SLING,
  SWITCH_OUTHOLE,
  SWITCH_RT_OUT_LANE,  
  SWITCH_LOW_1_THUMP, //SHOOT_LANE,
  SWITCH_LOW_2_THUMP // 39
};


#define SWITCH_DEBOUNCE_DURATION 10 //10 loops


// *******************************
// LIGHTING SERIAL SETUP
// *******************************
#include <SoftwareSerial.h>

SoftwareSerial mySerialOne(19, 18); // RX, TX
SoftwareSerial mySerialTwo(17, 16); // RX, TX
SoftwareSerial mySerialThree(15, 14); // RX, TX


void setup() {  

// *******************************
// LIGHTING SERIAL SETUP
// *******************************
//  mySerialOne.begin(9600);
//  mySerialTwo.begin(9600);
//  mySerialThree.begin(9600);

//  mySerialOne.begin(38400);
//  mySerialTwo.begin(38400);
//  mySerialThree.begin(38400);
  
// *******************************
// MATRIX SETUP SECTION
// ******************************* 

// -----------------
// MATRIX DRIVE OUTPUT
  pinMode(A0,OUTPUT); // analog in used a row drive out
  pinMode(A1,OUTPUT); // analog in used a row drive out
  pinMode(A2,OUTPUT); // analog in used a row drive out
  pinMode(A3,OUTPUT); // analog in used a row drive out
  pinMode(A4,OUTPUT); // analog in used a row drive out
  pinMode(A5,OUTPUT); // analog in used a row drive out

// -----------------------
// MATRIX SWITCH INPUT
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);

// -------------------
// DEBUG LED INDICATOR
  pinMode(10,OUTPUT); // analog in used a row drive out

// -------------------------
// FAST SWITCH OUTPUT
// TODO check these, should set almost all remaining pins to output
  //for (j = 22; j < 46; j++)
  for (j = 22; j < 54; j++) // Doesn't include last analog channels
  {
      pinMode(j,OUTPUT); // to FAST hardware
  }

// -----------------------
// LAST BANK OF FAST OUTPUTS
  pinMode(A8,OUTPUT);
  pinMode(A9,OUTPUT);
  pinMode(A10,OUTPUT);
  pinMode(A11,OUTPUT);
  pinMode(A12,OUTPUT);
  pinMode(A13,OUTPUT);
  pinMode(A14,OUTPUT);
  pinMode(A15,OUTPUT);

  
#if (SERIAL_MONITOR == 1)
  Serial.begin(9600);           // start serial for output
#endif

//  --------------------------
//  INITIALIZE SWITCH STATE ON, SINCE WE TRIGGER ON RISING EDGE
  //for (j = 0; j < 40; j++) // OLD, 40 outputs
  for (j = 0; j < 48; j++) // NEW, 48 outputs
  {
    switchStateNow[j] = 1; //
    switchStatePrev[j] = 1;//
    switchNew[j] = 0;
    switchDebounce[j] = 100;
  }
  
Serial.print("Starting");
Serial.print("\r\n");
            
} // end setup


void loop() 
{


// *******************************
// MATRIX SECTION
// ******************************* 
  flagLoops = !flagLoops;
  if (flagLoops == 0)
  {
  digitalWrite(10, HIGH); // DEBUG LED
  }
  else
  {
  digitalWrite(10, LOW); // DEBUG LED
  }
  
  //  *****************************************
  //  -----------------------------------------
  //             START READ SWITCH
  //  -----------------------------------------
  //  *****************************************  

// *******************************
// DRIVE SECTION
// ******************************* 
  // SET DRIVE LINES HERE
  for (j = 0; j < 5; j++) // 0 to 4
  {
    // START ALL LOW (no signal)
//    digitalWrite(14, LOW); // pins 14-17
//    digitalWrite(15, LOW); // pins 14-17
//    digitalWrite(16, LOW); // pins 14-17
//    digitalWrite(17, LOW); // pins 14-17    
//    digitalWrite(18, LOW); // pins 14-17 

    // START ALL LOW (no signal)
    digitalWrite(A0, LOW); // pins 14-17
    digitalWrite(A1, LOW); // pins 14-17
    digitalWrite(A2, LOW); // pins 14-17
    digitalWrite(A3, LOW); // pins 14-17    
    digitalWrite(A4, LOW); // pins 14-17
    digitalWrite(A5, LOW); // pins 14-17
    
    // DRIVE ONE LINE HIGH
    //digitalWrite((j+14), HIGH); // pins 14-17

    // DRIVE ONE LINE HIGH
    switch (j)
    {
      default:
      break;
      
      case 0:
      digitalWrite(A0, HIGH);
      break;

      case 1:
      digitalWrite(A1, HIGH);
      break;

      case 2:
      digitalWrite(A2, HIGH);
      break;

      case 3:
      digitalWrite(A3, HIGH);
      break;

      case 4:
      digitalWrite(A4, HIGH);
      break;

      // doesn't get here, only 0~4
      case 5:
      digitalWrite(A5, HIGH);
      break;     
    }
    
    // WAIT HERE FOR RISE TIME
    delayMicroseconds(400) ;


// *******************************
// SCANNING AND OUTPUT SECTION
// *******************************    
    // START SCAN
    for (i = 0; i < 8; i++) 
    { 
      switchStatePrev[((j*8) + i)] = switchStateNow[((j*8) + i)]; // rotate variable
      switchStateNow[((j*8) + i)] = digitalRead(i + 2); // pins 2-9

      #if (OUTPUT_DIRECT == 1)
        if (switchStateNow[(j*8) + i] == 0)
        {
          if (j == 4)
          {
            // DRIVE OUTPUT LINE HIGH
            switch (i)
            {
              default:
              break;
              
              case 0:
              digitalWrite(A8, HIGH);
              break;
        
              case 1:
              digitalWrite(A9, HIGH);
              break;
        
              case 2:
              digitalWrite(A10, HIGH);
              break;
        
              case 3:
              digitalWrite(A11, HIGH);
              break;
        
              case 4:
              digitalWrite(A12, HIGH);
              break;
        
              case 5:
              digitalWrite(A13, HIGH);
              break;

              case 6:
              digitalWrite(A14, HIGH);
              break;

              case 7:
              digitalWrite(A15, HIGH);
              break;
            }
          }
          else
          {
            digitalWrite((22 + (j*8) + i), HIGH);
          }
        }
        else
        {
          if (j == 4)
          {
            // DRIVE OUTPUT LINE HIGH
            switch (i)
            {
              default:
              break;
              
              case 0:
              digitalWrite(A8, LOW);
              break;
        
              case 1:
              digitalWrite(A9, LOW);
              break;
        
              case 2:
              digitalWrite(A10, LOW);
              break;
        
              case 3:
              digitalWrite(A11, LOW);
              break;
        
              case 4:
              digitalWrite(A12, LOW);
              break;
        
              case 5:
              digitalWrite(A13, LOW);
              break;

              case 6:
              digitalWrite(A14, LOW);
              break;

              case 7:
              digitalWrite(A15, LOW);
              break;
            }
          }
          else
          {
            digitalWrite((22 + (j*8) + i), LOW);
          }
        }
      #endif
          
      // check for a "new" state
    #if (DEBOUNCE_MODE)
      if ((switchStateNow[((j*8) + i)] == switchStatePrev[((j*8) + i)]) || (switchDebounce[((j*8) + i)] > 0))
    #else
      if ( switchStateNow[((j*8) + i)] == switchStatePrev[((j*8) + i)]) 
    #endif
      {
        switchNew[((j*8) + i)] = 0; // same as old
      } // end if
      
      else // must be new if not old and new equals one
      {
        if (switchStateNow[((j*8) + i)] == 1)
        {
          switchNew[((j*8) + i)] = 1; // new
          
          #if (DEBOUNCE_MODE)
            switchDebounce[((j*8) + i)] = SWITCH_DEBOUNCE_DURATION; // set timer
          #endif
          
          #if (SERIAL_MONITOR == 1)
            Serial.print("Switch = ");
            Serial.print((j*8) + i + 33); // TODO check this formatting later
            Serial.print("\r\n");
          #endif
          
        }
      } // end else
    } // end for i
  } // end for j    

/*
          if (switchStateNow[0] == 0)
          {
            //digitalWrite(24, HIGH); //
            digitalWrite((10 + 12), HIGH); //
          }
          else
          {
            //digitalWrite(24, LOW); //
            digitalWrite((10 + 12), LOW); //
          }
          
          if (switchStateNow[1] == 0)
          {
            //digitalWrite(25, HIGH); //
            digitalWrite(23, HIGH); //
          }
          else
          {
            //digitalWrite(25, LOW); //
            digitalWrite(23, LOW); //
          }
          
          if (switchStateNow[3] == 0)
          {
            //digitalWrite(25, HIGH); //
            digitalWrite(23, HIGH); //
          }
          else
          {
            //digitalWrite(25, LOW); //
            digitalWrite(23, LOW); //
          }
   */       
          
  #if (DEBOUNCE_MODE)
    //for (j = 0; j < 40; j++) 
    for (j = 0; j < 48; j++) 
    {
      if (switchDebounce[j] > 0) 
      {
        switchDebounce[j] -= 1; // ramp down to zero
      }
    }
  #endif

  //delay(10) ; // 10ms loop time
  
  // end read switches

//return;

} // end MAIN LOOP
