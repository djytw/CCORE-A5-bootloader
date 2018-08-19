// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : usb_cdc_config.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "includes.h"
#include "usb_reg.h"
#include "usb_const.h"






const UINT8 USB_cdc_Device_Descriptor[18] =   //USB�豸������
{
    0x12,                       //bLength: 0x12 �ֽ�
    DT_DEVICE,                  //bDescriptorType: �豸
    //0x10, 0x01,               //bcdUSB: version2.0
    0x00, 0x02,
    0x02,                       //bDeviceClass�ֶΡ����豸�������豸��������ָ���豸�����ͣ�
    							//�������������ü������������ӿڣ��ͻᱻϵͳ��Ϊ��һ��USB�����豸���Ӷ������豸������������0x02Ϊͨ���豸�������롣
    0x00,                       //bDeviceSubClass: ����0������Ϊ0
    0x00,                       //bDeviceProtocol: Э��0������Ϊ0
    0x40,                       //bMaxPacketSize0: 64�ֽڣ��˵�0����������
    0x88, 0x88,                 //idVendor:  ���� ID
    0x07, 0x00,                 //idProduct: ��Ʒ ID
    0x00, 0x01,                 //bcdDevice: �豸�汾
    0x01,                       //iManufacturer: �ַ�������
    0x02,                       //iProduct: �ַ�������
    0x03,                       //iSerialNumber: �ַ�������
    0x01,                       //bNumConfigurations:֧�ֵ�������1
};
	//Device Qualifier Descriptor
const unsigned char USB_cdc_Device_Qualifier_Descriptor[10] =
	{

	        //Device Qualifier(0x0A bytes)
	        0x0A,                   //bLength: 0x12 bytes
	        0x06,                   //bDescriptorType: DEVICE
	        0x00, 0x02,             //bcdUSB_cdc: version 2.0
	        0x00,                   //bDeviceClass: independent interfaces
	        0x00,                   //bDeviceSubClass: 0
	        0x00,                   //bDeviceProtocol: class specific protocols NOT used on device basis
	        0x40,                   //bMaxPacketSize0 for other speed
	        0x01,                   //bNumConfigurations for other-speed configuration
	        0x00,                   //Reserved,must be 0        
	};
