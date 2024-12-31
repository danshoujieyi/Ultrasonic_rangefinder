#include "MENU.h"

extern float temperature_1000,humidity_100;
extern float distance_1000,distance_offset_1000;

extern unsigned char time_data[8];
extern char *weekdays_temp[1];

unsigned char Display_Array[76];
extern uint16_t Data_Distance;
uint8_t my_congfig[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0F, 0x1F, 0x3F, 0x00}; /*"δ�����ļ�",0*/

//要写入到STM32 FLASH的字符串数组
uint16_t datatemp[6] = {0,0,0,0,0,0};// 末尾用来存储报警阈值

///////////////
extern u8 c;
extern uint32_t cnt;
void My_ShowChar(u8 x,u8 y,u8 mode)
{
    u8 i,m,temp,size2;
    u8 x0=x,y0=y;
    if(16==8)size2=6;
    else size2=(16/8+((16%8)?1:0))*(16/2);  //得到字体一个字符对应点阵集所占的字节数
    for(i=0;i<size2;i++)
    {
        temp=my_congfig[i];
        for(m=0;m<8;m++)
        {
            if(temp&0x01)OLED_DrawPoint(x,y,mode);
            else OLED_DrawPoint(x,y,!mode);
            temp>>=1;
            y++;
        }
        x++;
        if((16!=8)&&((x-x0)==16/2))
        {x=x0;y0=y0+8;}
        y=y0;
    }
//	OLED_Refresh();
}
void  menu_1(void)///菜单一
{
    u8 i;
//	OLED_Clear();
    //********************************************///
    OLED_DrawLine(0,0,80,0,1);
    OLED_DrawLine(0,0,0,46,1);
    OLED_DrawLine(80,0,80,46,1);
    OLED_DrawLine(0,46,80,46,1);
    for(i=5;i<=40;i+=5)
        OLED_DrawLine(77,i,80,i,1);

    OLED_DrawLine(80,46,84,46,1);OLED_ShowString(81,47,(unsigned char*)"0cm",8,1);
    OLED_DrawLine(80,25,84,25,1);OLED_ShowString(81,27,(unsigned char*)"200cm",8,1);
    OLED_DrawLine(80,0,84,0,1);	 OLED_ShowString(81,2 ,(unsigned char*)"450cm",8,1);

    OLED_ShowChinese(0,48,0,16,1);
    OLED_ShowChinese(16,48,1,16,1);
    OLED_ShowChinese(32,48,2,16,1);
    OLED_ShowChinese(48,48,3,16,1);
    OLED_ShowChinese(64,48,4,16,1);

//	OLED_Refresh();
}

void  menu_2(void)///菜单二
{
//	OLED_Clear();
    OLED_ShowString(0,0,(unsigned char*)"Real-time:   CM",16,1);
//	OLED_DrawLine(0,16,127,16,1);
//	OLED_DrawLine(0,16,0,64,1);
//	OLED_DrawLine(0,63,127,63,1);
//	OLED_DrawLine(127,16,127,63,1);
    OLED_DrawLine(64,16,64,64,1);

    OLED_ShowString(0,16 ,(unsigned char*)"1:   cm",16,1);
    OLED_ShowString(0,32 ,(unsigned char*)"2:   cm",16,1);
    OLED_ShowString(0,48 ,(unsigned char*)"3:   cm",16,1);

    OLED_ShowString(65,16 ,(unsigned char*)"4:   cm",16,1);
    OLED_ShowString(65,32 ,(unsigned char*)"5:   cm",16,1);
    OLED_ShowString(65,48 ,(unsigned char*)"6:   cm",16,1);
//	OLED_Refresh();
}
// Header:  显示时间界面
// File Name: menu_3
// Author:
// Date:
void menu_3(void)
{
    OLED_ShowChinese(0,0,27,16,1);
    OLED_ShowChinese(16,0,28,16,1);
    OLED_ShowNum (30,0,time_data[0],4,16,1);
    OLED_ShowChar(62,0,'-',16,1);
    OLED_ShowNum (70,0,time_data[1],2,16,1);
    OLED_ShowChar(86,0,'-',16,1);
    OLED_ShowNum (94,0,time_data[2],2,16,1);

    OLED_ShowChinese(0,24,29,16,1);
    OLED_ShowChinese(16,24,30,16,1);
    OLED_ShowNum (40,24,time_data[3],2,16,1);
    OLED_ShowChar(56,24,':',16,1);
    OLED_ShowNum (64,24,time_data[4],2,16,1);
    OLED_ShowChar(80,24,':',16,1);
    OLED_ShowNum (88,24,time_data[5],2,16,1);

    OLED_ShowString(0,48,weekdays_temp[0],16,1);

//    OLED_ShowChinese(0,48,0,16,1);
//    OLED_ShowChinese(16,48,1,16,1);
//    OLED_ShowChinese(32,48,2,16,1);
//    OLED_ShowChinese(48,48,3,16,1);
//    OLED_ShowChinese(64,48,4,16,1);
    OLED_ShowString(106,48 ,(unsigned char*)"cm",16,1);
//	OLED_Refresh();
}

