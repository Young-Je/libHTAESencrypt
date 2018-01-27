//
//  libHTAESencrypt.m
//  libHTAESencrypt
//
//  Created by yangzhexu on 21/01/2018.
//  Copyright © 2018 yangzhexuxjtu. All rights reserved.
//

#import "libHTAESencrypt.h"
#import "NSString+Base64.h"

@implementation libHTAESencrypt

+ (NSString *)encrypt:(NSString *)message{
    const char * instr = [message UTF8String];
    unsigned long instrlen = [message length];
    char EnData[200] = {0};
    int outlen;
    JX_EncodeQRInfo((char *)instr, (int)instrlen, EnData, &outlen);
    return [NSString stringWithUTF8String:EnData];
}

+ (NSString *)decrypt:(NSString *)base64EncodedString{

    return nil;
}
@end
