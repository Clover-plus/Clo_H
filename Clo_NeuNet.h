#ifndef CLONEUNET_H
#define CLONEUNET_H
#include "Clo_Matrix.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define _EZNOTE Clo_Matrix<float>

#ifndef _ATFUNC
#define _ATFUNC

float Clo_ATF_(float x) {
	return x > 0 ? 1 - 1 / (1 + x) : 0;
}

float Clo_ReLU(float x) {
	return x > 0 ? (x < 10 ? x : 10) : 0;//max(0,x)&x<10
}

float ATF_ReLU(float x) {//Rectified linear unit线性整流函数
	return x > 0 ? x : 0;//max(0,x)
}

float ATF_Sigmoid(float x) {
	return 1 / (1 + exp(-x));
}
#endif
class Neuront:public _EZNOTE
{//默认float
	private:
		float a;
		
	public:
		Neuront();
		Neuront(int);
		Neuront(_EZNOTE,int);
		Neuront(float*,int);
		float operator*(float*);
};

Neuront::Neuront():_EZNOTE(1){
	a=0;
}

Neuront::Neuront(int LENGTH):_EZNOTE(LENGTH){
	renewp(METHOD_NUM,0);
	a=0;
}

Neuront::Neuront(_EZNOTE C, int Length):_EZNOTE(C.getp(),Length){
	a=0;
}

Neuront::Neuront(float *f, int Length):_EZNOTE(f,Length){
	a=0;
}

float Neuront::operator*(float *X){
	//return (_EZNOTE(X,getRC())*_EZNOTE(getp(),getRC())).getp()[0]+a;
	return 0;
}

//
#define _EZNLIST Clo_Matrix<Neuront>
//
class NeurList:public _EZNLIST
{
	private:
		int lrow;//length per neur
	public:
		NeurList();
		NeurList(int);
		NeurList(int,int);
		int addNeur(float*m=0);
		int getlr();
		int getlen();
};

NeurList::NeurList():_EZNLIST(1){
	//
	lrow=0;
}

NeurList::NeurList(int Len):_EZNLIST(Len){
	//
	lrow=0;
}

NeurList::NeurList(int Len,int Lenoflist):_EZNLIST(Lenoflist){
	renewp(METHOD_NEURLIST,&Len);
	lrow=Len;
}

int NeurList::addNeur(float*m){
	int len=getRC();
	Neuront *h=new Neuront[len+1];
	for(int i=0;i<len;++i)h[i]=getp()[i];
	if(m==0)h[len]=Neuront(lrow);
	else{
		h[len]=Neuront(m,lrow);
	}
	setp(h,len+1,1);
	return 0;
}

int NeurList::getlr(){
	return lrow;
}

int NeurList::getlen(){
	return getRC();
}

class NeurListEx:public _EZNOTE
{
	private:
		//int lrow;//length per neur//row
		//int lenoflist//length of list//column
	public:
		NeurListEx();
		NeurListEx(int);
		NeurListEx(int,int);
		NeurListEx(int, int, _EZNOTE);
		NeurListEx(int, int, float*);
		~NeurListEx();
		int addNeur(float*m=0);
		int getlr();
		int getlen();
		int disturbance(float);
};
NeurListEx::~NeurListEx() {
	//
}
NeurListEx::NeurListEx():_EZNOTE(1,1){
	//
	
}
NeurListEx::NeurListEx(int Len):_EZNOTE(Len){
	//
	
}
NeurListEx::NeurListEx(int Len,int Lenoflist):_EZNOTE(Len,Lenoflist){
	//
}
NeurListEx::NeurListEx(int Len, int Lenoflist, _EZNOTE TP) : _EZNOTE(TP.getp(), Len, Lenoflist) {
	//
}
NeurListEx::NeurListEx(int Len, int Lenoflist, float* P) : _EZNOTE(P, Len, Lenoflist) {
	//
}
int NeurListEx::addNeur(float*m){
	addRC(ADD_COLUMN);
	return 0;
}
//len per neur
int NeurListEx::getlr(){
	return getRC(0);
}
//len of list
int NeurListEx::getlen(){
	return getRC(1);
}
int NeurListEx::disturbance(float mu) {
	int t1 = getlr();
	int t2 = getlen();
	int t = t1*t2;
	/*for (int i1=0; i1 < t1; ++i1) {
		for (int i2 = 0; i2 < t2; ++i2) {
			getp()[i1*t2 + i2] += mu*(randInt(-3,3));
		}
	}*/
	for (int i = 0; i < t; ++i) {
		getp()[i] += mu*randInt(-3, 3);
	}
	return 0;
}

