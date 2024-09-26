#include <mbed.h>


BufferedSerial bluetooth(PA_9, PA_10, 9600); // D8  D2


int main() {

while(1){

 bluetooth.read(&recv, 1);
  

 if (recv == 'N') {
  
  mode = false; 
    mode1 = false; 

 }
 if (recv == 'm') {
  mode = true; 
  mode1=false;
 }
  if (recv == 'z') {
  mode1 = true; 
  mode = false;
 }

}
 }