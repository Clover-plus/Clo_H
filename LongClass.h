//
//This is a .h which is about some longclass, in order to solve the maxmize
//question.
//
//
#ifndef LonGclass_H
#define LonGclass_H
#include <stdio.h>

/*int_16:0~32767*/
/*unsigned int_16:0~65535*/
/*int_32:2147483647*/
/*unsigned int_32:0~4294967295*/

#define TP_DEFAULT 1
#define TP_BRANEW 2
#define uS unsigned
#ifndef uint
#define uint unsigned int
#endif
const unsigned int MAX_INT_NOTE=999999999;/*999,999,999*/
const unsigned int MAX_INT_NOTE_PLUS=1000000000;/*1,000,000,000*/
const int EXPPNOTE=9;/*the number of digits(exponents) per NOTE*/
const uint E4 = 10000;
const uint E5 = 100000;
const uint E6 = 1000000;
const uint E7 = 10000000;
const uint E8 = 100000000;
class IntNote;
class LongInt;
int UintDigitsBinary(uint);
#include "Clo_Math.h"

int UINTtodigits(unsigned int x){
	/*It's ruled that the top of x must be 0, also x<=2147483647(x>=0, of course)*/
	int i=0;
	if (x == 0)return 1;
	else while(x){
		x=x/10;
		++i;
	}
	return i;
}

int UintDigitsBinary(uint x) {
	int i = 0;
	while (x) {
		x >>= 1;
		++i;
	}
	return i;
}

uint* UintMultiplication(uint n1, uint n2) {
	/*based on the MAX_INT_NOTE*/
	//under promotion
	/*pointer A should be delete later*/
	uint* A = new uint[2];
	uint N[2][3], temp[2];
	uint NN[3];
	N[0][0] = n1 / E8;
	temp[0] = n1%E8;
	N[0][2] = temp[0] % E4;
	N[0][1] = temp[0] / E4;
	N[1][0] = n2 / E8;
	temp[1] = n2%E8;
	N[1][2] = temp[1] % E4;
	N[1][1] = temp[1] / E4;
	NN[0] = N[0][1] * N[1][1];//E4*E4=E8
	NN[1] = N[0][1] * N[1][2] + N[0][2] * N[1][1];//E4
	NN[2] = N[0][0] * temp[1] + N[1][0] * temp[0];//E8
	A[0] = NN[0] / 10 + NN[1] / E5 + NN[2] /10 + N[0][0] * N[1][0]*E7;
	A[1] = NN[0] % 10 * E8 + NN[1] % E5 * E4 + N[0][2] * N[1][2] + NN[2] % 10 * E8;
	A[0] += A[1] / MAX_INT_NOTE_PLUS;
	A[1] = A[1] % MAX_INT_NOTE_PLUS;
	return A;
}

uint* UintMultiBinary(uint n1, uint n2) {
	/*based on the MAX_INT_NOTE*/
	//finished
	/*pointer A should be delete later*/
	uint* A = new uint[2];
	uint N1[2],N2[2];
	uint Z[3];
	N1[0] = n1 >> 15;
	N1[1] = n1 & 0x00007FFF;
	N2[0] = n2 >> 15;
	N2[1] = n2 & 0x00007FFF;
	/*Karatsuba Multiplication*/
	Z[0] = N1[0] * N2[0];
	Z[1] = N1[1] * N2[1];
	Z[2] = (N1[0] + N1[1])*(N2[0] + N2[1]) - Z[0] - Z[1];
	/*A=Z[0]<<30+Z[1]+Z[2]<<15*/
	A[0] = Z[0] + (Z[2] >> 15);
	A[1] = Z[1] + (Z[2] << 15 & 0x3FFFFFFF);
	A[0] += A[1] >> 30;
	A[1] &= 0x3FFFFFFF;
	/*turn Binary to Decimal*/
	int i = UintDigitsBinary(A[0]);
	uint temp = 0, temp1 = 0;
	int temp2 = 0;
	while (i>0) {
		temp1 = (A[0] << (30 - i)) + (A[1] >> i);
		temp2 = temp1 - MAX_INT_NOTE_PLUS;//note
		if (temp2>=0) {
			temp += 1<<i;
			temp1 = temp2;
			A[0] = temp1 >> (30 - i);
			A[1] = (A[1] << (32 - i) >> (32 - i)) + (temp1 << (2 + i) >> 2);
			i = UintDigitsBinary(A[0]);
		}
		else {
			/*this should not be occur twice in the row*/
			--i;
		}
	}
	//i==0
	temp1 = (A[0] << 30) + A[1];
	temp2 = temp1 - MAX_INT_NOTE_PLUS;//note
	if (temp2 >= 0) {
		temp += 1;
		A[1] = temp2;
	}
	//end of i==0
	A[0] = temp;
	return A;
}

