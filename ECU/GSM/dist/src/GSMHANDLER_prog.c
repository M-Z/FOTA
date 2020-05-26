/*
   GSM_handler.c

    Created on: 15 May 2020
        Author: Michael
*/

#include "STD_Types.h"
#include "BIT_MATH.h"

#include "RCC_int.h"
#include "NVIC_int.h"
#include "USART_int.h"
#include "DMA_int.h"

//#include "GSM_priv.h"
#include "GSM_int.h"
#include "GSM_conf.h"

#include "GSMHANLDER_priv.h"
#include "GSMHANDLER_int.h"

#include "crypto.h"
#include "Application.h"

MessageState GSM_enuListenFlag = IDLE;

u8 au8listenBuffer[64];
u8 * pu8StatePtr;
u8 GSMHANDLER_u8TransmissionCompleteFlag = 0;

/*****************************************/
/***********Public Functions**************/
/*****************************************/


/* Sending Procedure*/
u8MailBoxIndex = CANHANDLER_vidSend(CANHANDLER_u8UPDATEPROGRESS, CAN_u8DATAFRAME, &u8UpdateProgress, 1);
if (u8MailBoxIndex == 3)
{
	  pu8CanData = &u8UpdateProgress;
	  u8CanFrameType = CAN_u8DATAFRAME;
	  u8CanMessageID = CANHANDLER_u8UPDATEPROGRESS;
	  u8 u8CanDataLength = 1;
	  enuSendFlag = SendingMessage;
}
else
{
	u8state++;
}

