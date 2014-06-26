// rdWebServer.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>

#include "rdWebApp.h"


int main(int argc, char* argv[])
{
	rdWebApp webservice;
	webservice.Run();


	int a;
	scanf("%d", &a);
	return 0;
}
