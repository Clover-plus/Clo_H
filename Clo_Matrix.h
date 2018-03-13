/*
Clover 
2017.10.23
*/ 
#ifndef CloverMatrix_H
#define CloverMatrix_H
#include <iostream>

#include "Clo_Math.h"

#define int_Clo_Array_
#define Clo_Array_
class int_Clo_Array
{
	private:
		int *p;
		int Length;
		
	public:
		int_Clo_Array(int);
		int operator[](int);
};

int_Clo_Array::int_Clo_Array(int length){
	p=new int[length];
	Length=length;
}

int int_Clo_Array::operator[](int SUBSCRIPT){
	return p[SUBSCRIPT-1];
}

template<class Arr>
class Clo_Array
{
	private:
		Arr *p;
		int Length;
		
	public:
		Clo_Array(int);
		Arr operator[](int);
};
template<class Arr>
Clo_Array<Arr>::Clo_Array(int length){
	p=new Arr[length];
	Length=length;
}
template<class Arr>
Arr Clo_Array<Arr>::operator[](int Subscript){
	return p[Subscript-1];
}

#ifndef int_Clo_Matrix_
#define int_Clo_Matrix_
#define DISPLAYMETHOD int
#define METHOD_ROW 0
#define METHOD_COLUMN 1
/**/
class int_Clo_Matrix
{
	/*按行存储*/
	private:
		int *p;//head
		int row;//行数
		int column;//列数
	
	public:
		int_Clo_Matrix(int,int);
		int display(DISPLAYMETHOD);
		int* operator[](int);
		
};

int_Clo_Matrix::int_Clo_Matrix(int Row,int Column){
	p=new int[Row*Column];
	row=Row;
	column=Column;
}

int int_Clo_Matrix::display(DISPLAYMETHOD METHOD=METHOD_ROW){
	switch(METHOD){
		case METHOD_ROW:{
			for(int r=0;r<row;++r){
				for(int c=0;c<column;++c){
					std::cout<<p[r*column+c]<<' ';
				}
				std::cout<<'\n';
			}
			std::cout<<std::endl;
			break;
		}
	}
	return 0;
}

int* int_Clo_Matrix::operator[](int SUBN){
	return &p[column*(SUBN-1)-1];
}

#endif/*INT_CMatrix*/
#define Clo_Matrix_
#define TYPEROW 0
#define TYPECOLUMN 1
#define METHOD_NUM 0
#define METHOD_NEURLIST 1
#define ADD_ROW 0
#define ADD_COLUMN 1
template<class T>
class Clo_Matrix
{
	/*按行存储*/
	private:
		T *p;//head
		int row;//行数
		int column;//列数
	