void menu_4(void){
    OLED_ShowChinese(0,0,5,16,1);
    OLED_ShowChinese(16,0,6,16,1);
    OLED_ShowChinese(32,0,7,16,1);
//      temperature = SHT20_Read(T_ADDR);
    //temperature = temperature*1000;
    //OLED_ShowNum(48,0,(int)temperature/1000,3,16,1);
    OLED_ShowChar(72,0,'.',16,1);
    //OLED_ShowNum(78, 0, (int)temperature%1000,3,16,1);
    OLED_ShowChinese(104,0,13,16,1);

    OLED_ShowChinese(0,16,8,16,1);
    OLED_ShowChinese(16,16,9,16,1);
    OLED_ShowChinese(32,16,10,16,1);
    OLED_ShowChinese(48,16,11,16,1);
    OLED_ShowChinese(61,16,12,16,1);
//      humidity = SHT20_Read(PH_ADDR);
    //humidity = humidity*100;
    //OLED_ShowNum(70,16,(int)humidity/100,2,16,1);
    OLED_ShowChar(86,16,'.',16,1);
    //OLED_ShowNum(92, 16, (int)humidity%100,2,16,1);
    OLED_ShowChinese(108,16,14,16,1);

    OLED_ShowChinese(0,32,15,16,1);
    OLED_ShowChinese(16,32,16,16,1);
    OLED_ShowChinese(32,32,17,16,1);
//    distance = Hcsr04GetLength();
    //distance = distance*1000;
    //OLED_ShowNum(50,32,(int)distance/1000,3,16,1);
    OLED_ShowChar(74,32,'.',16,1);
    //OLED_ShowNum(80, 32, (int)distance%1000,3,16,1);
    OLED_ShowChar(104,32,'c',16,1);
    OLED_ShowChar(112,32,'m',16,1);

    OLED_ShowChinese(0,48,20,16,1);
    OLED_ShowChinese(16,48,16,16,1);
    OLED_ShowChinese(32,48,17,16,1);
//      distance_offset = Hcsr04GetLength_offset();
    //distance_offset = distance_offset*1000;
    //OLED_ShowNum(50,48,(int)distance_offset/1000,3,16,1);
    OLED_ShowChar(74,48,'.',16,1);
    //OLED_ShowNum(80, 48, (int)distance_offset%1000,3,16,1);
    OLED_ShowChar(104,48,'c',16,1);
    OLED_ShowChar(112,48,'m',16,1);

    OLED_Refresh();
}

