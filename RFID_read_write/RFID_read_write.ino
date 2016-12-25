#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
/*
 * Pin connections for UNO:
 * 9  - RST
 * 10 - SDA
 * 11 - MOSI
 * 12 - MISO
 * 13 - SCK
 */
MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key; // will hold card info

// Every 4th block is a trailer block that contains access and security info, modulo 4.
const int blockSize = 16;

int writeBlockNumber = 2; // The block we want to write the data.
int readBlockNumber = 2;
byte writeBlockContent[blockSize] = { "Denis Cosmin" }; // 16 character max
byte readBlockContent[18] = { 0 };

// Will write the data to the block.
int writeBlock(int block, byte data[]) {
  int status;
  
  if ( (block + 1) % 4 == 0) {
    Serial.println("Warning: Writing on a trailer block!");
    return 0;
  }

  int trailerBlock = block + (4 - block % 4) - 1;
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &mfrc522.uid);
  if ( status != MFRC522::STATUS_OK ) {
    Serial.print("PCD_Authenticate() failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return status;
  }

  status = mfrc522.MIFARE_Write(block, data, blockSize);
  if ( status != MFRC522::STATUS_OK ) {
    Serial.print("MIFARE_Write() failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return status;
  }
  return MFRC522::STATUS_OK;
}

// Will try to dump the whole card info.
void dumpCard() {
  for(int i = 0; i < blockSize; ++i) {
      Serial.print("Block ");
      Serial.print(i);
      Serial.print(" ");
      if ( readBlock(i, readBlockContent) == MFRC522::STATUS_OK ) {
        printReadBlock();
      }
  }
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

// Will read the block.
// These functions must be called if you wish to read a new card.
//    mfrc522.PICC_HaltA();
//    mfrc522.PCD_StopCrypto1();
int readBlock(int block, byte data[]) {
  int status;
  byte readSize = blockSize + 2;
  
  int trailerBlock = block + (4 - block % 4) - 1;
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &mfrc522.uid);

  if ( status != MFRC522::STATUS_OK ) {
    Serial.print("PCD_Authenticate() failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return status;
  }

  status = mfrc522.MIFARE_Read(block, data, &readSize);
  if ( status != MFRC522::STATUS_OK ) {
    Serial.print("MIFARE_Read() failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return status;
  }
  
  return MFRC522::STATUS_OK;
}

// Will print the contents of the readBlockContent.
void printReadBlock() {
  for (int i = 0; i < blockSize; ++i) {
    Serial.print(readBlockContent[i], HEX);
    Serial.print(" ");
  }
  Serial.print(" -> ");
  for (int i = 0; i < blockSize; ++i) {
    Serial.write(readBlockContent[i]);
  }
  
  Serial.println();
}

// Will print the card id that is stored in mfrc522.uid.uidByte
void printCardUid() {
  Serial.print("Card ID: ");
  for (int i = 0; i < mfrc522.uid.size; ++i) {
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for serial.
  SPI.begin();

  mfrc522.PCD_Init();
  Serial.println("Initialized...");

  // default access key STANDARD KEY 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF
  for (int i = 0; i < 6; ++i) {
    key.keyByte[i] = 0xFF;
  }
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent() ) {
      return;  // No card present, continue.
  } 
  if ( ! mfrc522.PICC_ReadCardSerial() ) {
      // On success this function will return 1 and set the uid struct mfrc522.uid
      return;
  }

  printCardUid();

  // Write data to block.
//  writeBlock(15, writeBlockContent);
//  if ( readBlock(13, readBlockContent) == MFRC522::STATUS_OK )
//    printReadBlock();

  dumpCard();

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

