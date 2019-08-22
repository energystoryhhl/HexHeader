#ifndef  APPENDFILE_H
#define APPENDFILE_H

#include "noncopyable.h"
#include "BinaryFile.h"

#include <memory>
#include <vector>

#include <ostream>

using namespace std;
using namespace HexHeader;
using namespace FileUtil;

namespace HexHeader
{
	namespace FileUtil
	{
		typedef unsigned long location_t;

		typedef vector<char> HexData_t;


		class AppendFile : public noncopyable
		{
		public:


			AppendFile(char * filename);

			~AppendFile();

			bool insert(location_t location, vector<char>::iterator & start, size_t len);

			bool push_back(char chr);

			bool erase(location_t location, size_t len);

			bool cover(location_t location, vector<char>::iterator & start, size_t len);

			string bufferToString();

			size_t size() const;

			size_t fileSize() const;

			bool writeToFile(const char *newFilename = NULL);

			//shared_ptr<char>

		private:
			std::unique_ptr<HexHeader::FileUtil::BinaryFile> p_binaryFile_;
			vector<char> vecBuffer_;
			std::unique_ptr<char> p_buff_;

			size_t fileSize_;
			size_t bufSize_;
		};

	}//namespace FileUtle
}

#endif // ! APPENDFILE_H