typedef struct IntNoteArray
{
	IntNote* head;
	IntNote* tail;
	unsigned int length;/*also int will work*/ 
	unsigned int digits;/*also int will work*/
}INTARRY;



class IntNote
{
	public:
		unsigned int n;
		IntNote* next;
		IntNote* prev;
		IntNote();
		~IntNote();
		friend INTARRY* NewIntArry(int);//unnessary friend
		friend void DeleteIntArry(INTARRY*);//unnessary friend
		friend INTARRY* NewIntArry(char*,int);//unnessary friend
		IntNote* visit(uint subs);
};

IntNote::IntNote(){
	/*this do nothing now*/
}

IntNote::~IntNote(){
	/*a bug thing*/
	if(next)delete next;
	prev=NULL;
}

IntNote* IntNote::visit(uint subs) {
	/*this function is not well defined, the returned thing should be examed if it's next==NULL and it's still legal even when the two are equal*/
	IntNote* temp = this;
	for (uint i = 0; i < subs&&temp->next!=NULL; ++i) {
		temp = temp->next;
	}
	return temp;
}

IntNote* NweIntNote(int length){
	//IntNote
	IntNote *p=new IntNote;
	/*do nothing here now*/
	return p;
}

INTARRY* NewIntArry(int Length){
	INTARRY *p=new IntNoteArray;
	p->digits=Length;
	p->length=C_Ceil(Length,EXPPNOTE);
	IntNote* temp;
	temp=new IntNote;
	p->head = temp;
	temp->prev=NULL;/*tag for head*/
	temp->n=0;/*blank for head*/
	for(uint i=0;i<p->length;++i){
		temp->next=new IntNote;
		temp->next->prev=temp;
		temp=temp->next;
		temp->n = 0;
	}
	//temp->n=0;//for the upper line this is no longer needed.
	temp->next=NULL;/*tag of tail*/
	p->tail=temp;
	return p;
}

INTARRY* NewIntArry(INTARRY* P){
	INTARRY *p=new IntNoteArray;
	p->digits=P->digits;
	p->length=P->length;
	IntNote* temp;
	temp = new IntNote;
	p->head = temp;
	IntNote* tempp=P->head;
	
	temp->prev=NULL;/*tag for head*/
	//temp->n=0;/*blank for head*/
	temp->n = tempp->n;//not always blank
	for(uint i=0;i<p->length;++i){
		temp->next=new IntNote;
		temp->next->prev=temp;
		temp=temp->next;
		tempp=tempp->next;
		temp->n=tempp->n;
	}
	temp->next=NULL;/*tag of tail*/
	p->tail=temp;
	return p;
}

INTARRY* NewIntArry(char* Num,int Length){
	INTARRY *p=new IntNoteArray;
	p->digits=Length;
	p->length=C_Ceil(Length,EXPPNOTE);
	unsigned int tempp[EXPPNOTE];
	/*clearify tempp*/
	tempp[0] = 1;
	for (int i = 1; i<EXPPNOTE; ++i) {
		tempp[i] = 10 * tempp[i - 1];
	}
	IntNote* temp;
	temp=new IntNote;
	p->head = temp;
	temp->prev=NULL;/*tag for head*/
	temp->n=0;/*blank for head*/
	for(uint i=0,d=0;i<p->length&&d<p->digits;++i){
		temp->next=new IntNote;
		temp->next->prev=temp;
		temp=temp->next;
		temp->n=0;/*put the value as zero*/
		for(uint dd=0;dd<EXPPNOTE &&d <p->digits;++d,++dd){
			temp->n+=tempp[dd]*ChartoInt(Num[Length-1-d]);
		}
	}
	temp->next=NULL;/*tag of tail*/
	p->tail=temp;
	return p;
}

