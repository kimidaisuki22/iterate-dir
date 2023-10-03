#include "dir_size.h"
#include "dir_time.h"
#include "include/dir-iter/dir-iter.h"
#include <filesystem>
#include <iostream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>
int main(int argc, char **argv) {
  std::string line;
  while (std::getline(std::cin, line)) {
    std::filesystem::path path = line;
    std::cout << path << ": " << get_dir_size(path) << "\n";
  }
  return 0;
}
