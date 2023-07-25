#include"modbus.h"

#define PCS_ADDR_BIAS 0x0000
#define PCS_DEV_STATUS 0x0001
#define PCS_WARNING 0x0002
#define PCS_FAULT 0x0003
#define PCS_DCVOLT 0x0004
#define PCS_DCCURR 0x0005
#define PCS_DCPWR 0x0006

#define MODBUS_READ_WRITE 0x00
#define MODBUS_READ_ONLY 0x03

typedef enum ModbusType
{
	UINT8 = 0,
	UINT16,
	UINT32,
	INT8,
	INT16,
	INT32,
	FLOAT,
	DFLOAT,
	BIT,
}ModbusType;

typedef struct ModbusDescription
{
	uint16_t CID;
	uint16_t rw;
	ModbusType type;
	uint16_t addr;
	uint16_t bias;
	float resolution;
	uint16_t valbias;
	char *unit;
	void *val;
}ModbusDesc;

// typedef struct ModbusDescriptorTable
// {
// 	ModbusDesc *desc;
// 	ModbusDesc *ptr;
// 	uint16_t num;
// }ModbusTable;

// ModbusErr ModbusTableInit(ModbusTable *table, uint16_t rows);
// ModbusErr ModbusTableAdd(ModbusTable *table, ModbusDesc *desc);
// ModbusErr ModbusTableDel(ModbusTable *table, uint16_t CID);

// static uint16_t holding_regs[100], input_regs[100];

//ModbusErr ModbusTxBuild(ModbusDesc *desc, uint16_t n);
ModbusErr ModbusDescBuild(ModbusDesc *desc, uint16_t n);
ModbusErr ModbusRxMailCallback(ModbusDesc *desc, ModbusRxMail *rx);
ModbusErr ModbusRegGet(ModbusDesc *desc, uint16_t CID, void *r);
ModbusErr ModbusRegSet(ModbusDesc *desc, uint16_t CID, void *w);

int main()
{
	// ModbusTxMail msg;
	// ModbusTxMailInit(&msg);
	// ModbusTxMailReadInput(&msg, 0x01, 0x2134, 0xac56);
    // ModbusTxMailPrint(&msg);
    // ModbusTxMailRead(&msg, 0x01, 0x2134, 0xac56);
    // ModbusTxMailPrint(&msg);
	// ModbusTxMailWriteMulti(&msg, 0x01, 0x0517, 4, 0x1234, 0x3214, 0x6815, 0x7815);
	// ModbusTxMailPrint(&msg);
	// ModbusTxMailWriteSingle(&msg, 0x01, 0x3891, 0xfe51);
    // ModbusTxMailPrint(&msg);
	ModbusDesc desc[10] = {
		{PCS_DEV_STATUS, MODBUS_READ_ONLY, UINT16, 0x1001, 0x0000, 1, 0, NULL},
		{PCS_WARNING, MODBUS_READ_ONLY, UINT16, 0x1002, 0x0000, 1, 0, NULL},
		{PCS_FAULT, MODBUS_READ_ONLY, UINT16, 0x1003, 0x0000, 1, 0, NULL},
		{PCS_DCVOLT, MODBUS_READ_ONLY, UINT32, 0x1004, 0x0000, 0.001f, 0, "V"},
		{PCS_DCCURR, MODBUS_READ_ONLY, INT32, 0x1006, 0x0000, 0.001f, 0, "A"},
		{PCS_DCPWR, MODBUS_READ_ONLY, INT32, 0x1008, 0x0000, 0.001f, 0, "W"},
	};
	ModbusDescBuild(desc, 10);
	printf("%d\n", sizeof(ModbusDesc));
}

ModbusErr ModbusDescBuild(ModbusDesc *desc, uint16_t n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		switch (desc[i].type)
		{
		case UINT8:
		case INT8:
			desc[i].val = (uint8_t *)malloc(sizeof(uint8_t));
			break;
		case UINT16:
		case INT16:
			desc[i].val = (uint16_t *)malloc(sizeof(uint16_t));
			break;
		case UINT32:
		case INT32:
			desc[i].val = (uint32_t *)malloc(sizeof(uint32_t));
			break;
		default:
			desc[i].val = NULL;
		}
	}
	return MODBUS_OK;
}

ModbusErr ModbusRxMailCallback(ModbusDesc *desc, ModbusRxMail *rx)
{
	ModbusDesc *ptr;
	switch(rx->transaction)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	default:
		return MODBUS_ERR;
	}
	return MODBUS_OK;
}
