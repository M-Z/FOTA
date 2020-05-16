#ifndef STD_TYPES_H
#define STD_TYPES_H




typedef unsigned char		u8;
typedef unsigned short int	u16;
typedef unsigned long int	u32;
typedef signed char			s8;
typedef signed short int	s16;
typedef signed long int		s32;
typedef float  				f32;
typedef double 				f64;

#define ENABLE				1
#define DISABLE				0

#define TRUE 				0b1
#define FALSE 				0b0

//------------------HASH ERROR STATUS----------------------------------------------------------------------
#define HASH_SUCCESS             (s32) (0)    /*!<  hash Success */
#define HASH_ERR_BAD_OPERATION   (s32) (4001) /*!<  hash Invalid operation */
#define HASH_ERR_BAD_CONTEXT     (s32) (4002) /*!<  hash The HASH context contains some invalid or uninitialized values */
#define HASH_ERR_BAD_PARAMETER   (s32) (4003) /*!<  hash One of the expected function parameters is invalid */
//----------------------------------------------------------------------------------------------------------


typedef enum {
	OK,
	NOK,
	wait,
	indexOutOfRange,
	nullPointer,
	numberOutOfRange,
	elementNotFound,
	limitReached,
	hashSuccess,
	hashErrBadOperation,
	HashErrBadContext,
	HashErrBadParameter
} Error_Status;

typedef enum{
	updateExist,
	updateNotExist,
	updateRollbackExist,
	VehicleNotFound,
	IncorrectPassword,
	checkupdate
} Update_Status;

typedef enum
{
	FAILED = 0,
	PASSED = !FAILED
} TestStatus;


#endif
