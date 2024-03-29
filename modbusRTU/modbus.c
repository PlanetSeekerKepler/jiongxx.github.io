#include"modbus.h"

/* ModbusCRC 高位字节值表 */
const uint16_t auchCRCHi[] = {
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
		0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
		0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
		0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
		0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
		0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
		0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
		0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
		0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
		0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
		0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
		0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
		0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
		0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
		0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
		0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
		0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
		0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
} ;

/* CRC低位字节值表*/
const uint16_t auchCRCLo[] = {
		0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
		0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
		0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
		0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
		0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
		0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
		0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
		0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
		0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
		0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
		0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
		0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
		0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
		0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
		0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
		0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
		0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
		0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
		0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
		0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
		0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
		0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
		0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
		0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
		0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
		0x43, 0x83, 0x41, 0x81, 0x80, 0x40
} ;

#ifdef WINDOWS_DEBUG
/// @brief 打印Modbus发送信息，用于Windows调试
/// @param tx Modbus发送信息
void ModbusTxMailPrint(ModbusTxMail *tx)
{
	int i;
	for(i = 0; i < tx->size; i++)
        printf("%02x ", tx->data[i]);
	printf("\n");
}
#endif

/// @brief 主机校验Modbus接收信息
/// @param tx Modbus发送信息
/// @param rx Modbus接收信息
/// @note Modbus接收信息不充分，需要额外比对发送信息
/// @return Modbus错误码
ModbusErr ModbusRxMailCheck(ModbusTxMail *tx, ModbusRxMail *rx)
{
	configASSERT(tx);
	configASSERT(rx);
	uint16_t txsize, rxsize, calc_crc, rx_crc;
    /* 地址、功能码不匹配 */
	if (tx->data[0] != rx->data[0] || tx->data[1] != rx->data[1] )
		return MODBUS_ERR;
	switch (rx->data[1])
	{
	case MODBUS_READ_COILS:
		/* Unfinished */
		break;
	case MODBUS_READ_HOLDING_REGS:
	case MODBUS_READ_INPUT_REG:
		/* 数量校验 */
		txsize = *(uint16_t *)(tx->data + 4);
		rxsize = rx->data[2];
		if (UINT16_ENDIAN(txsize) != (rxsize >> 1))
			return MODBUS_ERR;
		/* CRC */
		rx_crc = *(uint16_t *)(rx->data + rxsize + 3);
		calc_crc = ModbusCRC(rx->data, rxsize + 3);
		if (UINT16_ENDIAN(rx_crc) != calc_crc)
			return MODBUS_ERR;
		break;
	case MODBUS_WRITE_SINGLE_REG:
	case MODBUS_WRITE_MULTIPLE_REGS:
	    /* Unfinished */
	default:
		return MODBUS_ERR;
	}
	return MODBUS_OK;
}

/// @brief 初始化Modbus发送信息
/// @param tx Modbus发送信息
/// @return Modbus错误码
ModbusErr ModbusTxMailInit(ModbusTxMail *tx)
{
	tx->data = NULL;
	tx->size = 0;
	tx->err = 0;
	tx->transaction = 0;
	tx->timeout = 1000;
	return MODBUS_OK;
}

/// @brief 释放Modbus发送信息
/// @param tx Modbus发送信息
/// @return Modbus错误码
ModbusErr ModbusTxMailFree(ModbusTxMail *tx)
{
	vPortFree(tx->data);
	tx->size = 0;
    return MODBUS_OK;
}


/// @brief 生成Modbus读线圈信息
/// @param tx Modbus发送信息
/// @param addr 设备地址
/// @param caddr 线圈地址
/// @param csize 线圈数量
/// @return 
ModbusErr ModbusTxMailReadCoil(ModbusTxMail *tx, uint8_t addr, uint16_t caddr, uint16_t csize)
{
	configASSERT(tx);
	if (csize > 2000)
		return MODBUS_ERR;
	if (!(tx->data))
        tx->data = (uint8_t *)pvPortMalloc(8);
	else if (tx->size < 8)
	{
		vPortFree(tx->data);
		tx->data = (uint8_t *)pvPortMalloc(8);
	}
	tx->size = 8;
	tx->data[0] = addr;
	tx->data[1] = MODBUS_READ_COILS;
	*(uint16_t *)(tx->data + 2) = UINT16_ENDIAN(caddr);
    *(uint16_t *)(tx->data + 4) = UINT16_ENDIAN(csize);
    *(uint16_t *)(tx->data + 6) = ModbusCRC(tx->data, 6);
	return MODBUS_OK;
}

/// @brief 生成Modbus读输入寄存器信息
/// @param tx Modbus发送信息
/// @param addr 设备地址
/// @param regaddr 寄存器地址
/// @param regsize 寄存器数量
/// @return Modbus错误码
ModbusErr ModbusTxMailReadInput(ModbusTxMail *tx, uint8_t addr, uint16_t regaddr, uint16_t regsize)
{
	configASSERT(tx);
	if (regsize > 125)
		return MODBUS_ERR;
	if (!(tx->data))
        tx->data = (uint8_t *)pvPortMalloc(8);
	else if (tx->size < 8)
	{
		vPortFree(tx->data);
		tx->data = (uint8_t *)pvPortMalloc(8);
	}
    tx->size = 8;
    tx->data[0] = addr;
    tx->data[1] = MODBUS_READ_INPUT_REG;
    *(uint16_t *)(tx->data + 2) = UINT16_ENDIAN(regaddr);
    *(uint16_t *)(tx->data + 4) = UINT16_ENDIAN(regsize);
    *(uint16_t *)(tx->data + 6) = ModbusCRC(tx->data, 6);
    return MODBUS_OK;
}

