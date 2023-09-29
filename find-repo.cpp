#include "dir_time.h"
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
      nlohmann::json repo;
      repo["path"] = p.parent_path().string();
      repo["changed_before_seconds"] = get_dir_changed_time(p.parent_path()).count();


      json["repos"].push_back(repo);
      // std::cout << "path: " << p.parent_path() << "\n";
    }
  });

  std::cout << json;
  return 0;
}
