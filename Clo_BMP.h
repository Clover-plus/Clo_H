#ifndef _CLO_BMPREADER_H_
#define _CLO_BMPREADER_H_

#include <windows.h>
#include <stdio.h>
#define GARWARRF float
#define GARWARRL long

//��BMP�ļ�
int openbmpfile(FILE *&p, char *filename) {
	char *name = new char[100];//��֧���ر𳤵��ļ���;
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

//���ļ�ͷ
BITMAPFILEHEADER readBMPhead(FILE* &p){
	BITMAPFILEHEADER header;
	fread(&header,sizeof(BITMAPFILEHEADER),1,p);
	return header;
}

//��λͼ��Ϣͷ
BITMAPINFOHEADER readBMPIIhead(FILE* &p){
	BITMAPINFOHEADER header;
	fread(&header,sizeof(BITMAPINFOHEADER),1,p);
	return header;
}

DWORD readOffBits(BITMAPFILEHEADER A){
	return A.bfOffBits;
}

//��ȡ�ļ�����(1,4,8,16,24,32)
WORD readBitCount(BITMAPINFOHEADER A){
	return A.biBitCount;
}

//��ȡ�ļ����
LONG readWidth(BITMAPINFOHEADER A){
	return A.biWidth;
}

//��ȡ�ļ��߶�
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
//RGBת�Ҷ�
//�˻Ҷ���ԭ���෴����Ҫ255-xת��.
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
