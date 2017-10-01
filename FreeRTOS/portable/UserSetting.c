/**~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
＊　ファイル名： main_apl.c
＊　責務　　　： ユーザmain関数定義
＊　作成日　　： 2017/10/1
＊　作成者　　： kern-gt

＊　コンパイラ：CC-RX

＊　備考：
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~**/

/**----------------------------------------------------------------------------
<<利用ファイルのヘッダ>>
-----------------------------------------------------------------------------**/
/* Kernel includes. */
#include "../FreeRTOS.h"

/*
	configASSERT()定義

*/
void vAssertCalled( void )
{
	volatile unsigned long ul = 0;

	taskENTER_CRITICAL();
	{
		/* Use the debugger to set ul to a non-zero value in order to step out
		of this function to determine why it was called. */
		while( ul == 0 )
		{
			portNOP();
		}
	}
	taskEXIT_CRITICAL();
}

/*
	カーネルタイマ初期化

	このコールバック関数はOS起動時に呼びだされ、FreeRTOSconfig.hで
	定義されたシステムクロックマクロとOStick周期マクロより、設定を
	行った後タイマを起動する。

	カーネルタイマに割り当てられたタイマは
	Renesas/RX600/RX64M/CMT0
	である。

	なお、OStickハンドラはport.cに定義されている。そのため、コード生成
	を用いる場合は上記に示すタイマを使用しないこと。

	下に示すコードはデモ用サンプルから引用している。

	The RX port uses this callback function to configure its tick interrupt.
	This allows the application to choose the tick interrupt source.

*/
void vApplicationSetupTimerInterrupt( void )
{
	const uint32_t ulEnableRegisterWrite = 0xA50BUL, ulDisableRegisterWrite = 0xA500UL;

    /* Disable register write protection. */
    SYSTEM.PRCR.WORD = ulEnableRegisterWrite;

	/* Enable compare match timer 0. */
	MSTP( CMT0 ) = 0;

	/* Interrupt on compare match. */
	CMT0.CMCR.BIT.CMIE = 1;

	/* Set the compare match value. */
	CMT0.CMCOR = ( unsigned short ) ( ( ( configPERIPHERAL_CLOCK_HZ / configTICK_RATE_HZ ) -1 ) / 8 );

	/* Divide the PCLK by 8. */
	CMT0.CMCR.BIT.CKS = 0;

	/* Enable the interrupt... */
	_IEN( _CMT0_CMI0 ) = 1;

	/* ...and set its priority to the application defined kernel priority. */
	_IPR( _CMT0_CMI0 ) = configKERNEL_INTERRUPT_PRIORITY;

	/* Start the timer. */
	CMT.CMSTR0.BIT.STR0 = 1;

    /* Reneable register protection. */
    SYSTEM.PRCR.WORD = ulDisableRegisterWrite;
}