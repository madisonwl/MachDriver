

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Fri Aug 19 14:36:37 2016
 */
/* Compiler settings for SinumerikDriver.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_SinumerikDriver,0xBB4ADB0D,0x412D,0x4F9A,0x8A,0x63,0xEF,0xBE,0x50,0x87,0xA0,0x11);


MIDL_DEFINE_GUID(IID, DIID_ISinumerikDriverCom,0xA5DF808F,0x92DA,0x405B,0x87,0x28,0xFE,0x2B,0x45,0xF3,0x9F,0xD4);


MIDL_DEFINE_GUID(CLSID, CLSID_SinumerikDriverCom,0x6DCF3119,0x9C41,0x4B14,0xA6,0xBF,0xDC,0x3C,0xED,0xB3,0xC8,0x47);


MIDL_DEFINE_GUID(IID, DIID_ISinumerikDriverSer,0x8E729AA6,0x9E85,0x45E2,0xBC,0x41,0x76,0xFA,0xE5,0x6E,0xC1,0x35);


MIDL_DEFINE_GUID(CLSID, CLSID_SinumerikDriverSer,0x4CB51EDE,0x4B17,0x4ED2,0x9C,0xD7,0xD6,0x2F,0x02,0xFB,0x9E,0x32);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



