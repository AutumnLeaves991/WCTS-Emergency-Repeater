#include <DTMF.h>

int sensorPin = A0;
int led = 13;

int flags[5] = {0,0,0,0,0};
// 0 - Star Recieved / Command Mode on
// 1 - 
// 2 -
// 3 -
// 4 -
// 5 - 

char command[4];
int command_index = 0;

float n=128.0; // amount of samples dtmf library takes
float sampling_rate=8926.0; // sampling rate in Hz
DTMF dtmf = DTMF(n,sampling_rate); // Instantiate the dtmf library with the number of samples to be taken and the sampling rate.

void setup(){
  pinMode(led, OUTPUT);     
  Serial.begin(115200);
  Serial.println("+------------------+");
  Serial.println("|Dtmf Decoder V1   |");
  Serial.println("|By Douglas Reilly |");
  Serial.println("+------------------+");
  
}

int nochar_count = 0;
float d_mags[8];
void loop()
{
  char thischar; // This reads N samples from sensorpin (must be an analog input) and stores them in an array within the dtmf library.
  dtmf.sample(sensorPin);
  // The first argument is the address of a user-supplied array of 8 floats in which the function will return the magnitudes
  //of the eight tones. The second argument is the value read by the ADC when there is no signal present. A voltage divider with precisely equal
  // resistors will presumably give a value of 511 or 512. My divider gives a value of 506.
  // If you aren't sure what to use, set this to 512
  dtmf.detect(d_mags,50);
  thischar = dtmf.button(d_mags,1800.);
  if(thischar){
    if(flags[0]==1){
      command[command_index] = thischar;
      command_index++;
    }
    
    if(thischar == '#'){
     flags[0] = 0; 
     Serial.print("Sequence Recieved: ");
     for(int i=0; i!=5; i++){
       Serial.print(command[i]);
      }
      Serial.println();
      char command[4] = {0,0,0,0};
      command_index = 0;
      Serial.println("Command mode OFF!");
    }
    
    if(thischar == '*'){
      Serial.println("Command mode ON!");
      flags[0] = 1;
    }
  }
}