void DeleteIntArry(INTARRY* ita){
	//may bug
	if (ita != NULL) {
		int Length=ita->length;
		IntNote* temp=ita->head;
		delete temp;
		//temp = NULL;
		delete ita;
	}
}

void MeasureIntArry(INTARRY* P) {
	/*measure length*/
	P->length = 0;
	IntNote *temp = P->head;
	while (temp->next != NULL) {
		P->length = P->length + 1;
		temp = temp->next;
	}
	/*measure digits*/
	unsigned int i = 0;
	unsigned int temp1 = P->tail->n;
	for (;temp1>0; ++i) {
		temp1 = temp1 / 10;
	}
	P->digits = EXPPNOTE*(P->length - 1) + i;
}

void ZeroClearArry(INTARRY* P) {
	/*clear the zero over the top*/
	IntNote *temp = P->tail;
	while (temp != P->head&&temp->n == 0) {
		temp->next = NULL;//Necessary
		temp = temp->prev;
		delete temp->next;
	}
	temp->next = NULL;
	P->tail = temp;
	MeasureIntArry(P);
}

class LongInt
{
	private:
		INTARRY* p;
		
	public:
		LongInt();
		LongInt(int);
		LongInt(char*,int);
		LongInt(INTARRY*,int);
		LongInt(IntNote*, uint, uint);
		LongInt(const LongInt&);
		~LongInt();
		void Display();
		char* toC();
		IntNote* visit(uint subs);//untested
		int vTop();
		int SetExp(uint);
		friend LongInt LIAddition(LongInt F, LongInt N);
		LongInt& operator=(LongInt&);
		LongInt operator+(LongInt&);
		LongInt operator-(LongInt&);
		LongInt operator*(LongInt&);
};

LongInt::LongInt(){
	p = NULL;
	/*this do nothing now*/
}

LongInt::LongInt(int Length){
	/*Is it nessary to classify the array?*/
	p=NewIntArry(Length);//Length here mean digits
}

LongInt::LongInt(char* Num,int Length=0){
	/*It's important to have the Length so that function can be surely endable*/
	if(Length==0)Length=C_strlen(Num);//addition
	p=NewIntArry(Num,Length);
}

LongInt::LongInt(INTARRY* P,int tp=TP_DEFAULT){
	switch(tp){
		case TP_DEFAULT:{
			p=P;
			break;
		}
		case TP_BRANEW:{
			p=NewIntArry(P);
			break;
		}
		default:{
			p=P;
			break;
		}
	}
}

LongInt::LongInt(IntNote* P,uint N=NULL,uint len=NULL) {
	IntNote *temp,*temp1;
	this->p = new INTARRY;
	temp = new IntNote;
	p->head = temp;
	temp = p->head;
	temp1 = P;//P is head-note
	temp->prev = NULL;
	if(N)temp->n = N;//N is exp
	else temp->n = temp1->n;
	if (len) {
		/*make sure the len is smaller than length of P*/
		for (uint i = 0; i < len; ++i) {
			temp->next = new IntNote;
			temp->next->prev = temp;
			temp = temp->next;
			temp1 = temp1->next;
			temp->n = temp1->n;
		}
	}
	else {
		while (temp1->next != NULL) {
			temp->next = new IntNote;
			temp->next->prev = temp;
			temp = temp->next;
			temp1 = temp1->next;
			temp->n = temp1->n;
		}
	}

	temp->next = NULL;
	this->p->tail = temp;
	MeasureIntArry(this->p);
}

LongInt::LongInt(const LongInt& I) {
	this->p = NewIntArry(I.p);
}

LongInt::~LongInt(){
	DeleteIntArry(p);
}

void LongInt::Display(){
	IntNote* temp;
	int temp1 = 0;
	temp=p->tail;
	printf("%u", temp->n);
	temp = temp->prev;
	for(uint i=1;i<p->length;++i){
		temp1 = EXPPNOTE - UINTtodigits(temp->n);
		for (int i1 = 0; i1 < temp1; ++i1)printf("0");
		printf("%u",temp->n);
		temp=temp->prev;
	}
}

