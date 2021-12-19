//
// Created by matej on 18/12/2021.
//

#ifndef OPROJECT_OVEREYE_FILESYSTEM_MOCK_H
#define OPROJECT_OVEREYE_FILESYSTEM_MOCK_H

#include "filesystem/filesystem_proxy.h"
#include <gmock/gmock.h>

class filesystem_mock : public mzlib::filesystem_proxy
{
public:

   MOCK_CONST_METHOD1(read_file, std::string(const std::string_view));
   MOCK_CONST_METHOD1(read_file, std::string(const std::filesystem::path&));
   MOCK_CONST_METHOD3(read_file, std::string(const std::string_view, const std::streampos, const std::streampos));
   MOCK_CONST_METHOD1(read_file_lines, std::vector<std::string>(std::string_view));
   MOCK_CONST_METHOD3(get_files, std::vector<std::string>(const std::filesystem::path&, mzlib::option::recursive, mzlib::option::include_hidden));
   MOCK_CONST_METHOD2(save_file, void(const std::string_view, const std::string_view));
   MOCK_CONST_METHOD2(save_file, void(const std::filesystem::path&, const std::string_view));
   MOCK_CONST_METHOD2(append_file, void(const std::string_view, const std::string_view));

   MOCK_CONST_METHOD1(exists, bool(const std::filesystem::path&));
   MOCK_CONST_METHOD1(create_directories, bool(const std::filesystem::path&));
   MOCK_CONST_METHOD1(is_regular_file, bool(const std::filesystem::path&));

   MOCK_CONST_METHOD0(get_system_app_config_location, std::filesystem::path());

};

#endif //OPROJECT_OVEREYE_FILESYSTEM_MOCK_H
