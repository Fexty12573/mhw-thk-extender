#include <Windows.h>
#include <nlohmann/json.hpp>

#include <filesystem>
#include <fstream>
#include <vector>

#include "loader.h"
#include "thk_extender.h"

namespace fs = std::filesystem;
using namespace loader;

struct ThkExtensionPlugin
{
	fs::path dll;
	fs::path json;
};

DWORD WINAPI Setup([[maybe_unused]] LPVOID hDll)
{
	char dir[MAX_PATH] = { 0 };
	GetCurrentDirectoryA(MAX_PATH, dir);

	std::vector<ThkExtensionPlugin> extensions;
	fs::path path;

	if (std::string(dir).ends_with("plugins"))
		path = fs::path(dir) / "thk-extensions";
	else
		path = fs::path(dir) / "nativePC\\plugins\\thk-extensions";


	// Collect all extensions
	for (fs::directory_entry entry : fs::directory_iterator(path))
	{
		if (entry.path().extension() == ".dll")
		{
			ThkExtensionPlugin ext;
			ext.json = ext.dll = entry.path();
			ext.json.replace_extension(".json");

			extensions.push_back(ext);
			LOG(INFO) << "<thk-extender> Found Extension " << ext.dll.filename();
		}
	}

	// Apply all extensions
	for (const auto& ext : extensions)
	{
		auto mod = LoadLibraryA(ext.dll.string().c_str());

		if (mod)
		{
			std::ifstream file(ext.json);
			nlohmann::json config = nlohmann::json::object();

			file >> config;

			for (const auto& entry : config["functions"])
			{
				auto name = entry["name"].get<std::string>();
				auto id = std::stoi(entry["id"].get<std::string>(), nullptr, 16);

				THKFunction_t func = (THKFunction_t)GetProcAddress(mod, name.c_str());

				if (func)
				{
					THKExtender::AddThkFunction(func, id);
					LOG(INFO) << "<thk-extender> Successfully added THK extension '" << name << "'";
				}
				else
				{
					LOG(INFO) << "<thk-extender> Failed to retrieve function \""
						<< name << "\" from extension " << ext.dll.filename()
						<< " (" << GetLastError() << ")" ;
				}
			}
		}
		else
		{
			LOG(INFO) << "<thk-extender> Failed to load extension " << ext.dll.filename();
		}
	}

	THKExtender::Initialize();

	return 0;
}

BOOL APIENTRY DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
		CreateThread(nullptr, 0, Setup, hDll, 0, nullptr);

	return TRUE;
}
