#ifndef _FPEC_PRIV_H
#define _FPEC_PRIV_H

// Base Address
#define FPEC_BASE_ADDRESS           	0x40022000
#define MAIN_MEMORY_BASE_ADDRESS		0x08000000

typedef struct {
	u32	ACR;
	u32 KEYR;
	u32 OPTKEYR;
	u32 SR;
	u32 CR;
	u32 AR;
	u32 Reserved;
	u32 OBR;
	u32 WRPR;
} FPEC_REG;

#define FPEC ((FPEC_REG *) FPEC_BASE_ADDRESS)

#define RDPRT 	0x00A5
#define KEY1 	0x45670123
#define KEY2 	0xCDEF89AB

#endif
