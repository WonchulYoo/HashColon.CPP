#ifndef HASHCOLON_SINGLETONCLI
#define HASHCOLON_SINGLETONCLI

// std libraries
#include <exception>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <vector>
// modified external libraries
#include <HashColon/CLI11.hpp>
#include <HashColon/CLI11_JsonSupport.hpp>

namespace HashColon
{
	class SingletonCLI
	{
	private:
		static inline std::shared_ptr<SingletonCLI> _instance = nullptr;
		static inline std::once_flag _onlyOne;
		static inline std::string _appDescription = "";

		CLI::App cli;
		std::vector<std::string> _configfiles;

		SingletonCLI(size_t id) : cli(_appDescription){};
		SingletonCLI(const SingletonCLI &rs) { _instance = rs._instance; };
		SingletonCLI &operator=(const SingletonCLI &rs);
		CLI::App *GetCLI_core(CLI::App *app, const std::string iClassname);

	public:
		enum class ConfigurationFileType
		{
			toml,
			ini,
			json
		};
		~SingletonCLI(){};

		static SingletonCLI &GetInstance(size_t thread_id = 0);
		static SingletonCLI &Initialize(
			ConfigurationFileType configtype = ConfigurationFileType::toml,
			std::string appDescription = "");

		SingletonCLI &AddConfigFile(std::string configFileName);
		SingletonCLI &AddConfigFile(std::vector<std::string> configFileNames);

		std::vector<std::string> &GetConfigFileList();

		void Parse(int argc, char **argv,
				   std::vector<std::string> configFiles);

		CLI::App *GetCLI(const std::string iClassname = "");
	};
}

#endif
