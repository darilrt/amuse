#pragma once

#include <string>
#include <functional>
#include <unordered_map>
#include <filesystem>

namespace io {
	class FileWatcher {
	public:
		static void OnFileChange(const std::string& path, const std::function<void()>& callback);

	private:
		static std::unordered_map<std::string, std::filesystem::file_time_type> m_lastWriteTimes;
		static std::unordered_map<std::string, std::function<void()>> m_callbacks;

		FileWatcher();
	};
}