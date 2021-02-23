#include "StdAfx.h"
#include "BigIntApi.h"
#include "BigIntegerLibrary.hh"





API_LIBBIGINT_EXT  BigIntObj bigint_createInstance(long initVal) {
	BigInteger * p = new BigInteger();
	*p = initVal;
	return p;
}
 
API_LIBBIGINT_EXT  void bigint_deleteInstance(const BigIntObj  p) {
	 delete (BigInteger*)p;
}

API_LIBBIGINT_EXT void bigint_setInt(BigIntObj& ret,long val)
{
	(*((BigInteger*)ret)) = BigInteger(val);
}

API_LIBBIGINT_EXT  int bigint_compare(const BigIntObj& left, const BigIntObj& right) {
	BigInteger v = (*((BigInteger*)left)) > (*((BigInteger*)right));
	if( (*((BigInteger*)left)) > (*((BigInteger*)right)) ){
		return 1;
	} else if( (*((BigInteger*)left)) == (*((BigInteger*)right)) ){
		return 0;
	}
	return -1;
}

API_LIBBIGINT_EXT  bool bigint_math(BigIntObj& ret, const BigIntObj& left, const BigIntObj& right, char opt) {
	switch (opt)
	{
	case '+':
		(*((BigInteger*)ret)) = (*((BigInteger*)left)) + (*((BigInteger*)right));
		break;
	case '-':
		(*((BigInteger*)ret)) = (*((BigInteger*)left)) - (*((BigInteger*)right));
		break;
	case '*':
		(*((BigInteger*)ret)) = (*((BigInteger*)left)) * (*((BigInteger*)right));
		break;
	case '/':
		(*((BigInteger*)ret)) = (*((BigInteger*)left)) / (*((BigInteger*)right));
		break;
	case '%':
		(*((BigInteger*)ret)) = (*((BigInteger*)left)) % (*((BigInteger*)right));
		break;
	default:
		return false;
		break;
	}
	return true;
}

API_LIBBIGINT_EXT bool bigint_math2(BigIntObj& ret, const BigIntObj& left, long right, char opt)
{
	BigInteger b(right);
	return bigint_math(ret, left, &b , opt);
}

API_LIBBIGINT_EXT bool bigint_math3(BigIntObj& ret, const BigIntObj& left, const char * pStr, char opt)
{ 
	BigInteger b = stringToBigInteger(pStr);
	return bigint_math(ret, left, &b , opt);
}

API_LIBBIGINT_EXT bool bigint_math4(BigIntObj& ret, const BigIntObj& left, unsigned long right, char opt)
{
	BigInteger b(right);
	return bigint_math(ret, left, &b , opt);
}

API_LIBBIGINT_EXT void bigint_pow(BigIntObj& ret, const BigIntObj& left, int base, int exponent)
{
	BigInteger src = (*((BigInteger*)left));
	for (int i=0; i<abs(exponent); i++) {
		if(exponent < 0) {
			src /= base;
		} else { 
			src *= base;
		}
	} 
	(*((BigInteger*)ret)) = src;
}

API_LIBBIGINT_EXT  void bigint_from_bigInt(BigIntObj& ret, const BigIntObj& src) {
	(*((BigInteger*)ret)) = (*((BigInteger*)src));
}

API_LIBBIGINT_EXT void bigint_from_long(BigIntObj& ret, long n)
{
	(*((BigInteger*)ret)) = BigInteger(n);
}

API_LIBBIGINT_EXT void bigint_from_ulong(BigIntObj& ret,unsigned long n)
{
	(*((BigInteger*)ret)) = BigInteger(n);
}


API_LIBBIGINT_EXT void bigint_from_int(BigIntObj& ret, int n)
{
	(*((BigInteger*)ret)) = BigInteger(n);
}

API_LIBBIGINT_EXT void bigint_from_uint(BigIntObj& ret,unsigned int n)
{
	(*((BigInteger*)ret)) = BigInteger(n);
}

API_LIBBIGINT_EXT long bigint_to_long(const BigIntObj& n)
{
	return (*((BigInteger*)n)).toLong();
}

API_LIBBIGINT_EXT unsigned long bigint_to_ulong(const BigIntObj& n)
{
	return (*((BigInteger*)n)).toUnsignedLong();
}

API_LIBBIGINT_EXT void bigint_bigIntegerToString(const BigIntObj& pBigInt, char * pszBuff, int & lenBuff)
{
	int len = bigIntegerToString((*((BigInteger*)pBigInt))).length();
	if (pszBuff) {
		lstrcpy(pszBuff, bigIntegerToString((*((BigInteger*)pBigInt))).c_str());
		lenBuff = len+1;
	} else {
		lenBuff = len+1;
	}
}

API_LIBBIGINT_EXT void bigint_stringToBigInteger(BigIntObj& ret, const char * pStr)
{
	(*((BigInteger*)ret)) = stringToBigInteger(pStr);
}
