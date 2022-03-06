#include <SD.h>

#define filename "log.txt"

class SDcard {

	private: 

		void setup(int chipSelect) {
  			// Serial.begin(9600); // start serial connection to print out debug messages and data
  
  			pinMode(chipSelect, OUTPUT); // chip select pin must be set to OUTPUT mode
  			if (!SD.begin(chipSelect)) { // Initialize SD card
				Serial.println("sd_fail"); // if return value is false, something went wrong.
			}
			
			if (SD.exists(filename)) { // if file exists, delete it
				Serial.println("File exists.");
				if (SD.remove(filename) == true) {
				Serial.println("Successfully removed file.");
				} else {
				Serial.println("Could not remove file.");
				}
			}
		}

	public:

		SDcard(int chipSelect) {
			setup(chipSelect);
		}

		void logWrite(String data) {
			File file = SD.open(filename, FILE_WRITE); // open file to write data
			if (file) {
				file.println(" " + data); // write to file
				file.close(); // close file
			} else {
				Serial.println("w_error");
			}
		}

		void logRead() {
			File file = SD.open(filename, FILE_READ); // open file to read data
			if (file) {
				Serial.println("---");
				char character;
				while ((character = file.read()) != -1) { // this while loop reads data stored in file and prints it to serial monitor
					Serial.print(character);
				}
				file.close();
				Serial.println("---");
			} else {
				Serial.println("r_error");
			}
		}
};
