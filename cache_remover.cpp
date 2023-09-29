#include "dir_size.h"
#include <_types/_uint64_t.h>
#include <cstddef>
#include <filesystem>
#include <git2/global.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <vector>
#include <git2.h>
inline std::vector<std::filesystem::path> get_cache_dirs() {
  return {
      ".cache",
      "build",
  };
}
inline uint64_t
get_cache_dirs_size(std::filesystem::path root,
                    std::vector<std::filesystem::path> cache_dirs) {
  uint64_t size{};
  for (auto sub : cache_dirs) {
    auto dir = root / sub;
    bool skip = false;
    if (!std::filesystem::exists(dir)) {
      skip = true;
    }

    if (skip) {
      continue;
    }
    size += get_dir_size(dir);
  }
  return size;
}
int main(int argc, char **argv) {
  std::string json_str;
  while (true) {
    char ch = std::cin.get();
    if (!std::cin) {
      break;
    }
    json_str.push_back(ch);
  }
  nlohmann::json json = nlohmann::json::parse(json_str);

  git_libgit2_init();
  for (auto repo : json["repos"]) {
    std::string p = repo["path"];
    auto repo_size = get_dir_size(p);
    repo["repo_size"] = repo_size;
    auto cache_size = get_cache_dirs_size(p, get_cache_dirs());
    repo["cache_size"] = cache_size;

    auto code_size = repo_size - cache_size;
    repo["code_size"] = code_size;
    std::cout << repo << "\n";
  }
  git_libgit2_shutdown();

  return 0;
}