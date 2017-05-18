#include <reg52.h>

#define ON  0
#define OFF 1

char red_delay = 11;   // 红灯延迟
char green_delay = 7;
char yellow_delay = 3;



// 定时器0 初始化
void timer0_init();
// 按键扫描
void key_scan();
// 更新红绿灯
void update_LED();
// 关闭所有的灯
void emergency_fun();
// 显示剩余时间
void show_time(void);
// 初始化引脚 全部拉低
void init_pin(void);
// 设置函数
void setting_fun(void);


// 引脚定义
// 紧急按钮
sbit key_eme     = P1^2;
sbit key_setting = P1^3;
sbit key_add     = P1^4;
sbit key_sub     = P1^5;

sbit car_left_ew   = P3^0;
sbit car_red_ew    = P3^1;
sbit car_yellow_ew = P3^2;
sbit car_green_ew  = P3^3;
sbit car_right_ew  = P3^4;

sbit car_left_sn   = P3^5;
sbit car_red_sn    = P3^6;
sbit car_yellow_sn = P3^7;
sbit car_green_sn  = P1^0;
sbit car_right_sn  = P1^1;


sbit peo_green  = P2^7;
sbit peo_red    = P2^6;  


// 数码管
sbit car_lock_high = P2^2;
sbit car_lock_low  = P2^3; 

sbit car_lock_high_sn = P2^4;
sbit car_lock_low_sn  = P2^5;
 
sbit peo_lock_high = P2^0;
sbit peo_lock_low  = P2^1;  

unsigned char time_ew ;   // 秒
unsigned char time_sn ;
unsigned char peo_time;
//                                0     1   2    3    4    5   6    7    8      9
const unsigned char code duan[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80, 0x90};
// 0 1 人行道   2 3  东西车道
unsigned char time_array[6] ={0};

typedef enum 
{
    red,
    yellow,
    green, 
    emergency, // 紧急境况
    setting,   // 设置状态
} LedState;

LedState state,state1;

char setState = -1;  // 0 red 1 green 2 yellow 3 right

void main(void)
{
    init_pin();
    state = red;    // 默认是红灯
    state1 = green;
    time_ew   = red_delay ;   // 秒
    time_sn   = green_delay;
    peo_time  = red_delay ;    

    car_right_ew = 0;  // 右转灯常亮
    car_right_sn = 0;
    // 初始化定时器0 定时50ms 
    timer0_init();
    
    while(1)
    {
     // 扫描按键
     key_scan();
     // 更新LED
     update_LED();
     // 显示剩余时间 
     show_time();
    }   
}

void key_scan()
{   
    static char key_eme_flag = 0,key_flag = 0;
    // 紧急境况 
    if(key_eme == 0)  
       key_eme_flag = 1;
    else if( key_eme_flag == 1){
        key_eme_flag = 0;
        // 如果当前状态是 紧急或者设置状态  则退出当前状态 进入红绿灯状态
        if(state == emergency || state == setting)
        {
          state    = red;          // 恢复为红灯状态
          time_ew  = red_delay ;   // 秒
          peo_time = red_delay ; 
        }
        else{
            state  = emergency;  
            state1 = emergency;
        }            
    }
    if(key_setting == 0)      // 状态机
        key_flag = 1;
    else if(key_flag == 1)
    {
       key_flag = 0;
       if(state == setting) 
       {  
         if( setState++ >= 3) setState = 0;
       }
       else // 如果不是设置状态 进入设置状态
       {
          state = setting; 
          setState = 0; // 默认第一个设置是红灯
        }
    }
}