//
#define _EZNEURNET Clo_Matrix<NeurList>
//

class NeurNet:public _EZNEURNET
{
	private:
		//
		
	public:
		NeurNet();
		NeurNet(int);
		NeurNet(int,int);
		NeurList* invite(int);
		int addList(int);
		int addList(int,int);//not recommand
};

NeurNet::NeurNet():_EZNEURNET(1){
	//
}
NeurNet::NeurNet(int len):_EZNEURNET(1){
	getp()[0]=NeurList(len,1);
	//
}
NeurNet::NeurNet(int len,int lenoflist):_EZNEURNET(1){
	getp()[0]=NeurList(len,lenoflist);
}
NeurList* NeurNet::invite(int N){
	return &getp()[N-1];//自然编号(1，2，3，...)
}
int NeurNet::addList(int lenoflist){
	int num=getRC();
	//int lenofrow=getp()[0].getlr();
	NeurList *h=new NeurList[num+1];
	for(int i=0;i<num;++i)h[i]=getp()[i];
	int len=h[num-1].getlen();
	h[num]=NeurList(len,lenoflist);
	setp(h,num+1,1);
	return 0;
}
int NeurNet::addList(int pos,int m){
	if(pos<=getRC()&&pos>0){
		int num=getRC();
		int i=0;
		NeurList *h=new NeurList[num+1];
		for(;i<pos;++i)h[i]=getp()[i];
		int len=h[i-1].getlen();
		int lenoflist=getp()[i].getlr();
		h[i]=NeurList(len,lenoflist);
		for(++i;i<=num;++i)h[i]=getp()[i-1];
		setp(h,num+1,1);
	}
	else{
		return -1;
	}
	return 1;
}

//
#define _EZNEURNETEX Clo_Matrix<NeurListEx>
//
typedef struct Clo_NeurNetExtable
{
	int len;//num of Neurlist
	int inputsize;//row of 1st list
	int lenth;//sum of size
	int *size;//size of per list
	float *otptC;
}NeurNetExtable, NeurNettable;
typedef struct Clo_Neurpair
{
	int row;//len
	int column;//lenoflist
}Neurpair;
//
class NeurNetEx:public _EZNEURNETEX
{
	private:
		//
		
	public:
		NeurNetEx();
		NeurNetEx(int);
		NeurNetEx(int,int);
		NeurNetEx(NeurNetExtable);
		NeurListEx* invite(int);
		int addList(int);
		int addList(int,int);//not recommand
		_EZNOTE input(float*,int);
		NeurNetExtable otptC();
		int traintype1(float*, int);//random disturbance
		//int inputC(NeurNetExtable);
};

