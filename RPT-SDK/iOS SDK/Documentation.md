Printer is a demo project that demonstrates how to connect and print using Bluetooth and WiFi. It can send data to the connected printer and receive feedback. The relevant SDK can be found in the directory ~./Printer/PrinterSDK/...

### API Description

Bluetooth management class: [TSCBLEManager.h] [POSBLEManager.h]
Responsible for managing Bluetooth connection, sending and receiving data. Callbacks are done through delegates (see TSCPrinterSDK.h, POSPrinterSDK.h for details).

WiFi management class: [TSCWIFIManager.h] [POSWIFIManager.h]
Responsible for managing WiFi connection, sending and receiving data. Callbacks are done through delegates (see TSCPrinterSDK.h, POSPrinterSDK.h for details).

To use the SDK, you need to add the following system frameworks as dependencies:

- SystemConfiguration.framework
- CoreBluetooth.framework
- CFNetwork.framework