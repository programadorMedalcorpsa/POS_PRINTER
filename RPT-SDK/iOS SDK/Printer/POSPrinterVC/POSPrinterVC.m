//
//  POSPrinterVC.m
//  Printer
//

#import "POSPrinterVC.h"
#import "POSPrinterSDK.h"
#import "UIView+Toast.h"

typedef NS_ENUM(NSInteger, ConnectType) {
    NONE = 0,   //None
    BT,         //Bluetooth
    WIFI,       //WiFi
};

@interface POSPrinterVC ()<UITextFieldDelegate, POSBLEManagerDelegate, POSWIFIManagerDelegate>

// connect state tip
@property (weak, nonatomic) IBOutlet UILabel *connectStateLabel;

// wifi
@property (weak, nonatomic) IBOutlet UITextField *wifiTextField;

// connect type
@property (assign, nonatomic) ConnectType connectType;

// indicator
@property (strong, nonatomic) UIActivityIndicatorView *indicator;

// check status button
@property (weak, nonatomic) IBOutlet UIButton *checkStatusButton;

// disconnect button
@property (weak, nonatomic) IBOutlet UIButton *disconnectButton;

// print text button
@property (weak, nonatomic) IBOutlet UIButton *printTextButton;

// print qrcode button
@property (weak, nonatomic) IBOutlet UIButton *printQRCodeButton;

// print barcode button
@property (weak, nonatomic) IBOutlet UIButton *printBarCodeButton;

// print picture button
@property (weak, nonatomic) IBOutlet UIButton *printPictureButton;

// scan bluetooth button
@property (weak, nonatomic) IBOutlet UIButton *scanButton;

// connnect wifi button
@property (weak, nonatomic) IBOutlet UIButton *connectButton;

@end

@implementation POSPrinterVC

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [POSBLEManager sharedInstance].delegate = self;
    [POSWIFIManager sharedInstance].delegate = self;
    
    self.wifiTextField.delegate = self;
    
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(keyboardDismiss)];
    self.view.userInteractionEnabled = YES;
    [self.view addGestureRecognizer:tap];
    
    [self initView];
    
}

- (void)initView {
    _indicator = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
    _indicator.center = self.view.center;
    [self.view addSubview:self.indicator];
    
    _checkStatusButton.layer.cornerRadius = 10.f;
    _disconnectButton.layer.cornerRadius = 10.f;
    _printTextButton.layer.cornerRadius = 10.f;
    _printQRCodeButton.layer.cornerRadius = 10.f;
    _printBarCodeButton.layer.cornerRadius = 10.f;
    _printPictureButton.layer.cornerRadius = 10.f;
    _scanButton.layer.cornerRadius = 10.f;
    _connectButton.layer.cornerRadius = 10.f;
}

- (void)dealloc {
    [[POSBLEManager sharedInstance] removeDelegate:self];
    [self discount:nil];
}

- (void)keyboardDismiss {
    [self.wifiTextField resignFirstResponder];
}


#pragma mark - Action

// check status
- (IBAction)checkStatusAction:(UIButton *)sender {
    Byte queryArr[] = {0x10, 0x04, 0x02};
    NSData *queryData = [NSData dataWithBytes:queryArr length:sizeof(queryArr)];
    
    switch (self.connectType) {
        case WIFI:
        {
            [[POSWIFIManager sharedInstance] writeCommandWithData:queryData receiveCallBack:^(NSData *responseData) {
                [self getStatusWithData:responseData];
            }];
        }
            break;
            
        case BT:
        {
            [[POSBLEManager sharedInstance] writeCommandWithData:queryData receiveCallBack:^(CBCharacteristic *characteristic, NSError *error) {
                NSData *responseData = characteristic.value;
                [self getStatusWithData:responseData];
            }];
        }
            break;
            
        default:
            break;
    }
    
}

- (void)getStatusWithData:(NSData *)responseData {
    
    if (responseData.length == 0) return;
    
    if (responseData.length == 1) {
        const Byte *byte = (Byte *)[responseData bytes];
        unsigned status = byte[0];
        
        if (status == 0x12) {
            [self.view makeToast:@"Ready" duration:1.f position:CSToastPositionCenter];
        } else if (status == 0x16) {
            [self.view makeToast:@"Cover opened" duration:1.f position:CSToastPositionCenter];
        } else if (status == 0x32) {
            [self.view makeToast:@"Paper end" duration:1.f position:CSToastPositionCenter];
        } else if (status == 0x36) {
            [self.view makeToast:@"Cover opened & Paper end" duration:1.f position:CSToastPositionCenter];
        } else {
            [self.view makeToast:@"error" duration:1.f position:CSToastPositionCenter];
        }
    }
}


// wifi connect
- (IBAction)wifiConnectAction:(UIButton *)sender {
    if (self.wifiTextField.text.length == 0) {
        [self.view makeToast:@"please input wifi address" duration:1.f position:CSToastPositionCenter];
    }
    
    if ([POSWIFIManager sharedInstance].isConnect) {
        [[POSWIFIManager sharedInstance] disconnect];
    }
    
    [self keyboardDismiss];
    [self.indicator startAnimating];
    [[POSWIFIManager sharedInstance] connectWithHost:self.wifiTextField.text port:9100];
}

//discount manual
- (IBAction)discount:(UIButton *)sender {
    switch (self.connectType) {
        case BT:
            [[POSBLEManager sharedInstance] disconnectRootPeripheral];
            break;
            
        case WIFI:
            [[POSWIFIManager sharedInstance] disconnect];
            break;
            
        default:
            break;
    }
}

