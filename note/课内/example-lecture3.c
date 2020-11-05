#include <stdlib.h>

struct date* date_create_right (char * c){
	struct date * d = malloc();//未指定大小？
	return d;
}

//错误例子，不能返回局部变量给指针
int * date_create_wrong( struct date *d, char *c ){
	int i = 5; 
	d = malloc ();

	return &i;
}


int main (){

	struct date *d; 

	int * i = date_create_wrong( d, "string");

	struct date *b; 

	b = date_create_right ("string");

}

int x = 1;

int *p1 = &x; //x地址

int *p2 = &p1; //p1指针地址
 
int * p3 = &p2;//p2指针地址

int value = *(*(*p3))//1