#pragma once


typedef unsigned long long	ULONGLONG;
typedef unsigned long long  QWORD;
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef double              DOUBLE;
typedef signed __int64      INT64;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef short				SHORT;
typedef float               FLOAT;
typedef int                 INT;
typedef unsigned int        UINT;
typedef wchar_t				WCHAR;
typedef char				CHAR;

typedef unsigned long long SESSION_ID;

//////////////////////////
// ERROR DEFINE
//////////////////////////
// TODO 번호맥이기
#define ERROR_NO_SEESSION					1
#define ERROR_BAD_PACKET					2
#define ERROR_BAD_SESSION					3
#define ERROR_NOT_MATCH_RECV_SIZE			4
#define ERROR_SESSION_EXCEEDING_MAX_INDEX	5
#define ERROR_SESSION_CREATION_FAILED		6