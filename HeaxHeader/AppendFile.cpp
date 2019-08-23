#include "stdafx.h"
#include "AppendFile.h"

namespace HexHeader
{
	namespace FileUtil
	{
		AppendFile::AppendFile(char *filename)
			:p_binaryFile_(new HexHeader::FileUtil::BinaryFile(filename)),
			p_buff_(new char[p_binaryFile_->size() * 2])
			//p_buff_(new char(p_binaryFile_->Size() * 2)  )
		{
			
			assert(p_binaryFile_ != NULL);
			assert(p_buff_ != NULL);

			loadBuffer();
		}


		AppendFile::~AppendFile()
		{
			cout << "~AppendFile()" << endl;
		}

		bool AppendFile::insert(location_t location, vector<char>::iterator & start, size_t len)
		{
			if (static_cast<size_t>(location) >= vecBuffer_.size())
			{
				goto fail;
			}

			vecBuffer_.insert(vecBuffer_.begin() + location, start, start + len);
			return true;
			
		fail:
			return false;

		}

		bool AppendFile::push_back(char chr)
		{
			
			vecBuffer_.push_back(chr);
			return true;

			fail:
			return false;
		}

		bool AppendFile::erase(location_t location, size_t len)
		{
			if (vecBuffer_.size() < location)
			{
				goto fail;
			}

			vecBuffer_.erase(vecBuffer_.begin() + location, vecBuffer_.begin() + len);
			return true;

		fail:
			return false;
		}

		bool AppendFile::cover(location_t location, vector<char>::iterator & start, size_t len)
		{
			if (vecBuffer_.size() < location)
			{
				goto fail;
			}

			vecBuffer_.erase(vecBuffer_.begin() + location, vecBuffer_.begin() + len);

			vecBuffer_.insert(vecBuffer_.begin() + location, start, start + len);

			return true;

			fail:
			return false;
		}

		string AppendFile::bufferToString()
		{
			char buf[5] = { 0 };
			string str;
			int t = 0;
			for (auto i : vecBuffer_)
			{
				unsigned char tmp = i;
				sprintf(buf, "%02x ", tmp);
				//printf("%02x ", tmp);
				str.append(buf,3);
				if (((t + 1) % 16) == 0)
				{
					str.append("\r\n");
					//printf("\n ");
				}
				t++;
			}
			return str;
		}

		size_t AppendFile::size() const
		{
			return vecBuffer_.size();
		}

		size_t AppendFile::fileSize() const
		{
			return p_binaryFile_->size();
		}

		bool AppendFile::writeToFile(const char * newFilename)
		{
			if (newFilename == NULL)
			{
				newFilename = p_binaryFile_->fileName().append("_header_added").c_str();
			}
			BinaryFile newFile(newFilename);
			size_t size = newFile.write(vecBuffer_.data(), vecBuffer_.size());
			if (size != vecBuffer_.size())
				return false;
			else
				return true;
		}

		bool AppendFile::writeToCurFile()
		{
			size_t size = p_binaryFile_->write(vecBuffer_.data(), vecBuffer_.size());
			if (size != vecBuffer_.size())
				return false;
			else
				return true;
		}

		void AppendFile::loadBuffer()
		{
			fileSize_ = p_binaryFile_->size();

			assert(fileSize_ >= 0);

			size_t size = p_binaryFile_->read(p_buff_.get(), fileSize_);

			/*
			for (int i = 0; i < fileSize_; i++)
			{
			unsigned char tmp = *(p_buff_.get() + i);

			printf("%02x ", tmp);


			if (((i + 1) % 16) == 0 )
			printf("\n");
			}

			BinaryFile bfile("test.dat");
			bfile.write(p_buff_.get(), fileSize_);
			*/

			assert(size == fileSize_);

			vecBuffer_.clear();

			vecBuffer_.insert(vecBuffer_.begin(), p_buff_.get(), p_buff_.get() + fileSize_);
		}


	}//namespace FileUtle
}