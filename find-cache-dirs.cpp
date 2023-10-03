#include "cache_dirs.h"
#include "include/dir-iter/dir-iter.h"
#include "is_sub_dir.h"
#include <filesystem>
#include <iostream>
#include <vector>
bool is_cache_dir_name(const std::filesystem::path &p) {
  static auto dirs = get_cache_dirs();
  auto name = p.filename();

  for (auto dir : dirs) {
    if (name == dir) {
      return true;
    }
  }
  return false;
}
int main(int argc, char **argv) {
  std::string root = argv[1];
  dir_iter::simple_iterate(root, [](const std::filesystem::path &p) {
    if (std::filesystem::is_directory(p) && is_cache_dir_name(p)) {
      static std::vector<std::filesystem::path> tasked;
      for(auto& t:tasked){
        if(is_sub_dir(t, p)){
          return;
        }
      }
      tasked.push_back(p);
      std::cout << p.string() << "\n";
    }
  });

  return 0;
}
