#include <Arduino.h>
#include <driver/dac.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <string>

/** randomly generated UUID */
static constexpr auto SERVICE_UUID = "83336cef-8fbc-4b77-857b-0aebec87160c";
static constexpr auto RAW_CHARA_UUID = "83336cef-8fbc-4b77-857b-0aebec87160d";
static constexpr auto VOLT_CHARA_UUID = "83336cef-8fbc-4b77-857b-0aebec87160e";

static uint8_t g_dac_value = 0;

class MyCharacteristicCallback : public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic *chara)
    {
        auto value = chara->getValue();
        if (value.length() < 1)
        {
            return;
        }

        g_dac_value = atoi(value.c_str());
        dac_output_voltage(DAC_CHANNEL_1, g_dac_value);
    }

    void onRead(BLECharacteristic *chara)
    {
        std::string value = std::to_string(g_dac_value);
        chara->setValue(value);
    }
};

class VoltCharaCallback : public BLECharacteristicCallbacks
{
    void onRead(BLECharacteristic *chara)
    {
        auto mv = (g_dac_value * 3300) / 255;
        std::string value = std::to_string(mv);

        chara->setValue(value);
    }
};

class ServerCallbacks : public BLEServerCallbacks
{
    void onDisconnect(BLEServer *server)
    {
        server->getAdvertising()->start();
    }
};

void setup()
{
    Serial.begin(9600);

    BLEDevice::init("BLEDAC");

    auto *server = BLEDevice::createServer();
    server->setCallbacks(new ServerCallbacks());

    auto *service = server->createService(SERVICE_UUID);

    auto *chara = service->createCharacteristic(RAW_CHARA_UUID, BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_READ);
    chara->setCallbacks(new MyCharacteristicCallback());

    auto *voltChara = service->createCharacteristic(VOLT_CHARA_UUID, BLECharacteristic::PROPERTY_READ);
    voltChara->setCallbacks(new VoltCharaCallback());

    service->start();

    auto *adv = BLEDevice::getAdvertising();
    adv->addServiceUUID(SERVICE_UUID);
    adv->setScanResponse(true);
    adv->setMinPreferred(0x06);
    adv->setMaxPreferred(0x12);

    BLEDevice::startAdvertising();

    dac_output_enable(DAC_CHANNEL_1);
    dac_output_voltage(DAC_CHANNEL_1, g_dac_value);
}

void loop()
{
}