#include <mbed.h>
#include <BLEDevice.h>

BLEDevice ble;

/*
* The Beacon payload (encapsulated within the MSD advertising data structure)
* has the following composition:
* 128-Bit UUID = E2 0A 39 F4 73 F5 4B C4 A1 2F 17 D1 AD 07 A9 61
* Major/Minor  = 0000 / 0000
* Tx Power     = C8 (-56dB)
*/
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


const static char DEVICE_NAME[] = "my iBeacon";

int main()
{
    /* Initialize BLE baselayer */
	ble.init();

    /* Set up iBeacon data*/
	ble.accumulateAdvertisingPayload(GapAdvertisingData::BREDR_NOT_SUPPORTED | GapAdvertisingData::LE_GENERAL_DISCOVERABLE);
	ble.accumulateAdvertisingPayload(GapAdvertisingData::MANUFACTURER_SPECIFIC_DATA, iBeaconPayload, sizeof(iBeaconPayload));
	ble.accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LOCAL_NAME, (uint8_t *)DEVICE_NAME, sizeof(DEVICE_NAME));

	ble.setAdvertisingType(GapAdvertisingParams::ADV_NON_CONNECTABLE_UNDIRECTED);

    /* Set advertising interval. Longer interval = longer battery life */
    ble.setAdvertisingInterval(160); /* 100ms; in multiples of 0.625ms. */
	ble.startAdvertising();

	for(;;)
	{
		ble.waitForEvent();
	}

	return 0;
}