char* LongInt::toC(){
	/*It's important to delete the char* smtm after*/
	char* str=new char[p->digits+1];
	IntNote* tnote=p->tail;
	unsigned int temp=0,temp1=0,tempp[EXPPNOTE];
	int index=0;
	/*clearify tempp*/
	tempp[0]=1;
	for(int i=1;i<EXPPNOTE;++i){
		tempp[i]=10*tempp[i-1];
	}
	//for the tail there is no need to put zero ahead
	int sw = 0;
	temp = tnote->n;
	for (int id = EXPPNOTE - 1; id >= 0; --id) {
		temp1 = temp / tempp[id];
		if (temp1||sw) {
			str[index] = temp1+'0';
			++index;
			temp = temp%tempp[id];
			sw = 1;
		}
	}
	//end the block for tail
	tnote = tnote->prev;
	for(uint i=1;i<p->length;++i){
		temp=tnote->n;
		for(int id=EXPPNOTE-1;id>=0;--id){
			temp1=temp/tempp[id];
			str[index] = temp1+'0';
			++index;
			if(temp1){
				temp=temp%tempp[id];
			}
		}
		tnote=tnote->prev;
	}
	if(index!=p->digits)str[index]='e';/*error*/
	str[p->digits]='\0';
	return str;
}

IntNote* LongInt::visit(uint subs) {
	IntNote* temp = p->head;
	//return head when subs is greater than length
	if (subs <= p->length) {
		for (uint i = 0; i < subs; ++i) {
			temp = temp->next;
		}
	}
	return temp;
}

int LongInt::vTop() {
	int temp = EXPPNOTE*p->length - p->digits;
	return p->tail->n / C_EXP10(temp);
}

int LongInt::SetExp(uint N) {
	this->p->head->n = N;
	return 0;
}

LongInt LIAddition(LongInt F, LongInt N)
{
	//untested
	//This is for Multiplication
	int mlen = longerfingeru(F.p->head->n + F.p->length, N.p->head->n + N.p->length);
	int mexp = longerfingeru(F.p->head->n, N.p->head->n);
	uint minexp = mexp ? N.p->head->n : F.p->head->n;
	uint maxexp = mexp ? F.p->head->n : N.p->head->n;
	INTARRY* P=new IntNoteArray;
	IntNote *temp, *temp1, *temp2;
	int mark = 0;
	uint ii = 0;
	temp = new IntNote;
	P->head = temp;
	temp->prev = NULL;/*blank*/
	temp->n = minexp;/*Tag/Exp*/
	if (mexp) {
		temp1 = N.p->head;/*temp1 's exp is smaller*/
		temp2 = F.p->head;
	}
	else {
		temp1 = F.p->head;
		temp2 = N.p->head;
	}
	/*add 0 quest*/
	for (ii = minexp; ii < maxexp && temp1->next != NULL; ++ii) {
		temp->next = new IntNote;
		temp->next->prev = temp;
		temp = temp->next;
		temp1 = temp1->next;
		temp->n = temp1->n;//plus 0
	}
	/*add the digits as 0*/
	for (; ii < maxexp; ++ii) {
		temp->next = new IntNote;
		temp->next->prev = temp;
		temp = temp->next;
		temp->n = 0;//as 0
	}
	//adding start
	for (int i = 0; temp1->next != NULL && temp2->next != NULL; ++i) {
		temp->next = new IntNote;
		temp->next->prev = temp;
		temp = temp->next;
		temp1 = temp1->next;
		temp2 = temp2->next;
		if (mark)temp->n = temp1->n + temp2->n + 1;
		else temp->n = temp1->n + temp2->n;//endif
		if (temp->n>MAX_INT_NOTE) {
			temp->n = temp->n%MAX_INT_NOTE_PLUS;
			mark = 1;
		}
		else mark = 0;//endif
	}
	if (mlen == mexp)temp1 = temp2;
	while (mark) {
		temp->next = new IntNote;
		temp->next->prev = temp;
		temp = temp->next;
		if (temp1->next != NULL) {
			temp1 = temp1->next;
			temp->n = temp1->n + 1;
			if (temp->n>MAX_INT_NOTE) {
				temp->n = 0;
				mark = 1;
			}
			else mark = 0;//endif
		}
		else {
			temp->n = 1;//top of temp eq 1
			mark = 0;
		}
	}
	while (temp1->next != NULL) {
		temp->next = new IntNote;
		temp->next->prev = temp;
		temp = temp->next;
		temp1 = temp1->next;
		temp->n = temp1->n;
	}
	temp->next = NULL;/*tag for tail*/
	P->tail = temp;
	MeasureIntArry(P);
	return LongInt(P);
}