void menu_5(void){
    //    distance = Hcsr04GetLength();
    //distance = distance*1000;
    OLED_ShowChinese(0,0,15,16,1);
    OLED_ShowChinese(16,0,16,16,1);
    OLED_ShowChinese(32,0,17,16,1);
    //OLED_ShowNum(50,32,(int)distance/1000,3,16,1);
    OLED_ShowChar(74,0,'.',16,1);
    //OLED_ShowNum(80, 32, (int)distance%1000,3,16,1);
    OLED_ShowChar(104,0,'c',16,1);
    OLED_ShowChar(112,0,'m',16,1);

    OLED_ShowChinese(0,16,20,16,1);
    OLED_ShowChinese(16,16,16,16,1);
    OLED_ShowChinese(32,16,17,16,1);
//      distance_offset = Hcsr04GetLength_offset();
    //distance_offset = distance_offset*1000;
    //OLED_ShowNum(50,48,(int)distance_offset/1000,3,16,1);
    OLED_ShowChar(74,16,'.',16,1);
    //OLED_ShowNum(80, 48, (int)distance_offset%1000,3,16,1);
    OLED_ShowChar(104,16,'c',16,1);
    OLED_ShowChar(112,16,'m',16,1);

    OLED_ShowChinese(0,32,21,16,1);
    OLED_ShowChinese(16,32,22,16,1);
    OLED_ShowChinese(32,32,23,16,1);
    OLED_ShowChinese(48,32,24,16,1);
    OLED_ShowChinese(64,32,12,16,1);
   // OLED_ShowNum(80,32,cnt[0],2,16,1);
    OLED_ShowChar(104,32,'c',16,1);
    OLED_ShowChar(112,32,'m',16,1);

    OLED_ShowChinese(0,48,25,16,1);
    OLED_ShowChinese(16,48,26,16,1);
    OLED_ShowChinese(32,48,21,16,1);
    OLED_ShowChinese(48,48,22,16,1);
    OLED_ShowChinese(64,48,12,16,1);
    //OLED_ShowChinese(80,48,25,16,1);
    ///OLED_ShowChinese(80,48,26,16,1);

    OLED_Refresh();
}

//清屏函数 (1,1) (79,44)
void OLED_MyClear(void)
{
    u8 i,m,n,x,y;
    for(x=1;x<=76;x++)
        for(y=1;y<=44;y++)
        {
            i=y/8;
            m=y%8;
            n=1<<m;
            {
                OLED_GRAM[x][i]=~OLED_GRAM[x][i];
                OLED_GRAM[x][i]|=n;
                OLED_GRAM[x][i]=~OLED_GRAM[x][i];
            }
        }

}

void Select_menu(u8 m)
{
    switch(m)
    {
        case 1:OLED_ShowChar(56,16,' ',16,1);OLED_ShowChar(56,32,' ',16,1);OLED_ShowChar(56,48,' ',16,1);OLED_ShowChar(121,16,' ',16,1);OLED_ShowChar(121,32,' ',16,1);
            OLED_ShowChar(121,48,' ',16,1);My_ShowChar(120,0,1);OLED_Refresh();break;
        case 2:OLED_ShowChar(56,32,' ',16,1);OLED_ShowChar(56,48,' ',16,1);OLED_ShowChar(121,16,' ',16,1);OLED_ShowChar(121,32,' ',16,1);OLED_ShowChar(121,48,' ',16,1);
            OLED_ShowChar(120,0,' ',16,1);My_ShowChar(56, 16,1);OLED_Refresh();break;
        case 3:OLED_ShowChar(56,16,' ',16,1);OLED_ShowChar(56,48,' ',16,1);OLED_ShowChar(121,16,' ',16,1);OLED_ShowChar(121,32,' ',16,1);OLED_ShowChar(121,48,' ',16,1);
            OLED_ShowChar(120,0,' ',16,1);My_ShowChar(56, 32,1);OLED_Refresh();break;
        case 4:OLED_ShowChar(56,16,' ',16,1);OLED_ShowChar(56,32,' ',16,1);OLED_ShowChar(121,16,' ',16,1);OLED_ShowChar(121,32,' ',16,1);OLED_ShowChar(121,48,' ',16,1);
            OLED_ShowChar(120,0,' ',16,1);My_ShowChar(56, 48,1);OLED_Refresh();break;
        case 5:OLED_ShowChar(56,16,' ',16,1);OLED_ShowChar(56,32,' ',16,1);OLED_ShowChar(56,48,' ',16,1);OLED_ShowChar(121,32,' ',16,1);OLED_ShowChar(121,48,' ',16,1);
            OLED_ShowChar(120,0,' ',16,1);My_ShowChar(121,16,1);OLED_Refresh();break;
        case 6:OLED_ShowChar(56,16,' ',16,1);OLED_ShowChar(56,32,' ',16,1);OLED_ShowChar(56,48,' ',16,1);OLED_ShowChar(121,16,' ',16,1);OLED_ShowChar(121,48,' ',16,1);
            OLED_ShowChar(120,0,' ',16,1);My_ShowChar(121,32,1);OLED_Refresh();break;
        case 7:OLED_ShowChar(56,16,' ',16,1);OLED_ShowChar(56,32,' ',16,1);OLED_ShowChar(56,48,' ',16,1);OLED_ShowChar(121,16,' ',16,1);OLED_ShowChar(121,32,' ',16,1);
            OLED_ShowChar(120,0,' ',16,1);My_ShowChar(121,48,1);OLED_Refresh();break;
    }
}
void Updata_menu2(void)//更新菜单页数据
{
    STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);
    OLED_ShowNum(16,16,datatemp[0],3,16,1);
    OLED_ShowNum(16,32,datatemp[1],3,16,1);
    OLED_ShowNum(16,48,datatemp[2],3,16,1);
    OLED_ShowNum(81,16,datatemp[3],3,16,1);
    OLED_ShowNum(81,32,datatemp[4],3,16,1);
    OLED_ShowNum(81,48,datatemp[5],3,16,1);
    OLED_Refresh();
}

