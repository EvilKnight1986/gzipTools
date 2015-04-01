#include "gzip.h"
#include <Windows.h>

int main(void)
{
        Byte* pSrc[9952] = {

        Byte Dst[700480] = {0} ;
        uLong uDstLen = 700480;

        if (-1 != httpgzdecompress(data, 9952, Dst, &uDstLen))
        {
                MessageBox(NULL, TEXT("Decompress Success! "), TEXT("Tips"), MB_OK) ;
        }
        return 0 ;
}