/// @brief 生成Modbus读保持寄存器信息
/// @param tx Modbus发送信息
/// @param addr 设备地址
/// @param regaddr 寄存器地址
/// @param regsize 寄存器数量
/// @return Modbus错误码
ModbusErr ModbusTxMailRead(ModbusTxMail *tx, uint8_t addr, uint16_t regaddr, uint16_t regsize)
{
	configASSERT(tx);
	if (regsize > 125)
		return MODBUS_ERR;
	if (!(tx->data))
        tx->data = (uint8_t *)pvPortMalloc(8);
	else if (tx->size < 8)
	{
		vPortFree(tx->data);
		tx->data = (uint8_t *)pvPortMalloc(8);
	}
    tx->size = 8;
    tx->data[0] = addr;
    tx->data[1] = MODBUS_READ_HOLDING_REGS;
    *(uint16_t *)(tx->data + 2) = UINT16_ENDIAN(regaddr);
    *(uint16_t *)(tx->data + 4) = UINT16_ENDIAN(regsize);
    *(uint16_t *)(tx->data + 6) = ModbusCRC(tx->data, 6);
    return MODBUS_OK;
}

/// @brief 生成Modbus写单个保持寄存器信息
/// @param tx Modbus发送信息
/// @param addr 设备地址
/// @param regaddr 寄存器地址
/// @param regval 寄存器值
/// @return Modbus错误码
ModbusErr ModbusTxMailWriteSingle(ModbusTxMail *tx, uint8_t addr, uint16_t regaddr, uint16_t regval)
{
	configASSERT(tx);
	if (!(tx->data))
        tx->data = (uint8_t *)pvPortMalloc(8 * sizeof(uint8_t));
	else if (tx->size < 8)
	{
		vPortFree(tx->data);
		tx->data = (uint8_t *)pvPortMalloc(8);
	}
    tx->size = 8;
    tx->data[0] = addr;
    tx->data[1] = MODBUS_WRITE_SINGLE_REG;
    *(uint16_t *)(tx->data + 2) = UINT16_ENDIAN(regaddr);
    *(uint16_t *)(tx->data + 4) = UINT16_ENDIAN(regval);
    *(uint16_t *)(tx->data + 6) = ModbusCRC(tx->data, 6);
    return MODBUS_OK;
}

/// @brief 生成Modbus写多个保持寄存器信息
/// @param tx Modbus发送信息
/// @param addr 设备地址
/// @param regaddr 寄存器地址
/// @param regsize 寄存器数量
/// @param ... 寄存器值
/// @return Modbus错误码
ModbusErr ModbusTxMailWriteMulti(ModbusTxMail *tx, uint8_t addr, uint16_t regaddr, uint16_t regsize, ...)
{
	configASSERT(tx);
	if (regsize > 120)
		return MODBUS_ERR;
	va_list va;
	va_start(va, regsize);
	tx->size = 9 + (regsize << 1);
	if (!tx->data)
        tx->data = (uint8_t *)pvPortMalloc(tx->size);
	else if (tx->size < regsize)
	{
		vPortFree(tx->data);
		tx->data = (uint8_t *)pvPortMalloc(tx->size);
	}
    tx->data[0] = addr;
    tx->data[1] = MODBUS_WRITE_MULTIPLE_REGS;
	tx->data[6] = (uint8_t)(regsize << 1);
	int i;
	uint16_t temp;
	uint16_t *dataaddr = (uint16_t *)(tx->data + 7);
	uint16_t *crcaddr = dataaddr + regsize;
    *(uint16_t *)(tx->data + 2) = UINT16_ENDIAN(regaddr);
    *(uint16_t *)(tx->data + 4) = UINT16_ENDIAN(regsize);
	for (i = 0; i < regsize; i++)
	{
		temp = (uint16_t)va_arg(va, uint32_t);
		*(dataaddr + i) = UINT16_ENDIAN(temp);
	}
	*(crcaddr) = ModbusCRC(tx->data, 7 + (regsize << 1));
    return MODBUS_OK;
}

/// @brief ModbusCRC16位校验
/// @param puchMsg 数组地址
/// @param usDataLen 数组长度
/// @return 16位校验
uint16_t ModbusCRC(uint8_t *puchMsg, uint16_t usDataLen)
{
    uint16_t uchCRCHi = 0xFF ;              /* 高CRC字节初始化  */
    uint16_t uchCRCLo = 0xFF ;              /* 低CRC 字节初始化 */
    uint32_t uIndex ;                       /* CRC循环中的索引  */
    while (usDataLen--)                     /* 传输消息缓冲区   */
    {
        uIndex = uchCRCHi ^ *puchMsg++ ;    /* 计算CRC          */
        uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex] ;
        uchCRCLo = auchCRCLo[uIndex] ;
    }
#if (MODBUS_WORD_ENDIAN == MODBUS_WORD_BIG_ENDIAN)
    return (uchCRCHi << 8 | uchCRCLo) ;
#elif (MODBUS_WORD_ENDIAN == MODBUS_WORD_LITTLE_ENDIAN)
    return (uchCRCLo << 8 | uchCRCHi) ;
#else
    return 0;
#endif
}