#ifndef  APPENDFILE_H
#define APPENDFILE_H

#include "noncopyable.h"
#include "BinaryFile.h"

#include <memory>
#include <vector>

#include <ostream>
#include <memory>
using namespace std;
using namespace HexHeader;
using namespace FileUtil;

namespace HexHeader
{
	namespace FileUtil
	{
		typedef unsigned long location_t;

		typedef vector<unsigned char> HexData_t;

		typedef unsigned char HexDataElemt_t;
		

		class AppendFile : public noncopyable
		{
		public:


			AppendFile(char * filename);

			~AppendFile();

			bool insert(location_t location, vector<HexDataElemt_t>::iterator & start, size_t len);

			bool push_back(HexDataElemt_t chr);

			bool erase(location_t location, size_t len);

			bool cover(location_t location, vector<HexDataElemt_t>::iterator & start, size_t len);

			string bufferToString();

			size_t size() const;

			size_t fileSize() const;

			//
			//save as
			bool writeToFile(const char *newFilename = NULL);

			//
			//save
			bool writeToCurFile();

			void loadBuffer();

			void cleanFile() { p_binaryFile_->cleanFile(); };

			HexData_t & buffer() {
				return vecBuffer_;
			}

			void setHeaderSize(int sz)
			{
				heaserSize_ = sz;
			}

			int headerSize()
			{
				return heaserSize_;
			}

			//shared_ptr<char>

		private:
			std::unique_ptr<HexHeader::FileUtil::BinaryFile> p_binaryFile_;
			HexData_t vecBuffer_;
			std::unique_ptr<HexDataElemt_t> p_buff_;

			size_t fileSize_;
			size_t bufSize_;
			int heaserSize_;
		};

	}//namespace FileUtle
}

#endif // ! APPENDFILE_H