void Updata_menu4(void)
{
    // OELD刷新显示界面

    OLED_ShowNum(48,0,(int)temperature_1000/1000,3,16,1);
    OLED_ShowNum(78, 0, (int)temperature_1000%1000,3,16,1);

    OLED_ShowNum(70,16,(int)humidity_100/100,2,16,1);
    OLED_ShowNum(92, 16, (int)humidity_100%100,2,16,1);

    OLED_ShowNum(50,32,(int)distance_1000/1000,3,16,1);
    OLED_ShowNum(80, 32, (int)distance_1000%1000,3,16,1);

    OLED_ShowNum(50,48,(int)distance_offset_1000/1000,3,16,1);
    OLED_ShowNum(80, 48, (int)distance_offset_1000%1000,3,16,1);
    OLED_Refresh();

}

void Updata_menu5(void)
{

    OLED_ShowNum(50,0,(int)distance_1000/1000,3,16,1);
    OLED_ShowNum(80, 0, (int)distance_1000%1000,3,16,1);
    OLED_ShowNum(50,16,(int)distance_offset_1000/1000,3,16,1);
    OLED_ShowNum(80, 16, (int)distance_offset_1000%1000,3,16,1);
    OLED_ShowNum(80,32,cnt,3,16,1);
    OLED_Refresh();

}

void Delete_select(u8 t,u16 *p)//删除所选数据
{
    t+=1;
    switch(t)
    {
        case 1:OLED_ShowString(0, 16 ,(unsigned char*)"1:  0cm",16,1);p[0]=0;break;
        case 2:OLED_ShowString(0, 32 ,(unsigned char*)"2:  0cm",16,1);p[1]=0;break;
        case 3:OLED_ShowString(0, 48 ,(unsigned char*)"3:  0cm",16,1);p[2]=0;break;
        case 4:OLED_ShowString(65,16 ,(unsigned char*)"4:  0cm",16,1);p[3]=0;break;
        case 5:OLED_ShowString(65,32 ,(unsigned char*)"5:  0cm",16,1);p[4]=0;break;
        case 6:OLED_ShowString(65,48 ,(unsigned char*)"6:  0cm",16,1);p[5]=0;break;
        case 7:p[6]=0;break;
    }
    OLED_Refresh();//刷新
}
void Dotting(u8 *p,u8 mode)
{
    u8 j;
    for(j=76;j>0;j--)
    {
        //p[j] = p[j-1];
        OLED_DrawPoint(77-j,45-p[j],mode);
        //////printf("%d\r ",p[j]);
        //				if(j==75)
        //					OLED_MyClear();
    }
    OLED_Refresh();
}
void Dotting1(u8 *p,u8 mode)
{
    u8 j;
    for(j=76;j>0;j--)
    {
//		p[j] = p[j-1];
        OLED_DrawPoint(77-j,45-p[j],mode);
        //////printf("%d\r ",p[j]);
        //				if(j==75)
        //					OLED_MyClear();
    }

}
void Retrude(u8 *p)
{
    u8 j;
    for(j=76;j>0;j--)
    {
        p[j] = p[j-1];
    }
}
