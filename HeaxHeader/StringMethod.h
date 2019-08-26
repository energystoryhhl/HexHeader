#pragma once
#include <string>
#include <vector>
#include "stdafx.h"
#include <atlconv.h>

#include <ostream>

using namespace std;

namespace HexHeader
{
	namespace Detail
	{
		string Wchr2str(CString & wchr);

		template<class T>
		T string_as_T(const std::string& s)
		{
			// Convert from a string to a T  
			// Type T must support >> operator 
			//字符串 转换成 不同类型
			T t;
			if (!s.find("0x"))
			{
				return t = (unsigned char)strtoul(s.c_str(), NULL, 16);
			}
			std::istringstream ist(s);
			ist >> t;
			return t;
		}

		void str2UcArray(vector<unsigned char> & buf, string str);



	}//namespace Detail
}
