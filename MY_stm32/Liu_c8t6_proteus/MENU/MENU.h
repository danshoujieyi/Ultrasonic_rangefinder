#ifndef __MY_DESGIN__H__
#define __MY_DESGIN__H__
#include "STMflash.h"
#include "stdio.h"
#include "OLED2.h"

extern unsigned char Display_Array[76];
void  menu_1(void);///�˵�һ
void  menu_2(void);///�˵���
void OLED_MyClear(void);
void  menu_3(void);
void My_ShowChar(uint8_t x,uint8_t y,uint8_t mode);
void Select_menu(uint8_t m);
void Updata_menu2(void);//���²˵�ҳ����
void menu_4(void);
void Updata_menu4(void);
void menu_5(void);
void Updata_menu5(void);
void Delete_select(uint8_t t,uint16_t *p);//ɾ����ѡ����
void Dotting(uint8_t *p,uint8_t mode);
void Retrude(uint8_t *p);

#endif

