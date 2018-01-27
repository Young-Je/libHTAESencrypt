//
//  libHTAESencrypt.h
//  libHTAESencrypt
//
//  Created by yangzhexu on 21/01/2018.
//  Copyright © 2018 yangzhexuxjtu. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SrcAes256.h"
#define ASEENCRYPTIONKEY @"HuTongJinMaiKeJij67HKJnu8737<>&#"
@interface libHTAESencrypt : NSObject
+ (NSString *)encrypt:(NSString *)message;
+ (NSString *)decrypt:(NSString *)base64EncodedString;
@end
