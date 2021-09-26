#ifndef Clo_Math_H_
#define Clo_Math_H_

#ifndef Clo_PI
#define Clo_PI 3.1415926535897932384626433832795
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

#ifndef uint
#define uint unsigned int
#endif

#define BBSFlag_last 1
#define BBSFlag_odd 2
#define BBSFlag_even 3
const unsigned int PFORUINT = 4294967295;
static unsigned int RAND_X = 1;
static unsigned int BBSNext = 101355;

int UintOdd() {
	int k = 0;
	unsigned int temp = BBSNext;
	while (temp) {
		temp/=2;
		if(temp&0x00000001)k=1-k;
	}
	return k;
}

uint BBSRandFunction(int f) {
	BBSNext = BBSNext*BBSNext % 192649;//383 * 503
	switch (f) {
		case BBSFlag_last: {
			return BBSNext&0x00000001;
			break;
		}
		case BBSFlag_odd: {
			return UintOdd();
			break;
		}
		case BBSFlag_even: {
			return 1-UintOdd();//!UintOdd();
			break;
		}
		default : return BBSNext&0x00000001;
	}
}

void SETSEED(unsigned int L) {
	RAND_X = L*16807 % PFORUINT;
}

uint Rand_ALL()
{
	RAND_X = RAND_X*RAND_X % PFORUINT;
	return RAND_X;
}

int RandInt(int i, int j) {
	return (int)(Rand_ALL()*(j - i + 1) + i);
}

void blank() {
	printf("\n");
}

int randInt(int i, int j) {
	return (int)(rand()%(j - i + 1) + i);
}
template<class T>
T Clo_MAX(T a,T b){
	return a>b?a:b;
}
template<class T>
T Clo_MIN(T a,T b){
	return a>b?b:a;
}
template<class T>
T Clo_ABS(T x){
	return x>0?x:0-x;
}

unsigned int factorial(int n){
	unsigned int temp=1;
	for(int i=1;i<=n;++i){
		temp*=i;
	}
	return temp;
}

double Clo_sin(double x,int n=115){
	while(x>=Clo_PI){
		x-=2*Clo_PI;
	}
	while(x<=Clo_PI){
		x+=2*Clo_PI;
	}
	double temp=1,ans=0;
	for(int i=1,sw=1;i<=n;++i,++sw){
		temp*=x/i;
		if(sw==1){
			ans+=temp;
			sw=-3;
		}else if(sw==-1){
			ans-=temp;
		}
	}
	return ans;
}

double Clo_cos(double x,int n=115){
	x=Clo_PI/2-x;
	while(x>=Clo_PI){
		x-=2*Clo_PI;
	}
	while(x<=Clo_PI){
		x+=2*Clo_PI;
	}
	double temp=1,ans=0;
	for(int i=1,sw=1;i<=n;++i,++sw){
		temp*=x/i;
		if(sw==1){
			ans+=temp;
			sw=-3;
		}else if(sw==-1){
			ans-=temp;
		}
	}
	return ans;
}

int ChartoInt(char c){
	if(c>'9')return -1;
	else return c-'0';
}

char InttoChar(int _int){
	if(_int>9||_int<0)return -1;
	else return _int+'0';
}

int C_Ceil(int Ua,int Ub){
	return (Ua+Ub-1)/Ub;
}

uint C_Ceil(uint Ua,uint Ub){
	return (Ua+Ub-1)/Ub;
}

int longerfinger(int a,int b){
	/*not meaningful in fuct*/
	return a>b?1:0;
}

int longerfingeru(unsigned int a,unsigned int b){
	return a>b?1:0;
}

unsigned int C_EXP10(unsigned int x){
	/* x > 0 & x < 10*/
	if(x>0)return 10*C_EXP10(x-1);
	else return 1;
}

unsigned int C_strlen(char * a){
	unsigned int k=0;
	while(a[k]!='\0'){
		++k;
	}
	return k;
}

unsigned int C_strlen(const char * a){//untested
	unsigned int k=0;
	while(*(a+k)!='\0'){
		++k;
	}
	return k;
}


//InvSqrt && CarmSqrt have not been fully tested by myself yet.
//BTW it's not accurate; it's nearly number. However, it's fast.

float InvSqrt(float x){
	//Alg by Carmack in QUAKE3
	float xhalf=0.5f*x;
	int i=(int)x;
	//MagicNumber
	i= 0x5f3759df -(i>>1);
	x=(float)i;
	//Newton-Raphson Method
	x=x*(1.5f-xhalf*x*x);
	return x;
}

float CarmSqrt(float x){
	//by Carmack in QUAKE3
	union{
		int intPart;
		float floatPart;
	} convertor;
	union{
		int intPart;
		float floatPart;
	} convertor2;
	convertor.floatPart = x;
	convertor2.floatPart = x;
	convertor.intPart = 0x1FBCF800 + (convertor.intPart >> 1);
	convertor2.intPart = 0x5f3759df - (convertor2.intPart >> 1);
	return 0.5f*(convertor.floatPart + (x * convertor2.floatPart));
}

/*
//Here defined a struct to save the result of (uint*uint).
*/

int C_UintDigitsBinary(uint x) {
	int i = 0;
	while (x) {
		x >>= 1;
		++i;
	}
	return i;
}

class LongUint
{
public:
	uint A[2];
	LongUint();
	LongUint(uint, uint);
	uint operator%(uint);
};

LongUint::LongUint() {

}

LongUint::LongUint(uint n1, uint n2) {
	/*
	this part of code is an copy of the function( UintMultiBinary) in LongClass.h
	*/
	uint N1[2], N2[2];
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
}