void show_time(void)
{
  static unsigned char i =0;  // 状态延时
  static unsigned char state = 0; // 数码管扫描
  if( i++ >= 100)
  { 
    i=0;
    if(state == 0)
    if(peo_time>=0 && peo_time <= 99 ){
        time_array[0] = peo_time/10;
        time_array[1] = peo_time%10;
    }
    if(state ==2)
    if(time_ew>=0 && time_ew <= 99 ){
        time_array[2] = time_ew/10;
        time_array[3] = time_ew%10;      
     }
    if(state == 4)
    if(time_sn >=0 && time_sn <=99 )
    {
        time_array[4] = time_sn/10;
        time_array[5] = time_sn%10;
    }
    P0 = 0xFF; // 清屏
    switch(state)
    {
        case 0: peo_lock_high    = 1; car_lock_low_sn  = 0;
            break;
        case 1: peo_lock_low     = 1; peo_lock_high    = 0;
            break; 
        case 2: car_lock_high    = 1; peo_lock_low     = 0;
            break;
        case 3: car_lock_low     = 1; car_lock_high    = 0;
            break; 
        case 4: car_lock_high_sn = 1; car_lock_low     = 0;
            break;
        case 5: car_lock_low_sn  = 1; car_lock_high_sn = 0; 
            break; 
    }
    P0 = duan[time_array[state++]];   
    if((state)>=6) state = 0;
  }   
}

// 更新led灯
void update_LED()
{   
    switch(state)
    {
        case red:
            car_red_ew    = ON;  // 车 红灯
            car_green_ew  = OFF;
            car_yellow_ew = OFF;
            car_left_ew   = OFF;
  
            peo_green  = ON;      // 人行道 绿灯
            peo_red    = OFF; 
            break;
        case green : 
            car_red_ew    = OFF;  // 车 红灯
            car_green_ew  = ON;
            car_yellow_ew = OFF;
            car_left_ew   = ON;

            peo_green  = OFF;     // 人行道 绿灯
            peo_red    = ON; 
            break;
        case yellow:
            car_red_ew    = OFF;  // 车 黄灯
            car_green_ew  = OFF;
            car_yellow_ew = ON;
            car_left_ew   = OFF;
            
            peo_green  = OFF;  // 人行道 绿灯
            peo_red = ON; 
            break;

        case emergency:    // 紧急情况下全部灯不亮
             emergency_fun();
            break;
        case setting:  
            // 什么都不做 交给setting_fun做
            setting_fun();
            break;
    }
    switch(state1)
    {
        case red: 
            car_red_sn    = ON;  // 南北 绿灯
            car_green_sn  = OFF;
            car_yellow_sn = OFF;
            car_left_sn   = OFF;
            
//            peo_green  = ON;      // 人行道 绿灯
//            peo_red    = OFF; 
            break;
        case green : 
            car_red_sn    = OFF;  // 南北 绿灯
            car_green_sn  = ON;
            car_yellow_sn = OFF;
            car_left_sn   = ON;
            
//            peo_green  = OFF;     // 人行道 绿灯
//            peo_red    = ON; 
            break;
        case yellow:
      
            car_red_sn    = OFF;  // 南北 绿灯
            car_green_sn  = OFF;
            car_yellow_sn = ON;
            car_left_sn   = OFF;
            
//            peo_green  = OFF;  // 人行道 绿灯
//            peo_red = ON; 
            break;
          case emergency:    // 紧急情况下全部灯不亮
             emergency_fun();
    }
}

