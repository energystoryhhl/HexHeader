#include "Command.h"


namespace HexHeader {
	namespace Command {

		CmdLine::CmdLine(string &cmd, string delim)
			:
			command_(cmd)
		{
			if (cmd == "")
			{
			}
			else
			{
				commandElemts = split(delim);
			}

		}

		vector<string> CmdLine::split(string & delim)
		{

			vector<string> res;
			if ("" == command_) return res;
			//先将要切割的字符串从string类型转换为char*类型  
			char * strs = new char[command_.length() + 1]; //不要忘了  
			strcpy(strs, command_.c_str());

			char * d = new char[delim.length() + 1];
			strcpy(d, delim.c_str());

			char *p = strtok(strs, d);
			while (p) {
				string s = p; //分割得到的字符串转换为string类型  
				res.push_back(s); //存入结果数组  
				p = strtok(NULL, d);
			}

			return res;
		}

		vector<string> CmdLine::elemts() const
		{
			return commandElemts;
		}

		/*operation*/
		Operation::Operation(AppendFile * file, vector<HexDataElemt_t>& hex, vector<string> op)
			:
			file_(file),
			hex_(hex),
			op_(op)
		{	


		}

		Operation::~Operation()
		{


		}

		int Operation::doOperation()
		{
			if (op_.size() <= 1)
				return OpCodeError; //op code error!

			string op1 = op_[0];
			unsigned int start = string_as_T<unsigned int>(op_[1]);
			unsigned int size = 0;
				
			if (op_.size() > 2)
			{
				size = string_as_T<unsigned int>(op_[2]);

			}
			else {
				size = hex_.size();
			}

			if(op1 == "insert" || op1 == "Insert")
			{
				if (size > hex_.size())
				{
					size = hex_.size();
				}
				return file_->insert(start, hex_.begin(), size);
			}

			if (op1 == "cover" || op1 == "Cover" || op1 == "modify" || op1 == "Modify")
			{
				if (size > hex_.size())
				{
					size = hex_.size();
				}
				return file_->cover(start, hex_.begin(), size);
			}

			if (op1 == "erase" || op1 == "Erase" || op1 == "delete" || op1 == "Delete")
			{
				if(op_.size() <= 2)
					return OpCodeError;
				return file_->erase(start, size);
			}


			return NoOpcodeMatch;

		}

	}//namespace Command
}