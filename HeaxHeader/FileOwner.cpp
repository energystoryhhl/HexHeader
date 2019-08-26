#include "FileOwner.h"

namespace HexHeader
{
	FileOwner::FileOwner()
		:p_appendFile_(),
		p_dlg(NULL),
		fileOpened_(false)
	{

	}

	FileOwner::FileOwner(void *dlg)
		:p_appendFile_(),
		p_dlg(dlg),
		fileOpened_(false)
	{

	}

	int FileOwner::open(string & path)
	{
		p_appendFile_.reset(new AppendFile( (char *)path.c_str()));
		fileOpened_ = true;
		return 0;
	}

	void FileOwner::close()
	{
		if (true == fileOpened_)
		{
			p_appendFile_.reset(nullptr);
		}
		fileOpened_ = false;
	}

	bool FileOwner::save()
	{
		if (false == fileOpened_)
			return false;

		file().cleanFile();

		return file().writeToCurFile();

	}

	bool FileOwner::saveAs(const char * newFilename)
	{
		if (false == fileOpened_)
			return false;
		//file().cleanFile();

		return file().writeToFile(newFilename);
	}

}