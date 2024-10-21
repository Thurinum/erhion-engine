#pragma once

#include <expected>
#include <string>
#

namespace Erhion::Utils {
	class FileReader {
	public:
		static result<string, string> ReadString(const std::string& path);
	};
}