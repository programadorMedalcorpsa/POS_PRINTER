//
//  POSCommand.h
//  Printer
//

#import <Foundation/Foundation.h>
#import "POSImageTranster.h"

/**
 Pos command
 */
@interface POSCommand : NSObject

/**
 Horizontal positioning<br>
 HT<br>
 09<br>
 */
+(NSData *) horizontalPosition;
/**
 Print and wrap<br>
 LF<br>
 0A<br>
 */
+(NSData *) printAndFeedLine;
/**
 Print and go back to standard mode<br>
 FF<br>
 OC<br>
 */
+(NSData *) printAndBackStandardModel;
/**
 Print and tab<br>
 CR<br>
 0D<br>
 */
+(NSData *) printAndTabs;
/**
 Cancel print data in page mode<br>
 CAN<br>
 18<br>
 */
+(NSData *) canclePrintDataByPageModel;
/**
 Transfer real-time status<br>
 DLE EOT n<br>
 10 04 n<br>
 (int) n: 1<=n<=4.<br>
 */
+(NSData *) sendRealTimeStatus:(int) n;
/**
 Real-time request to printer<br>
 DLE ENQ n<br>
 10 05 n<br>
 (int) n: 1<=n<=2.<br>
 */
+(NSData *) requestRealTimeForPrint:(int) n;
/**
 Generate cash box pulses in real time<br>
 DLE DC4 n m t<br>
 10 14 01 m t<br>
 (int) m: m=0,或1；<br>
 (int) t: 1<=t<=8.<br>
 */
+(NSData *) openCashBoxRealTimeWithM:(int) m andT:(int) t;
/**
 Printing in page mode<br>
 ESC FF<br>
 1B 0C<br>
 This command is only valid in page mode<br>
 */
+(NSData *) printUnderPageModel;
/**
 Set character right spacing<br>
 1B 20 n<br>
 (int) n: 0~255,in dots.<br>
 */
+(NSData *) setCharRightSpace:(int) n;
/**
 Select print mode<br>
 ESC !n<br>
 1B 21 n<br>
 (int) n: 0~255, the last digit of n, 0: cancel, 1: select.<br>
 */
+(NSData *) selectPrintModel:(int) n;
/**
 Set absolute print position<br>
 ESC $ nL nH<br>
 1B 24 nL nH<br>
 nL+nH*256 the distance from the beginning of the line<br>
 */
+(NSData *) setAbsolutePrintPositionWithNL:(int) nL andNH:(int) nH;
/**
 Select or cancel user-defined characters<br>
 ESC % n<br>
 1B 25 n<br>
 (int) n: 0~255, the last digit of n, 0: cancel, 1: select.<br>
 */
+(NSData *) selectOrCancleCustomChar:(int) n;
/**
 Define user-defined characters
 ESC * m nL nH d1 d2 ...dk<br>
 (int) c1: start character code<br>
 (int) c2: end character code，32<=c1<=c2<=127<br>
 (Byte*) bytes: character binary data<br>
 */
+(NSData *) defineUserDefinedCharactersWithM:(int) m andNL:(int) nL andNH:(int) nH andBytes:(Byte *) bytes;
/**
 Select bitmap mode<br>
 ESC * m nL nH d1 d2 ...dk<br>
 m  range：0，1，32，33，Density representing different points <br>
 nL range：0-255<br>
 nH range：0-3<br>
 b={d1,d2...dk},m=0,1时，k=nL+256*nH;m=32,33时，k=(nL+256*nH)*3;d:0-255;<br>
 */
+(NSData *) selectBmpModelWithM:(int) m andnL:(int) nL andnH:(int) nH andNSData:(NSData *) data;
/**
 Select or deselect underline mode<br>
 ESC-n<br>
 1B 2D n<br>
 (int) n:0 or 48 cancel;1 or 49 select(by 1 dot);2 or 50 select (by 2 dots).<br>
 */
+(NSData *) selectOrCancleUnderLineModel:(int) n;
/**
 Set default line spacing<br>
 ESC 2<br>
 */
+(NSData *) setDefultLineSpace;
/**
 Set line spacing<br>
 ESC 3 n<br>
 1B 33 n<br>
 */
+(NSData *) setDefultLineSpace:(int) n;
/**
 Select printer<br>
 ESC = n<br>
 1B 3D n<br>
 n:0or1<br>
 */
+(NSData *) selectPrinter:(int) n;
/**
 Cancel user-defined characters<br>
 ESC ? n<br>
 Cancel the character with code n in user-defined characters<br>
 n range：32-127<br>
 */
