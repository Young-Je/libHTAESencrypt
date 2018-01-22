//
//  libHTAESencrypt.m
//  libHTAESencrypt
//
//  Created by yangzhexu on 21/01/2018.
//  Copyright © 2018 yangzhexuxjtu. All rights reserved.
//

#import "libHTAESencrypt.h"

@implementation libHTAESencrypt

+ (NSString *)encrypt:(NSString *)message{
    return [self encrypt:message password:ASEENCRYPTIONKEY];
}

+ (NSString *)decrypt:(NSString *)base64EncodedString{
    return [self decrypt:base64EncodedString password:ASEENCRYPTIONKEY];
}
@end
