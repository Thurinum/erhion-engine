#pragma once

namespace Quixot::Core {
	class FileReader {
	public:
		static either<string, string> ReadString(const std::string& path);
	};
}