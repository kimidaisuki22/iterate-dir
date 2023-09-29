#include "include/dir-iter/dir-iter.h"
#include <filesystem>
#include <iostream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
int main(int argc, char **argv) {
  auto root = argv[1];
  nlohmann::json json;
  dir_iter::simple_iterate(root, [&json](const std::filesystem::path &p) {
    if (std::filesystem::is_directory(p) && p.filename() == ".git") {
      json["repo"].push_back(p.parent_path().string());
      // std::cout << "path: " << p.parent_path() << "\n";
    }
  });

  std::cout << json;
  return 0;
}
