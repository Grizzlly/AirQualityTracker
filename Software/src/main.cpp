#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

#define BLE_SERVER_NAME "BME688_ESP32"
#define BLE_SERVER_UUID "8eb32be4-3f0b-4830-8a2f-6262d4e37465"

BLECharacteristic bmeHumidityCharacteristics("8eb32be4-3f0b-4830-8a2f-6262d4e37465", BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor bmeHumidityDescriptor(BLEUUID((uint16_t)0x2902));

bool deviceConnected = false;

class ServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    deviceConnected = true;
  };

  void onDisconnect(BLEServer *pServer)
  {
    deviceConnected = false;
  }
};

// put function declarations here:
int myFunction(int, int);

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  BLEDevice::init(BLE_SERVER_NAME);
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new ServerCallbacks());

  BLEService *pService = pServer->createService(BLE_SERVER_UUID);

  pService->addCharacteristic(&bmeHumidityCharacteristics);
  bmeHumidityDescriptor.setValue("BME688 Humidity");
  bmeHumidityCharacteristics.addDescriptor(&bmeHumidityDescriptor);

  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->addServiceUUID(BLE_SERVER_UUID);
  pServer->getAdvertising()->start();
  Serial.println("BLE Server started, waiting for connections...");
}

void loop()
{
  if (deviceConnected)
  {
    // Simulate sending data
    uint8_t humidityData[2] = {0x01, 0x02}; // Example data
    bmeHumidityCharacteristics.setValue(humidityData, sizeof(humidityData));
    bmeHumidityCharacteristics.notify();
    delay(1000); // Send data every second
  }
  delay(100);
}

// put function definitions here:
int myFunction(int x, int y)
{
  return x + y;
}