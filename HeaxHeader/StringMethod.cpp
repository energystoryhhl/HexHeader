#include "StringMethod.h"
#include <afxpriv.h>


namespace HexHeader
{
	namespace Detail
	{
		string Wchr2str(CString & wchr)
		{
			USES_CONVERSION;
			char * str = T2A(wchr);
			return str;
			//std::cout << "open file: " << pFileName << std::endl;
		}

		void str2UcArray(vector<unsigned char>& buf, string str)
		{
			if (str == "")
				return;
			assert(buf.size() == 0);

			//unsigned int num = string_as_T<unsigned int>(str);

			str.erase(str.begin(), str.begin() + 2);

			assert(str.size() % 2 == 0);

			for (int i = 0; i < str.size() / 2; i++)
			{
				unsigned char chr = (unsigned char)strtol(str.substr(i * 2, 2 ).c_str(), NULL, 16);
				
				buf.push_back(chr);
			}
		}






	}//namespace Detail
}
