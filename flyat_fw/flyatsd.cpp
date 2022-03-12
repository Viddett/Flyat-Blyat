#include "flyatsd.h"

#define filename "log.txt"

void sdSetup(int chipSelect){
	pinMode(chipSelect, OUTPUT); // chip select pin must be set to OUTPUT mode
	if (!SD.begin(chipSelect)) { // Initialize SD card
		#ifdef debug
		Serial.println("sd_fail"); // if return value is false, something went wrong.
		#endif
	}
	
	if (SD.exists(filename)) { // if file exists, delete it
		#ifdef debug
		Serial.println("File exists.");
		#endif
		if (SD.remove(filename) == true) {
			#ifdef debug
			Serial.println("Successfully removed file.");
		} else {
			Serial.println("Could not remove file.");
			#endif 
		}
	}
}

void sdLogWrite(String data) {
	File file = SD.open(filename, FILE_WRITE); // open file to write data
	if (file) {
		file.println(String(millis()) + " " + data); // write to file
		file.close(); // close file
	} else {
		#ifdef debug
		Serial.println("w_error");
		#endif
	}
}

// void logRead() {
// 	File file = SD.open(filename, FILE_READ); // open file to read data
// 	if (file) {
// 		Serial.println("---");
// 		char character;
// 		while ((character = file.read()) != -1) { // this while loop reads data stored in file and prints it to serial monitor
// 			Serial.print(character);
// 		}
// 		file.close();
// 		Serial.println("---");
// 	} else {
// 		Serial.println("r_error");
// 	}
// }