+(NSData *) cancleUserDefinedCharacters:(int) n;
/**
 Initialize the printer<br>
 ESC @<br>
 1B 40<br>
 */
+(NSData *) initializePrinter;
/**
 Set the horizontal tab position<br>
 ESC D n1 ...nk NUL<br>
 data={n1...nk};k<=32;Tab distance=character width*k<br>
 */
+(NSData *) setHorizontalTabsPosition:(NSData *) data;
/**
 Select or deselect bold mode<br>
 ESC E n<br>
 1B 45 n<br>
 (int) n: 0~255, the last digit of n, 0: cancel, 1: select.<br>
 */
+(NSData *) selectOrCancleBoldModel:(int) n;
/**
 Select or cancel dual printing mode<br>
 ESC G n<br>
 1B 47 n<br>
 (int) n: 0~255, the last digit of n, 0: cancel, 1: select.<br>
 */
+(NSData *) selectOrCancleDoublePrintModel:(int) n;
/**
 Print and feed<br>
 ESC J n<br>
 1B 4A n<br>
 (int) n: specify the length(in inch) feeds.
 */
+(NSData *) printAndFeed:(int) n;
/**
 Select page mode<br>
 ESC L<br>
 1B 4C<br>
 
 */
+(NSData *) selectPagemodel;
/**
 Select font<br>
 ESC M n<br>
 1B 4D n<br>
 n range： 0，1，48，49；<br>
 */
+(NSData *) selectFont:(int) n;
/**
 Select international character set<br>
 ESC R n<br>
 n:0-15，Means an international character set<br>
 1B 52 n<br>
 */
+(NSData *) selectInternationCharacterSets:(int) n;
/**
 Select standard mode<br>
 ESC S<br>
 1B 53<br>
 */
+(NSData *) selectStabdardModel;
/**
 Select the print area orientation in page mode<br>
 ESC T n<br>
 1B 54 n<br>
 (int) n: 0<=n<=3 or 48<=n<=51;n means specify the orientation and starting position of the print area<br>
 */
+(NSData *) selectPrintDirectionUnderPageModel:(int) n;
/**
 Select or deselect Rotate 90 degrees clockwise<br>
 This command is only valid in page mode<br>
 ESC V n<br>
 1B 56 n<br>
 (int) n: n=0 or 48 means cancel；n=1 or 49 means select.<br>
 */
+(NSData *) selectOrCancleCW90:(int) n;
/**
 Setting the print area in page mode<br>
 ESC W xL xH yL yH dxL dxH dyL dyH<br>
 1B 57 xL xH yL yH dxL dxH dyL dyH<br>
 xL+xH*256 Means the start bit in the x direction<br>
 yL+yH*256 Means the start bit in the y direction<br>
 dxL+dxH*256 Means width in x direction <br>
 dyL+dyH*256 Means height in y direction<br>
 */
+(NSData *) setPrintAreaUnderPageModelWithxL:(int) xL
                                       andxH:(int) xH
                                       andyL:(int) yL
                                       andyH:(int) yH
                                      anddxL:(int) dxL
                                      anddxH:(int) dxH
                                      anddyL:(int) dyL
                                      anddyH:(int) dyH;
/**
 Set relative landscape print position<br>
 ESC \ nL nH<br>
 1B 5C nL nH<br>
 nL+nH*256 Means the set size<br>
 */
+(NSData *) setRelativeHorizontalPrintPositionWithnL:(int) nL andnH:(int) nH;
/**
 Select an alignment<br>
 ESC a n<br>
 1B 61 n<br>
 */
+(NSData *) selectAlignment:(int) n;
/**
 Select the printer sensor to output the paper-cut signal<br>
 ESC c 3 n<br>
 1B 63 33 n<br>
 (int) n:0~255.<br>
 */
+(NSData *) selectPrintTransducerOutPutPageOutSignal:(int) n;
/**
 Select Printer Sensor - Stop Printing<br>
 ESC c 4 n<br>
 1B 63 34 n<br>
 (int) n:0~255.<br>
 */
+(NSData *) selectPrintTransducerStopPrint:(int) n;
/**
 Allow or disallow keystrokes<br>
 ESC c 5 n<br>
 1B 63 35 n<br>
 (int) n: last decision，1:allow，0:forbid<br>
 */
+(NSData *) allowOrForbidPressButton:(int) n;
/**
 print and advance paper n lines<br>
 ESC d n<br>
 1B 64 n<br>
 (int) n:0~255.<br>
 */
