#include "STD_Types.h"
#include "util.h"
#include "RCC_int.h"
#include "RTC_cfg.h"
#include "RTC_int.h"
#include "DIO_int.h"
#include "NVIC_int.h"
#include "AFIO_init.h"
#include "AFIO_config.h"
#include "USART_int.h"
#include "DMA_int.h"
#include "SCH_int.h"
#include "SCH_cfg.h"
#include "SCB_int.h"
#include "CAN.h"
#include "CANHANDLER_int.h"
#include "CANHANDLER_cfg.h"
#include "GSM_int.h"
#include "GSMHANDLER_int.h"
#include "crypto.h"
#include "Application.h"

#include "Timer_int.h"



void Blink_LED1(void);

int	main(int argc, char* argv[])
{
    filter_type filters[] =
    {
        {CANHANDLER_u8NEXTMSGREQUEST,REMOTE_FRAME, STANDARD_FORMAT},
        {CANHANDLER_u8GUIUPDATEACCEPT,REMOTE_FRAME, STANDARD_FORMAT},
        {CANHANDLER_u8ECUSWVERSION, DATA_FRAME, STANDARD_FORMAT},
        {CANHANDLER_u8GETFLASHBANK, DATA_FRAME, STANDARD_FORMAT},
        {CANHANDLER_u8ECUDTCs, DATA_FRAME, STANDARD_FORMAT},
        {CANHANDLER_u8ECUDTCs, REMOTE_FRAME, STANDARD_FORMAT}
    };
    DMA_Config newDMA =
    {
        DMA_CHANNEL_5,	// Channel number: CHANNEL_1, CHANNEL_2, ...
        FALSE,			// Memory to Memory: TRUE, FALSE
        VERY_HIGH,		// LOW, MEDIUM, HIGH, VERY_HIGH
        BITS_8,			// Specifies Source data size alignment (byte, half word, word).
        BITS_8,			// Specifies Destination data size alignment (byte, half word, word).
        TRUE,			// Specifies if MEM address is incremented or not
        FALSE,			// Specifies PERIPHRAL address is incremented or not.
        FALSE,			// Specifies the normal or circular operation mode: TRUE, FALSE
        FROM_PERIPHRAL,	// If the data will be transferred from memory to peripheral: FROM_MEM, FROM_PERIPHRAL
        FALSE,			// Transfer error interrupt enable
        FALSE,			// Half transfer interrupt enable
        FALSE			// Transfer complete interrupt enable
    };


    DMA_Config DMA_Transmit =
    {
        DMA_CHANNEL_4,	// Channel number: CHANNEL_1, CHANNEL_2, ...
        FALSE,			// Memory to Memory: TRUE, FALSE
        VERY_HIGH,		// LOW, MEDIUM, HIGH, VERY_HIGH
        BITS_8,			// Specifies Source data size alignment (byte, half word, word).
        BITS_8,			// Specifies Destination data size alignment (byte, half word, word).
        FALSE,			// Specifies if MEM address is incremented or not
        TRUE,			// Specifies PERIPHRAL address is incremented or not.
        FALSE,			// Specifies the normal or circular operation mode: TRUE, FALSE
        FROM_PERIPHRAL,	// If the data will be transferred from memory to peripheral: FROM_MEM, FROM_PERIPHRAL
        FALSE,			// Transfer error interrupt enable
        FALSE,			// Half transfer interrupt enable
        TRUE			// Transfer complete interrupt enable
    };

    RCC_vidInit();
    RCC_vidEnablePeripheral(RCC_u8GPIOACLK);
    RCC_vidEnablePeripheral(RCC_u8GPIOBCLK);
    RCC_vidEnablePeripheral(RCC_u8GPIOCCLK);
    RCC_vidEnablePeripheral(RCC_u8USART1CLK);
    RCC_vidEnablePeripheral(RCC_u8CANCLK);
    RCC_vidEnablePeripheral(RCC_u8AFIOCLK);
    RCC_vidEnablePeripheral( RCC_u8DMA1CLK );

    /* RTC initialization */
    RCC_vidEnablePeripheral(RCC_u8BKPCLK);
    RCC_vidEnablePeripheral(RCC_u8PWRCLK);
    RCC_vidInitRTCCLK();

    AFIO_vidinit();
    DIO_vidInit();

    NVIC_vidInit();
    NVIC_vidEnableInterrupt(NVIC_u8DMA1_CHANNEL5);
    NVIC_vidEnableInterrupt(NVIC_u8DMA1_CHANNEL4);
    NVIC_vidEnableInterrupt(NVIC_u8USB_HP_CAN_TX);
    NVIC_vidEnableInterrupt(NVIC_u8USB_LP_CAN_RX0);
    NVIC_vidSetPriority(NVIC_u8USB_HP_CAN_TX, 3);	//Group 0, sub 3
    NVIC_vidSetPriority(NVIC_u8USB_LP_CAN_RX0, 3);	//Group 0, sub 3
    SCB_vidSetInterruptPriority(SCB_u8SYSTICK, 4);	//Group 1, sub 0

    RCC_vidEnablePeripheral(RCC_u8TIM1CLK);
    NVIC_vidEnableInterrupt(NVIC_u8TIM1_UP);
    Timer1_UEV_Interrupt();


    DMA_enumInit(newDMA);
    DMA_enumInit(DMA_Transmit);

    USART_enumInit(USART_CHANNEL_1);

    /* Create Tasks */
    task led1 = {1000, 1, RUNNING, Blink_LED1};
    task gsm  = {10, 0, RUNNING, GSMHANDLER_vidTask};
    task CANReceiver = {10, 6, RUNNING, CANHANDLER_vidReceive};
    task CANSender = {10, 5, RUNNING,CANHANDLER_vidSendTask};

    /* Send Tasks to Scheduler */
    SCH_vidCreateTask(0, &gsm);
    SCH_vidCreateTask(1, &CANReceiver);
    SCH_vidCreateTask(2, &CANSender);
    SCH_vidCreateTask(3, &led1);

    /* Start the Scheduler */
    SCH_vidStart();


    //------------CAN Bus Intialization---------------------------------------------------------------------
    CAN_setup ();                                   // setup CAN interface
    CAN_vid_filter_list(filters,CANHANDLER_u8MAXFILTERNUMBERS);
    CAN_testmode(0);      // Normal, By Salma
    CAN_start ();                                   // leave init mode
    CAN_waitReady ();                               // wait til mbx is empty
    if (CAN_RxRdy)
    {
        CAN_RxRdy = 0;
    }

    while (1)
    {

    }
}


void Blink_LED1(void)
{
    static u8 x = 0;
    if (x == 0)
    {
        DIO_vidSetPinValue(DIO_u8PORTC, DIO_u8PIN13, DIO_u8LOW);
        x = 1;
    }
    else if (x == 1)
    {
        DIO_vidSetPinValue(DIO_u8PORTC, DIO_u8PIN13, DIO_u8HIGH);
        x = 0;
    }
}
