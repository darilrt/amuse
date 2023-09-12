#include "amuse/file.h"

#include "amuse/es.h"

std::unordered_map<std::string, std::filesystem::file_time_type> io::FileWatcher::m_lastWriteTimes;
std::unordered_map<std::string, std::function<void()>> io::FileWatcher::m_callbacks;

bool firstCall = true;

void io::FileWatcher::OnFileChange(const std::string& path, const std::function<void()>& callback) {
	if (firstCall) {
		es::AddEventListener("Tick", [&](const es::Event& e) {
			for (auto& [path, callback] : m_callbacks) {
				std::filesystem::file_time_type currentModified = std::filesystem::last_write_time(path);

				if (currentModified != m_lastWriteTimes[path]) {
					m_lastWriteTimes[path] = currentModified;

					callback();
				}
			}
		});

		firstCall = false;
	}
	m_callbacks[path] = callback;
}

io::FileWatcher::FileWatcher() { }
