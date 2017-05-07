/******************************************************************************/
//	工程：DES
//	功能：DES加、解密文件
//  作者：epsoft|MISTP

/******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <afxwin.h>

#include "des.h"

#define DECRYPT_FILE "DES加密密文.txt"
#define ENCRYPT_FILE "DES解密明文.txt"
//! 约束文件最大2M
#define MAX_FILE	1024*1024*2

/******************************************************************************/
//	名称：Decode
//	功能：数据类型轮换(unsigned char -> unsigned long int)
//  参数：output:	指向unsigned long int类型输出缓冲区
//		  input:	指向unsigned char类型输入缓冲区
//		  len:		输入数据长度(字节)
//	返回：无

/******************************************************************************/
void Decode( unsigned long int *output, unsigned char *input, unsigned int len )
{
	unsigned int i, j;

	for( i=0, j=0; j<len; i++, j+=4 )
		output[i] = ((unsigned long int)input[j]) | (((unsigned long int)input[j+1]) << 8) |
		(((unsigned long int)input[j+2]) << 16) | (((unsigned long int)input[j+3]) << 24);
}

/******************************************************************************/
//	名称：Encode
//	功能：数据类型轮换(unsigned long int -> unsigned char)
//  参数：output:	指向unsigned char输出缓冲区
//		  input:	指向unsigned long int输入缓冲区
//	返回：无

/******************************************************************************/
void Encode(unsigned char * output, unsigned long int * input){
	unsigned char * temp = (unsigned char *)input;
	output[0] = temp[0];
	output[1] = temp[1];
	output[2] = temp[2];
	output[3] = temp[3];
}

/******************************************************************************/
//	名称：usage
//	功能：帮助信息
//  参数：应用程序名称
//	返回：提示信息

/******************************************************************************/
void Usage( const char *appname )
{
	printf( "\n\tusage: des -e 明文文件 64位密钥\n" );
	printf( "\tusage: des -d 密文文件 64位密钥\n" );
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
		(strlen( argv[3] ) >(64/8) ) )
	{
		Usage( argv[0] );
		return false;
	}

	return true;
}

//! 程序主函数
int main( int argc, char **argv )
{
	//! to-do
	//init cipher [64b]
	unsigned char cipher[100] = "ilikeyou";
	unsigned k1, k2;
	Decode(( unsigned long int *)&k1, cipher, 4);
	Decode(( unsigned long int *)&k2, &cipher[4], 4);
	
	unsigned char file[100] = "hackyard";
	unsigned m1, m2;
	Decode((unsigned long *)&m1, file, 4);
	Decode((unsigned long *)&m2, &file[4], 4);
	
	unsigned c1, c2;
	int i;

	//Des encode
	des_encrypt(k1, k2, m1, m2, c1, c2);
	
	//print encoded hex
	unsigned char * temp = (unsigned char *)&c1;

	for(i = 0; i< 4; i++){
		printf("%02X", temp[i]);
	}
	temp = (unsigned char *)&c2;
	
	for(i = 0; i< 4; i++){
		printf("%02X", temp[i]);
    }
    printf("\n");
    
    //Des decode
	des_decrypt(k1, k2, c1, c2, m1, m2);
	
	//print decoded hex
	temp = (unsigned char *)&m1;

	for(i = 0; i< 4; i++){
		printf("%02X", temp[i]);
	}
	temp = (unsigned char *)&m2;
	
	for(i = 0; i< 4; i++){
		printf("%02X", temp[i]);
    }
    printf("\n");
    
    //print string
    temp = (unsigned char *)&m1;
    for(i = 0; i< 4; i++){
		printf("%c", temp[i]);
	}
	temp = (unsigned char *)&m2;
	for(i = 0; i< 4; i++){
		printf("%c", temp[i]);
    }
    
    
/*	
	if(CheckParse(argc, argv)){
		if(argv[1][1] == 'e'){
			des_encrypt(k1, k2, m1, m2, c1, c2);
			unsigned char * temp = (unsigned char *)&c1;
			for(i = 0; i< 4; i++){
				printf("%02X", temp[i]);
			}
			temp = (unsigned char *)&c2;
			for(i = 0; i< 4; i++){
				printf("%02X", temp[i]);
			}
			
		}else{
			des_decrypt(k1, k2, c1, c2, m1, m2);
			
		}
	}
*/

}