+(NSData *) printAndFeedForwardWhitN:(int) n;
/**
 Generate cash box control pulses<br>
 ESC p m t1 t2<br>
 1B 70 m t1 t2<br>
 (int) m: connection pin ,0 or 1 or 48 or 49.<br>
 t1 ,t2 :0~255.<br>
 */
+(NSData *) creatCashBoxContorPulseWithM:(int) m andT1:(int) t1 andT2:(int) t2;
/**
 Select character code table<br>
 ESC t n<br>
 1B 74 n<br>
 (int) n: 0~10 or 16~19<br>
 */
+(NSData *) selectCharacterCodePage:(int) n;
/**
 To select or cancel upside-down printing<br>
 ESC { n<br>
 1B 7B n<br>
 (int) n: last decision，1:select，0:cancel<br>
 */
+(NSData *) selectOrCancleConvertPrintModel:(int) n;
/**
 Print bitmap downloaded to flash<br>
 FS p n m<br>
 (int) n: means image at n position in flash cache<br>
 (int) m: print flash bitmap way，0~3 or 48~51，means normal，double width，double height，double width and height<br>
 */
+(NSData *) printBmpInFLASHWithN:(int) n andM:(int) m;
/**
 Define flash bitmap<br>
 FS q n [xL xH yL yH d1...dk]...[xL xH yL yH d1...dk]<br>
 1C 71 n data<br>
 n:Define bitmap counts<br>
 data=[xL xH yL yH d1...dk]...[xL xH yL yH d1...dk]，means the data of bitmap，each bitmap include xL xH yL yH means bitmap's width and height<br>
 */
+(NSData *)definedFlashBmpWithN:(int)n andBmp:(UIImage *)image andBmpType:(BmpType) bmptype andPrintType:(PrintRasterType) type andPaperHeight:(int) paperheight;
/**
 Select character size<br>
 GS ! n<br>
 (int) n:0~255,n 0-3 character height，4-7 character width<br>
 */
+(NSData *) selectCharacterSize:(int) n;
/**
 Set absolute position in page mode<br>
 GS $ nL nH<br>
 1D 24 nL nH<br>
 nL ,nH range：0~255，nL+nH*256 means position，unit:inch<br>
 */
+(NSData *) setAbsolutePositionUnderPageModelWithnL:(int) nL andnH:(int) nH;
/**
 Define download bitmap<br>
 GS x y[d1...d(8*xy)]<br>
 1D 2A data<br>
 (UIImage*) image :image<br>
 */
+(NSData *)definedDownLoadBmp:(UIImage *)image byType:(BmpType) bmptype;
/**
 Execute printer data hex dump<br>
 GS ( A pL pH n m<br>
 1D 28 41 02 00 00 01<br>
 */
+(NSData *) executePrintDataSavaByTeansformToHex;
/**
 Print download bitmap<br>
 GS / m<br>
 1D 2F m<br>
 (int) m:print mode，range：0~3 or 48~51.<br>
 */
+(NSData *) printDownLoadBmp:(int) m;
/**
 Start or end macro definition<br>
 GS :<br>
 1D 3A<br>
 */
+(NSData *) startOrStopMacrodeFinition;
/**
 Select or cancel the black and white reverse print mode<br>
 GS B n<br>
 1D 42 n<br>
 (int) n: the last digit of n. 1:select; 0:cancel.<br>
 */
+(NSData *) selectOrCancleInvertPrintModel:(int) n;
/**
 Select the HRI character print position<br>
 GS H n<br>
 1D 48 n<br>
 (int) n:0~3 or 48~51,means the printing position of the characters relative to the barcode。<br>
 */
+(NSData *) selectHRICharactersPrintPosition:(int) n;

/**
 Set left margin<br>
 GS L nL nH<br>
 1D 4C nL nH<br>
 (nL+nH*256)*horiz movement unit，means left margin，unit：inch.<br>
 */

+(NSData *) setLeftSpaceWithnL:(int) nL andnH:(int) nH;
/**
 Set horizontal and vertical movement units<br>
 GS P x y<br>
 1D 50 x y<br>
 (int) x: horizontal，0~255.<br>
 (int) y: vertical，0~255.<br>
 */

+(NSData *) setHorizontalAndVerticalMoveUnitWithX:(int) x andY:(int) y;
/**
 Select the cut paper mode and cut the paper<br>
 GS V m<br>
 1D 56 m<br>
 (int) m:0 or 48, full cut;1 or 49，half cut.<br>
 */

