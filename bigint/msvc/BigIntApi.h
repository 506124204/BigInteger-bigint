#pragma once
#include <string>



#ifdef EXT_LIBBIGINT

#define API_LIBBIGINT_EXT __declspec(dllexport) 

#else
#define API_LIBBIGINT_EXT __declspec(dllimport) 

#endif

typedef void*  BigIntObj;


API_LIBBIGINT_EXT BigIntObj bigint_createInstance(long initVal);
API_LIBBIGINT_EXT void bigint_deleteInstance(const BigIntObj p);

API_LIBBIGINT_EXT void bigint_setInt(BigIntObj& ret,long val);

/*
left < right: -1
left = right: 0
left > right: 1
*/
API_LIBBIGINT_EXT int bigint_compare(const BigIntObj& left, const BigIntObj& right);

/*
 opt: +, -, *, /, %
 */
API_LIBBIGINT_EXT bool bigint_math(BigIntObj& ret, const BigIntObj& left, const BigIntObj& right, char opt);
API_LIBBIGINT_EXT bool bigint_math2(BigIntObj& ret, const BigIntObj& left, long right, char opt);
API_LIBBIGINT_EXT bool bigint_math3(BigIntObj& ret, const BigIntObj& left, const char * pStr, char opt);
API_LIBBIGINT_EXT bool bigint_math4(BigIntObj& ret, const BigIntObj& left, unsigned long right, char opt);
API_LIBBIGINT_EXT void bigint_pow(BigIntObj& ret, const BigIntObj& left, int base, int exponent);
API_LIBBIGINT_EXT void bigint_from_bigInt(BigIntObj& ret, const BigIntObj& src);
API_LIBBIGINT_EXT void bigint_from_long(BigIntObj& ret, long n);
API_LIBBIGINT_EXT void bigint_from_ulong(BigIntObj& ret, unsigned long n);
API_LIBBIGINT_EXT void bigint_from_int(BigIntObj& ret, int n);
API_LIBBIGINT_EXT void bigint_from_uint(BigIntObj& ret, unsigned int n);
API_LIBBIGINT_EXT long bigint_to_long(const BigIntObj& n);
API_LIBBIGINT_EXT unsigned long bigint_to_ulong(const BigIntObj& n);
API_LIBBIGINT_EXT void bigint_bigIntegerToString(const BigIntObj& pBigInt, char * pszBuff, int& lenBuff);
API_LIBBIGINT_EXT void bigint_stringToBigInteger(BigIntObj& ret, const char * pStr);

class BigInt
{
protected:
private:
	BigIntObj pInt;
public:
	BigInt(){
		pInt = bigint_createInstance(0);
	}
	  
	BigInt(const BigInt& bigInt){
		pInt = bigint_createInstance(0);
		bigint_from_bigInt(pInt, bigInt.pInt);
	}

	BigInt(int n){
		pInt = bigint_createInstance(0);
		bigint_from_int(pInt, n);
	}

	BigInt(long n){
		pInt = bigint_createInstance(0);
		bigint_from_long(pInt, n);
	}

	BigInt(unsigned int n){
		pInt = bigint_createInstance(0);
		bigint_from_uint(pInt, n);
	}

	BigInt(unsigned long n){
		pInt = bigint_createInstance(0);
		bigint_from_ulong(pInt, n);
	}

	BigInt(const std::string& str){
		pInt = bigint_createInstance(0);
		bigint_stringToBigInteger(pInt, str.c_str());
	}

	
	~BigInt(){
		bigint_deleteInstance(pInt);
	}

public:
	std::string toString(){
		char * p = NULL;
		int len = 0;
		bigint_bigIntegerToString(pInt, p, len);
		p = (char *)calloc(len+8,sizeof(char));
		bigint_bigIntegerToString(pInt, p, len);
		std::string str(p);
		free(p);
		return str;
	}

	unsigned long toULong(){
		if(*this < ULONG_MAX)
			return bigint_to_ulong(pInt);
		return ULONG_MAX;
	}

	unsigned long toLong(){
		if(*this < ULONG_MAX)
			return bigint_to_long(pInt);
		return ULONG_MAX;
	}

	
	BigInt fromString(const std::string & str){
	     bigint_stringToBigInteger(pInt, str.c_str());
		 return *this;
	}

	static BigInt pow(const BigInt& src, int base,int Exponent){
		BigInt bi;
		bigint_pow(bi.pInt, src.pInt, base, Exponent);
		return bi;
	}
	 
	static BigInt pow(const long& src, int base,int Exponent){
		BigInt bi;
		bigint_pow(bi.pInt, BigInt(src).pInt, base, Exponent);
		return bi;
	}
public:
	void operator ++(   ){
		bigint_math2(pInt, this->pInt, 1, '+');
	}
	void operator ++(int){
		bigint_math2(pInt, pInt, 1, '+');
	}
	void operator --(   ){
		bigint_math2(pInt, pInt, 1, '-');
	}
	void operator --(int){
		bigint_math2(pInt, pInt, 1, '-');
	}
	//////////////////////////////////////////////////////////////////////////
	BigInt operator +(const BigInt &x){
		BigInt bi;
		bigint_math(bi.pInt, this->pInt, x.pInt, '+');
		return bi;
	}