const UINT8 USB_cdc_Configuration_Descriptor[] =  //USB����������
{                                 //USB����������
    0x09,                         //bLength  ��������������
    DT_CONFIGURATION,             //bDescriptor   ����������
    0x43,						  //wTotalLength  �ü��ϵ��ܳ���  ���ֽ�
	0x00, 						  //wTotalLength  �ü��ϵ��ܳ���  ���ֽ�
    0x02,                         //bNumInterface  �����õĽӿ���Ϊ2
    0x01,                         //bConfiguration Value   �����õ�ֵΪ1
    0x00,                         //iConfiguration    ������û���ַ�������
    0xa0,                         //bmAttributes
    0x32,                         //bMaxPower   �豸������100mA

	/*******************CDC��ӿ�������*********************/
    0x09,                         //bLength:    �ӿ�����������
    INTERFACE_TYPE,                         //bDescriptorType   �ӿ�������
    0x00,                         //bInterfaceNumber   �ӿڱ��
    0x00,                         //bAlternateSetting   �ӿڱ��ñ��
    0x01,                         //bNumEndpoints     ��0�˵���,CDC�ӿ�ֻʹ��һ���ж�
    0x02,                         //bInterfaceClass:   �ýӿ���ʹ�õ��ࡣCDC��������Ϊ0x02��
    0x02,                         //bInterfaceSubClass  �ýӿ���ʹ�õ����ࡣҪʵ��USBת���ڣ�
 							      //�ͱ���ʹ��Abstract Control Model���������ģ�ͣ����ࡣ���ı��Ϊ0x02��
    0x01,                         //bInterfaceProtocol ʹ��Common AT Commands��ͨ��AT���Э�顣��Э��ı��Ϊ0x01��
    0x00,                         //iInterface   �ýӿڵ��ַ�������ֵ������û�У�Ϊ0��
    /***************����Ϊ����������****************/
 	/********* Header Functional Descriptor ********/
	0x05,						  //bFunctionLength�ֶΡ�������������Ϊ5�ֽ�
 	0x24,						  //bDescriptorType�ֶΡ�����������Ϊ������ӿڣ�CS_INTERFACE�����Ϊ0x24��
	0x00,						  //bDescriptorSubtype�ֶΡ�����������ΪHeader Functional Descriptor���Ϊ0x00��
	0x10,0x01,					  //bcdCDC�ֶΡ�CDC�汾�ţ�Ϊ0x0110�����ֽ����ȣ�
	 /**** Call Management Functional Descriptor ****/
	0x05,						  //bFunctionLength�ֶΡ�������������Ϊ5�ֽ�
 	0x24,						  //bDescriptorType�ֶΡ�����������Ϊ������ӿڣ�CS_INTERFACE�����Ϊ0x24��
	0x01,						  //bDescriptorSubtype�ֶΡ�����������ΪCall Management functional descriptor�����Ϊ0x01��
	0x00,						  //bmCapabilities�ֶΡ��豸�Լ�������call management
 	0x00,						  //bDataInterface�ֶΡ�û��������ӿ�����call management
	/*** Abstract Control Management Functional Descriptor ***/
	0x04,						  //bFunctionLength�ֶΡ�������������Ϊ4�ֽ�
	0x24,						  //bDescriptorType�ֶΡ�����������Ϊ������ӿڣ�CS_INTERFACE�����Ϊ0x24��
	0x02,						  //bDescriptorSubtype�ֶΡ�����������ΪAbstract Control Management functional descriptor�����Ϊ0x02��
	0x02,						  //bmCapabilities�ֶΡ�֧��Set_Line_Coding��Set_Control_Line_State��Get_Line_Coding�����Serial_State֪ͨ
	/***  Union Functional Descriptor  **/
	0x05,						  //bFunctionLength�ֶΡ�������������Ϊ5�ֽڡ�
	0x24,						  //bDescriptorType�ֶΡ�����������Ϊ������ӿڣ�CS_INTERFACE�����Ϊ0x24��
	0x06,						  //bDescriptorSubtype�ֶΡ�����������ΪUnion functional descriptor�����Ϊ0x06��
	0x00,						  //MasterInterface�ֶΡ�����Ϊǰ����Ϊ0��CDC�ӿڡ�
	0x01,						  //SlaveInterface�ֶΣ�����Ϊ���������Ϊ1��������ӿڡ�
	/***********  ����Ϊ�ӿ�0�Ķ˵�������  *******/
	0x07,						  //bLength�ֶΡ��˵�����������Ϊ7�ֽڡ�
	DT_ENDPOINT,				  //bDescriptorType�ֶΡ��˵����������Ϊ0x05��
	0x80+INDEX_EP3,				  //bEndpointAddress�ֶΡ��˵�ĵ�ַ������ʹ������˵�1��D7λ��ʾ���ݷ�������˵�D7Ϊ1����������˵�1�ĵ�ַΪ0x81��
	0x03,						  //bmAttributes�ֶΡ�D1~D0Ϊ�˵㴫������ѡ�񡣸ö˵�Ϊ�ж϶˵㡣�ж϶˵�ı��Ϊ3������λ����Ϊ0��
	0x40,0x00,					  //wMaxPacketSize�ֶΡ��ö˵����������512�ֽ�
	0xFF,						  //bInterval�ֶΡ��˵��ѯ��ʱ�䣬��������Ϊ10��֡ʱ�䣬��10ms��
	/*********  ����Ϊ�ӿ�1�����ݽӿڣ��Ľӿ�������  *********/
	0x09,						  //bLength�ֶΡ��ӿ��������ĳ���Ϊ9�ֽڡ�
	INTERFACE_TYPE,						  //bDescriptorType�ֶΡ��ӿ��������ı��Ϊ0x04��
	0x01,						  //bInterfaceNumber�ֶΡ��ýӿڵı�ţ��ڶ����ӿڣ����Ϊ1��
 	0x00,						  //bAlternateSetting�ֶΡ��ýӿڵı��ñ�ţ�Ϊ0��
	0x02,						  //bNumEndpoints�ֶΡ���0�˵����Ŀ�����豸��Ҫʹ��һ�������˵㣬����Ϊ2��
	0x0A,						  //bInterfaceClass�ֶΡ��ýӿ���ʹ�õ��ࡣ������ӿڵĴ���Ϊ0x0A��
	0x00,						  //bInterfaceSubClass�ֶΡ��ýӿ���ʹ�õ�����Ϊ0��
	0x00,						  //bInterfaceProtocol�ֶΡ��ýӿ���ʹ�õ�Э��Ϊ0��
	0x00, 						  //iConfiguration�ֶΡ��ýӿڵ��ַ�������ֵ������û�У�Ϊ0��
	/*****  ����Ϊ�ӿ�1��������ӿڣ��Ķ˵�������  *****/
	/*************** ��������˵�2������ ******************/
	0x07,						  //bLength�ֶΡ��˵�����������Ϊ7�ֽڡ�
	DT_ENDPOINT,				  //bDescriptorType�ֶΡ��˵����������Ϊ0x05��
	0x80+INDEX_EP1,				  //bEndpointAddress�ֶΡ��˵�ĵ�ַ������ʹ������˵�2��D7λ��ʾ���ݷ�������˵�D7Ϊ1����������˵�2�ĵ�ַΪ0x82��
	0x02,						  //bmAttributes�ֶΡ�D1~D0Ϊ�˵㴫������ѡ�񡣸ö˵�Ϊ�����˵㣬�����˵�ı��Ϊ0x02������λ����Ϊ0��
	0x40,0x00,					  //wMaxPacketSize�ֶΡ��ö˵�����������˵�2��������Ϊ512�ֽڡ�ע����ֽ����ȡ�
	0x00,						  //bInterval�ֶΡ��˵��ѯ��ʱ�䣬����������˵���Ч��
	/*************** ��������˵�2������ ******************/
	0x07,						  //bLength�ֶΡ��˵�����������Ϊ7�ֽڡ�
	DT_ENDPOINT,			      //bDescriptorType�ֶΡ��˵����������Ϊ0x05��
	INDEX_EP2,					  //bEndpointAddress�ֶΡ��˵�ĵ�ַ������ʹ������˵�2��D7λ��ʾ���ݷ�������˵�D7Ϊ1����������˵�2�ĵ�ַΪ0x82��
	0x02,						  //bmAttributes�ֶΡ�D1~D0Ϊ�˵㴫������ѡ�񡣸ö˵�Ϊ�����˵㣬�����˵�ı��Ϊ0x02������λ����Ϊ0��
	0x40,0x00,					  //wMaxPacketSize�ֶΡ��ö˵�����������˵�2��������Ϊ512�ֽڡ�ע����ֽ����ȡ�
	0x00,						  //bInterval�ֶΡ��˵��ѯ��ʱ�䣬����������˵���Ч��
};


	//standard string Descriptor,serial number