	protected:
		int getRC(int=TYPEROW);
		int setp(T*);
		int setp(T*,int);//not recommand
		int setp(T*,int,int);
	public:
		Clo_Matrix(int=1);//0向量（列）
		Clo_Matrix(int,int);//0矩阵
		Clo_Matrix(T* H,int);//创建列向量
		Clo_Matrix(T* H,int,int);
		Clo_Matrix(Clo_Matrix&);
		~Clo_Matrix();
		void deletep();
		int renewp(int,int*);
		int display(DISPLAYMETHOD=METHOD_ROW);
		int Rotate(double,int,int);//rotate旋转
		Clo_Matrix transpos();//transposition转置
		T*& getp();
		Clo_Matrix<T> addRC(int=1,T=0,int=ADD_ROW);//only support <int><unsigned><float><double><etc.>
		Clo_Matrix<T> Activate(T ACTF(T));
		int max_id();
		int Clo_softmax();
		T*& operator[](int);
		Clo_Matrix<T> operator+(Clo_Matrix<T>&);
		Clo_Matrix<T> operator*(Clo_Matrix<T>&);
		//friend Clo_Matrix<float> operator*(Clo_Matrix<T>&, Clo_Matrix<T>&);
		int operator=(const Clo_Matrix<T>&);
};
//
//
template<class T>
Clo_Matrix<T>::Clo_Matrix(Clo_Matrix &M) {
	int mlen = M.row*M.column;
	row = M.row;
	column = M.column;
	p = new T[mlen];
	for (int i = 0; i < mlen; ++i) {
		p[i] = M.p[i];
	}
}
template<class T>
void Clo_Matrix<T>::deletep() {
	delete[] p;
}
template<class T>
Clo_Matrix<T>::~Clo_Matrix() {
	delete[] p;
}
template<class T>
Clo_Matrix<T>::Clo_Matrix(int Row){
	p=new T[Row];
	row=Row;
	column=1;
}
template<class T>
int Clo_Matrix<T>::renewp(int METHOD,int* m){
	switch(METHOD){
		case METHOD_NUM:{
			for(int i=0;i<row;++i){
				p[i]=0;
			}
			break;
		}
		case METHOD_NEURLIST:{
			int len=m[0];
			for(int i=0;i<row;++i){
				p[i]=T(len);
			}
			break;
		}
		default:{
			break;
		}
	}
	return 0;
}
template<class T>
Clo_Matrix<T>::Clo_Matrix(int Row,int Column){
	p=new T[Row*Column];
	for(int i=0;i<Row*Column;++i){
		p[i]=0;
	}
	row=Row;
	column=Column;
}
template<class T>
Clo_Matrix<T>::Clo_Matrix(T *H,int Length){
	p=new T[Length];
	memcpy(p, H, Length * sizeof(T));
	//delete[] H;
	row=Length;
	column=1;
}
template<class T>
Clo_Matrix<T>::Clo_Matrix(T *H,int Row,int Column){
	int Length = Row*Column;
	p = new T[Length];
	memcpy(p, H, Length * sizeof(T));
	//delete[] H;
	row=Row;
	column=Column;
}
template<class T>
int Clo_Matrix<T>::display(DISPLAYMETHOD METHOD){
	switch(METHOD){
		case METHOD_ROW:{
			for(int r=0;r<row;++r){
				for(int c=0;c<column;++c){
					std::cout<<p[r*column+c]<<' ';
				}
				std::cout<<'\n';
			}
			std::cout<<std::endl;
			break;
		}
		case METHOD_COLUMN: {
			for (int c = 0; c<column; ++c) {
				for (int r = 0; r<row; ++r) {
					std::cout << p[r*column + c] << ' ';
				}
				std::cout << '\n';
			}
			std::cout << std::endl;
			break;
		}
	}
	return 0;
}
template<class T>
int Clo_Matrix<T>::Rotate(double theta,int i,int j){
	if(row==column&&i!=j){
		Clo_Matrix<T> M1=Clo_Matrix(row,column);
		for(int ii=1;ii<=row;++ii)M1[ii][ii]=1;
		double SIN=Clo_sin(theta);
		double COS=Clo_cos(theta);
		M1[i][i]=M1[j][j]=COS;
		if(i>j){
			M1[i][j]=-SIN;
			M1[j][i]=SIN;
		}else{
			M1[i][j]=SIN;
			M1[j][i]=-SIN;
		}
		p=(M1*Clo_Matrix(p,row,column)).getp();
		return 0;
	}
	else{
		return 1;
	}
}
template<class T>
Clo_Matrix<T> Clo_Matrix<T>::transpos(){
	T *q=new T[row*column];
	for(int i1=0,temp=0;i1<column;++i1)
	for(int i2=0;i2<row;++i2){
		q[temp++]=p[i2*column+i1];
	}
	return Clo_Matrix(q,column,row);
}
template<class T>
T*& Clo_Matrix<T>::getp(){
	return p;
}
template<class T>
Clo_Matrix<T> Clo_Matrix<T>::addRC(int num, T tp, int METHOD){
	int temp,t1=row,t2=column;
	T* h;
	if(!METHOD){
		t1 += num;
	}
	else{
		t2 += num;
	}
	temp = t1*t2;
	h=new T[temp];
	int sum=column*row;
	for(int i=0;i<sum;++i)h[i]=p[i];
	for(int i=sum;i<temp;++i)h[i]=tp;
	Clo_Matrix<T> P(h, t1, t2);
	Clo_Matrix<T> tempm;
	tempm = P;
	delete[] h;
	return tempm;
	//return Clo_Matrix(h, t1, t2);
}
template<class T>
Clo_Matrix<T> Clo_Matrix<T>::Activate(T ACTF(T)) {
	int temp = row*column;
	T *q = new T[temp];
	for (int i = 0; i < temp; ++i) {
		q[i] = ACTF(p[i]);
	}
	Clo_Matrix<T> P(q, row, column);
	Clo_Matrix<T> tempm;
	tempm = P;
	delete[] q;
	return tempm;
	//return Clo_Matrix(q, row, column);
}
template<class T>
int Clo_Matrix<T>::max_id() {
	int temp = row*column;
	int r = 0;
	for (int i = 1; i < temp; ++i) {
		if (p[i] > p[r])r = i;
	}
	return r;
}
template<class T>
int Clo_Matrix<T>::Clo_softmax() {
	int temp = row*column;
	float temp1=0;
	int r = 0;
	for (int i = 0; i < temp; ++i) {
		temp1 += p[i];
	}
	if (temp1 == 0)temp1 = 1;
	for (int i = 0; i < temp; ++i) {
		p[i] = p[i] / temp1;
	}
	return 0;
}
template<class T>
T*& Clo_Matrix<T>::operator[](int Subscript){
	return &p[column*(Subscript-1)-1];
}
template<class T>
int Clo_Matrix<T>::operator=(const Clo_Matrix<T> &M) {
	delete[] p;
	p = NULL;
	int mlen = M.row*M.column;
	row = M.row;
	column = M.column;
	p = new T[mlen];
	for (int i = 0; i < mlen; ++i) {
		p[i] = M.p[i];
	}
	return 0;
}
template<class T>
Clo_Matrix<T> Clo_Matrix<T>::operator+(Clo_Matrix<T> &M){
	if(row==M.row&&column==M.column){
	for(int i=0;i<row*column;++i)
			p[i]+=M.p[i];
		}
	return Clo_Matrix(p,row,column);
}
/*
template<class T>
Clo_Matrix<T> Clo_Matrix<T>::operator*(Clo_Matrix<T> &M){
	if(column==M.row){
		T *p1=new T[row*M.column];
		int i = 0;
		for(int i1=0;i1<row;++i1)
			for(int i2=0;i2<M.column;++i2,++i){
				p1[i]=0;
				for(int i3=0;i3<column;++i3)//column==M.row
				{
					p1[i]+=p[i1*column+i3]*M.p[i3*M.column+i2];
				}
			}
			return Clo_Matrix<T>(p1,row,M.column);
		}
	else{
		return Clo_Matrix<T>(p,row,column);
	}
}
*/
template<class T>
Clo_Matrix<T> Clo_Matrix<T>::operator*(Clo_Matrix<T> &M) {
	if (column == M.row) {
		T *p1 = new T[row*M.column];
		
		int i = 0;
		for (int i1 = 0; i1<row; ++i1)
			for (int i2 = 0; i2<M.column; ++i2, ++i) {
				p1[i] = 0;
				for (int i3 = 0; i3<column; ++i3)//column==M.row
				{
					p1[i] += p[i1*column + i3] * M.p[i3*M.column + i2];
				}
			}
		Clo_Matrix<T> P(p1, row, M.column);
		Clo_Matrix<T> temp;
		temp = P;
		delete[] p1;
		return temp;
	}
	else {
		return Clo_Matrix<T>(p, row, column);
	}
}
template<class T>
int Clo_Matrix<T>::getRC(int TYPE){
	switch(TYPE){
		case TYPEROW:{
			return row;
			break;//~
		}
		case TYPECOLUMN:{
			return column;
			break;//~
		}
		default:{
			return -1;
			break;//~
		}
	}
}
template<class T>
int Clo_Matrix<T>::setp(T *h) {
	int len = row*column;
	delete[] p;
	p = new T[len];
	memcpy(p, h, len * sizeof(T));
	return 0;
}
template<class T>
int Clo_Matrix<T>::setp(T *h, int len){
	delete[] p;
	p = new T[len];
	memcpy(p, h, len * sizeof(T));
	return 0;
}
template<class T>
int Clo_Matrix<T>::setp(T *h, int Row, int Column) {
	column = Column;
	row = Row;
	int len = row*column;
	delete[] p;
	p = new T[len];
	memcpy(p, h, len * sizeof(T));
	return 0;
}
#undef DISPLAYMETHOD
//#undef METHOD_ROW
//#undef METHOD_COLUMN

#endif/*CloverMatrix*/
