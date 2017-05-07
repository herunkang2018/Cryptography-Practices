#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <afxwin.h>

#include "aes.h"

#define DECRYPT_FILE "AES加密密文.txt"
#define ENCRYPT_FILE "AES解密明文.txt"
//! 约束文件最大2M
#define MAX_FILE	1024*1024*2

/******************************************************************************/
//	名称：usage
//	功能：帮助信息
//  参数：应用程序名称
//	返回：提示信息

/******************************************************************************/
void Usage( const char *appname )
{
	printf( "\n\tusage: aes -e 明文文件 128位密钥\n" );
	printf( "\tusage: aes -d 密文文件 128位密钥\n" );
}

/******************************************************************************/
//	名称：FileOut
//	功能：加/解密结果输出到当前目录磁盘文件中
//  参数：strOut指向输出字符缓冲区，输出大小len，strFile为输出文件
//	返回：更新成功返回实际输出长度，否则返回0

/******************************************************************************/
int FileOut( const void *strOut, int len, const char *strFile )
{
	FILE *fp = NULL;
	int iWrite=0;

	if( strOut == NULL || len ==0 )
		goto out;

	//! 打开文件句柄
	if( (fp = fopen( strFile,"wb" )) == NULL ) // 二进制写
		goto out;

	iWrite = fwrite( strOut, 1, len, fp );
	fclose(fp);

out:
	return iWrite;
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
	if( (argc != 4) || 
		(argv[1][1]!='e' && argv[1][1]!='d') ||
		(strlen( argv[3] ) >(128/8) ) )
	{
		Usage( argv[0] );
		return false;
	}

	return true;
}

//把len长度的uchar类型数据转换成ulong类型
//具体怎么转换需要看AES api里面的uint参数是如何使用的 
void Decode( unsigned long int *output, unsigned char *input, unsigned int len )
{
	unsigned int i, j;

	for( i=0, j=0; j<len; i++, j+=4 )
		output[i] = ((unsigned long int)input[j]) | (((unsigned long int)input[j+1]) << 8) |
		(((unsigned long int)input[j+2]) << 16) | (((unsigned long int)input[j+3]) << 24);
}

//每次把一个ulong类型的数据转换成四个uchar，并打印出来 
void Encode(unsigned char * output, unsigned long int * input){
	unsigned char * temp = (unsigned char *)input;
	output[0] = temp[0];
	output[1] = temp[1];
	output[2] = temp[2];
	output[3] = temp[3];
	int i;
	for(i = 0; i < 4; i++){
		printf("%c", output[i]);
	}
}

//! 程序主函数
int main( int argc, char **argv )
{
	//in -> out
	unsigned char keytemp[100] = "hacking1hacking2hacking3hacking4";//256b -> 32B ->4int
	
	char intemp[100] = "hackingwhackinge";
	unsigned int * minwen = (unsigned int *)malloc(16);
	Decode((unsigned long *)minwen, (unsigned char *)intemp, 16);
	
	//Aes encode 
	aes_encrypt(keytemp, minwen);	
 	
 	//Aes decode
	//由于上面已经加密，这时minwen里面存放的是密文了 
 	aes_decrypt(keytemp, minwen);
 	unsigned char * output = (unsigned char *)malloc(16);
 	Encode(output, (unsigned long *)minwen);
 	Encode(output, (unsigned long *)&minwen[1]);
 	Encode(output, (unsigned long *)&minwen[2]);
 	Encode(output, (unsigned long *)&minwen[3]);
	return 0;
}
