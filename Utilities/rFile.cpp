#include "stdafx.h"

const int rPATH_MKDIR_FULL = wxPATH_MKDIR_FULL;

//enum rSeekMode
//{
//	rFromStart,
//	rFromCurrent,
//	rFromEnd
//};
//
//	enum OpenMode
//	{
//		read,
//		write,
//		read_write,
//		write_append,
//		write_excl
//	};

wxFile::OpenMode convertOpenMode(rFile::OpenMode open)
{
	wxFile::OpenMode mode;
	switch (open)
	{
	case rFile::read:
		mode = wxFile::read;
		break;
	case rFile::write:
		mode = wxFile::write;
		break;
	case rFile::read_write:
		mode = wxFile::read_write;
		break;
	case rFile::write_append:
		mode = wxFile::write_append;
		break;
	case rFile::write_excl:
		mode = wxFile::write_excl;
		break;
	}
	return mode;
}

rFile::OpenMode rConvertOpenMode(wxFile::OpenMode open)
{
	rFile::OpenMode mode;
	switch (open)
	{
	case wxFile::read:
		mode = rFile::read;
		break;
	case wxFile::write:
		mode = rFile::write;
		break;
	case wxFile::read_write:
		mode = rFile::read_write;
		break;
	case wxFile::write_append:
		mode = rFile::write_append;
		break;
	case wxFile::write_excl:
		mode = rFile::write_excl;
		break;
	}
	return mode;
}

wxSeekMode convertSeekMode(rSeekMode mode)
{
	wxSeekMode ret;
	switch (mode)
	{
	case rFromStart:
		ret = wxFromStart;
		break;
	case rFromCurrent:
		ret = wxFromCurrent;
		break;
	case rFromEnd:
		ret = wxFromEnd;
		break;
	}
	return ret;
}

rSeekMode rConvertSeekMode(wxSeekMode mode)
{
	rSeekMode ret;
	switch (mode)
	{
	case wxFromStart:
		ret = rFromStart;
		break;
	case wxFromCurrent:
		ret = rFromCurrent;
		break;
	case wxFromEnd:
		ret = rFromEnd;
		break;
	}
	return ret;
}


rFile::rFile()
{
	handle = reinterpret_cast<void*>(new wxFile());
}

rFile::rFile(const std::string& filename, rFile::OpenMode open)
{

	handle = reinterpret_cast<void*>(new wxFile(fmt::FromUTF8(filename), convertOpenMode(open)));
}

rFile::rFile(int fd)
{
	handle = reinterpret_cast<void*>(new wxFile(fd));
}

rFile::~rFile()
{
	delete reinterpret_cast<wxFile*>(handle);
}

bool rFile::Access(const std::string &filename, rFile::OpenMode mode)
{
	return wxFile::Access(fmt::FromUTF8(filename), convertOpenMode(mode));
}

size_t rFile::Write(const void *buffer, size_t count)
{
	return reinterpret_cast<wxFile*>(handle)->Write(buffer,count);
}

bool rFile::Write(const std::string &text)
{
	return reinterpret_cast<wxFile*>(handle)->Write(fmt::FromUTF8(text));
}

bool rFile::Close()
{
	return reinterpret_cast<wxFile*>(handle)->Close();
}

bool rFile::Create(const std::string &filename, bool overwrite, int access)
{
	return reinterpret_cast<wxFile*>(handle)->Create(fmt::FromUTF8(filename),overwrite,access);
}

bool rFile::Open(const std::string &filename, rFile::OpenMode mode, int access)
{
	return reinterpret_cast<wxFile*>(handle)->Open(fmt::FromUTF8(filename), convertOpenMode(mode), access);
}

bool rFile::Exists(const std::string &file)
{
	return wxFile::Exists(fmt::FromUTF8(file));
}

bool rFile::IsOpened() const
{
	return reinterpret_cast<wxFile*>(handle)->IsOpened();
}

size_t	rFile::Length() const
{
	return reinterpret_cast<wxFile*>(handle)->Length();
}

