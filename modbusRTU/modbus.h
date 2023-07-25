#ifndef _MODBUS_H
#define _MODBUS_H

#include<stdarg.h>
#include<stdlib.h>

/* 是否使用FreeRTOS库 */
#define FREERTOS 0
/* 是否在芯片上调试 */
#define DEBUG_ON_CHIP 0

#if (!FREERTOS)
#include<assert.h>
#define configASSERT(e) assert(e)
#define pvPortMalloc(size) malloc(size)
#define vPortFree(ptr) free(ptr)
#else
#include "FreeRTOS.h"
#include "task.h"
#endif

#if (!DEBUG_ON_CHIP)
#include<stdio.h>
#define WINDOWS_DEBUG
/* exact-width signed integer types */
typedef signed char int8_t;
typedef signed short int int16_t;
typedef signed int int32_t;
/* exact-width unsigned integer types */
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
#endif

typedef void (*PollCallback)(const void *);
typedef void (*DisconnCallback)(const void *);

typedef struct UARTDeviceList
{
	//QueueHandle_t t;
	ModbusDev *dev;
	UARTDevList *prev;
	UARTDevList *next;
}UARTDevList;

typedef struct ModbusDevice
{
	uint16_t addr;
	char name[20];
	uint16_t status;
	uint16_t prd;
	uint16_t timeout;
	uint16_t conn;
	uint16_t crcEnable;
	PollCallback pollcb;
	DisconnCallback disconncb;
}ModbusDev;

typedef struct ModbusTxMail
{
	uint8_t *data;
	uint16_t size;
	uint16_t timeout;
	uint16_t transaction;
	uint16_t err;
}ModbusTxMail;

typedef struct ModbusRxMail
{
	uint8_t *data;
	uint16_t size;
	uint16_t timeout;
	uint16_t transaction;
	uint16_t err;
}ModbusRxMail;

typedef enum ModbusError
{
	MODBUS_ERR = 0,
	MODBUS_OK,
	MODBUS_TX_TIMEOUT,
	MODBUS_RX_TIMEOUT,
	MODBUS_TX_OVERFLOW,
	MODBUS_RX_OVERFLOW
}ModbusErr;

/* Modbus function code */
#define MODBUS_READ_COILS           0x01U
#define MODBUS_WRITE_SINGLE_COIL    0x05U
#define MODBUS_WRITE_MULTIPLE_COILS 0x15U
#define MODBUS_READ_INPUT_REG       0x04U
#define MODBUS_READ_HOLDING_REGS    0x03U
#define MODBUS_WRITE_SINGLE_REG     0x06U
#define MODBUS_WRITE_MULTIPLE_REGS  0x10U

#define MODBUS_WORD_BIG_ENDIAN 0x00
#define MODBUS_WORD_LITTLE_ENDIAN 0x01

#ifndef MODBUS_WORD_ENDIAN
	#define MODBUS_WORD_ENDIAN MODBUS_WORD_LITTLE_ENDIAN
#endif

#if (MODBUS_WORD_ENDIAN == MODBUS_WORD_LITTLE_ENDIAN)
	#define UINT16_ENDIAN(a) (((a) << 8) | ((a) >> 8))
#else
	#define UINT16_ENDIAN(a) (a)
#endif

uint16_t ModbusCRC(uint8_t *puchMsg, uint16_t usDataLen);
ModbusErr ModbusTxMailInit(ModbusTxMail *tx);
ModbusErr ModbusTxMailFree(ModbusTxMail *tx);
ModbusErr ModbusRxMailCheck(ModbusTxMail *tx, ModbusRxMail *rx);
ModbusErr ModbusTxMailReadCoil(ModbusTxMail *tx, uint8_t addr, uint16_t caddr, uint16_t csize);
ModbusErr ModbusTxMailReadInput(ModbusTxMail *tx, uint8_t addr, uint16_t regaddr, uint16_t regsize);
ModbusErr ModbusTxMailRead(ModbusTxMail *tx, uint8_t addr, uint16_t regaddr, uint16_t regsize);
ModbusErr ModbusTxMailWriteSingle(ModbusTxMail *tx, uint8_t addr, uint16_t regaddr, uint16_t regval);
ModbusErr ModbusTxMailWriteMulti(ModbusTxMail *tx, uint8_t addr, uint16_t regaddr, uint16_t regval, ...);
#ifdef WINDOWS_DEBUG
void ModbusTxMailPrint(ModbusTxMail *tx);
#endif

#endif