#include<stdio.h>
#include<string.h>

//仿射密码加密 
int encode(int a, int b, char * str){
	int len = strlen(str);
	int i;
	for(i = 0; i < len; i++){
		int temp = a*(str[i] - 'a') + b;
		temp %= 26;
		str[i] = (char)(temp + 'a');
	}
}

//求一个数关于26的逆 
int aa(int a){
	int i;
	for(i = 0; i < 26; i++){
		int temp = (i*a)%26;
		if(temp == 1){
			return i;
		}
	}
}

//仿射密码解密 
int decode(int a, int b, char * str){
	int k = aa(a);
	int i, len = strlen(str);
	for(i = 0; i< len; i++){
		int temp = k*(str[i] - 'a' -b);
		temp %= 26;
		str[i] = (char) temp + 'a';
	}
}

//显示函数（dumb） 
void display(char * str){
	printf("%s\n", str);
}

int main(){
	char input[1024];
	int a,b;
	//input a and b
	scanf("%s", input);
	scanf("%d", &a);
	
	//loop until a is vaild
	//思考问题：a与26必须互质，不然a的逆不存在 
	while(a%2 == 0 || a%13 == 0){
		scanf("%d", &a);
	}
	scanf("%d", &b);
	
	//test it 
	decode(a, b, input);
//	encode(a, b, input);
	display(input);
} 
