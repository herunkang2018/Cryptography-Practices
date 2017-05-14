/******************************************************************************/
//	工程：RSA
//	功能：RSA加、解密文件
//  作者：epsoft|MISTP

/******************************************************************************/

#include <stdio.h>
//#include <afxwin.h>
#include <math.h>
#include "rsa.h"
#include<string.h>
#include<stdlib.h>

#define DECRYPT_FILE "RSA加密密文.txt"
#define ENCRYPT_FILE "RSA解密明文.txt"
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
	printf( "\n\tusage:rsa -k 素数P 素数Q\n" );
	printf( "\tusage: rsa -e 明文文件 公钥e 公钥n\n" );
	printf( "\tusage: rsa -d 密文文件 私钥d 私钥n\n" );
}

/******************************************************************************/
//	名称：IsNumber
//	功能：判断数字字符数组
//  参数：strNumber:字符数组
//	返回：数字字组数组返回true，否则返回false;

/******************************************************************************/
bool IsNumber( const char *strNumber )
{
	unsigned int i;

	if( !strNumber )
		return false;

	for ( i = 0 ; i < strlen(strNumber) ; i++ )
	{
		if ( strNumber[i] < '0' || strNumber[i] > '9' )
			return false;
	}

	return true;
}

/******************************************************************************/
//	名称：IsPrimeNumber
//	功能：判断素数
//  参数：num: 输入整数
//	返回：素数返回true，否则返回false;

/******************************************************************************/
bool IsPrimeNumber( unsigned int num )
{
	unsigned int i;
	if( num <= 1 )
		return false;

	unsigned int sqr = (unsigned int)sqrt((double)num);
	for( i = 2; i <= sqr; i++ )
	{
		if( num % i == 0 )
			return false;
	}

	return true;
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
	bool bRes = false;

	if( argc != 4 && argc != 5 )
		goto out;

	if( argc == 4 && argv[1][1] == 'k' )
	{
		//! 生成公、私钥对
		if( !IsNumber( argv[2] ) || 
			!IsNumber( argv[3] ) ||
			atoi( argv[2] ) > MAX_PRIME ||
			atoi( argv[3] ) > MAX_PRIME )
			goto out;
	}
	else if( (argc == 5) && (argv[1][1] == 'e' || argv[1][1] == 'd') )
	{
		//! 加密、解密操作
		if( !IsNumber( argv[3] ) ||
			!IsNumber( argv[4] ) ||
			atoi( argv[3] ) > MAX_NUM ||
			atoi( argv[4] ) > MAX_NUM )
			goto out;
	}
	bRes = true;

out:
	return bRes;
}

/******************************************************************************/
//	名称：kOption1
//	功能：程序k选项操作：由素数P、Q生成私钥d集合
//  参数：uiP: 程序入口参数P; uiQ: 程序入口参数Q
//	返回：执行正确返回生成私钥数目，否则返回0

/******************************************************************************/
unsigned int kOption1( unsigned int uiP, unsigned int uiQ )
{
	unsigned int uiRes = 0;

	if( !IsPrimeNumber( uiP ) )
	{
		printf( "P输入错误，P必须为(0, %d]素数", MAX_PRIME );
		return uiRes;
	}
	if( !IsPrimeNumber( uiQ ) )
	{
		printf( "Q输入错误，Q必须为(0, %d]素数", MAX_PRIME );
		return uiRes;
	}
	if( uiP == uiQ )
	{
		printf( "素数P与素数Q相同，很容易根据公钥n开平方得出素数P和Q，这种加密不安全，请更换素数!\n" );
		return uiRes;
	}
	printf( "正在生成私钥d集合......\n" );
	uiRes = MakePrivatedKeyd( uiP, uiQ );

	return uiRes;
}
#define Max 1000
unsigned int d, e, n;
unsigned int p, q;
char ctemp[Max];
int itemp[Max];
//! 程序主函数(Use MFC in a Shared DLL)
int main( int argc, char **argv )
{
	//rsa -k 素数P 素数Q 
	if(argv[1][1] == 'k'){
		p = atoi(argv[2]);
		q = atoi(argv[3]);
		int size = kOption1(p, q);	//num size
		printf("private key size is %d, please choose one: \n", size);
		scanf("%d", &size);
		int ret = MakePairkey(p, q, size);
		if(ret == ERROR_NOPUBLICKEY){
			printf("ERROR_NOPUBLICKEY");
		}else if(ret == ERROR_GENERROR){
			printf("ERROR GENERROR");
		}else if(ret == OK){
			//e private d public
			printf("ret ok\n");
			n = GetPairKey(d, e);
			printf("d is %d, e is %d, n is %d\n", d, e, n);
		}else{
			printf("debug info\n");
		}
	}
		
		scanf("%s", ctemp);
		int clen = strlen(ctemp);
		
		//rsa -e 明文string 公钥e 公钥n
		rsa_encrypt(n, d, ctemp, clen, itemp);
		int i;
		for(i = 0; i < clen; i++){
			printf("%d ", itemp[i]);
		}
		printf("\n");
		rsa_decrypt(n, e, itemp, clen, ctemp);
		for(i = 0; i < clen; i++){
			printf("%c ", ctemp[i]);
		}
	/*
	if(CheckParse(argc, argv)){
		if(argv[1][1] == 'k'){
			p = atoi(argv[2]);
			q = atoi(argv[3]);
			int size = kOption1(p, q);	//num size
			printf("private key size is %d,please choose one: \n", size);
			scanf("%d", size);
			int ret = MakePairkey(p, q);
			if(ret == ERROR_NOPUBLICKEY){
				printf("ERROR_NOPUBLICKEY");
			}else if(ret == ERROR_GENERROR){
				printf("ERROR GENERROR");
			}else if(ret == OK){
				//e private d public
				n = GetPairKey(d, e);
			}
			
		}else if(argv[1][1] == 'e'){
			//rsa -e 明文string 公钥e 公钥n
			//rsa_encrypt( int n, int e, char *mw, int mLength, int *&cw )
			rsa_encrypt(n, d, argv[2], sizeof(argv[2]), itemp);
			int i;
			int len = sizeof(argv[2]);
			for(i = 0; i < len; i++){
				printf("%d ", itemp[i]);
			}
		}else{
			//rsa -d 密文ints e n
		//	rsa_encrypt( int n, int e, char *mw, int mLength, int *&cw )
			e = atoi(argv[3]);
			n = atoi(argv[4]);

			rsa_decrypt(n, e, argv[2], sizeof(argv[2]), ctemp);
			int i;
			int len = sizeof(argv[2]);
			for(i = 0; i < len; i++){
				printf("%c ", itemp[i]);
			}
		}
	}
	*/

//	return true;
}