NeurNetEx::NeurNetEx():_EZNEURNETEX(1){
	//
}
NeurNetEx::NeurNetEx(int len):_EZNEURNETEX(1){
	getp()[0]=NeurListEx(len+1,1);
	//
}
NeurNetEx::NeurNetEx(int len,int lenoflist):_EZNEURNETEX(1){
	getp()[0]=NeurListEx(len+1,lenoflist);
}
NeurNetEx::NeurNetEx(NeurNetExtable Table) : _EZNEURNETEX(Table.len) {
	Neurpair *pp = new Neurpair[Table.len];
	pp[0].row = Table.inputsize+1;//+1 for const a[]
	for (int i = 0; i < Table.len-1; ++i) {
		pp[i].column = Table.size[i] / pp[i].row;
		pp[i + 1].row = pp[i].column + 1;//+1 for const a[]
	}
	pp[Table.len - 1].column = Table.size[Table.len - 1] / pp[Table.len - 1].row;
	//初始化各list
	int lenth = 0;
	for (int i = 0; i < Table.len; ++i) {
		getp()[i] = NeurListEx(pp[i].row, pp[i].column, &Table.otptC[lenth]);
		lenth += Table.size[i];
	}
}
NeurListEx* NeurNetEx::invite(int N){
	return &getp()[N-1];//自然编号(1，2，3，...)
}
int NeurNetEx::addList(int lenoflist){
	int num=getRC();
	//int lenofrow=getp()[0].getlr();
	NeurListEx *h=new NeurListEx[num+1];
	for(int i=0;i<num;++i)h[i]=getp()[i];
	int len=h[num-1].getlen();
	h[num]=NeurListEx(len+1,lenoflist);//len+1 for const a[]
	setp(h,num+1,1);
	return 0;
}
int NeurNetEx::addList(int pos,int m){//m not func. just to avoid renamefunc addlist
	if(pos<=getRC()&&pos>0){
		int num=getRC();
		int i=0;
		NeurListEx *h=new NeurListEx[num+1];
		for(;i<pos;++i)h[i]=getp()[i];
		int len=h[i-1].getlen();
		int lenoflist=getp()[i].getlr();
		h[i]=NeurListEx(len+1,lenoflist);////len+1 for const a[]
		for(++i;i<=num;++i)h[i]=getp()[i-1];
		setp(h,num+1,1);
	}
	else{
		return -1;
	}
	return 1;
}
_EZNOTE NeurNetEx::input(float *m, int length) {
	_EZNOTE INPUT(m, 1, length);
	//_EZNOTE temp;
	int len = getRC();
	for (int i = 0; i < len; ++i) {
		
		INPUT = INPUT.addRC(1, 1,METHOD_COLUMN);
		INPUT = INPUT*getp()[i];
		INPUT = INPUT.Activate(ATF_ReLU);
		//INPUT = ((INPUT.addRC(1, 1, METHOD_COLUMN))*getp()[i]).Activate(ATF_ReLU);
#ifdef TEST
		getp()[i].display();
INPUT.display();
#endif // TEST

	}
	return INPUT;
}
int NeurNetEx::traintype1(float*m, int ans) {
	_EZNOTE OUTP = input(m, getp()[0].getlr()-1);
	int theans = OUTP.max_id();
	int lim = 0;
	int sup = 1000;
	int len = getRC();
	while (theans != ans && lim < sup) {
		for (int i = 0; i < len; ++i) {
			getp()[i].disturbance(1e-2f);
		}
		//if(lim==0)
		OUTP = input(m, getp()[0].getlr()-1);
		//
		theans = OUTP.max_id();
		//
		printf("%d ", theans);
		++lim;
	}
	return lim < sup ? 0 : 1;
}
NeurNetExtable NeurNetEx::otptC() {
	NeurNetExtable Table;
	Table.inputsize = getp()[0].getlr()-1;//-1 for const a[]
	Table.len= getRC();
	Table.lenth = 0;
	int i1 = 0;
	Table.size = new int[Table.len];
	for (int i = 0; i < Table.len; ++i) {
		Table.size[i] = getp()[i].getlen()*getp()[i].getlr();
		Table.lenth += Table.size[i];
	}
	Table.otptC = new float[Table.lenth];
	for (int i = 0; i < Table.len; ++i) {
		for (int i2=0; i2 < Table.size[i]; ++i2,++i1) {
			Table.otptC[i1] = getp()[i].getp()[i2];
		}
	}
	return Table;
}

int pullNeurNetExtable(FILE *&fp, NeurNetExtable table) {
	fwrite(&table.len, sizeof(int), 1, fp);
	fwrite(&table.inputsize, sizeof(int), 1, fp);
	fwrite(&table.lenth, sizeof(int), 1, fp);
	if (fwrite(table.size, sizeof(int), table.len, fp) != table.len) {
		printf("error_fwrite_size\n");
	}
	if (fwrite(table.otptC, sizeof(float), table.lenth, fp) != table.lenth) {
		printf("error_fwrite_size\n");
	}
	return 0;
}

NeurNetExtable drawNeurNetExtable(FILE *&fp) {
	NeurNetExtable Table;
	fread(&Table.len, sizeof(int), 1, fp);
	fread(&Table.inputsize, sizeof(int), 1, fp);
	fread(&Table.lenth, sizeof(int), 1, fp);
	Table.size = new int[Table.len];
	Table.otptC = new float[Table.lenth];
	if (fread(Table.size, sizeof(int), Table.len, fp) != Table.len) {
		printf("error_fread_size\n");
	}
	if (fread(Table.otptC, sizeof(float), Table.lenth, fp) != Table.lenth) {
		printf("error_fread_lenth\n");
	}
	if (!feof(fp)) {
		printf("error_File_notEOF\n");
	}
	//over
	return Table;
}



#endif/*CLONEUNET_H*/
