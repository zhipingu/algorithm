#pragma once

typedef struct st_global {
	int hello;
	int world;
}Global, *GlobalPtr;

Global Global_get_instance();
const GlobalPtr Global_get_instancePtr();
void Global_set_hello(int hello);
int * fun();

#define GLOBAL Global_get_instance()//����typedef Global_get_instance() GLOBAL����֧��
#define GLOBAL_PTR Global_get_instancePtr()
#define GLOBAL_HELLO(hello) (Global_set_hello(hello))