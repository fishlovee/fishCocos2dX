#include "iconvstring.h"



std::string toUtf8String(const string fromcode, const string strSrc)
{
	iconv_t ct = iconv_open(DX_UFF8_CODE, fromcode.c_str());
	if (ct == 0) return "";

	size_t inbytesleft = strSrc.length();
	const char * szinBuf = strSrc.c_str();

	size_t outbytesleft = inbytesleft * 4;
	char *szoutBuf = new char[outbytesleft + 1];
	char *pBuf = szoutBuf;
	memset(szoutBuf, 0, outbytesleft + 1);
	size_t  t = iconv(ct, &szinBuf, &inbytesleft,&szoutBuf,&outbytesleft);

	string ret = string(pBuf);
	delete[] pBuf;
	iconv_close(ct);
	return ret;
}


std::string GBKToUTF8(const char *strChar, const char* toCode, const char* formCode)
{
	std::string utf8Str;
	iconv_t iconvH;
	iconvH = iconv_open(formCode, toCode);
	if (iconvH == 0) {
		return "";
	}

	const char** pin = &strChar;
	size_t strLength = strlen(strChar);
	char *outbuf = (char*)malloc(strLength * 4);
	char *pBuff = outbuf;
	memset(outbuf, 0, strLength * 4);
	size_t outLength = strLength * 4;
	size_t  t = iconv(iconvH, pin, &strLength, &outbuf, &outLength);
	if (-1 == t) {
		iconv_close(iconvH);
		return "";
	}
	utf8Str = pBuff;
	iconv_close(iconvH);
	return utf8Str;
}
