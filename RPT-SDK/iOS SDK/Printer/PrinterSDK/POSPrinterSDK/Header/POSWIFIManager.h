//
//  POSWIFIManager.h
//  Printer
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef void(^POSWIFIManagerReceiveBlock)(NSData *data);
typedef void(^POSWIFIManagerWriteBlock)(long tag);

@class POSWIFIManager;
@protocol POSWIFIManagerDelegate <NSObject>
@optional
/**
 * connect success
 */
- (void)POSwifiConnectedToHost:(NSString *)host port:(UInt16)port;
/**
 * disconnect error
 */
- (void)POSwifiDisconnectWithError:(NSError *)error;
/**
 * send data success
 */
- (void)POSwifiWriteValueWithTag:(long)tag;
/**
 * receive printer data
 */
- (void)POSwifiReceiveValueForData:(NSData *)data;
@end

@interface POSWIFIManager : NSObject
// host
@property (nonatomic, copy) NSString *hostStr;
// port
@property (nonatomic, assign) UInt16 port;
// whether connect
@property (nonatomic, assign) BOOL isConnect;

@property (nonatomic, weak) id<POSWIFIManagerDelegate> delegate;

@property (nonatomic, copy) POSWIFIManagerReceiveBlock receiveBlock;
@property (nonatomic, copy) POSWIFIManagerWriteBlock writeBlock;

/**
 *  singleton
 */
+ (instancetype)sharedInstance;
/**
 *  connect printer address
 */
- (void)connectWithHost:(NSString *)hostStr port:(UInt16)port;
/**
 *  disconnect
 */
- (void)disconnect;
/**
 *  write command to printer
 */
- (void)writeCommandWithData:(NSData *)data;
/**
 *  remove a delegate
 */
- (void)removeDelegate:(id<POSWIFIManagerDelegate>) delegate;
/**
 *  remove all delegates
 */
- (void)removeAllDelegates;
/**
 *  write command to printer with receive callback
 */
- (void)writeCommandWithData:(NSData *)data receiveCallBack:(POSWIFIManagerReceiveBlock)receiveBlock;
/**
 *  write command to printer with write callback
 */
- (void)writeCommandWithData:(NSData *)data writeCallBack:(POSWIFIManagerWriteBlock)receiveBlock;
/**
 *  get copyright
 */
+ (NSString *)GetCopyRight;

@end