	BigInt operator -(const BigInt &x){
		BigInt bi;
		bigint_math(bi.pInt, this->pInt, x.pInt, '-');
		return bi;
	}
	
	BigInt operator *(const BigInt &x){
		BigInt bi;
		bigint_math(bi.pInt, this->pInt, x.pInt, '*');
		return bi;
	}

	BigInt operator /(const BigInt &x){
		BigInt bi;
		bigint_math(bi.pInt, this->pInt, x.pInt, '/');
		return bi;
	}

	BigInt operator %(const BigInt &x){
		BigInt bi;
		bigint_math(bi.pInt, this->pInt, x.pInt, '%');
		return bi;
	}

	BigInt operator =(const BigInt &x){
		bigint_from_bigInt(pInt, x.pInt);
		return *this;
	}	 
	
	BigInt operator +=(const BigInt &x){
		BigInt bi;
		bigint_math(bi.pInt, this->pInt, x.pInt, '+');
		bigint_from_bigInt(pInt, bi.pInt);
		return *this;
	}	 

	
	BigInt operator -=(const BigInt &x){
		BigInt bi;
		bigint_math(bi.pInt, this->pInt, x.pInt, '-');
		bigint_from_bigInt(pInt, bi.pInt);
		return *this;
	}	 

	BigInt operator *=(const BigInt &x){
		BigInt bi;
		bigint_math(bi.pInt, this->pInt, x.pInt, '*');
		bigint_from_bigInt(pInt, bi.pInt);
		return *this;
	}	 
	
	
	BigInt operator /=(const BigInt &x){
		BigInt bi;
		bigint_math(bi.pInt, this->pInt, x.pInt, '/');
		bigint_from_bigInt(pInt, bi.pInt);
		return *this;
	}	 

	bool operator !=(const BigInt &x){
		return bigint_compare(this->pInt, x.pInt)? true : false;
	}	 

	//////////////////////////////////////////////////////////////////////////
	BigInt operator +(const long &x){
		BigInt bi;
		bigint_math2(bi.pInt, this->pInt, x, '+');
		return bi;
	}

	BigInt operator -(const long &x){
		BigInt bi;
		bigint_math2(bi.pInt, this->pInt, x, '-');
		return bi;
	}

	BigInt operator *(const long &x){
		BigInt bi;
		bigint_math2(bi.pInt, this->pInt, x, '*');
		return bi;
	}

	BigInt operator /(const long &x){
		BigInt bi;
		bigint_math2(bi.pInt, this->pInt, x, '/');
		return bi;
	}

	BigInt operator %(const long &x){
		BigInt bi;
		bigint_math2(bi.pInt, this->pInt, x, '%');
		return bi;
	}
//
	BigInt operator +(const unsigned long &x){
		BigInt bi;
		bigint_math4(bi.pInt, this->pInt, x, '+');
		return bi;
	}
	
	BigInt operator -(const unsigned long &x){
		BigInt bi;
		bigint_math4(bi.pInt, this->pInt, x, '-');
		return bi;
	}
	
	BigInt operator *(const unsigned long &x){
		BigInt bi;
		bigint_math4(bi.pInt, this->pInt, x, '*');
		return bi;
	}
	
	BigInt operator /(const unsigned long &x){
		BigInt bi;
		bigint_math4(bi.pInt, this->pInt, x, '/');
		return bi;
	}
	
	BigInt operator %(const unsigned long &x){
		BigInt bi;
		bigint_math4(bi.pInt, this->pInt, x, '%');
		return bi;
	}
	//

	BigInt operator +(const int &x){
		BigInt bi;
		bigint_math2(bi.pInt, this->pInt, x, '+');
		return bi;
	}
	
	BigInt operator -(const int &x){
		BigInt bi;
		bigint_math2(bi.pInt, this->pInt, x, '-');
		return bi;
	}
	
	BigInt operator *(const int &x){
		BigInt bi;
		bigint_math2(bi.pInt, this->pInt, x, '*');
		return bi;
	}
	
	BigInt operator /(const int &x){
		BigInt bi;
		bigint_math2(bi.pInt, this->pInt, x, '/');
		return bi;
	}
	
	BigInt operator %(const int &x){
		BigInt bi;
		bigint_math2(bi.pInt, this->pInt, x, '%');
		return bi;
	}
	//

	BigInt operator =(const long &x){
		bigint_from_long(pInt, x);
		return *this;
	}

