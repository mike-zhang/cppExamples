#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <endian.h>

#define htonl64 htobe64
#define ntohl64 be64toh

uint64_t htonf64(double dvalue)
{
    uint64_t ulltmp = 0;
    memcpy(&ulltmp,&dvalue,8);
    ulltmp = htonl64(ulltmp);
    return ulltmp;
}

double ntohf64(uint64_t ulvalue)
{
    uint64_t ulltmp = 0;
    double ret = 0.0;
    ulltmp = ntohl64(ulvalue);
    memcpy(&ret,&ulltmp,8);
    return ret;    
}

int main()
{
    double a = 123.456;
    uint64_t b = 0;
    double c = 0.0;
    printf("a = %lf\n",a);
    b = htonf64(a);
    printf("b = %ld\n",b);
    c = ntohf64(b);
    printf("c = %lf\n",c);
    return 0;
}