size_t  rFile::Read(void *buffer, size_t count)
{
	return reinterpret_cast<wxFile*>(handle)->Read(buffer,count);
}

size_t 	rFile::Seek(size_t ofs, rSeekMode mode)
{
	return reinterpret_cast<wxFile*>(handle)->Seek(ofs, convertSeekMode(mode));
}

size_t rFile::Tell() const
{
	return reinterpret_cast<wxFile*>(handle)->Tell();
}

std::string rGetCwd()
{
	return fmt::ToUTF8(wxGetCwd());
}

bool rMkdir(const std::string &path)
{
	return wxMkdir(fmt::FromUTF8(path));
}

bool rRmdir(const std::string &path)
{
	return wxRmdir(fmt::FromUTF8(path));
}

bool rDirExists(const std::string &path)
{
	return wxDirExists(fmt::FromUTF8(path));
}

bool rFileExists(const std::string &path)
{
	return wxFileExists(fmt::FromUTF8(path));
}

bool rRemoveFile(const std::string &path)
{
	return wxRemoveFile(fmt::FromUTF8(path));
}

bool rIsWritable(const std::string& path)
{
	return wxIsWritable(fmt::FromUTF8(path));
}

bool rIsReadable(const std::string& path)
{
	return wxIsReadable(fmt::FromUTF8(path));
}

bool rIsExecutable(const std::string& path)
{
	return wxIsExecutable(fmt::FromUTF8(path));
}

rDir::rDir()
{
	handle = reinterpret_cast<void*>(new wxDir());
}

rDir::~rDir()
{
	delete reinterpret_cast<wxDir*>(handle);
}

rDir::rDir(const std::string &path)
{
	handle = reinterpret_cast<void*>(new wxDir(fmt::FromUTF8(path)));
}

bool rDir::Open(const std::string& path)
{
	return reinterpret_cast<wxDir*>(handle)->Open(fmt::FromUTF8(path));
}

bool rDir::Exists(const std::string &path)
{
	return wxDir::Exists(fmt::FromUTF8(path));
}

bool rDir::GetFirst(std::string *filename) const
{
	wxString str;
	bool res;
	res = reinterpret_cast<wxDir*>(handle)->GetFirst(&str);
	*filename = str.ToStdString();
	return res;
}

bool rDir::GetNext(std::string *filename) const
{
	wxString str;
	bool res;
	res = reinterpret_cast<wxDir*>(handle)->GetNext(&str);
	*filename = str.ToStdString();
	return res;
}

	
	
rFileName::rFileName()
{
	handle = reinterpret_cast<void*>(new wxFileName());
}

rFileName::~rFileName()
{
	delete reinterpret_cast<wxFileName*>(handle);
}

rFileName::rFileName(const rFileName& filename)
{
	handle = reinterpret_cast<void*>(new wxFileName(*reinterpret_cast<wxFileName*>(filename.handle)));
}


rFileName::rFileName(const std::string& name)
{
	handle = reinterpret_cast<void*>(new wxFileName(fmt::FromUTF8(name)));
}

std::string rFileName::GetFullPath()
{
	return fmt::ToUTF8(reinterpret_cast<wxFileName*>(handle)->GetFullPath());
}

std::string rFileName::GetPath()
{
	return fmt::ToUTF8(reinterpret_cast<wxFileName*>(handle)->GetPath());
}

std::string rFileName::GetName()
{
	return fmt::ToUTF8(reinterpret_cast<wxFileName*>(handle)->GetName());
}

std::string rFileName::GetFullName()
{
	return fmt::ToUTF8(reinterpret_cast<wxFileName*>(handle)->GetFullName());
}

bool rFileName::Mkdir(const std::string& name, int permissions , int flags )
{
	return wxFileName::Mkdir(fmt::FromUTF8(name), permissions, flags);
}

bool rFileName::Normalize()
{
	return reinterpret_cast<wxFileName*>(handle)->Normalize();
}