+(NSData *) selectCutPageModelAndCutpage:(int) m;

/**
 Select the cut paper mode and cut the paper<br>
 GS V m n<br>
 1D 56 m n<br>
 (int) m: m=66.<br>
 (int) n: paper feed n，and half cut paper<br>
  */

+(NSData *) selectCutPageModelAndCutpageWithM:(int) m andN:(int) n;
/**
 Set the print area width<br>
 GS W nL nH<br>
 1D 57 nL nH<br>
 (nL+nH*256)*horiz movement unit，means print area width.<br>
 */
+(NSData *) setPrintAreaWidthWithnL:(int) nL andnH:(int) nH;
/**
 Set absolute print position in page mode<br>
 GS \ nL nH<br>
 1D 5C nL nH<br>
 (nL+nH*256)*vertical movement unit，means vertical movement distance relative to the current print position.<br>
 */
 +(NSData *) setVertivalRelativePositionUnderPageModelWithNL:(int) nL andNH:(int) nH;
/**
 Execute macro command<br>
 GS ^ r t m<br>
 1D 5E r t m<br>
 (int) r:0~255,execute counts.<br>
 (int) t:0~255,execute wait time.<br>
 (int) m:0 or 1,execute model.<br>
 */
+(NSData *) executeMacrodeCommandWithR:(int) r andT:(int) t andM:(int) m;
/**
 Turn automatic status return on or off<br>
 GS a n<br>
 1D 61 n<br>
 (int) n: 0~255,n each bit means a different type of status return.<br>
 */
+(NSData *) openOrCloseAutoReturnPrintState:(int) n;
/**
 Select HRI font<br>
 GS f n<br>
 1D 66 n<br>
 (int) n: 0 or 48 normal；1 or 49 compression.<br>
 */
+(NSData *) selectHRIFont:(int) n;
/**
 Select barcode height<br>
 GS h n<br>
 1D 68 n<br>
 (int) n: 1~255,defualt:162.<br>
 */
+(NSData *) setBarcodeHeight:(int) n;
/**
 Print barcode<br>
 GS k m d1...dk NUL<br>
 1D 6B m d1...dk 00<br>
 (int) m:barcode type，0~6.<br>
 (NSString*) content: barcode content.<br>
 */
+(NSData *) printBarcodeWithM:(int) m andContent:(NSString *) content useEnCodeing:(NSStringEncoding) strEncoding;
/**
 Print barcode<br>
 GS k m n d1...dk<br>
 1D 6B m n d1...dk<br>
 (int) m: barcode type,66~73.<br>
 (int) n: barcode content's width.<br>
 */
+(NSData *) printBarcodeWithM:(int)m andN:(int) n andContent:(NSString *)content useEnCodeing:(NSStringEncoding) strEncoding;
/**
 Return status<br>
 GS r n<br>
 1D 72 n<br>
 (int) n: 1,2,49,50;1 or 49 return
 sensor status ，2 or 50 return to cash box status.<br>
 */
+(NSData *) returnState:(int) n;
/**
 Print raster bitmap<br>
 GS V 0 m<br>
 (PrintRasterType) m:print mode.<br>
 (UIImage *) image:image instance.<br>
 (BmpType) type:dither or threshold.<br>
 
 */
+(NSData *) printRasteBmpWithM:(PrintRasterType) m andImage:(UIImage *) image andType:(BmpType) type;
/**
 Set barcode width<br>
 GS w n<br>
 1D 77 n<br>
 (int) n:2~6,defualt 3.<br>
 */
+(NSData *) setBarcodeWidth:(int) n;
/**
 Set Chinese character mode<br>
 FA ! n<br>
 1C 21 n<br>
 (int) n: 0~255,different bits define character patterns.
 */
+(NSData *) setChineseCharacterModel:(int) n;
/**
 Select Chinese mode<br>
 FS &<br>
 1C 26<br>
 */
+(NSData *) selectChineseCharacterModel;
/**
 Select or cancel Chinese character underline mode<br>
 FS - n<br>
 1C 2D n<br>
 (int) n:0~2 or 48~50.<br>
 */
+(NSData *) selectOrCancelChineseCharUnderLineModel:(int) n;
/**
 Cancel Chinese mode<br>
 FS .<br>
 1C 2E<br>
 */
+(NSData *) CancelChineseCharModel;
/**
 User-defined Chinese characters<br>
 FS 2 c1 c2 d1...dk<br>
 1C 32 FE c2 d1...dk<br>
 (int) c2: A1H<=c2<=FEH.<br>
 (Byte*) bytes:means byte array of chinese character.<br>
 */
