#include "Encrypt.h"
#include "noncopyable.h"
#include "AppendFile.h"

#include <string>
#include <vector>
#include "AppendFile.h"
#include "openssl\sha.h"

using namespace std;

//{"CRC16", "CRC32", "SHA256", "CMAC", "ECC"}
namespace HexHeader
{
	namespace Encrypt
	{
		EncryptBase::EncryptBase(vector<string> & op, vector<HexDataElemt_t>& hex,AppendFile &file)
			:op_(op),
			hex_(hex),
			file_(file)
		{


		}

		bool EncryptBase::doEncrypt()
		{
			if (op_.size() < 3)
				return false;
			string encryptName = op_[0];
			hex_.clear();

			if (encryptName == "SHA256")
			{
				int outLen = 256 / 8;
				unsigned char outBuf[32] = { 0 };
				int start = string_as_T<int>(op_[1]);
				int len = string_as_T<int>(op_[2]);
				if (len == -1)
				{
					len = file_.fileSize() - start;
				}

				SHA256(file_.buffer().data() + start, len, outBuf);
				hex_.insert(hex_.begin(),outBuf, outBuf + outLen);
				return true;
			}
			


		}

	}//namespace Encrypt
}