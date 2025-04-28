//
//  POSBLEManager.h
//  Printer
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

typedef void (^POSBLEManagerReceiveCallBackBlock)(CBCharacteristic *characteristic, NSError *error);
typedef void (^POSBLEManagerWriteCallBackBlock) (CBCharacteristic *characteristic, NSError *error);

@protocol POSBLEManagerDelegate <NSObject>
@optional
/**
 *  found peripheral list
 */
- (void)POSbleUpdatePeripheralList:(NSArray *)peripherals RSSIList:(NSArray *)rssiList;
/**
 *  connect success
 */
- (void)POSbleConnectPeripheral:(CBPeripheral *)peripheral;
/**
 *  connect fail
 */
- (void)POSbleFailToConnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error;
/**
 *  disconnect
 */
- (void)POSbleDisconnectPeripheral:(CBPeripheral *)peripheral;
/**
 *  send data success
 */
- (void)POSbleWriteValueForCharacteristic:(CBCharacteristic *)character error:(NSError *)error;
/**
 *  receive printer data
 */
- (void)POSbleReceiveValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error;
@end

@interface POSBLEManager : NSObject

@property (nonatomic,weak) id<POSBLEManagerDelegate> delegate;

//peripheral that write
@property (nonatomic,strong) CBPeripheral *writePeripheral;

@property (nonatomic, copy) POSBLEManagerReceiveCallBackBlock receiveBlock;
@property (nonatomic, copy) POSBLEManagerWriteCallBackBlock writeBlock;

//whether connect
@property (nonatomic, assign) BOOL isConnect;

/**
 *  singleton
 */
+ (instancetype)sharedInstance;
/**
 *  start scan
 */
- (void)startScan;
/**
 *  stop scan
 */
- (void)stopScan;
/**
 *  connect special one
 */
- (void)connectDevice:(CBPeripheral *)peripheral;
/**
 *  disconnect manual
 */
- (void)disconnectRootPeripheral;
/**
 *  send command
 */
- (void)writeCommandWithData:(NSData *)data;
/**
 *  remove a delegate
 */
- (void)removeDelegate:(id<POSBLEManagerDelegate>)delegate;
/**
 *  remove all delegates
 */
- (void)removeAllDelegates;
/**
 * send command data with callback
 */
- (void)writeCommandWithData:(NSData *)data receiveCallBack:(POSBLEManagerReceiveCallBackBlock)receiveBlock;
/**
 *  send command data write callback
 */
- (void)writeCommandWithData:(NSData *)data writeCallBack:(POSBLEManagerWriteCallBackBlock)writeBlock;
/**
 *  get copyright
 */
+ (NSString *)GetCopyRight;

@end
