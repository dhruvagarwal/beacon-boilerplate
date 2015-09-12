#include <mbed.h>
#include <BLEDevice.h>

BLEDevice ble;

const static uint8_t iBeaconPayload[] = {
	0x4c, 0x00,
	0x02,
	0x15,
	0xE2, 0x0A, 0x39, 0xF4, 0x73, 0xF5, 0x4B, 0xC4,
	0xA1, 0x2F, 0x17, 0xD1, 0xAD, 0x07, 0xA9, 0x61,
	0x00, 0x00,
	0x00, 0x00,
	0xC8
};


const static char DEVICE_NAME[] = "iBeacon";

int main()
{
	ble.init();
	ble.accumulateAdvertisingPayload(GapAdvertisingData::BREDR_NOT_SUPPORTED | GapAdvertisingData::LE_GENERAL_DISCOVERABLE);
	ble.accumulateAdvertisingPayload(GapAdvertisingData::MANUFACTURER_SPECIFIC_DATA, iBeaconPayload, sizeof(iBeaconPayload));
	ble.accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LOCAL_NAME, (uint8_t *)DEVICE_NAME, sizeof(DEVICE_NAME));

	// ble.setAdvertisingType(GapAdvertisingParams::ADV_NON_CONNECTABLE_UNDIRECTED);

	ble.setAdvertisingInterval(160);
	ble.startAdvertising();

	for(;;)
	{
		ble.waitForEvent();
	}

	return 0;
}
