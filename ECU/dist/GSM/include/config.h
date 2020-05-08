#ifndef __CRL_CONFIG_H__
#define __CRL_CONFIG_H__

/*! Used to specify the memory representation of the platform.
  *   - CRL_ENDIANNESS=1 for LITTLE ENDIAN
  *   - CRL_ENDIANNESS=2 for BIG ENDIAN \n
  *   This setting is \b VERY \b IMPORTANT */
#define CRL_ENDIANNESS  1  /*!< LITTLE ENDIAN is selected */

#define INCLUDE_SHA256  /*!< This defines if SHA-256 functions are included in the library */

#endif  /*__CRL_CONFIG_H__*/
