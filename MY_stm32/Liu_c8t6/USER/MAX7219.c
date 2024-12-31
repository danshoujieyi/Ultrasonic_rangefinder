#include "MAX7219.h"


/*дһ���ֽ�*/
void MAX7219_WriteByte (uint8_t byte)
{
	for(int i =0;i<8;i++)
	{
		CLK(0);
		DIN(byte&0x80);
		byte=byte<<1;
		CLK(1);
	}
}
/*д�Ĵ���*/
void MAX7219_WriteReg(uint8_t Reg,uint8_t data)
{
	LOAD(0);
	MAX7219_WriteByte (Reg);
	MAX7219_WriteByte (data);
	LOAD(1);
}

/**
  * ��    �� ��ʾ���� �ú���Ϊ��BCD�����µ���ʾ
  * ��    �� uint8_t location���ڼ�λ��ʾ 1~8��
  * ��    �� uint8_t num����ʾ�����֣�0~9��Line��E,H,L,P,blank��
  * ��    �� uint8_t dot: �Ƿ���ҪС����
  */
void MAX7219_ShowNum(uint8_t location,uint8_t num,uint8_t dot)
{
	if(dot==0)	MAX7219_WriteReg (location,num);
	else	
	{
		num |=0x80;
		MAX7219_WriteReg (location,num);		
	}
}

/**
  * ��    �� MAX7219_Clear ���������
  */
void MAX7219_Clear(void)
{
	for(int i=1;i<=8;i++)
	{
		MAX7219_ShowNum(i,blank,0);
	}
}
/**
  * ��    �� ��ʼ��MAX7219
  * ��    �� uint8_t BCD��D7~D0���ƶ��ڵ�����ܲ���BCD���롣
  * ��    �� uint8_t Intensity����������ܵ����� 0~15(0��ʾϨ��)
  * ��    �� uint8_t DisplayNum: �������ʾ�ĸ�����1~8
  */
void MAX7219_Init (uint8_t BCD,uint8_t Intensity,uint8_t DisplayNum)
{
// ʹ��GPIOʱ��
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

// GPIO��ʼ���ṹ��
    GPIO_InitTypeDef GPIO_InitStruct = {0};

// ��ʼ��GPIOB
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // �������
    GPIO_InitStruct.Pull = GPIO_NOPULL;         // ������������
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // �ٶ����ȼ�
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

// ��ʼ��GPIOA
    GPIO_InitStruct.Pin = GPIO_PIN_7;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


	/*������������ƼĴ���*/
	MAX7219_WriteReg (0x0c,0x01);//����Ϊ����ģʽ
	MAX7219_WriteReg (0x09,BCD);//����BCD���룬8������ܾ�ʹ��BCD����
	MAX7219_WriteReg (0x0a,Intensity);//��������
	
	DisplayNum-=1;
	MAX7219_WriteReg (0x0b,DisplayNum);//8������ܲ�����ʾ
	
	MAX7219_WriteReg (0x0f,0x01);//����ģʽ�����������ȫ��
	HAL_Delay(100);
	MAX7219_WriteReg (0x0f,0x00);//������ʾģʽ
	
	MAX7219_Clear();
}