uint LongUint::operator%(uint m) {
	/*
	this part of code is an copy of the function( UintMultiBinary) in LongClass.h
	*/
	/*Calculate the modulus*/
	int i = C_UintDigitsBinary(A[0]);
	uint temp = 0, temp1 = 0;
	int temp2 = 0;
	while (i>0) {
		temp1 = (A[0] << (30 - i)) + (A[1] >> i);
		temp2 = temp1 - m;//note
		if (temp2 >= 0) {
			temp += 1 << i;
			temp1 = temp2;
			A[0] = temp1 >> (30 - i);
			A[1] = (A[1] << (32 - i) >> (32 - i)) + (temp1 << (2 + i) >> 2);
			i = C_UintDigitsBinary(A[0]);
		}
		else {
			/*this should not be occur twice in the row*/
			--i;
		}
	}
	//i==0
	temp1 = (A[0] << 30) + A[1];
	temp2 = temp1 - m;//note
	if (temp2 >= 0) {
		temp += 1;
		A[1] = temp2;
	}
	//end of i==0
	A[0] = temp;

	return A[1]%m;
}

//Miller-Rabin Test
//if n < 2,047, it is enough to test a = 2
//if n < 4,759,123,141, it is enough to test a = 2, 7, and 61

int MillerRabinTest(uint a, uint q, uint k, uint p) {
	//p=n
	//p-1=2^k*q
	uint temp=a;
	uint pm = p - 1;
	for (uint i = 1; i < q; ++i)temp = LongUint(temp, a) % p;//q-1 times, as temp==a at first.
	if (temp == 1)return 1;//uncertain
	for (uint i = 1; i < k&&temp != pm; ++i)temp = LongUint(temp, temp) % p;//k-1 times
	return temp == pm ? 1 : 0;
}

int MR_is_prime(uint n) {
	//return 1 when n is prime
	//return 0 when n is not prime
	uint i = 1;
	if ((n & 0x00000001) == 0)return n==2?1:0;//even. not prime, of cause.(except 2)
	uint N = n >> 1;
	while ((N & 0x00000001) == 0) {
		N >>= 1;
		++i;
	}
	if (N < 2047)return MillerRabinTest(2, N, i, n);
	else {
		if (MillerRabinTest(2, N, i, n)) {
			if (MillerRabinTest(7, N, i, n)) {
				return MillerRabinTest(61, N, i, n);
			}
		}
		return 0;
	}
}

uint gcd(uint a, uint b) {
	/*greatest common divisor*/
	/*Euclid*/
	if (a&&b) {
		if (b%a == b)return a%b ? gcd(b, a%b) : b;
		else return b%a ? gcd(a, b%a) : a;
	}
	else return 0;
}

int* Euclidgcd(uint a, uint b) {
	/*xa+yb=gcd(a,b)*/
	int *A;
	int x, y;
	if (a&&b) {
		if (b%a == b) {
			//a > b
			A = Euclidgcd(b, a%b);
			//unfinished
			x = A[0];
			y = A[1];
			A[0] = y;
			A[1] = x - y*(int)(a / b);
			return A;
		}
		else {
			//a <= b
			A = Euclidgcd(a, b%a);
			x = A[0];
			y = A[1];
			A[0] = y;
			A[1] = x - y*(int)(b / a);
			return A;
		}
	}
	else {
		int *A0 = new int[2];//delete later
		A0[0] = 1;
		A0[1] = 0;
		return A0;
	}
}

uint lcm(uint a, uint b) {
	/*lowest common multiple*/
	return a*b / gcd(a, b);
}

uint CombinNumber(uint m, uint n){
	//untested
	/*  /  m  \
		|     |
		\  n  /
	*/
	uint a=1;
	for(uint i=0;i<m;++i)a*=n-i;
	return a/factorial(m);
}

int LucasTheorem(uint m, uint n, uint p){
	//untested
	/*  /  m  \
		|     | mod p (p is prime)
		\  n  /
	*/
	if(MR_is_prime(p)){
		if(m<p&&n<p){
			/*m%p==m && n%p==n*/
			return (int)CombinNumber(m,n);
		}
		else {
			return LucasTheorem(m/p,n/p,p)+(int)CombinNumber(m%p,n%p);
		}
	}
	else return -1;//error_p_is_not_prime
}

unsigned int ModExp(unsigned int a, unsigned int e, unsigned int m){
    unsigned int temp = 0;
    if( m == 0 ) return 0;
    if( e == 0 ) return 1;
    else if ( e == 1) return a%m;
    else if ( e % 2 ){
        temp = ModExp(a, e>>1, m);
        temp = (unsigned long long)temp*temp % m;
        return (unsigned long long)temp*a % m;
    }
    else {
        //e%2 == 0
        temp = ModExp(a, e/2 , m);
        return (unsigned long long)temp*temp % m;
    }
}

int PrimeTest(int a){
    int *table;
    int tempindex = (int)sqrt(a) + 1;
    table = new int[tempindex];
    if( a < 2 ) return 0;
    //int table
    for( int i = 2; i < tempindex; ++i) table[i] = 1;
    //end int
    for( int i = 2; i < tempindex; ++i){
        if( table[i] == 1){
            if( a%i == 0 ) return 0;//a is not prime.
            for( int i1 = 2; i1*i <tempindex; ++i1){
                table[i*i1] == 0;
            }
        }//end if
    }
    return 1;//a is prime.
}
#endif /*Clo_PI*/
#endif /*Clo_Math_H_*/
