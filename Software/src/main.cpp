#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <Wire.h>
#include <Adafruit_BME680.h>

#define BLE_SERVER_NAME "BME680_ESP32"
#define BLE_SERVER_UUID "8eb32be4-3f0b-4830-8a2f-6262d4e37465"

#define BME680_I2C_ADDRESS 0x77
#define PIN_SDI 21
#define PIN_SCK 22
#define temperatureCelsius

Adafruit_BME680 bme;

BLECharacteristic bmeTemperatureCharacteristics("af8a2be6-71c5-4ae4-bbd2-a94f9792a4ec", BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ);
BLEDescriptor bmeTemperatureDescriptor(BLEUUID((uint16_t)0x2902));

BLECharacteristic bmeHumidityCharacteristics("e242d07e-eefc-4c70-b27f-7e3e63f63b78", BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ);
BLEDescriptor bmeHumidityDescriptor(BLEUUID((uint16_t)0x2903));

BLECharacteristic bmePressureCharacteristics("16175616-eaad-4208-be2c-f5bbddd512b5", BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ);
BLEDescriptor bmePressureDescriptor(BLEUUID((uint16_t)0x2904));

BLECharacteristic bmeGasCharacteristics("b8f3a0c4-5d1e-4b2c-9f6d-7a2e5f3b8c7d", BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ);
BLEDescriptor bmeGasDescriptor(BLEUUID((uint16_t)0x2905));

float temp = 0;
float hum = 0;
float pres = 0;

bool deviceConnected = false;

class ServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    deviceConnected = true;
    Serial.println("Device connected");
  };

  void onDisconnect(BLEServer *pServer)
  {
    deviceConnected = false;
    Serial.println("Device disconnected");
    // Restart advertising after disconnection
    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->start();
  }
};

void initBME680()
{
  // if (!bme.begin(BME680_I2C_ADDRESS))
  // {
  //   Serial.println("Could not find a valid BME680 sensor, check wiring!");
  //   // while (1)
  //   //   delay(10);
  // }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting BLE Server...");

  initBME680();
  Serial.println("BME680 initialized.");

  BLEDevice::init(BLE_SERVER_NAME);
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new ServerCallbacks());

  BLEService *pService = pServer->createService(BLE_SERVER_UUID);

  pService->addCharacteristic(&bmeTemperatureCharacteristics);
  bmeTemperatureDescriptor.setValue("BME688 Temperature");
  bmeTemperatureCharacteristics.addDescriptor(&bmeTemperatureDescriptor);

  pService->addCharacteristic(&bmePressureCharacteristics);
  bmePressureDescriptor.setValue("BME688 Pressure");

  bmePressureCharacteristics.addDescriptor(&bmePressureDescriptor);
  pService->addCharacteristic(&bmeGasCharacteristics);
  bmeGasDescriptor.setValue("BME688 Gas");
  bmeGasCharacteristics.addDescriptor(&bmeGasDescriptor);

  pService->addCharacteristic(&bmeHumidityCharacteristics);
  bmeHumidityDescriptor.setValue("BME688 Humidity");
  bmeHumidityCharacteristics.addDescriptor(&bmeHumidityDescriptor);
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->addServiceUUID(BLE_SERVER_UUID);
  pAdvertising->start();
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

    uint8_t temperatureData[2] = {0x03, 0x04}; // Example data
    bmeTemperatureCharacteristics.setValue(temperatureData, sizeof(temperatureData));
    bmeTemperatureCharacteristics.notify();

    uint8_t pressureData[2] = {0x05, 0x06}; // Example data
    bmePressureCharacteristics.setValue(pressureData, sizeof(pressureData));
    bmePressureCharacteristics.notify();

    uint8_t gasData[2] = {0x07, 0x08}; // Example data
    bmeGasCharacteristics.setValue(gasData, sizeof(gasData));
    bmeGasCharacteristics.notify();

    delay(1000); // Send data every second
  }
  delay(100);
}
