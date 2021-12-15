/******************** (C) COPYRIGHT 2015 TIKO *****************************
* File Name          : rs485.c
* Author             : Tiko Zhong
* Date First Issued  : DEC12,2021
* Description        : This file provides a set of functions needed to manage the
*                      communication using HAL_UARTxxx
********************************************************************************
* History:
* DEC12, 2021: V0.1
	+ 115200bps, 5ms/command test pass

****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _RS485_DEV_H
#define _RS485_DEV_H

/* Includes ------------------------------------------------------------------*/
#include "misc.h"
#include "uartdev.h"

/* Exported types ------------------------------------------------------------*/
typedef struct{
	UartDev_t uartdev;
	PIN_T DE, DET;
	//u8 squ;
	u16 tick;
}Rs485Rsrc_t;

typedef struct{
	Rs485Rsrc_t rsrc;
	u16 (*RxFetchFrame)	(Rs485Rsrc_t *pRsrc, u8* frame, u16 frameLen);
	u16 (*Send)			(Rs485Rsrc_t *pRsrc, const u8* BUF, u16 len);
	u16 (*SendStr)		(Rs485Rsrc_t *pRsrc, const char* FORMAT_ORG, ...);
	u16 (*TxPolling)	(Rs485Rsrc_t *pRsrc);
	u16 (*RxPolling)	(Rs485Rsrc_t *pRsrc);
}Rs485Dev_t;


/* Exported variables --------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void setupRs485Dev(
	Rs485Dev_t *pDev,
	UART_HandleTypeDef* huart,
	u8* p,				// all rx pool, tx pool, rx double buffer
	u16	rxPoolLen,		// lenth of rx pool, better 512 for 115200bps
	u16 rxBufLen,		// lenth of rx buffer, better >=100 for 115200bps + 4ms polling
	u16 txPoolLen,		// lenth of tx pool, must be power(2,n), better 512 for 115200bps
	const PIN_T DE,		// DE PIN for bus chip
	const PIN_T DET,	// DET PIN for bus chip
	s8 (*beforeSend)(void),		// before send, test and take bus
	s8 (*afterSend)(UART_HandleTypeDef *)	// after send, release bus
);
	
#endif /* _MY_UART_H */

/**********************END OF FILE****/
