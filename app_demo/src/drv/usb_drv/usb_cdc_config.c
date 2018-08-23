// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : usb_cdc_config.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "includes.h"
#include "usb_reg.h"
#include "usb_const.h"






const UINT8 USB_cdc_Device_Descriptor[18] =   //USB设备描述符
{
    0x12,                       //bLength: 0x12 字节
    DT_DEVICE,                  //bDescriptorType: 设备
    //0x10, 0x01,               //bcdUSB: version2.0
    0x00, 0x02,
    0x02,                       //bDeviceClass字段。本设备必须在设备描述符中指定设备的类型，
    							//否则，由于在配置集合中有两个接口，就会被系统认为是一个USB复合设备，从而导致设备工作不正常。0x02为通信设备类的类代码。
    0x00,                       //bDeviceSubClass: 子类0，必须为0
    0x00,                       //bDeviceProtocol: 协议0，必须为0
    0x40,                       //bMaxPacketSize0: 64字节（端点0的最大包长）
    0x88, 0x88,                 //idVendor:  厂商 ID
    0x07, 0x00,                 //idProduct: 产品 ID
    0x00, 0x01,                 //bcdDevice: 设备版本
    0x01,                       //iManufacturer: 字符串索引
    0x02,                       //iProduct: 字符串索引
    0x03,                       //iSerialNumber: 字符串索引
    0x01,                       //bNumConfigurations:支持的配置数1
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
const UINT8 USB_cdc_Configuration_Descriptor[] =  //USB配置描述符
{                                 //USB配置描述符
    0x09,                         //bLength  配置描述符长度
    DT_CONFIGURATION,             //bDescriptor   配置描述符
    0x43,						  //wTotalLength  该集合的总长度  低字节
	0x00, 						  //wTotalLength  该集合的总长度  高字节
    0x02,                         //bNumInterface  该配置的接口数为2
    0x01,                         //bConfiguration Value   该配置的值为1
    0x00,                         //iConfiguration    该配置没有字符串索引
    0xa0,                         //bmAttributes
    0x32,                         //bMaxPower   设备最大电流100mA

	/*******************CDC类接口描述符*********************/
    0x09,                         //bLength:    接口描述符长度
    INTERFACE_TYPE,                         //bDescriptorType   接口描述符
    0x00,                         //bInterfaceNumber   接口编号
    0x00,                         //bAlternateSetting   接口备用编号
    0x01,                         //bNumEndpoints     非0端点数,CDC接口只使用一个中断
    0x02,                         //bInterfaceClass:   该接口所使用的类。CDC类的类代码为0x02。
    0x02,                         //bInterfaceSubClass  该接口所使用的子类。要实现USB转串口，
 							      //就必须使用Abstract Control Model（抽象控制模型）子类。它的编号为0x02。
    0x01,                         //bInterfaceProtocol 使用Common AT Commands（通用AT命令）协议。该协议的编号为0x01。
    0x00,                         //iInterface   该接口的字符串索引值。这里没有，为0。
    /***************以下为功能描述符****************/
 	/********* Header Functional Descriptor ********/
	0x05,						  //bFunctionLength字段。该描述符长度为5字节
 	0x24,						  //bDescriptorType字段。描述符类型为类特殊接口（CS_INTERFACE）编号为0x24。
	0x00,						  //bDescriptorSubtype字段。描述符子类为Header Functional Descriptor编号为0x00。
	0x10,0x01,					  //bcdCDC字段。CDC版本号，为0x0110（低字节在先）
	 /**** Call Management Functional Descriptor ****/
	0x05,						  //bFunctionLength字段。该描述符长度为5字节
 	0x24,						  //bDescriptorType字段。描述符类型为类特殊接口（CS_INTERFACE）编号为0x24。
	0x01,						  //bDescriptorSubtype字段。描述符子类为Call Management functional descriptor，编号为0x01。
	0x00,						  //bmCapabilities字段。设备自己不管理call management
 	0x00,						  //bDataInterface字段。没有数据类接口用作call management
	/*** Abstract Control Management Functional Descriptor ***/
	0x04,						  //bFunctionLength字段。该描述符长度为4字节
	0x24,						  //bDescriptorType字段。描述符类型为类特殊接口（CS_INTERFACE）编号为0x24。
	0x02,						  //bDescriptorSubtype字段。描述符子类为Abstract Control Management functional descriptor，编号为0x02。
	0x02,						  //bmCapabilities字段。支持Set_Line_Coding、Set_Control_Line_State、Get_Line_Coding请求和Serial_State通知
	/***  Union Functional Descriptor  **/
	0x05,						  //bFunctionLength字段。该描述符长度为5字节。
	0x24,						  //bDescriptorType字段。描述符类型为类特殊接口（CS_INTERFACE）编号为0x24。
	0x06,						  //bDescriptorSubtype字段。描述符子类为Union functional descriptor，编号为0x06。
	0x00,						  //MasterInterface字段。这里为前面编号为0的CDC接口。
	0x01,						  //SlaveInterface字段，这里为接下来编号为1的数据类接口。
	/***********  以下为接口0的端点描述符  *******/
	0x07,						  //bLength字段。端点描述符长度为7字节。
	DT_ENDPOINT,				  //bDescriptorType字段。端点描述符编号为0x05。
	0x80+INDEX_EP3,				  //bEndpointAddress字段。端点的地址。这里使用输入端点1。D7位表示数据方向，输入端点D7为1。所以输入端点1的地址为0x81。
	0x03,						  //bmAttributes字段。D1~D0为端点传输类型选择。该端点为中断端点。中断端点的编号为3。其它位保留为0。
	0x40,0x00,					  //wMaxPacketSize字段。该端点的最大包长。512字节
	0xFF,						  //bInterval字段。端点查询的时间，这里设置为10个帧时间，即10ms。
	/*********  以下为接口1（数据接口）的接口描述符  *********/
	0x09,						  //bLength字段。接口描述符的长度为9字节。
	INTERFACE_TYPE,						  //bDescriptorType字段。接口描述符的编号为0x04。
	0x01,						  //bInterfaceNumber字段。该接口的编号，第二个接口，编号为1。
 	0x00,						  //bAlternateSetting字段。该接口的备用编号，为0。
	0x02,						  //bNumEndpoints字段。非0端点的数目。该设备需要使用一对批量端点，设置为2。
	0x0A,						  //bInterfaceClass字段。该接口所使用的类。数据类接口的代码为0x0A。
	0x00,						  //bInterfaceSubClass字段。该接口所使用的子类为0。
	0x00,						  //bInterfaceProtocol字段。该接口所使用的协议为0。
	0x00, 						  //iConfiguration字段。该接口的字符串索引值。这里没有，为0。
	/*****  以下为接口1（数据类接口）的端点描述符  *****/
	/*************** 批量输入端点2描述符 ******************/
	0x07,						  //bLength字段。端点描述符长度为7字节。
	DT_ENDPOINT,				  //bDescriptorType字段。端点描述符编号为0x05。
	0x80+INDEX_EP1,				  //bEndpointAddress字段。端点的地址。我们使用输入端点2。D7位表示数据方向，输入端点D7为1。所以输入端点2的地址为0x82。
	0x02,						  //bmAttributes字段。D1~D0为端点传输类型选择。该端点为批量端点，批量端点的编号为0x02。其它位保留为0。
	0x40,0x00,					  //wMaxPacketSize字段。该端点的最大包长。端点2的最大包长为512字节。注意低字节在先。
	0x00,						  //bInterval字段。端点查询的时间，这里对批量端点无效。
	/*************** 批量输出端点2描述符 ******************/
	0x07,						  //bLength字段。端点描述符长度为7字节。
	DT_ENDPOINT,			      //bDescriptorType字段。端点描述符编号为0x05。
	INDEX_EP2,					  //bEndpointAddress字段。端点的地址。我们使用输入端点2。D7位表示数据方向，输入端点D7为1。所以输入端点2的地址为0x82。
	0x02,						  //bmAttributes字段。D1~D0为端点传输类型选择。该端点为批量端点，批量端点的编号为0x02。其它位保留为0。
	0x40,0x00,					  //wMaxPacketSize字段。该端点的最大包长。端点2的最大包长为512字节。注意低字节在先。
	0x00,						  //bInterval字段。端点查询的时间，这里对批量端点无效。
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