	BigInt operator =(const unsigned long &x){
		bigint_from_ulong(pInt, x);
		return *this;
	}
	BigInt operator =(const int &x){
		bigint_from_int(pInt, x);
		return *this;
	}
	BigInt operator =(const unsigned int &x){
		bigint_from_uint(pInt, x);
		return *this;
	}
 
	//////////////////////////////////////////////////////////////////////////

	bool operator ==(const BigInt &x){
		return bigint_compare(this->pInt, x.pInt)==0 ? true : false;
	}
	bool operator >(const BigInt &x){
		return bigint_compare(this->pInt, x.pInt)>0 ? true : false;
	}

	bool operator <(const BigInt &x){
		return bigint_compare(this->pInt, x.pInt)<0 ? true : false;
	}

	bool operator >=(const BigInt &x){
		return bigint_compare(this->pInt, x.pInt)>=0 ? true : false;
	}

	bool operator <=(const BigInt &x){
		return bigint_compare(this->pInt, x.pInt)<=0 ? true : false;
	}

	//////////////////////////////////////////////////////////////////////////
	bool operator ==(const int &x){
		BigInt bi(x);
		return bigint_compare(this->pInt, bi.pInt)==0 ? true : false;
	}
	bool operator >(const int &x){
		BigInt bi(x);
		return bigint_compare(this->pInt, bi.pInt)>0 ? true : false;
	}

	bool operator <(const int &x){
		BigInt bi(x);
		return bigint_compare(this->pInt, bi.pInt)<0 ? true : false;
	}

	bool operator >=(const int &x){
		BigInt bi(x);
		return bigint_compare(this->pInt, bi.pInt)>=0 ? true : false;
	}

	bool operator <=(const int &x){
		BigInt bi(x);
		return bigint_compare(this->pInt, bi.pInt)<=0 ? true : false;
	}

	bool operator !=(const int &x){
		BigInt bi(x);
		return bigint_compare(this->pInt, bi.pInt)!=0 ? true : false;
	}


	//////////////////////////////////////////////////////////////////////////
	bool operator ==(const unsigned int &x){
		BigInt bi(x);
		return bigint_compare(this->pInt, bi.pInt)==0 ? true : false;
	}
	bool operator >(const unsigned int &x){
		BigInt bi(x);
		return bigint_compare(this->pInt, bi.pInt)>0 ? true : false;
	}

	bool operator <(const unsigned int &x){
		BigInt bi(x);
		return bigint_compare(this->pInt, bi.pInt)<0 ? true : false;
	}

	bool operator >=(const unsigned int &x){
		BigInt bi(x);
		return bigint_compare(this->pInt, bi.pInt)>=0 ? true : false;
	}

	bool operator <=(const unsigned int &x){
		BigInt bi(x);
		return bigint_compare(this->pInt, bi.pInt)<=0 ? true : false;
	}

	bool operator !=(const unsigned int &x){
		BigInt bi(x);
		return bigint_compare(this->pInt, bi.pInt)!=0 ? true : false;
	}
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	bool operator ==(const long &x){
		BigInt bi(x);
		return bigint_compare(this->pInt, bi.pInt)==0 ? true : false;
	}
	bool operator >(const long &x){
		BigInt bi(x);
		return bigint_compare(this->pInt, bi.pInt)>0 ? true : false;
	}

	bool operator <(const long &x){
		BigInt bi(x);
		return bigint_compare(this->pInt, bi.pInt)<0 ? true : false;
	}

	bool operator >=(const long &x){
		BigInt bi(x);
		return bigint_compare(this->pInt, bi.pInt)>=0 ? true : false;
	}

	bool operator <=(const long &x){
		BigInt bi(x);
		return bigint_compare(this->pInt, bi.pInt)<=0 ? true : false;
	}

	bool operator !=(const long &x){
		BigInt bi(x);
		return bigint_compare(this->pInt, bi.pInt)!=0 ? true : false;
	}
	//////////////////////////////////////////////////////////////////////////
	bool operator ==(const unsigned long &x){
		BigInt bi(x);
		return bigint_compare(this->pInt, bi.pInt)==0 ? true : false;
	}
	bool operator >(const unsigned long &x){
		BigInt bi(x);
		return bigint_compare(this->pInt, bi.pInt)>0 ? true : false;
	}

	bool operator <(const unsigned long &x){
		BigInt bi(x);
		return bigint_compare(this->pInt, bi.pInt)<0 ? true : false;
	}

	bool operator >=(const unsigned long &x){
		BigInt bi(x);
		return bigint_compare(this->pInt, bi.pInt)>=0 ? true : false;
	}

	bool operator <=(const unsigned long &x){
		BigInt bi(x);
		return bigint_compare(this->pInt, bi.pInt)<=0 ? true : false;
	}


	bool operator !=(const unsigned long &x){
		BigInt bi(x);
		return bigint_compare(this->pInt, bi.pInt)!=0 ? true : false;
	}
};