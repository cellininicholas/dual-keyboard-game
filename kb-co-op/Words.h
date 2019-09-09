#if !defined(__WORDDATA_H__)
#define __WORDDATA_H__

 #include <SPI.h>
 #include <SD.h>

class Words {
   // static const char* PROGMEM balanced8Chars[];
   static const int PROGMEM NUM_8CHAR_BALWORD_FILES = 46; // 00-45

   public:
  
      static void toUpperCase(char* wordToUpper) {
         int i = 0;
         while(wordToUpper[i]) {
            if (wordToUpper[i]>=97 && wordToUpper[i]<=122) {
               wordToUpper[i] = wordToUpper[i] - 32;
               // printf ("\n Uppercase of Entered character is %c", Ch);
            }

            i++;
         }
      }

      static void InitSDCard(uint8_t SD_CS_PIN_NUM) {
         Serial.print("Initializing SD card...");
         int failures = 0;
         while (!SD.begin(SD_CS_PIN_NUM)) {
            failures = failures + 1;
            Serial.print("initialization #");
            Serial.print(failures);
            Serial.println(" failed!");
            delay (1000);
         }
         Serial.print("initialization done... ");
         Serial.print(failures);
         Serial.println(" failed SD.begin() attempts.");
      }

      static void EndSDCard() {
        SD.end();
      }

      static char * GetRandomBalance8CharWord(uint16_t rand1, uint16_t rand2) {
        return GetRandomBalance8CharWord(rand1, rand2, 0);
      }

      static char * GetRandomBalance8CharWord(uint16_t rand1, uint16_t rand2, uint8_t attemptNum) {
         
         // 8bal00.txt
         char filenameBuffer [10];
         int randFileNum = rand1 % (NUM_8CHAR_BALWORD_FILES-1);
         sprintf (filenameBuffer, "8bal%02d.txt", randFileNum);
         Serial.println(filenameBuffer);

//         InitSDCard();
         File myFile = SD.open(filenameBuffer);

         if (myFile) {

            uint32_t fileSize = myFile.size();
            char* readBuf = new char[fileSize];
            myFile.read(readBuf, fileSize);
            myFile.close(); // close the file:
//            EndSDCard();

            // Serial.write(readBuf);

            // read from the file until there's nothing else in it:
            // while (myFile.available()) {
            //    Serial.write(myFile.read());
            // }

            // TODO: Randomly select a word from the readBuf
            char* randomlySelectedWord = new char[9]; // 8 + null char
            randomlySelectedWord[8] = '\0'; // null character manually added
            int totalWords = 10;
            int randWordIndex = rand2 % (totalWords-1);
            strncpy ( randomlySelectedWord, readBuf + (9*randWordIndex), 8);

            delete[] readBuf;

            toUpperCase(randomlySelectedWord);
            return randomlySelectedWord;

         } else {
//            EndSDCard();
            attemptNum = attemptNum + 1;

            // if the file didn't open, print an error:
            Serial.print("error opening ");
            Serial.print(filenameBuffer);
            Serial.print(" ATTEMPT ");
            Serial.println(attemptNum + 1);

            if (attemptNum < 3) { return GetRandomBalance8CharWord(rand1, rand2, attemptNum); }
         }

         return NULL;
      }
};


#endif // __WORDDATA_H__
