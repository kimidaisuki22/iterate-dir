#include "dir_size.h"
#include <filesystem>
#include <iostream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

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
  for (auto repo : json["repos"]) {
    std::string p = repo["path"];
    auto repo_size = get_dir_size(p);
    repo["repo_size"] = repo_size;
    std::cout << repo << "\n";
  }

  return 0;
}