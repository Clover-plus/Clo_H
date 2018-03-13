#ifndef _CLO_BMPREADER_H_
#define _CLO_BMPREADER_H_

#include <windows.h>
#include <stdio.h>
#define GARWARRF float
#define GARWARRL long

//读BMP文件
int openbmpfile(FILE *&p, char *filename) {
	char *name = new char[100];//不支持特别长的文件名;
	int i = 0;
	strcpy(name, filename);
	strcat(name, ".bmp");
	if (!(p = fopen(name, "rb"))) {
		printf("error_fileopenfail:filename:%s",name);
		return 1;
	}
	delete[] name;
	return 0;
}

//读文件头
BITMAPFILEHEADER readBMPhead(FILE* &p){
	BITMAPFILEHEADER header;
	fread(&header,sizeof(BITMAPFILEHEADER),1,p);
	return header;
}

//读位图信息头
BITMAPINFOHEADER readBMPIIhead(FILE* &p){
	BITMAPINFOHEADER header;
	fread(&header,sizeof(BITMAPINFOHEADER),1,p);
	return header;
}

DWORD readOffBits(BITMAPFILEHEADER A){
	return A.bfOffBits;
}

//获取文件像素(1,4,8,16,24,32)
WORD readBitCount(BITMAPINFOHEADER A){
	return A.biBitCount;
}

//获取文件宽度
LONG readWidth(BITMAPINFOHEADER A){
	return A.biWidth;
}

//获取文件高度
LONG readHeight(BITMAPINFOHEADER A){
	return A.biHeight;
}

struct EZCBGR
{
	unsigned char B;
	unsigned char G;
	unsigned char R;
};

EZCBGR readEZCBGR(FILE *&p){
	EZCBGR I;
	//fscanf(p, "%3c", &I);
	fread(&I, sizeof(EZCBGR), 1, p);
	return I;
}
//RGB转灰度
//此灰度与原相相反，需要255-x转换.
long RGBtoGaryL(EZCBGR I){
	return (I.R*299+I.G*587+I.B*114+500)/1000;
}

long CloRGBtoGaryL(EZCBGR I){
	return (I.R*76+I.G*150+I.B*29)>>8;
}

float CloRGBtoGaryF(EZCBGR I){
	return float(I.R*0.229+I.G*0.587+I.B*0.114);
}

#endif//cloBMPreder
