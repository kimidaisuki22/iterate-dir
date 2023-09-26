#include "include/dir-iter/dir-iter.h"
#include <filesystem>
#include <iostream>
int main(int argc, char **argv) {
  auto root = argv[1];
  dir_iter::simple_iterate(root, [](const std::filesystem::path &p) {
    if (std::filesystem::is_directory(p) && p.filename() == ".git") {
      std::cout << "path: " << p.parent_path() << "\n";
    }
  });
  return 0;
}
