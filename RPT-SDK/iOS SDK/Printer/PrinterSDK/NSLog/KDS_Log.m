//
//  KDS_Log.m
//  Printer
//
//  Created by Apple Mac mini intel on 2022/11/4.
//  Copyright © 2022 Admin. All rights reserved.
//

#import "KDS_Log.h"

// Log 开关状态，默认不输出log信息
static BOOL KDS_Log_Switch = NO;

@implementation KDS_Log

void CustomLog(const char *func, int lineNumber, NSString *format, ...)
{
    if ([KDS_Log logEnable]) {  // 开启了Log
        va_list args;
        va_start(args, format);
        NSString *string = [[NSString alloc] initWithFormat:format arguments:args];
        NSString *strFormat = [NSString stringWithFormat:@"%@",string];
        NSLogv(strFormat, args);
        va_end(args);
    }
}

+ (BOOL)logEnable {
    return KDS_Log_Switch;
}

+ (void)setLogEnable:(BOOL)flag {
    KDS_Log_Switch = flag;
}

@end