LongInt& LongInt::operator=(LongInt &I) {
	this->p = NewIntArry(I.p);
	return *this;
}

LongInt LongInt::operator+(LongInt &I){
	INTARRY* P=new IntNoteArray;
	int mlen=longerfingeru(this->p->length,I.p->length);
	int minlen=mlen?I.p->length:this->p->length;
	IntNote *temp,*temp1,*temp2;
	int mark=0;
	temp=new IntNote;
	P->head=temp;
	temp->prev=NULL;/*blank*/
	temp->n=0;/*lag*/
	temp1=this->p->head;
	temp2=I.p->head;
	for(int i=0;i<minlen;++i){
		temp->next=new IntNote;
		temp->next->prev=temp;
		temp=temp->next;
		temp1=temp1->next;
		temp2=temp2->next;
		if(mark)temp->n=temp1->n+temp2->n+1;
		else temp->n=temp1->n+temp2->n;//endif
		if(temp->n>MAX_INT_NOTE){
			temp->n=temp->n%MAX_INT_NOTE_PLUS;
			mark=1;
		}
		else mark=0;//endif
	}
	if(!mlen)temp1=temp2;
	while(mark){
		temp->next = new IntNote;
		temp->next->prev = temp;
		temp = temp->next;
		if (temp1->next != NULL) {
			temp1 = temp1->next;
			temp->n = temp1->n + 1;
			if (temp->n>MAX_INT_NOTE) {
				temp->n = 0;
				mark = 1;
			}
			else mark = 0;//endif
		}
		else {
			temp->n = 1;//top of temp eq 1
			mark = 0;//loop end
		}
	}
	while(temp1->next!=NULL){
		temp->next=new IntNote;
		temp->next->prev=temp;
		temp=temp->next;
		temp1=temp1->next;
		temp->n=temp1->n;
	}
	temp->next=NULL;/*tag for tail*/
	P->tail=temp;
	MeasureIntArry(P);
	return LongInt(P);
}

LongInt LongInt::operator-(LongInt &I) {
	/*This is only work while A is bigger than B in A-B*/
	INTARRY* P = new IntNoteArray;
	int mlen = longerfingeru(this->p->length, I.p->length);
	int minlen = mlen ? I.p->length : this->p->length;
	IntNote *temp, *temp1, *temp2;
	int mark = 0;
	temp = new IntNote;
	P->head = temp;
	temp->prev = NULL;/*blank*/
	temp->n = 0;/*lag*/
	temp1 = this->p->head;
	temp2 = I.p->head;
	for (int i = 0; i<minlen; ++i) {
		temp->next = new IntNote;
		temp->next->prev = temp;
		temp = temp->next;
		temp1 = temp1->next;
		temp2 = temp2->next;
		temp->n = temp1->n + MAX_INT_NOTE_PLUS - temp2->n;
		if (temp->n>MAX_INT_NOTE_PLUS) {
			temp->n = temp->n - MAX_INT_NOTE_PLUS - mark;
			mark = 0;
		}
		else {
			if (temp->n == MAX_INT_NOTE_PLUS) {
				if (mark)temp->n = MAX_INT_NOTE;
				else temp->n = 0;
				//keep the mark const here
			}
			else {
				temp->n -= mark;
				mark = 1;
			}
		}
	}
	if (!mlen)temp1 = temp2;
	while (mark&&temp1->next != NULL) {
		temp->next = new IntNote;
		temp->next->prev = temp;
		temp = temp->next;
		temp1 = temp1->next;
		if (temp1->n) {
			temp->n = temp1->n - 1;
			mark = 0;
		}
		else {
			//bug
			temp->n = MAX_INT_NOTE;
			//mark = 1;
		}
	}
	while (temp1->next != NULL) {
		temp->next = new IntNote;
		temp->next->prev = temp;
		temp = temp->next;
		temp1 = temp1->next;
		temp->n = temp1->n;
	}
	temp->next = NULL;/*tag for tail*/
	P->tail = temp;
	ZeroClearArry(P);
	//MeasureIntArry(P);
	return LongInt(P);
}

