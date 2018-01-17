#include <stdio.h>
#include <math.h>

// IEEE754标准的64位浮点数存储格式
const int DoubleExp = (1<<10)-1;

typedef struct UFDP {
    unsigned long Fraction:52;
    unsigned long Exp:11;
    unsigned long S:1;
}UFDP;

void showDouble(double a)
{
    char *p2=(char*)&a;
    printf("showDouble : 0x ");
    for(int i = sizeof(a)-1 ; i >= 0 ; i-- )
    {
        printf("%02x ",*(p2+i) & 0x00000000000000ff);
    }
    printf("\n");
}

void showIEEE754(double a)
{
    // IEEE754
    unsigned long b=0;
    unsigned long c=0,logLen=0;
    printf("showIEEE754 a = %lf\n",a);
    if(a < 0) c = 1;
    b |= (c<<63);

    logLen = long(log2(long(a)));
    printf("showIEEE754 logLen = %d\n",logLen);
    c = (logLen + DoubleExp) << 52 ;
    printf("showIEEE754 c = %ld(0x%0lx)\n",c,c);
    b |= c;
    printf("showIEEE754 b = 0x%0lx\n",b);

    unsigned long varTmp=long(fabs(a));
    while((varTmp | 0xffefffffffffffff) != 0xffffffffffffffff)
    {
        varTmp = varTmp << 1;
    //    printf("showIEEE754 varTmp = 0x%08x\n",varTmp);
    }
    varTmp = varTmp & 0x000fffffffffffff;
    printf("showIEEE754 varTmp = 0x%0lx\n",varTmp);
    c = varTmp;
    printf("showIEEE754 c = 0x%0lx\n",c);
    double a1 = a - long(a);
    for(int i=52-logLen-1;i>0;i--)
    {
        a1 *= 2;
        printf("showIEEE754 i = %d , a1 = %lf , ",i,a1);
        // 将十进制的小数转换为二进制的小数的方法为将小数*2，取整数部分
        if( a1 > 0.999999 )
        {
            c |= ((unsigned long)(1) << i);
            a1 = a1 - long(a1);
            printf("showIEEE754 c = %0lx , ",c);
        }
        printf("showIEEE754 b = 0x%0lx\n",b);
    }
    b |= c;
    printf("showIEEE754 : 0x%0lx\n",b);

}

int main()
{
    double a = 12.5;
    UFDP *p = (UFDP*)&a;
    unsigned long b=0;

    printf("sizeof(double) : %d\n",sizeof(double));
    printf("sizeof(long) : %d\n",sizeof(long));

    printf("a = %lf\n",a);
    showDouble(a);
    printf("UFP : %0X,%0X,%0X\n",p->S,p->Exp,p->Fraction);
    b = ((unsigned long)(p->S)<<63) | ((unsigned long)(p->Exp)<<52) | p->Fraction;
    printf("b : 0x%0x\n",b);
    showIEEE754(a);
}