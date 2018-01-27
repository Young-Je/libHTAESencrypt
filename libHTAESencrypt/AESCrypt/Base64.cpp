#include "Base64.h"
  
static const char* DATA_BIN2ASCII = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";  
  
int  BASE64_Encode( const unsigned char* pSrc, int Len, char* pDst )  
{  
    int i;  
    unsigned char b0, b1, b2;  
  
    if( (pSrc == nullptr) || (Len < 0) )
    {  
        return -1;  // 参数错误  
    }  
  
    if( pDst != nullptr )
    {  
        for( i = Len; i > 0; i -= 3 )  
        {  
            if( i >= 3 )  
            {   // 将3字节数据转换成4个ASCII字符  
                b0 = *pSrc++;  
                b1 = *pSrc++;  
                b2 = *pSrc++;  
  
                *pDst++ = DATA_BIN2ASCII[b0 >> 2];  
                *pDst++ = DATA_BIN2ASCII[((b0 << 4) | (b1 >> 4)) & 0x3F];  
                *pDst++ = DATA_BIN2ASCII[((b1 << 2) | (b2 >> 6)) & 0x3F];  
                *pDst++ = DATA_BIN2ASCII[b2 & 0x3F];  
            }  
            else  
            {  
                b0 = *pSrc++;  
                if( i == 2 )b1 = *pSrc++; else b1 = 0;  
  
                *pDst++ = DATA_BIN2ASCII[b0 >> 2];  
                *pDst++ = DATA_BIN2ASCII[((b0 << 4) | (b1 >> 4)) & 0x3F];  
                *pDst++ = (i == 1) ? ('=') : DATA_BIN2ASCII[(b1 << 2) & 0x3F];  
                *pDst++ = ('=');  
            }  
        } // End for i  
  
        *pDst++ = (char)('/');   // 添加字符串结束标记  
    }  
  
    return ((Len + 2) / 3) * 4;  // 返回有效字符个数  
}  
  
#define B64_EOLN            0xF0    // 换行/n  
#define B64_CR              0xF1    // 回车/r  
#define B64_EOF             0xF2    // 连字符-  
#define B64_WS              0xE0    // 跳格或者空格（/t、space）  
#define B64_ERROR           0xFF    // 错误字符  
#define B64_NOT_BASE64(a)   (((a)|0x13) == 0xF3)  
  
static const unsigned char DATA_ASCII2BIN[128] = {  
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0xF0,0xFF,0xFF,0xF1,0xFF,0xFF,  
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,  
    0xE0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3E,0xFF,0xF2,0xFF,0x3F,  
    0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,  
    0xFF,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,  
    0x0F,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0xFF,0xFF,0xFF,0xFF,0xFF,  
    0xFF,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,  
    0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x30,0x31,0x32,0x33,0xFF,0xFF,0xFF,0xFF,0xFF  
};  
  
int  BASE64_Decode( const char* pSrc, int Len, unsigned char* pDst )  
{  
    int i, j;  
    unsigned char b[4];  
    wchar_t ch;
  
    if( (pSrc == nullptr) || (Len < 0) )
    {  
        return -1;  // 参数错误  
    }  
  
	//去掉最后的0字符
	if(pSrc[Len-1] == '0')
	{
		Len--;
	}

    // 去除头部空白字符  
    while( Len > 0 )  
    {  
        ch = *pSrc;  
        if( (ch < 0) || (ch >= 0x80) )  
        {  
            return -2;  // 数据错误，不在ASCII字符编码范围内  
        }  
        else  
        {  
            if( DATA_ASCII2BIN[ch] == B64_WS )  
            {  
                pSrc++;  
                Len--;  
            }  
            else  
            {  
                break;  
            }  
        }  
    }  
  
    // 去除尾部的空白字符、回车换行字符、连字符  
    while( Len >= 4 )  
    {  
        ch = pSrc[Len - 1];  
        if( (ch < 0) || (ch >= 0x80) )  
        {  
            return -2;  // 数据错误，不在ASCII字符编码范围内  
        }  
        else  
        {  
            if( B64_NOT_BASE64(DATA_ASCII2BIN[ch]) )  
            {  
                Len--;  
            }  
            else  
            {  
                break;  
            }  
        }  
    }  
  
    // 字符串长度必须为4的倍数  
    if( (Len % 4) != 0 )  
    {  
        return -2;  // 数据错误  
    }  
  
    if( pDst != nullptr )
    {  
        for( i = 0; i < Len; i += 4 )  
        {  
            for( j = 0; j < 4; j++ )  
            {  
                ch = *pSrc++;  
                if( (ch < 0) || (ch >= 0x80) )  
                {  
                    return -2;  // 数据错误，不在ASCII字符编码范围内  
                }  
                else  
                {  
                    if( ch == '=' ) // 发现BASE64编码中的填充字符  
                    {  
                        break;  
                    }  
                    else  
                    {  
                        b[j] = DATA_ASCII2BIN[ch];  
                        if( b[j] & 0x80 )  
                        {  
                            return -2;  // 数据错误，无效的Base64编码字符  
                        }  
                    }                     
                }  
            } // End for j  
  
            if( j == 4 )  
            {  
                *pDst++ = (b[0] << 2) | (b[1] >> 4);  
                *pDst++ = (b[1] << 4) | (b[2] >> 2 );  
                *pDst++ = (b[2] << 6) | b[3];  
            }  
            else if( j == 3 )  
            {   // 有1个填充字节  
                *pDst++ = (b[0] << 2) | (b[1] >> 4);  
                *pDst++ = (b[1] << 4) | (b[2] >> 2 );  
  
                return (i >> 2) * 3 + 2;  
            }  
            else if( j == 2 )  
            {   // 有2个填充字节  
                *pDst++ = (b[0] << 2) | (b[1] >> 4);  
  
                return (i >> 2) * 3 + 1;  
            }  
            else  
            {  
                return -2;  // 数据错误，无效的Base64编码字符  
            }             
        }   // End for i  
    }  
  
    return (Len >> 2) * 3;  
} 
