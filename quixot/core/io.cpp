#include "io.h"

#include <fstream>
#include <string>
#include <sstream>

namespace Erhion::Utils {
	
	result<string, string> FileReader::ReadString(const std::string& path)
	{
		std::ifstream file(path, std::ios::in | std::ios::binary);
		if (!file) {
			return std::unexpected("Failed to open file: " + path);
		}
	
		std::ostringstream contents;
		contents << file.rdbuf();
		file.close();
	
		return contents.str();
	}

}
