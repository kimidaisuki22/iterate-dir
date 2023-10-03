#include "dir_mask.h"
#include "dir_size.h"
#include "dir_time.h"
#include "include/dir-iter/dir-iter.h"
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <vector>
int main(int argc, char **argv) {
  std::string line;
  std::vector<std::string> dirs;
  while (std::getline(std::cin, line)) {
    std::filesystem::path path = line;
    dirs.push_back(line);
    std::cout << mask_parent_dirs_name(path.string()) << ": "
              << get_dir_size(path) << "\n";
  }
  freopen("/dev/tty", "rb", stdin);
  std::cin.clear();
  std::cout << "remove all dirs above? (y for yes)\n";
  // std::ifstream  tty{"/dev/tty",std::ios::binary};
  char token{};
  std::cin >> token;
  std::cout << ":" << token << ":\n";
  return 0;
}
