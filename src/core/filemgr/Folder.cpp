#include "Folder.hpp"
#include "FileMgr.hpp"

namespace YimMenu
{
	Folder::Folder(const std::filesystem::path& path) :
	    BaseObj(path)
	{
	}

	File Folder::GetFile(std::filesystem::path file_path) const
	{
		if (file_path.is_absolute())
			throw std::invalid_argument("folder#get_file requires a relative path.");
		if (file_path.string().contains(".."))
			throw std::invalid_argument("Relative path traversal is not allowed, refrain from using \"..\" in file paths.");

		return File(m_Path / file_path);
	}
}