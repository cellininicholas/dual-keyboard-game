#if !defined(__WORDDATA_H__)
#define __WORDDATA_H__

 #include <SPI.h>
 #include <SD.h>

class Words {
   // static const char* PROGMEM balanced8Chars[];

   public:
  
      static void InitSDCard() {
         Serial.print("Initializing SD card...");
         if (!SD.begin(53)) {
            Serial.println("initialization failed!");
            while (1);
         }
         Serial.println("initialization done.");
      }

      static char * GetRandomBalance8CharWord() {
         
         File myFile = SD.open("w00.txt"); // 8bal[00-45].txt
         if (myFile) {
            Serial.println("words-8bal-split/w00.txt:");

            // read from the file until there's nothing else in it:
            while (myFile.available()) {
               Serial.write(myFile.read());
            }
            // close the file:
            myFile.close();
         } else {
            // if the file didn't open, print an error:
            Serial.println("error opening words-8bal-split/w00.txt");
         }

         return NULL;
      }
};


#endif // __WORDDATA_H__
