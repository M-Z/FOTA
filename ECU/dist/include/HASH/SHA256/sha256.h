#ifndef __CRL_SHA256_H__
#define __CRL_SHA256_H__

#define CRL_SHA256_SIZE 32 /*!<  Number of bytes (u8) to store a SHA-256 digest. */

/** Structure for the SHA-256 context */ 
typedef HASHctx_stt SHA256ctx_stt;

/* Initialization of Context */
s32 SHA256_Init(SHA256ctx_stt *P_pSHA256ctx);
/* Data processing function */
s32 SHA256_Append(SHA256ctx_stt *P_pSHA256ctx, const u8 *P_pInputBuffer, s32 P_inputSize);
/* Returns digest */
s32 SHA256_Finish(SHA256ctx_stt *P_pSHA256ctx, u8 *P_pOutputBuffer, s32 *P_pOutputSize);


#endif   /*__CRL_SHA256_H__*/
