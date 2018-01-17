#include <stdio.h>
#include <math.h>

// IEEE754标准的32位浮点数存储格式

const int FloatExp = (1<<7)-1;

typedef struct UFP {
    unsigned int Fraction:23;
    unsigned int Exp:8;
    unsigned int S:1;
}UFP;


void showFloat(float a)
{
    // 内存表示形式
    char *p2=(char*)&a;
    printf("showFloat : 0x ");
    for(int i = sizeof(a)-1 ; i >= 0 ; i-- )
    {
        printf("%02x ",*(p2+i) & 0x000000ff);
    }
    printf("\n");
}

void showIEEE754(float a)
{
    // IEEE754 表示形式
    unsigned int b=0;
    unsigned int c=0,logLen=0;
    printf("showIEEE754 a = %f\n",a);

    if(a < 0) c = 1;
    b |= (c<<31);

    logLen = int(log2(int(a)));
    c = (logLen + FloatExp)<<23;
    //printf("showIEEE754 c = %d\n",c);
    b |= c;
    //printf("showIEEE754 b = 0x%08x\n",b);

    // 填入整数部分的二进制数据
    unsigned int varTmp=int(fabs(a));
    while((varTmp | 0xff7fffff) != 0xffffffff)
    {
        varTmp = varTmp << 1;
    //    printf("showIEEE754 varTmp = 0x%08x\n",varTmp);
    }
    printf("showIEEE754 varTmp = 0x%08x\n",varTmp);
    c = varTmp & 0x007fffff; // 去掉尾数最高位1
    printf("showIEEE754 c = 0x%08x\n",c);
    double a1 = a - int(a);
    // 填入小数部分的二进制数据
    for(int i=23-logLen-1;i>0;i--)
    {
        a1 *= 2;
        printf("showIEEE754 i = %d , a1 = %f , ",i,a1);
        // 将十进制的小数转换为二进制的小数的方法为将小数*2，取整数部分
        if( a1 > 0.999999 )
        {
            c |= (1 << i);
            a1 = a1 - long(a1);
            printf("showIEEE754 c = %08x , ",c);
        }
        printf("showIEEE754 b = 0x%08x\n",b);
    }
//    printf("showIEEE754 b = 0x%08x\n",b);
//    printf("showIEEE754 c = 0x%08x\n",c);
    b |= c;
    printf("showIEEE754 : 0x%08x\n",b);

}

int main()
{
    float a = 12.5;
    UFP *p = (UFP*)&a;
    unsigned int b=0;
    unsigned int aTmp1=0,aTmp2=0;
    printf("sizeof(float) : %d\n",sizeof(float));
    printf("sizeof(int) : %d\n",sizeof(int));
    printf("a = %f\n",a);
    showFloat(a);
    printf("UFP : %0X,%0X,%0X\n",p->S,p->Exp,p->Fraction);
    b = ((aTmp1=p->S)<<31) | ((aTmp2=p->Exp)<<23) | p->Fraction;
    printf("b : 0x%08x\n",b);
    showIEEE754(a);
}