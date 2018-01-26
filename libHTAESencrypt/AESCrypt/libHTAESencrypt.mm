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
    
    unsigned char AesBufInfo[256]={0};
    unsigned char k=0;
    const char *key = "HuTongJinMaiKeJij67HKJnu8737<>&#";
    const char * charMessage = [message UTF8String];
    unsigned long lengthMessage = [message length];
    memcpy(AesBufInfo,charMessage,lengthMessage);
    Do_Aes256(AesBufInfo,(unsigned char*)key,AesBufInfo,'e');
    
    char retAesBuf[256]={0};
    for(k=0;k<16;k++)
    {
        sprintf(retAesBuf + 2*k,"%02X",AesBufInfo[k]);
    }
    
    return [NSString stringWithUTF8String:retAesBuf];
}

+ (NSString *)decrypt:(NSString *)base64EncodedString{
    
    return nil;
}
@end