LongInt LongInt::operator*(LongInt &I){
	int mlen = longerfingeru(this->p->length, I.p->length);
	uint maxlen, minlen, halflen;
	IntNoteArray *temp1, *temp2;
	if (mlen) {
		maxlen = this->p->length;
		minlen = I.p->length;
		temp1 = this->p;//temp1 is longer
		temp2 = I.p;
	}
	else {
		maxlen = I.p->length;
		minlen = this->p->length;
		temp1 = I.p;
		temp2 = this->p;
	}
	if (maxlen == 1) {
		/*It's promised that minlen/maxlen >= 1*/
		uint* A = UintMultiBinary(temp1->head->next->n, temp2->head->next->n);
		INTARRY *P = new INTARRY;
		IntNote *temp = new IntNote;
		P->head = temp;
		temp->next = new IntNote;
		temp->next->prev = temp;
		temp = temp->next;
		temp->n = A[1];//low
		if (A[0]) {
			temp->next = new IntNote;
			temp->next->prev = temp;
			temp = temp->next;
			temp->n = A[0];//high
		}
		temp->next = NULL;//tail
		P->tail = temp;
		delete[] A;
		MeasureIntArry(P);
		P->head->n=temp1->head->n+temp2->head->n;
		return LongInt(P);
	}
	/*maxlen > 1*/
	halflen = maxlen >> 1;//maxlen/2
	if (minlen <= halflen) {
		/*A0,A1,B0,B1,A0=0*/
		LongInt A1,B0,B1;
		IntNote *Temp;
		Temp=temp1->head->visit(halflen);
		A1=LongInt(temp2,TP_BRANEW);
		B0=LongInt(Temp,temp1->head->n+halflen,maxlen-halflen);
		B1=LongInt(temp1->head,temp1->head->n,halflen);
		return LIAddition(A1*B0, A1*B1);
	}
	else{
		/*A0,A1,B0,B1,A0=0*/
		/*
		Z0=A0*B0
		Z1=A1*B1
		Z2=(A0+A1)(B0+B1)-Z0-Z1
		*/
		LongInt A0,A1,B0,B1,Z0,Z1,Z2;
		IntNote *Temp;
		Temp=temp1->head->visit(halflen);
		A0=LongInt(Temp,temp1->head->n+halflen,maxlen-halflen);
		A1=LongInt(temp1->head,temp1->head->n,halflen);
		Temp=temp2->head->visit(halflen);
		B0=LongInt(Temp,temp2->head->n+halflen,minlen-halflen);
		B1=LongInt(temp2->head,temp2->head->n,halflen);
#ifdef TEST
		blank();
		printf("A0:");
		A0.Display();
		blank();
		printf("A1:");
		A1.Display();
		blank();
		printf("B0:");
		B0.Display();
		blank();
		printf("B1:");
		B1.Display();
#endif
		Z0=A0*B0;
		Z1=A1*B1;
		Z2=(A0+A1)*(B0+B1)-(Z0+Z1);//at here the exp of Z2 is 0 which is ought to be '£¿'
		Z2.SetExp(halflen+temp1->head->n+temp2->head->n);//here halflen+?
#ifdef TEST
		blank();
		printf("Z0:");
		Z0.Display();
		blank();
		printf("Z1:");
		Z1.Display();
		blank();
		printf("Z2:");
		Z2.Display();
		blank();
#endif
		return LIAddition(LIAddition(Z0, Z1), Z2);
	}
	//may be unfinished
}

#endif/*longclass_h*/
