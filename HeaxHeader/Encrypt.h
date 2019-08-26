#pragma once
#include "Command.h"
#include "StringMethod.h"

namespace HexHeader
{
	namespace Encrypt
	{
		class EncryptBase : noncopyable
		{
		public:
			EncryptBase(vector<string> & op, vector<HexDataElemt_t>& hex, AppendFile &file);

			bool doEncrypt();

		private:
			vector<string> op_;
			vector<HexDataElemt_t>& hex_;
			AppendFile &file_;

		};//class EncryptBase : noncopyable






	}//namespace Encrypt
}