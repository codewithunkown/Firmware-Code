/*                         DATA TO BE TRANSFERRED

Finance Minister Arun Jaitley Tuesday hit out at former RBI governor Raghuram Rajan for 
predicting that the next banking crisis would be triggered by MSME lending, saying postmortem is
easier than taking action when it was required. Rajan, who had as the chief economist at IMF
warned of impending financial crisis of 2008, in a note to a parliamentary committee warned 
against ambitious credit targets and loan waivers, saying that they could be the sources of next banking 
crisis. Government should focus on sources of the next crisis, not just the last one.

In particular, government should refrain from setting ambitious credit targets or waiving loans.
Credit targets are sometimes achieved by abandoning appropriate due diligence, creating the 
environment for future NPAs," Rajan said in the note." Both MUDRA loans as well as the Kisan
Credit Card, while popular, have to be examined more closely for potential credit risk. Rajan, who 
was RBI governor for three years till September 2016, is currently.
 */
#include <EEPROM.h>

#define BAUD_RATE 2400 //Setting Baud Rate to 2400
#define DATA_SIZE 1024 //Setting Character Array Size

// Function prototypes
void WriteEEPROM();  //Writing Data To EEPROM
void LoopBack();    //LoopBack
void ReadEEPROM(); //Reading Data From EEPROM

// Global variables
int start , end , TotalBytes ;
char receivedData[DATA_SIZE];

void setup() {
  
  Serial.begin(BAUD_RATE); // Initialize serial port

  start=0 , end=0 , TotalBytes=0 ; // Initialize global variables

  Serial.println("Hello Waiting For The INPUT"); // Printing Message To PC
}

void loop() 
{  
  if (Serial.available() > 0)  //Blocking Function Waiting For The INPUT 
  {    
    start=millis();  // Start the timer
  
    WriteEEPROM();  // Receive data from PC and store it in EEPROM

    LoopBack();    // Printing Data To PC
    
    ReadEEPROM(); // Read Data From EEPROM And Print It To PC

    // Calculate and print transmission speed
    int transmissionTime = end - start;
    int bitsTransmitted = TotalBytes * 8;
    double speed = (double)bitsTransmitted / (double)transmissionTime * 1000; // Speed in bits per second

    Serial.print("Transmission speed: ");
    Serial.print(speed);
    Serial.println(" bits/second");
    Serial.print("Total Bytes: ");
    Serial.print(TotalBytes);
    Serial.print("\r\n\r\n");

    start=0, end=0 , TotalBytes=0 ;  // Reset global variables for the next transmission
    Serial.println("Hello Waiting For The INPUT"); // Printing Message To PC    
  }
 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LoopBack() 
{
  int len=strlen(receivedData);
  for (int i = 0; i < len; i++) 
  {
    Serial.write(receivedData[i]);
    TotalBytes++;
  }
  Serial.print("\r\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WriteEEPROM()
 {
  for (int i = 0; i < DATA_SIZE; i++) 
  {

    while (!Serial.available()) 
    {
      // Wait for data to be available
    }

    receivedData[i]=Serial.read();

    if(receivedData[i]=='\r' || receivedData[i]=='\n')   //Condition For Giving Data Less Than Usual
    {
      receivedData[i]='\0';
      EEPROM.write(i, receivedData[i]); // Write data to EEPROM
      end=millis();  // Record the end time after receiving all the data
      return;
    }
    EEPROM.write(i, receivedData[i]); // Write data to EEPROM 
  } 
  end=millis(); // Record the end time after receiving all the data
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void  ReadEEPROM()
 {
  int len=strlen(receivedData);
  Serial.print("\r\nReading Data From EEPROM\r\n");
  for (int i = 0; i < len ; i++) 
  {
    char data = EEPROM.read(i);
    Serial.write(data);
  }
  Serial.print("\r\n");
}
