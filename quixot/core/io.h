#pragma once

#include <expected>
#include <string>

namespace Quixot::Core {
	class FileReader {
	public:
		static result<string, string> ReadString(const std::string& path);
	};
}