#pragma once
#include <filesystem>
#include <vector>

inline std::vector<std::filesystem::path> get_cache_dirs() {
  return {
      ".cache",
      "build",
      "node_modules",
  };
}