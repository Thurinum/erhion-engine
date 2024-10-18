#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <expected>

namespace Erhion::Utils {
	class FileReader {
	public:
		using ReadStringResult = std::expected<std::string, std::string>;

		static ReadStringResult ReadString(const std::string& path) {
			std::ifstream file(path, std::ios::in | std::ios::binary);
			if (!file) {
				return std::unexpected("Failed to open file: " + path);
			}

			std::ostringstream contents;
			contents << file.rdbuf();
			file.close();

			return contents.str();
		}
	};
}