#include "stdafx.h"
#include "BinaryFile.h"


namespace HexHeader
{
	namespace FileUtil {

		BinaryFile::~BinaryFile()
		{
			close();
		}

		size_t BinaryFile::write(char chr)
		{
			
			return write(&chr, 1);;
		}

		size_t BinaryFile::write(char * buf, size_t len)
		{
			if (fd_ == NULL)
			{
				return -1;
			}

			return fwrite(buf,1,len,fd_);
		}

		size_t BinaryFile::write(char * buf, unsigned int location, size_t len)
		{
			if (fd_ == NULL)
			{
				return -1;
			}

			seek(location);

			write(buf, len);

			return size_t();
		}

		size_t BinaryFile::read(char *buf, size_t len)
		{
			if (fd_ == NULL)
			{
				return -1;
			}
			
			return fread(buf, 1, len, fd_);

		}

		size_t BinaryFile::read(char * buf, unsigned int location, size_t len)
		{
			if (fd_ == NULL)
				return -1;

			seek(location);

			size_t size = read(buf, len);

			return size;
		}

		size_t BinaryFile::size()
		{
			if (fd_ == NULL)
			{
				return -1;
			}

			fseek(fd_, 0l, SEEK_END);
			
			int size = ftell(fd_);
			rewind(fd_);

			return size;

			/*
						lCount = lSize / sizeof(int);
			ipPtr = (int*)malloc(lSize);
			rewind(fpFile);
			fread(ipPtr, sizeof(int), lCount, fpFile);
			*/
		}

		void BinaryFile::close()
		{
			cout << "~BinaryFile()" << endl;
			if (fd_ == NULL)
			{
			}
			else
			{
				fclose(fd_);
			}
		}

		void BinaryFile::seek(unsigned int location)
		{
			/*
			SEEK_SET： 文件开头
			SEEK_CUR： 当前位置
			SEEK_END： 文件结尾
			*/
			if (fd_ == NULL)
				return;

			fseek(fd_, location, SEEK_SET);
		}

		string BinaryFile::fileName()
		{
			return filename_;
		}


		BinaryFile::BinaryFile(const char* filename)
			:filename_(filename),
			fd_(fopen(filename_.c_str(), "ab+"))
		{
			assert(fd_ != NULL);
			size_ = size();
			/*
			char cbuff[1024] = { 0 };

			fread(cbuff, 1000, 1, fd_);

			string str(cbuff);

			printf("%s", cbuff);	
			*/

			//vecBuffer_.reserve(5120);

		}
	} //FileUtil {
}