const unsigned char USB_cdc_String_Descriptor[] =
	{

	        //Device (0x1a bytes)
	        0x1a,                   //bLength: 0x1A bytes
	        0x03,                   //bDescriptorType: STRING
	        
	        0x33,
			0x00,

			0x35,
		 	0x00,
		 	0x35,
		 	0x00,

			0x34,
		 	0x00,
		 	0x39,
		 	0x00,

			0x39,
		 	0x00,
		 	0x34,
		 	0x00,

			0x34,
		 	0x00,
		 	0x31,
		 	0x00,

			0x34,
		 	0x00,
		 	0x39,
		 	0x00,

			0x34,
		 	0x00

	};
//USB Language ID
const UINT8 UsbLanguageID[4] =
{
	4,				// Num bytes of this descriptor
	DT_STRING,				// String descriptor
	0x09,			// Language ID LSB
	0x04			// Language ID
};


//Manufacturer String
const UINT8 UsbStrDescManufacturer[12] =
{
	12,				// Num bytes of this descriptor
	DT_STRING,				// String descriptor
	'C',	0,
	'C',	0,
	'o',	0,
	'r',	0,
	'e',	0
};

//Product String
const UINT8 UsbStrDescProduct[30] =
{
	30,				// Num bytes of this descriptor
	3,				// String descriptor
	'U',	0,
	'S',	0,
	'B',	0,
	' ',	0,
	'C',	0,
	'D',	0,
	'C',	0,
	' ',	0,
	'D',	0,
	'E',	0,
	'V',	0,
	'I',	0,
	'C',	0,
	'E',	0
};



//Serial Number
const UINT8 UsbStrDescSerialNumber[34] =
{
	34,			// Num bytes of this descriptor
	DT_STRING,			// String descriptor
	'1',	0,
	'2',	0,
	'3',	0,
	'4',	0,
	'5',	0,
	'6',	0,
	'7',	0,
	'8',	0,
	'9',	0,
	'0',	0,
	'A',	0,
	'B',	0,
	'C',	0,
	'D',	0,
	'E',	0,
	'F',	0
};