- (void)buttonStateOn {
    _checkStatusButton.enabled = YES;
    _disconnectButton.enabled = YES;
    _printTextButton.enabled = YES;
    _printQRCodeButton.enabled = YES;
    _printBarCodeButton.enabled = YES;
    _printPictureButton.enabled = YES;
}

- (void)buttonStateOff {
    _checkStatusButton.enabled = NO;
    _disconnectButton.enabled = NO;
    _printTextButton.enabled = NO;
    _printQRCodeButton.enabled = NO;
    _printBarCodeButton.enabled = NO;
    _printPictureButton.enabled = NO;
}


#pragma mark - UITextFieldDelegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    return YES;
}


#pragma mark - POSBLEManagerDelegate

//connect success
- (void)POSbleConnectPeripheral:(CBPeripheral *)peripheral {
    _connectType = BT;
    _connectStateLabel.text = @"POS";
    
    [self buttonStateOn];
}

//bluetooth print success
- (void)POSbleWriteValueForCharacteristic:(CBCharacteristic *)character error:(NSError *)error {
    [self.indicator stopAnimating];
}

// disconnect
- (void)POSbleDisconnectPeripheral:(CBPeripheral *)peripheral {
    if ([POSWIFIManager sharedInstance].isConnect) {
        _connectType = WIFI;
        _connectStateLabel.text = @"POS";
    } else {
        _connectType = NONE;
        _connectStateLabel.text = @"NONE";
    }
    
    [self buttonStateOff];
    [self.indicator stopAnimating];
}


#pragma mark - POSWIFIManagerDelegate

//connected success
- (void)POSwifiConnectedToHost:(NSString *)host port:(UInt16)port {
    _connectType = WIFI;
    _connectStateLabel.text = @"POS";
    
    [self buttonStateOn];
    [self.indicator stopAnimating];
    [self.view makeToast:@"connect success" duration:1.f position:CSToastPositionCenter];
}

//disconnected mean error
- (void)POSwifiDisconnectWithError:(NSError *)error {
    if ([POSBLEManager sharedInstance].isConnect) {
        _connectType = BT;
        _connectStateLabel.text = @"POS";
    } else {
        _connectType = NONE;
        _connectStateLabel.text = @"NONE";
    }
    
    [self buttonStateOff];
    [self.indicator stopAnimating];
    [self.view makeToast:[NSString stringWithFormat:@"%@", error] duration:2.f position:CSToastPositionCenter];
}

//print success
- (void)POSwifiWriteValueWithTag:(long)tag {
    [self.indicator stopAnimating];
}


#pragma mark - Test Print

- (void)printWithData:(NSData *)printData {
    switch (self.connectType) {
        case NONE:
            [self.view makeToast:@"please connect printer" duration:1.f position:CSToastPositionCenter];
            break;
            
        case WIFI:
            [[POSWIFIManager sharedInstance] writeCommandWithData:printData];
            break;
            
        case BT:
            [[POSBLEManager sharedInstance] writeCommandWithData:printData];
            break;
            
        default:
            break;
    }
}

- (IBAction)posTextAction:(id)sender {
    NSMutableData *dataM = [NSMutableData dataWithData:[POSCommand initializePrinter]];
    NSStringEncoding gbkEncoding = CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingGB_18030_2000);
    [dataM appendData: [@"123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" dataUsingEncoding: gbkEncoding]];
    [dataM appendData:[POSCommand printAndFeedForwardWhitN:7]];
    [dataM appendData:[POSCommand selectCutPageModelAndCutpage:1]];

    [self printWithData:dataM];
}

- (IBAction)posQRCodeAction:(id)sender {
    NSMutableData *dataM = [NSMutableData dataWithData:[POSCommand initializePrinter]];
    [dataM appendData:[POSCommand selectAlignment:1]];
    [dataM appendData:[POSCommand printQRCode:6 level:48 code:@"www.google.com" useEnCodeing:NSUTF8StringEncoding]];
    [dataM appendData:[POSCommand printAndFeedForwardWhitN:6]];
    [dataM appendData:[POSCommand selectCutPageModelAndCutpage:1]];
    
    [self printWithData:dataM];
}

- (IBAction)posBarCodeAction:(UIButton *)sender {
    NSMutableData *dataM = [NSMutableData dataWithData:[POSCommand initializePrinter]];
    [dataM appendData:[POSCommand selectHRICharactersPrintPosition:2]];
    [dataM appendData:[POSCommand selectAlignment:1]];
    [dataM appendData:[POSCommand printBarcodeWithM:5 andContent:@"12345678" useEnCodeing:NSUTF8StringEncoding]];
    [dataM appendData:[POSCommand printAndFeedForwardWhitN:6]];
    [dataM appendData:[POSCommand selectCutPageModelAndCutpage:1]];
    
    [self printWithData:dataM];
}

- (IBAction)posPictureAction:(id)sender {
    UIImage *img = [UIImage imageNamed:@"image"];
    
    NSMutableData *dataM = [NSMutableData dataWithData:[POSCommand initializePrinter]];
    [dataM appendData:[POSCommand selectAlignment:1]];
    [dataM appendData:[POSCommand printRasteBmpWithM:RasterNolmorWH andImage:img andType:Dithering]];
    [dataM appendData:[POSCommand printAndFeedForwardWhitN:6]];
    [dataM appendData:[POSCommand selectCutPageModelAndCutpage:1]];
    
    [self printWithData:dataM];
}

@end
