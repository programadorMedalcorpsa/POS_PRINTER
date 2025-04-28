//
//  TSCBLEManager.h
//  Printer
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

typedef void (^TSCBLEManagerReceiveCallBackBlock)(CBCharacteristic *characteristic, NSError *error);
typedef void (^TSCBLEManagerWriteCallBackBlock) (CBCharacteristic *characteristic, NSError *error);

@protocol TSCBLEManagerDelegate <NSObject>
@optional
/**
 *  found peripheral list
 */
- (void)TSCbleUpdatePeripheralList:(NSArray *)peripherals RSSIList:(NSArray *)rssiList;
/**
 *  connect success
 */
- (void)TSCbleConnectPeripheral:(CBPeripheral *)peripheral;
/**
 *  connect fail
 */
- (void)TSCbleFailToConnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error;
/**
 *  disconnect
 */
- (void)TSCbleDisconnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error;
/**
 *  send data success
 */
- (void)TSCbleWriteValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error;
/**
 *  receive printer data
 */
- (void)TSCbleReceiveValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error;
@end

@interface TSCBLEManager : NSObject

@property (nonatomic,weak) id<TSCBLEManagerDelegate> delegate;

//peripheral that write
@property (nonatomic,strong) CBPeripheral *writePeripheral;

@property (nonatomic, copy) TSCBLEManagerReceiveCallBackBlock receiveBlock;
@property (nonatomic, copy) TSCBLEManagerWriteCallBackBlock writeBlock;

//是否连接
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
- (void)connectDevice:(CBPeripheral *) peripheral;
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
- (void)removeDelegate:(id<TSCBLEManagerDelegate>) delegate;
/**
 *  remove all delegates
 */
- (void)removeAllDelegates;
/**
 *  send command data receicve callback
 */
- (void)writeCommandWithData:(NSData *)data receiveCallBack:(TSCBLEManagerReceiveCallBackBlock)receiveBlock;
/**
 *  send command data write callback
 */
- (void)writeCommandWithData:(NSData *)data writeCallBack:(TSCBLEManagerWriteCallBackBlock)writeBlock;

/**
 *  get copyright
 */
+ (NSString *)GetCopyRight;

@end
