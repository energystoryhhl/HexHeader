#ifndef BINARYFILE_H
#define BINARYFILE_H

#include "noncopyable.h"

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

namespace HexHeader
{
	namespace FileUtil {
		

		class BinaryFile : public noncopyable
		{
		public:
			BinaryFile(const char* filename);

			~BinaryFile();

			size_t write(char chr);

			size_t write(char *buf, size_t len);
			
			size_t write(char *buf, unsigned int location, size_t len);

			size_t read(char *buf, size_t len);

			size_t read(char *buf, unsigned int location, size_t len);

			size_t size();

			bool ifOpen() const { return fd_ == NULL ? 0 : 1; }

			void close();

			void open();

			void cleanFile();

			void seek(unsigned int location);

			string fileName();


		private:
			string filename_;
			FILE* fd_;
			size_t size_;
			//ostringstream oss_;
			//std::vector<char> vecBuffer_;
		};
	}
}

#endif // !BINARYFILE_H
