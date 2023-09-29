#pragma once

#include "include/dir-iter/dir-iter.h"
#include <cassert>
#include <chrono>
#include <filesystem>

inline std::chrono::seconds
get_dir_changed_time(std::filesystem::path dir_path) {
  assert(std::filesystem::is_directory(dir_path));

  auto time = std::filesystem::last_write_time(dir_path);
  dir_iter::simple_iterate(dir_path, [&time](std::filesystem::path p){
    auto t = std::filesystem::last_write_time(p);
    time = std::max(t,time);
  });
  using Clock = decltype(time)::clock;
  auto now = Clock::now();

  return std::chrono::duration_cast<std::chrono::seconds>(now - time);
}