/****************************************************************************************/
/* Description: GSM Task in the Scheduler                        */
/* Input      : Void                                                          */
/* Output     : Void                                                                */
/* Scope      : Public                                                                  */
/****************************************************************************************/
void GSMHANDLER_vidTask(void)
{
  Error_Status enuresponseStatus = NOK;
  u8 u8MailBoxIndex = 0;
  static MessageState enuSendFlag = IDLE;
  static u8* pu8CanData = (void*)0;
  static u8 u8CanFrameType = 0;
  static u8 u8CanMessageID = 0;
  static u8 u8CanDataLength = 0;
  static u8 u8state = 1;
  static u8 u8flag = 0;
  if (enuSendFlag == SendingMessage)
  {
    u8MailBoxIndex = CANHANDLER_vidSend(u8CanMessageID, u8CanFrameType, pu8CanData, u8CanDataLength);
    /* Message Sent Successfully */
    if (u8MailBoxIndex < 3)
    {
      enuSendFlag = IDLE;
      /* Go to Next State */
      u8state++;
    }
    else
    {
      /* Do nothing */
    }
  }
  else
  {
    switch (u8state)
    {

      //Intialize GSM
      case 1:
        // Send ATEO Cmd
        switch (GSM_enuListenFlag)
        {
          case IDLE:
            DMA_enumSetCallback(DMA_CHANNEL_4, vidDMAIRQ);
            USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8listenBuffer, 64 );
            USART_enumDMASend(GSM_u8USARTChannel, DMA_CHANNEL_4, "ATE0\r\n", 0 );
            GSM_enuListenFlag = WaitingForMessage;
            break;
          case WaitingForMessage:
            /* Reset The transmission flag if the transmission is done */
            if (GSMHANDLER_u8TransmissionCompleteFlag == 1)
            {
              GSMHANDLER_u8TransmissionCompleteFlag = 0;
            }
            else
            {
              /* Check for OK response */
              enuresponseStatus = enuFindString(au8listenBuffer, "\r\n\OK\r\n", 64);
              if (enuresponseStatus == OK)
              {
                GSM_enuListenFlag = IDLE;
                u8state++;
              }
              else
              {
                /* Check for Error Response */
                enuresponseStatus = enuFindString(au8listenBuffer, "\r\n\ERROR\r\n", 64);
                if (enuresponseStatus == OK)
                {
                  GSM_enuListenFlag = IDLE;
                }
                else
                {
                  /* Do Nothing */
                }
              }
            }
            break;

          default:
            break;
        }
        break;

      case 2:
        switch (GSM_enuListenFlag)
        {
          case IDLE:
            USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8listenBuffer, 64 );
            USART_enumDMASend(GSM_u8USARTChannel, DMA_CHANNEL_4, "AT+SAPBR=3,1,\"Contype\",\"GPRS\"\r\n", 0 );
            GSM_enuListenFlag = WaitingForMessage;
            break;
          case WaitingForMessage:
            /* Reset The transmission flag if the transmission is done */
            if (GSMHANDLER_u8TransmissionCompleteFlag == 1)
            {
              GSMHANDLER_u8TransmissionCompleteFlag = 0;
            }
            else
            {
              /* Check for OK response */
              enuresponseStatus = enuFindString(au8listenBuffer, "\r\n\OK\r\n", 64);
              if (enuresponseStatus == OK)
              {
                GSM_enuListenFlag = IDLE;
                u8state++;
              }
              else
              {
                /* Check for Error Response */
                enuresponseStatus = enuFindString(au8listenBuffer, "\r\n\ERROR\r\n", 64);
                if (enuresponseStatus == OK)
                {
                  GSM_enuListenFlag = IDLE;
                }
                else
                {
                  /* Do Nothing */
                }
              }
            }
            break;

          default:
            break;
        }
        break;
      case 3:
        switch (GSM_enuListenFlag)
        {
          case IDLE:
            USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8listenBuffer, 64 );
            USART_enumDMASend(GSM_u8USARTChannel, DMA_CHANNEL_4, "AT+SAPBR=1,1\r\n", 0 );
            GSM_enuListenFlag = WaitingForMessage;
            break;
          case WaitingForMessage:
            /* Reset The transmission flag if the transmission is done */
            if (GSMHANDLER_u8TransmissionCompleteFlag == 1)
            {
              GSMHANDLER_u8TransmissionCompleteFlag = 0;
            }
            else
            {
              /* Check for OK response */
              enuresponseStatus = enuFindString(au8listenBuffer, "\r\n\OK\r\n", 64);
              if (enuresponseStatus == OK)
              {
                GSM_enuListenFlag = IDLE;
                u8state += 2;
              }
              else
              {
                /* Check for Error Response */
                enuresponseStatus = enuFindString(au8listenBuffer, "\r\n\ERROR\r\n", 64);
                if (enuresponseStatus == OK)
                {
                  u8state++;
                  GSM_enuListenFlag = IDLE;
                }
                else
                {
                  /* Do Nothing */
                }
              }
            }
            break;

          default:
            break;
        }
        break;

      case 4:
        switch (GSM_enuListenFlag)
        {
          case IDLE:
            USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8listenBuffer, 64 );
            USART_enumDMASend(GSM_u8USARTChannel, DMA_CHANNEL_4, "AT+SAPBR=0,1\r\n", 0 );
            GSM_enuListenFlag = WaitingForMessage;
            break;
          case WaitingForMessage:
            /* Reset The transmission flag if the transmission is done */
            if (GSMHANDLER_u8TransmissionCompleteFlag == 1)
            {
              GSMHANDLER_u8TransmissionCompleteFlag = 0;
            }
            else
            {
              /* Check for OK response */
              enuresponseStatus = enuFindString(au8listenBuffer, "\r\n\OK\r\n", 64);
              if (enuresponseStatus == OK)
              {
                GSM_enuListenFlag = IDLE;
                u8state--;
              }
              else
              {
                /* Check for Error Response */
                enuresponseStatus = enuFindString(au8listenBuffer, "\r\n\ERROR\r\n", 64);
                if (enuresponseStatus == OK)
                {
                  GSM_enuListenFlag = IDLE;
                }
                else
                {
                  /* Do Nothing */
                }
              }
            }
            break;

          default:
            break;
        }
        break;

      case 5:
        switch (GSM_enuListenFlag)
        {
          case IDLE:
            USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8listenBuffer, 64 );
            USART_enumDMASend(GSM_u8USARTChannel, DMA_CHANNEL_4, "AT+HTTPINIT\r\n", 0 );
            GSM_enuListenFlag = WaitingForMessage;
            break;
          case WaitingForMessage:
            /* Reset The transmission flag if the transmission is done */
            if (GSMHANDLER_u8TransmissionCompleteFlag == 1)
            {
              GSMHANDLER_u8TransmissionCompleteFlag = 0;
            }
            else
            {
              /* Check for OK response */
              enuresponseStatus = enuFindString(au8listenBuffer, "\r\n\OK\r\n", 64);
              if (enuresponseStatus == OK)
              {
                GSM_enuListenFlag = IDLE;
                u8state += 2;
              }
              else
              {
                /* Check for Error Response */
                enuresponseStatus = enuFindString(au8listenBuffer, "\r\n\ERROR\r\n", 64);
                if (enuresponseStatus == OK)
                {
                  u8state++;
                  GSM_enuListenFlag = IDLE;
                }
                else
                {
                  /* Do Nothing */
                }
              }
            }
            break;

          default:
            break;
        }
        break;

      case 6:
        switch (GSM_enuListenFlag)
        {
          case IDLE:
            USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8listenBuffer, 64 );
            USART_enumDMASend(GSM_u8USARTChannel, DMA_CHANNEL_4, "AT+HTTPTERM\r\n", 0 );
            GSM_enuListenFlag = WaitingForMessage;
            break;
          case WaitingForMessage:
            /* Reset The transmission flag if the transmission is done */
            if (GSMHANDLER_u8TransmissionCompleteFlag == 1)
            {
              GSMHANDLER_u8TransmissionCompleteFlag = 0;
            }
            else
            {
              /* Check for OK response */
              enuresponseStatus = enuFindString(au8listenBuffer, "\r\n\OK\r\n", 64);
              if (enuresponseStatus == OK)
              {
                GSM_enuListenFlag = IDLE;
                u8state--;
              }
              else
              {
                /* Check for Error Response */
                enuresponseStatus = enuFindString(au8listenBuffer, "\r\n\ERROR\r\n", 64);
                if (enuresponseStatus == OK)
                {
                  GSM_enuListenFlag = IDLE;
                }
                else
                {
                  /* Do Nothing */
                }
              }
            }
            break;

          default:
            break;
        }
        break;

      case 7:
        switch (GSM_enuListenFlag)
        {
          case IDLE:
            DMA_enumSetCallback(DMA_CHANNEL_4, vidDMAIRQ);
            USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8listenBuffer, 64 );
            USART_enumDMASend(GSM_u8USARTChannel, DMA_CHANNEL_4, "AT+HTTPSSL=1\r\n", 0 );
            GSM_enuListenFlag = WaitingForMessage;
            break;
          case WaitingForMessage:
            /* Reset The transmission flag if the transmission is done */
            if (GSMHANDLER_u8TransmissionCompleteFlag == 1)
            {
              GSMHANDLER_u8TransmissionCompleteFlag = 0;
            }
            else
            {
              /* Check for OK response */
              enuresponseStatus = enuFindString(au8listenBuffer, "\r\n\OK\r\n", 64);
              if (enuresponseStatus == OK)
              {
                GSM_enuListenFlag = IDLE;
                u8state++;
              }
              else
              {
                /* Check for Error Response */
                enuresponseStatus = enuFindString(au8listenBuffer, "\r\n\ERROR\r\n", 64);
                if (enuresponseStatus == OK)
                {
                  GSM_enuListenFlag = IDLE;
                }
                else
                {
                  /* Do Nothing */
                }
              }
            }
            break;

          default:
            break;
        }
        break;
      case 8:
        switch (GSM_enuListenFlag)
        {
          case IDLE:
            DMA_enumSetCallback(DMA_CHANNEL_4, vidDMAIRQ);
            USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8listenBuffer, 64 );
            USART_enumDMASend(GSM_u8USARTChannel, DMA_CHANNEL_4, "AT+HTTPPARA=\"CID\",1\r\n", 0 );
            GSM_enuListenFlag = WaitingForMessage;
            break;
          case WaitingForMessage:
            /* Reset The transmission flag if the transmission is done */
            if (GSMHANDLER_u8TransmissionCompleteFlag == 1)
            {
              GSMHANDLER_u8TransmissionCompleteFlag = 0;
            }
            else
            {
              /* Check for OK response */
              enuresponseStatus = enuFindString(au8listenBuffer, "\r\n\OK\r\n", 64);
              if (enuresponseStatus == OK)
              {
                GSM_enuListenFlag = IDLE;
                u8state++;
              }
              else
              {
                /* Check for Error Response */
                enuresponseStatus = enuFindString(au8listenBuffer, "\r\n\ERROR\r\n", 64);
                if (enuresponseStatus == OK)
                {
                  GSM_enuListenFlag = IDLE;
                }
                else
                {
                  /* Do Nothing */
                }
              }
            }
            break;

          default:
            break;
        }
        break;
      case 9:
        switch (GSM_enuListenFlag)
        {
          case IDLE:
            DMA_enumSetCallback(DMA_CHANNEL_4, vidDMAIRQ);
            USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8listenBuffer, 64 );
            USART_enumDMASend(GSM_u8USARTChannel, DMA_CHANNEL_4, "AT+HTTPPARA=\"REDIR\",1\r\n", 0 );
            GSM_enuListenFlag = WaitingForMessage;
            break;
          case WaitingForMessage:
            /* Reset The transmission flag if the transmission is done */
            if (GSMHANDLER_u8TransmissionCompleteFlag == 1)
            {
              GSMHANDLER_u8TransmissionCompleteFlag = 0;
            }
            else
            {
              /* Check for OK response */
              enuresponseStatus = enuFindString(au8listenBuffer, "\r\n\OK\r\n", 64);
              if (enuresponseStatus == OK)
              {
                GSM_enuListenFlag = IDLE;
                u8state++;
              }
              else
              {
                /* Check for Error Response */
                enuresponseStatus = enuFindString(au8listenBuffer, "\r\n\ERROR\r\n", 64);
                if (enuresponseStatus == OK)
                {
                  GSM_enuListenFlag = IDLE;
                }
                else
                {
                  /* Do Nothing */
                }
              }
            }
            break;

          default:
            break;
        }
        break;


      // Excute GSM_enuPOSTRequestInit
      case 10:
          switch (GSM_enuListenFlag)
          {
            case IDLE:
              DMA_enumSetCallback(DMA_CHANNEL_4, vidDMAIRQ);
              USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8listenBuffer, 64 );
              USART_enumDMASend(GSM_u8USARTChannel, DMA_CHANNEL_4, "AT+HTTPPARA=\"content\",\"application/json\"\r\n", 0 );
              GSM_enuListenFlag = WaitingForMessage;
              break;
            case WaitingForMessage:
              /* Reset The transmission flag if the transmission is done */
              if (GSMHANDLER_u8TransmissionCompleteFlag == 1)
              {
                GSMHANDLER_u8TransmissionCompleteFlag = 0;
              }
              else
              {
                /* Check for OK response */
                enuresponseStatus = enuFindString(au8listenBuffer, "\r\n\OK\r\n", 64);
                if (enuresponseStatus == OK)
                {
                  GSM_enuListenFlag = IDLE;
                  u8state++;
                }
                else
                {
                  /* Check for Error Response */
                  enuresponseStatus = enuFindString(au8listenBuffer, "\r\n\ERROR\r\n", 64);
                  if (enuresponseStatus == OK)
                  {
                    GSM_enuListenFlag = IDLE;
                  }
                  else
                  {
                    /* Do Nothing */
                  }
                }
              }
              break;

            default:
              break;
          }
        break;
      case 11:
          switch (GSM_enuListenFlag)
          {
            case IDLE:
              DMA_enumSetCallback(DMA_CHANNEL_4, vidDMAIRQ);
              USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8listenBuffer, 64 );
              USART_enumDMASend(GSM_u8USARTChannel, DMA_CHANNEL_4, "AT+HTTPPARA=\"URL\",\"34.65.7.33/API/firmware/v/5eb4957d8f310f60b7db600f\"\r\n", 0 );
              GSM_enuListenFlag = WaitingForMessage;
              break;
            case WaitingForMessage:
              /* Reset The transmission flag if the transmission is done */
              if (GSMHANDLER_u8TransmissionCompleteFlag == 1)
              {
                GSMHANDLER_u8TransmissionCompleteFlag = 0;
              }
              else
              {
                /* Check for OK response */
                enuresponseStatus = enuFindString(au8listenBuffer, "\r\n\OK\r\n", 64);
                if (enuresponseStatus == OK)
                {
                  GSM_enuListenFlag = IDLE;
                  u8state++;
                }
                else
                {
                  /* Check for Error Response */
                  enuresponseStatus = enuFindString(au8listenBuffer, "\r\n\ERROR\r\n", 64);
                  if (enuresponseStatus == OK)
                  {
                    GSM_enuListenFlag = IDLE;
                  }
                  else
                  {
                    /* Do Nothing */
                  }
                }
              }
              break;

            default:
              break;
          }
        	break;

       case 12:
           switch (GSM_enuListenFlag)
           {
             case IDLE:
               DMA_enumSetCallback(DMA_CHANNEL_4, vidDMAIRQ);
               USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8listenBuffer, 64 );
               USART_enumDMASend(GSM_u8USARTChannel, DMA_CHANNEL_4, "AT+HTTPDATA=100,10000\r\n", 0 );
               GSM_enuListenFlag = WaitingForMessage;
               break;
             case WaitingForMessage:
               /* Reset The transmission flag if the transmission is done */
               if (GSMHANDLER_u8TransmissionCompleteFlag == 1)
               {
                 GSMHANDLER_u8TransmissionCompleteFlag = 0;
               }
               else
               {
                 /* Check for OK response */
                 enuresponseStatus = enuFindString(au8listenBuffer, "DOWNLOAD\r\n", 64);
                 if (enuresponseStatus == OK)
                 {
                   GSM_enuListenFlag = IDLE;
                   u8state++;
                 }
                 else
                 {
                   /* Check for Error Response */
                   enuresponseStatus = enuFindString(au8listenBuffer, "\r\n\ERROR\r\n", 64);
                   if (enuresponseStatus == OK)
                   {
                     GSM_enuListenFlag = IDLE;
                   }
                   else
                   {
                     /* Do Nothing */
                   }
                 }
               }
               break;

             case 13:
                 switch (GSM_enuListenFlag)
                 {
                   case IDLE:
                     DMA_enumSetCallback(DMA_CHANNEL_4, vidDMAIRQ);
                     USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8listenBuffer, 64 );
                     USART_enumDMASend(GSM_u8USARTChannel, DMA_CHANNEL_4, "{\"vehicleName\":\"fota user\",\"password\":\"123\"}\r\n", 0 );
                     GSM_enuListenFlag = WaitingForMessage;
                     break;
                   case WaitingForMessage:
                     /* Reset The transmission flag if the transmission is done */
                     if (GSMHANDLER_u8TransmissionCompleteFlag == 1)
                     {
                       GSMHANDLER_u8TransmissionCompleteFlag = 0;
                     }
                     else
                     {
                       /* Check for OK response */
                       enuresponseStatus = enuFindString(au8listenBuffer, "\r\n\OK\r\n", 64);
                       if (enuresponseStatus == OK)
                       {
                         GSM_enuListenFlag = IDLE;
                         u8state++;
                       }
                       else
                       {
                         /* Check for Error Response */
                         enuresponseStatus = enuFindString(au8listenBuffer, "\r\n\ERROR\r\n", 64);
                         if (enuresponseStatus == OK)
                         {
                           GSM_enuListenFlag = IDLE;
                           u8state--;
                         }
                         else
                         {
                           /* Do Nothing */
                         }
                       }
                     }
            	 break;

              case 14:
                  switch (GSM_enuListenFlag)
                  {
                    case IDLE:
                      DMA_enumSetCallback(DMA_CHANNEL_4, vidDMAIRQ);
                      USART_enumDMAReceive( GSM_u8USARTChannel, DMA_CHANNEL_5, (u32*) au8listenBuffer, 64 );
                      USART_enumDMASend(GSM_u8USARTChannel, DMA_CHANNEL_4,"AT+HTTPACTION=1\r\n", 0 );
                      GSM_enuListenFlag = WaitingForMessage;
                      break;
                    case WaitingForMessage:
                      /* Reset The transmission flag if the transmission is done */
                      if (GSMHANDLER_u8TransmissionCompleteFlag == 1)
                      {
                        GSMHANDLER_u8TransmissionCompleteFlag = 0;
                      }
                      else
                      {
                        /* Check for OK response */
                        enuresponseStatus = enuFindString(au8listenBuffer, "OK", 64);
                        if ( enuresponseStatus == OK)
                        {
                        	enuresponseStatus = enuFindString(au8listenBuffer, "200", 64);
                        	if ( enuresponseStatus == OK)
                        	{
                        		if(u8CheckBufferTermination( au8ResponseBuffer, 64, 4 ) == 1)
                        		{
                        			enuresponseStatus = OK;
                                    GSM_enuListenFlag = IDLE;
                                    u8state++;
                        		}
                        		else
                        		{
                        			enuresponseStatus = NOK;
                        		}
                        	}
                        	else
                        	{
                                GSM_enuListenFlag = IDLE;
                                u8state = 5;
                        	}
                        }

                        }

                      }
                	   break;




             default:
               break;
           }
    	   break;


    }

  }
}


