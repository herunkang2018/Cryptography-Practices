/******************************************************************************/
//	工程：Singletable
//	功能：Singletable加、解密文件
//  作者：epsoft|MISTP

/******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "singletable.h"

#define DECRY_FILE "单表密文.txt"
#define ENCRY_FILE "单表明文.txt"

/******************************************************************************/
//	名称：usage
//	功能：帮助信息
//  参数：应用程序名称
//	返回：提示信息

/******************************************************************************/
void Usage( const char *appname )
{
	printf( "\n\tusage: singletable -e 明文文件 密钥词组\n" );
	printf( "\tusage: singletable -d 密文文件 密钥词组\n" );
}

/******************************************************************************/
//	名称：FileIN
//	功能：加/解密  结果  输出到当前目录磁盘文件中
//  参数：strFile --> strIn
//	返回：更新成功返回实际输出长度，否则返回0
 
/******************************************************************************/

int FileIn( const char *strIn, int len, const char *strFile )
{
	FILE *fp = NULL;
	int iRead=0;

	if( strIn == NULL || len ==0 )
		return false;


	//! 打开文件句柄
	if( (fp = fopen( strFile,"r" )) == NULL )	// 文本模式写
		return false;


	iRead = fread((void *)strIn, 1, len, fp );//len 3 [0]
	printf("%d", iRead);

	char * hjk = (char *)strIn;
	*(hjk+iRead) = '\0';
//	strIn[iRead] = '\0';
	fclose(fp);

	if( iRead>0 )
		return true;
	else
		return false;
}

/******************************************************************************/
//	名称：FileOut
//	功能：加/解密结果输出到当前目录磁盘文件中
//  参数：strOut指向输出字符缓冲区，输出大小len，strFile为输出文件
//	返回：更新成功返回实际输出长度，否则返回0

/******************************************************************************/
int FileOut( const char *strOut, int len, const char *strFile )
{
	FILE *fp = NULL;
	int iWrite=0;

	if( strOut == NULL || len ==0 )
		return false;

	//! 打开文件句柄
	if( (fp = fopen( strFile,"w" )) == NULL )	// 文本模式写
		return false;

	iWrite = fwrite( strOut, 1, len, fp );
	fclose(fp);

	if( iWrite>0 )
		return true;
	else
		return false;
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
	if( argc != 4 )
	{
		Usage( argv[0] );
		return false;
	}

	if( argv[1][1]!='e' && argv[1][1]!='d')
	{
		Usage( argv[0] );
		return false;
	}

	return true;
}

//! 程序主函数
int main( int argc, char **argv )
{

	char plain[1024];
	char crpt[1024];


	char * k = argv[3];

	if(CheckParse(argc, argv)){//true
		if(argv[1][1] == 'e'){

			FileIn( plain, 1024, argv[2]);
			printf("%s\n", plain);//qqq
			printf("%d\n", strlen(plain));//3

			if(UpdateChrTab(k, strlen(k) ) ){
				Encry(plain, strlen(plain), crpt, sizeof(crpt));
				printf("%d\n", strlen(plain));//3
				FileOut(crpt, strlen(plain), DECRY_FILE);
			}else{
				exit(0);
			}

		}else if(argv[1][1] == 'd'){
			FileIn( crpt, 1024, argv[2]);
			printf("%s\n", crpt);//qqq
			printf("%d\n", strlen(crpt));//3


			if(UpdateChrTab(k, strlen(k) ) ){
				Decry(crpt , strlen(crpt), plain, sizeof(plain));
				printf("%d\n", strlen(crpt));//3
				FileOut(plain, strlen(crpt), ENCRY_FILE);
			}else{
				exit(0);
			}
		}
		
	}else{
		printf("error argc!\n");
		exit(0);//false
	}

	return 0;
}