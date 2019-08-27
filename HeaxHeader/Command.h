#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>

#include "noncopyable.h"
#include "AppendFile.h"
#include "StringMethod.h"


using namespace std;
using namespace HexHeader;
using namespace Detail;

namespace HexHeader
{
	namespace Command
	{
		static const string opcodes[] = { "erase", "Erase" ,"delete" , "Delete",
										"insert" , "Insert",
										"cover" , "Cover" ,"modify" ,"Modify" };

		static const string encryptcodes[] = {"CRC16", "CRC32", "SHA256", "CMAC", "ECC"};

		static const  string ErrorCodeString[] = { "HexEmpty", "OpCodeError",
			"NoOpcodeMatch", "ErrorHexSize", "ParaErr" };

		class CmdLine : noncopyable
		{
		public:
			CmdLine(string &cmd, string delim = "");
			//~CmdLine();

			vector<string>  elemts() const;

		private:
			vector<string> split(string &delim);

		private:
			string command_;
			vector<string> commandElemts;

		};//class CmdLine

		class Operation : noncopyable
		{
		public:
			enum ErrorCode
			{
				HexEmpty = -1,
				OpCodeError = -2,
				NoOpcodeMatch = -3,
				ErrorHexSize = -4,
				ParaErr = -5
			};

			Operation(AppendFile* file, vector<HexDataElemt_t> &hex, vector<string> op);

			~Operation();

			int doOperation();
		private:
			AppendFile* file_;
			vector<HexDataElemt_t> &hex_;
			vector<string> op_;


		}; //class Operation : noncopyable


	}//namespace Command
}




#endif // !COMMAND_H

