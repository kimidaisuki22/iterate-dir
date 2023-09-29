#pragma once

#include "include/dir-iter/dir-iter.h"
#include <cassert>
#include <chrono>
#include <cstdint>
#include <filesystem>

inline uint64_t get_dir_size(std::filesystem::path dir_path) {
  assert(std::filesystem::is_directory(dir_path));
  uint64_t total_size{};
  dir_iter::simple_iterate(dir_path, [&total_size](std::filesystem::path p) {
    if (std::filesystem::is_regular_file(p)) {
      total_size += std::filesystem::file_size(p);
    }
  });

  return total_size;
}