#include <vector>
#ifndef SD_CARD_INTERFACE
#define SD_CARD_INTERFACE

#include "FS.h"      // SD Card ESP32
#include "SD_MMC.h"  // SD Card ESP32
#include <string>
//#include "app_httpd.cpp"
using namespace std;

void sd_flash_led() {
  File file = SD_MMC.open("/flash_file.txt", FILE_WRITE);

  if (!file) {
    Serial.println("Opening file to flash failed");
    return;
  }
  file.close();
}

const char* sd_read_targets() {
  File file = SD_MMC.open("/targets.txt", FILE_READ);
  const char* str;
  if (!file) {
    Serial.println("Opening file to read targets failed");
    return str;
  }
  str = file.readString().c_str();
  file.close();
  return str;

}

const char* init_Micro_SD_Card() {
  const char* str;
  // Start the MicroSD card
  Serial.println("Mounting MicroSD Card");
  if (!SD_MMC.begin()) {
    Serial.println("MicroSD Card Mount Failed");
    return str;
  }
  uint8_t cardType = SD_MMC.cardType();
  if (cardType == CARD_NONE) {
    Serial.println("No MicroSD Card found");
    return str;
  }
  sd_flash_led();
  str = sd_read_targets();
  Serial.print("Read all targets from MicroSD Card");
  SD_MMC.end();

  return str;
}




#endif  //SD_CARD_INTERFACE