+(NSData *) definedUserDefinedChineseCharWithCPosition:(int) c2 andNsdata:(Byte *) bytes;
/**
 Set the left and right spacing of Chinese characters<br>
 FS S n1 n2<br>
 1C 53 n1 n2<br>
 (int) n1:left spacing,0~255.<br>
 (int) n2:right spacing,0~255.<br>
 */
+(NSData *) setChineseCharLeftAndRightSpaceWithN1:(int) n1 andN2:(int) n2;
/**
 Select or cancel the double width and double height of Chinese characters<br>
 FS W n<br>
 1C 57 n<br>
 (int) n:0~255, the last digit of n, 1: select; 0: cancel.<br>
 */
+(NSData *) selectOrCancelChineseCharDoubleWH:(int) n;
/**
 The printer beeps for a single print<br>
 ESC B n t<br>
 1B 42 n t<br>
 (int) n: beeps counts，1~9.<br>
 (int) t: t*50ms means every beep time ，1~9.<br>
 */
+(NSData *) printerOrderBuzzingHintWithRes:(int) n andTime:(int) t;
/**
 The printer beeps and the alarm light flashes<br>
 ESC C m t n<br>
 1B 43 m t n<br>
 (int) m: Number of beeps, number of flashes of alarm light，1~20.<br>
 (int) t: (t*50ms) interval，1~20.<br>
 (int) n: 0~3, 0:no beep no flash; 1:beep; 2:flash, 3:beep and flash<br>
 */
+(NSData *) printerOrderBuzzingAndWaringLightWithM:(int) m andT:(int) t andN:(int) n;
/**
 QRCODE:Set cell size<br>
 GS ( 0 g n<br>
 1D 28 6B 30 67 n<br>
 (int) n:0~16.<br>
 */
+(NSData *) setQRcodeUnitsize:(int) n;
/**
 Set error correction level<br>
 GS ( 0 i n<br>
 1D 28 6B 30 69 n<br>
 */
+(NSData *) setErrorCorrectionLevelForQrcode:(int) n;
/**
 Transfer data to encoding buffer<br>
 GS ( 0 & nL nH d1...dk<br>
 1D 28 6B 30 80 nL nH d1...dk<br>
 (NSString *) str: QR code content.<br>
 */
+(NSData *) sendDataToStoreAreaWitQrcodeConent:(NSString *) str usEnCoding:(NSStringEncoding) strEnCoding;
/**
 Print the QR code of the encoded cache
 GS ( 0 ?<br>
 1D 28 6B 30 81<br>
 */
+(NSData *) printTheQRcodeInStore;
/**
 Print QR code<br>
 GS ( 0 g n<br>
 1D 28 6B 30 67 n....<br>
 (int) n:0~16.<br>
 (int) errLevel:L:48 M:49 Q:50 H:51.<br>
 */
+(NSData *)printQRCode:(int )n level:(int)errLevel code:(NSString *)code useEnCodeing:(NSStringEncoding)strEncoding;
+(NSData *)printDoubleQRCodeWithCellSize:(int)cellSize version:(int)version qr1IndicationX:(int)qr1IndicationX qr1ErrLevel:(NSString *)qr1ErrLevel qr1CodeText:(NSString *)qr1CodeText qr2IndicationX:(int)qr2IndicationX qr2ErrLevel:(NSString *)qr2ErrLevel qr2CodeText:(NSString *)qr2CodeText useEnCodeing:(NSStringEncoding)strEncoding;
/**
 Set the number of columns in the data region<br>
 1D 28 6B 03 00 30 41 n<br>
 */
+(NSData *) setPdf417Columns:(int) n;
/**
 set the width of the moudule<br>
 1D 28 6B 03 00 30 43 n<br>
 */
+(NSData *) setpdf417WidthOfModule:(int) n;
/**
 set the row height<br>
 1D 28 6B 03 00 30 44 n<br>
 */
+(NSData *) setpdf417RowHeight:(int) n;
/**
 store the data in the symbol storage area<br>
 1D 28 68 F9 00 30 50 30 d1...dk<br>
 */
+(NSData *) storethepdf417WithpL:(int) pL andpH:(int) pH andContent:(NSString*) content usEnCoding:(NSStringEncoding) strEnCoding;
/**
 print the pdf417 symbol data in the symbol storage area<br>
 1D 28 6B 03 00 30 51 n<br>
  */
+(NSData *)printPdf417InStore;

@end
