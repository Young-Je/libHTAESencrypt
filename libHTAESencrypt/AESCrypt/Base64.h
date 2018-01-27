
#ifdef  __cplusplus  
extern "C" {  
#endif  
  
int  BASE64_Encode( const unsigned char* pSrc, int Len, char* pDst );  
int  BASE64_Decode( const char* pSrc, int Len, unsigned char* pDst );  
  
#ifdef  __cplusplus  
}  
#endif  
