#include <string.h>
#include <ctype.h>

String input_Latitude, input_Longitude, send_Data;
int byteGPS=-1;
char linea[300] = "";
char comandoGPR[7] = "$GPRMC";
int cont=0;
int bien=0;
int conta=0;
int indices[13];

void setup() {
  Serial.begin(19200);
  Serial1.begin(4800);
  Serial2.begin(9600); // 57600 for Radio
  for (int i=0;i<300;i++){ // Initialize a buffer for received data
     linea[i]=' ';
   } 
}

void loop(){
  if(Serial1.available()){
    byteGPS = Serial1.read();
    if (byteGPS == -1) {
      delay(100);
    } else {
      // note: there is a potential buffer overflow here!
      linea[conta]=byteGPS;        // If there is serial port data, it is put in the buffer
      conta++;                      
      if (byteGPS==13){            // If the received byte is = to 13, end of transmission
	// note: the actual end of transmission is <CR><LF> (i.e. 0x13 0x10)
	cont=0;
	bien=0;
	// The following for loop starts at 1, because this code is clowny and the first byte is the <LF> (0x10) from the previous transmission.
	for (int i=1;i<7;i++){     // Verifies if the received command starts with $GPR
	  if (linea[i]==comandoGPR[i-1]){
	    bien++;
	  }
	}
	if(bien==6){               // If yes, continue and process the data
	  for (int i=0;i<300;i++){
	    if (linea[i]==','){    // check for the position of the  "," separator
	      // note: again, there is a potential buffer overflow here!
	      indices[cont]=i;
	      cont++;
	    }
	    if (linea[i]=='*'){    // ... and the "*"
	      indices[12]=i;
	      cont++;
	    }
	  }
	  for (int i=0;i<12;i++){
	    for (int j=indices[i];j<(indices[i+1]-1);j++){
	      switch(i){
	      case 2:input_Latitude += linea[j+1];break;
	      case 4:input_Longitude += linea[j+1];break;	       
	      }
	    }
	  }
	}
	conta=0;                    // Reset the buffer
	for (int i=0;i<300;i++){    //  
	  linea[i]=' ';             
	}                    
      }
    }
    if (input_Latitude != "" && input_Longitude != "") {
      send_Data = "#" + input_Latitude + "," + input_Longitude + "#$\n";
      Serial.print(send_Data);
      Serial2.print(send_Data);
      input_Latitude = "";
      input_Longitude = "";
    }
  }
}
