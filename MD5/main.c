/******************************************************************************/
//	工程：MD5
//	功能：MD5加、解密文件
//  作者：epsoft|MISTP

/******************************************************************************/

#include <stdio.h>
//#include <afxwin.h>
#include <string.h>
#include <stdlib.h>
#include "md5.h"

//! 文件最大2M
#define MAX_FILE 1024*1024*2

typedef int bool;
#define true 1
#define false 0

/******************************************************************************/
//	名称：usage
//	功能：帮助信息
//  参数：应用程序名称
//	返回：无

/******************************************************************************/
void Usage( const char *appname )
{
	printf( "\n\tusage: md5 文件\n" );
}

/******************************************************************************/
//	名称：CheckParse
//	功能：校验应用程序入口参数
//  参数：argc等于main主函数argc参数，argv指向main主函数argv参数
//	返回：若参数合法返回true，否则返回false
//  备注：简单的入口参数校验

/******************************************************************************/
bool CheckParse( int argc, char** argv )
{
	if( argc != 2 )
	{
		Usage( argv[0] );
		return false;
	}

	return true;
}

//! 主程序(Use MFC in a Shared DLL)
int main( int argc, char **argv )
{
	//! 在此处填写代码......
	int i;
	char input[1024];
	scanf("%s", input);
	unsigned int len = strlen(input);
	printf("%d\n", len);
	unsigned char out[16];
	md5_digest( input, len, out);
	for(i = 0; i < 16; i++){
		printf("%02X", out[i]);
	}
	return 0;
}
