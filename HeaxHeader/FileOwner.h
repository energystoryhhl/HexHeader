#ifndef FILEOWNER_H
#define FILEOWNER_H

//#include "stdafx.h"
#include "noncopyable.h"
//#include <HeaxHeaderDlg.h>

#include <memory>
#include <AppendFile.h>
#include <BinaryFile.h>
#include <string>


using namespace HexHeader;
using namespace FileUtil;
using namespace std;

namespace HexHeader
{
	class FileOwner : public noncopyable
	{
	public:
		FileOwner();
		FileOwner(void *dlg);

		int open(string & path);

		void close();

		bool save();

		bool saveAs(const char * newFilename);

		bool ifOpen(){ return fileOpened_;}

		AppendFile & file(){ return *p_appendFile_;}

		//data
		std::unique_ptr<AppendFile> p_appendFile_;


	private:
		void* p_dlg;
		bool fileOpened_;
		//std::

	};
}



#endif // !FILEOWNER_H

