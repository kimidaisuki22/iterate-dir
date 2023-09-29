#pragma once

#include <__chrono/duration.h>
#include <cassert>
#include <chrono>
#include <filesystem>

inline std::chrono::seconds
get_dir_changed_time(std::filesystem::path dir_path) {
  assert(std::filesystem::is_directory(dir_path));

  auto time = std::filesystem::last_write_time(dir_path);
  using Clock = decltype(time)::clock;
  auto now = Clock::now();

  return std::chrono::duration_cast<std::chrono::seconds>(now - time);
}