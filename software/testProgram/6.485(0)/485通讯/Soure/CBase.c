#include "Include.h"

//粗略延时 不精确！
void DelayNuS(unsigned int i)
{
        unsigned char t = 0;
        for(;i>0;i--)
        {
                for(t=0;t<2;t++)
                {
                }
        }
}

void DelayNmS(unsigned int i)
{
        for(;i>0;i--)
        {
                DelayNuS(1000);
        }
}

