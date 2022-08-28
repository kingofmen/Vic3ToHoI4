#include "out_mod.h"

#include <fstream>
#include <string>

#include "external/commonItems/Log.h"
#include "external/commonItems/OSCompatibilityLayer.h"
#include "external/fmt/include/fmt/format.h"



namespace out
{

namespace
{

void CreateOutputFolder(const std::string_view output_name)
{
   Log(LogLevel::Info) << "\tCopying blank mod";
   if (!commonItems::TryCreateFolder("output"))
   {
      throw std::runtime_error("Could not create output folder");
   }
   if (!commonItems::CopyFolder("blank_mod", std::string("output/").append(output_name)))
   {
      throw std::runtime_error("Could not copy blank_mod");
   }
}


void CreateModFiles(const std::string_view output_name, const GameVersion& game_version)
{
   Log(LogLevel::Info) << "\tCreating .mod files";

   std::ofstream modFile(std::string("output/").append(output_name).append(".mod"));
   if (!modFile.is_open())
   {
      throw std::runtime_error("Could not create .mod file");
   }
   modFile << fmt::format(
       "name = \"Converted - {}\"\n"
       "path = \"mod/{}/\"\n"
       "user_dir = \"{}_user_dir\"\n"
       "replace_path=\"common/ideologies\"\n"
       "replace_path=\"history/countries\"\n"
       "replace_path=\"history/states\"\n"
       "supported_version=\"{}\"",
       output_name,
       output_name,
       output_name,
       game_version.toWildCard());
   modFile.close();

   std::ofstream descriptorFile(std::string("output/").append(output_name).append("/descriptor.mod"));
   if (!descriptorFile.is_open())
   {
      throw std::runtime_error("Could not create descriptor.mod");
   }
   descriptorFile << fmt::format(
       "name = \"Converted - {}\"\n"
       "replace_path=\"common/ideologies\"\n"
       "replace_path=\"history/countries\"\n"
       "replace_path=\"history/states\"\n"
       "supported_version=\"{}\"",
       output_name,
       game_version.toWildCard());
   descriptorFile.close();
}

}  // namespace


void ClearOutputFolder(std::string_view output_name)
{
   const std::string output_folder = std::string("output/").append(output_name);
   if (commonItems::DoesFolderExist(output_folder))
   {
      Log(LogLevel::Info) << "Removing pre-existing copy of " << output_name;
   }

   if (!commonItems::DeleteFolder(output_folder))
   {
      throw std::runtime_error("Could not remove pre-existing output folder " + output_folder +
                               ". Please delete folder and try converting again.");
   }
}


void Output(const std::string_view output_name, const GameVersion& game_version)
{
   Log(LogLevel::Progress) << "80%";
   Log(LogLevel::Info) << "Outputting mod";

   CreateOutputFolder(output_name);
   CreateModFiles(output_name, game_version);
   Log(LogLevel::Progress) << "85%";
}

}  // namespace out