/****************************************************************************************/
/* Description: Interrupt Handler for the DMA                     */
/* Input      : Void                                                              */
/* Output     : Void                                                                */
/* Scope      : Private                                                                 */
/****************************************************************************************/
void vidDMAIRQ(void)
{
  GSMHANDLER_u8TransmissionCompleteFlag = 1;
}


/****************************************************************************************/
/* Description: Finds the expected string in the buffer                 */
/* Input      : u8* pu8Buffer                                                           */
/*              Description: Array to search for the string in                      */
/*        Range:  pointer to u8                         */
/*        const u8* pu8ExpectedString                       */
/*              Description: String to search for in the Buffer                     */
/*        Range:  pointer to u8                         */
/*        u32 u32Size                               */
/*              Description: Size of the array we are searching in                */
/*        Range:  u32                               */
/* Output     : Error_Status                                                            */
/*        Range: OK if the string is found, NOK if the string isn't found     */
/* Scope      : Private                                                                 */
/****************************************************************************************/
static Error_Status enuFindString(u8* pu8Buffer, const u8* pu8ExpectedString, u32 u32Size)
{
  u32 u32MessageCounter = 0;
  u32 u32StringStartIndex = 0;
  u32 u32StringCounter = 0;
  u8 u8FoundFlag = 1;

  // Loop through the pu8Buffer
  for (u32 u32StringStartIndex = 0; u32StringStartIndex < u32Size; u32StringStartIndex++)
  {
    // If match occurred
    if (pu8Buffer[u32StringStartIndex] == pu8ExpectedString[0])
    {
      u32MessageCounter = 1;
      u8FoundFlag = 1;
      // Loop through the message
      for (u32 u32StringCounter = u32StringStartIndex + 1; pu8ExpectedString[u32MessageCounter] != '\0'; u32StringCounter++)
      {
        if (pu8ExpectedString[u32MessageCounter] != pu8Buffer[u32StringCounter])
        {
          u8FoundFlag = 0;
          break;
        }
        u32MessageCounter++;
      }

      // If all match found and we have checked all the message
      if ((u8FoundFlag == 1) && (pu8ExpectedString[u32MessageCounter] == '\0'))
      {
        return OK;
      }
    }
  }

  return NOK;
}

//Error_Status DMAListen(u8* pu8state)
//{
//  GSM_u8ListenFlag = ON;
//
//  //Check if the GSM terminate the buffer or not
//  if(u8CheckBufferTermination(au8listenBuffer, 64, 2))
//  {
//    //check if the response is OK or NOK
//    if (enuFindString(au8listenBuffer, "OK", 64) == OK)
//    {
//      // Response contain "OK"
//      DMA_voidDisable(DMA_CHANNEL_5);
//      GSM_u8ListenFlag = OFF;
//      return OK;
//
//    }
//    else if(enuFindString(au8listenBuffer, "ERROR", 64) == OK)
//    {
//      // Response contain "ERROR"
//      DMA_voidDisable(DMA_CHANNEL_5);
//      GSM_u8ListenFlag = OFF;
//      return NOK;
//    }
//    else
//    {
//      // Unknown respose
//      DMA_voidDisable(DMA_CHANNEL_5);
//      GSM_u8ListenFlag = OFF;
//      //return unknown message
//    }
//
//  }
//  return wait;
//}
//
