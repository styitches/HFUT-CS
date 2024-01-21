#include "stdio.h"
#define GPKCON0 (*(volatile unsigned long *)0x7F008800)
#define GPKDAT (*(volatile unsigned long *)0x7F008808)

#define GPNCON (*(volatile unsigned long *)0x7F008830)
#define GPNDAT (*(volatile unsigned long *)0x7F008834)

#define GPFCON (*(volatile unsigned int *)0x7F0080A0)
#define GPFDAT (*(volatile unsigned int *)0x7F0080A4)
#define		TCON      	( *((volatile unsigned long *)(PWMTIMER_BASE+0x08)) )
#define		PWMTIMER_BASE			(0x7F006000)
void timer_init(unsigned long utimer, unsigned long uprescaler, unsigned long udivider, unsigned long utcntb, unsigned long utcmpb, int mode_x, int count_x);
void delay_short(volatile unsigned int n) {
    while (n--) {
    }
}
void delay(volatile unsigned int n) {
    while (n--) {
        delay_short(0x7ff);
    }

}
void buzzer_init(void)
{
    // 设置 GPF14 为 输出
    GPFCON |= 1 << 28;
    GPFCON &= ~(1 << 29);
}

int main()
{

    int dat = 0;

    // 配置GPK4-7为输出功能
    GPKCON0 = 0x11110000;

    // 所有LED熄灭
    GPKDAT = 0x000000f0;

    // 配置GPN为输入功能
    GPNCON = 0;

    // 初始化蜂鸣器
    buzzer_init();

    // 轮询的方式查询按键事件
    while (1)
    {
        dat = GPNDAT;
        if (!(dat & (1<<0)))
        {
            // KEY1被按下
            // 设置定时器
            int count = 1;
            int num = 1500000;
            while (num > 0)
            {
                //GPNDAT，低四位有效，哪位按下哪位为0
                if (!(GPNDAT & (1 << 0)))  //意思就是 若k1按下了 那么就进入if
                {
                    delay(10);//防抖
                    count++;             //按下一次 计数一次
                    num = 1500000;       //把倒计时还原
                    while (!(GPNDAT & (1 << 0))) { ; }
                }
                num--;
            }
            if (count%2 && count>0)//奇数次按下，定时器定时0.5s,蜂鸣器鸣叫间隔为1s
            {
                timer_init(0, 65, 4, 31250, 0, 0, count);//后两个参数含义（按键对应的模式、按下的次数）
                GPKDAT=0x00000060;//LED1、4亮
            }
            else if (count % 2 == 0 && count > 0)//偶数次按下，定时器定时0.25s,蜂鸣器鸣叫间隔为0.5s
            {
                timer_init(0, 65, 4, 15625, 0, 0, count);
                GPKDAT=0x00000090;//LED2、3亮
            }
        }
        if (!(dat & (1<<1)))
        {
            // KEY2被按下,两长一短的方式鸣叫
            // 设置定时器
            timer_init(0,65,4,31250,0,1,0);//设置鸣叫时间间隔为1s
			while(!(dat & (1<<1))){
				dat=GPNDAT;
			}	

        }
        if (!(dat & (1<<2)))
        {
            // KEY3被按下,两短一长的方式鸣叫
            // 设置定时器
            timer_init(0,65,4,31250,0,2,0);//设置鸣叫时间间隔为1s
			while(!(dat & (1<<2))){
				dat=GPNDAT;
			}	

        }
        if (!(dat & (1 << 3)))
        {
            // KEY4被按下
            while (!(GPNDAT & (1 << 3))) { ; }
            TCON &=  ~(1<<0);//关闭定时器
            GPKDAT = 0x000000f0;//LED熄灭
            GPFDAT = 0x00000000;//蜂鸣器关闭
        }
    }
}