void setting_fun(void)
{
    static char key_add_flag = 0;
    static char key_sub_flag = 0;
    switch(setState)
    {
        case 0:
            car_red_ew    = ON;  // 红灯设置状态   红灯亮
            car_green_ew  = OFF;
            car_yellow_ew = OFF;
            car_left_ew   = OFF; 
            if(key_add == 0 )
                key_add_flag = 1;
            else if(key_add_flag == 1)
            {
              key_add_flag = 0;
              if(red_delay++ >= 99) red_delay = 0;
            }
            if(key_sub == 0 )
                key_sub_flag =1;
            else if(key_sub_flag ==1)
            {
                key_sub_flag = 0;
                if(red_delay-- <=0) red_delay = 99;
            }
            time_ew = red_delay;
            peo_time = red_delay;
            break;
        case 1:
            car_red_ew    = OFF;  // 绿灯设置状态   绿灯亮
            car_green_ew  = ON;
            car_yellow_ew = OFF;
            car_left_ew   = OFF; 
            if(key_add == 0 )
                key_add_flag = 1;
            else if(key_add_flag == 1)
            {
              key_add_flag = 0;  
              if(green_delay++ >= 99) green_delay = 0;
            }
            if(key_sub == 0)
                key_sub_flag = 1;
            else if(key_sub_flag ==1)
            {
                key_sub_flag = 0;
                if(green_delay-- <=0) green_delay = 99;
            }
            time_ew = green_delay;
            peo_time = green_delay;
            break;
        case 2:
            car_red_ew    = OFF;  // 黄灯设置状态   黄灯亮
            car_green_ew  = OFF;
            car_yellow_ew = ON;
            car_left_ew   = OFF; 
            if(key_add == 0 )
                key_add_flag = 1;
            else if(key_add_flag == 1)
            {
              key_add_flag = 0;
              if(yellow_delay++ >= 99) yellow_delay = 0;
            }
            if(key_sub == 0)
                key_sub_flag = 1;
            else if(key_sub_flag ==1)
            {
                key_sub_flag = 0;
                if(yellow_delay-- <=0) yellow_delay = 99;
            }
            time_ew = yellow_delay;
            peo_time = yellow_delay;
            break;
        case 3:
            car_red_ew    = OFF;  // 左转设置状态   左转灯亮
            car_green_ew  = OFF;
            car_yellow_ew = OFF;
            car_left_ew   = ON; 
//            if(key_add == 0 )
//                key_flag = 1;
//            else if(key_flag == 1)
//            {
//              key_flag = 0;
//              if(yellow_delay++ >= 99) yellow_delay = 0;
//            }
//            time_ew = yellow_delay;
//            peo_time = yellow_delay;
            break;
    }
}

void init_pin(void)
{
    // 数码管
    car_lock_high = 0;
    car_lock_low  = 0; 

    car_lock_high_sn = 0;
    car_lock_low_sn  = 0;
 
    peo_lock_high = 0;
    peo_lock_low  = 0;  

}

void emergency_fun()
{
    car_left_ew   = OFF;
    car_red_ew    = ON;
    car_green_ew  = OFF;
    car_yellow_ew = OFF;
    car_right_ew  = OFF;

    car_left_sn   = OFF;
    car_red_sn    = ON;
    car_green_sn  = OFF;
    car_yellow_sn = OFF;
    car_right_sn  = OFF;

    
    peo_green  = OFF;
    peo_red    = ON;
 
    car_lock_high = 1 ;
    car_lock_low  = 1 ; 
    peo_lock_high = 1 ;
    peo_lock_low  = 1 ;
    P0 = 0xBF;
}


void state_change()
{
    peo_time--;
    switch(state)
    {
        case red:
            if(time_ew-- == 0) 
            { 
                state  = green;   // 转到green 状态
                time_ew = green_delay;
                peo_time  = yellow_delay+ green_delay + 1 ;           
            }
            break;
        case green: 
            if(time_ew-- == 0) // 绿灯20s
            {
                state = yellow;
                time_ew = yellow_delay; 
            }
            break;
        case yellow: 
            if(time_ew-- == 0)
            {
                state = red;
                time_ew = red_delay;
                peo_time  = red_delay;
            }
            break;
    }
    switch(state1)
    {
        case red:
            if(time_sn-- == 0) 
            { 
                state1  = green;   // 转到green 状态
                time_sn = green_delay;            
            }
            break;
        case green: 
            if(time_sn-- == 0) // 绿灯20s
            {
                state1 = yellow;
                time_sn = yellow_delay; 
            }
            break;
        case yellow: 
            if(time_sn-- == 0)
            {
                state1 = red;
                time_sn = red_delay;
            }
            break;
    }
}

// 中断服务程序
void ISR() interrupt 1      // 定时器 0    
{
    // 用来计算1s的变量
    static char time = 0;
    TH0 = 65536-50000/256;
    TL0 = 65536-50000%256;  // 定时时间50ms
    if(time++ == 20)        // 一秒
    {
        time = 0;     
        state_change();      // 红路灯的状态机
       
    } 
}

void timer0_init()
{
    TMOD |= 0x01;           // 16位定时器模式
    TH0 = 65536-50000/256;
    TL0 = 65536-50000%256;  // 定时时间50ms
    EA  = 1;                // 开总中断
    ET0 = 1;                // 允许定时器0中断
    TR0 = 1;                // 定时开始
}


