//
//  TSCPrinterSDK.h
//  Printer
//

/*
在SDK可见的头文件（.h文件）包含了蓝牙的连接:TSCBLEMananger.h WiFi的连接:TSCWIFIManager.h 是发送接收数据的方法和需要遵循的代理; 还有指令封装的工具类:TSCCommand,ZebraCommand;

 ### TSCBLEManager.h 是蓝牙管理类，处理蓝牙的连接相关和指令的发送。
 使用 [TSCBLEManager sharedInstance] 单例方法创建管理对象，创建的同时遵循代理，实现代理方法. 调用 startScan 方法开始扫描，并在代理方法 didUpdatePeripheralList 中拿到扫描结果。 connectDevice: 是蓝牙连接方法，连接指定的外设TSCBLEManager中有个 writePeripheral 属性，用来指定向哪个外设写数据，不指定默认位最后连接的那个外设。
 @protocol TSCBLEManagerDelegate <NSObject>
 // 发现的蓝牙设备后执行
 - (void)TSCbleUpdatePeripheralList:(NSArray *)peripherals RSSIList:(NSArray *)rssiList;
 // 连接成功后执行
 - (void)TSCbluConnectPeripheral:(CBPeripheral *)peripheral;
 // 连接失败后执行
 - (void)TSCbluFailToConnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error;
 // 断开连接后执行
 - (void)TSCbluDisconnectPeripheral:(CBPeripheral *)peripheral;
 // 发送数据成功
 - (void)TSCbluWriteValueForCharacteristic:(CBCharacteristic *)character error:(NSError *)error;
 @end
 
 
### WiFi管理类的使用说明：
 使用单例方法 [TSCWIFIManager shareWifiManager] 创建连接对象，设置代理，并实现代理方法。connectWithHost:port:是连接的方法，指定IP 和端口号。实现代理方法 (void)TSCwifiConnectedToHost:(NSString *)host port:(UInt16)port;
 
 连接成功后，发送数据使用-(void)writeCommandWithData:(NSData *)data 在TSCWIFIManager:- (void)TSCwifiWriteValueWithTag:(long)tag 代理方法中执行判断后的操作。

@protocol POSWIFIManagerDelegate <NSObject>
// 成功连接主机后执行
- (void)TSCwifiConnectedToHost:(NSString *)host port:(UInt16)port;
// 断开连接
- (void)TSCwifiDisconnectWithError:(NSError *)error;
// 写入数据后执行
- (void)TSCwifiWriteValueWithTag:(long)tag;
@end
 

TSCCommand.h条码指令封装工具类，所有返回值均为NSData类型;
ZPLCommand条码指令封装工具，所有返回值均为NSData类型;
CPCLCommand条码指令封装工具，所有返回值均为NSData类型;
这俩个指令工具类里的方法均为类方法，直接用类名调用，返回值都是NSData类型，可用于数据直接发送
 
打印前调用相关类的实例方法 - (void)getPeripheralStatus: 方法即可查询当前打印机状态
 */


#ifndef TSCPrinterSDK_h
#define TSCPrinterSDK_h

#import "TSCBLEManager.h"
#import "TSCWIFIManager.h"
#import "TSCCommand.h"
#import "ZPLCommand.h"
#import "CPCLCommand.h"
#import "KDS_Log.h"
#endif /* TSCPrinterSDK_h */
