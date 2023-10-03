#pragma once

#include <cstddef>
#include <string>
inline std::string mask_parent_dirs_name(std::string unix_path) {
  if (unix_path.empty()) {
    return {};
  }
  // avoid remove / on '/'
  if (unix_path.size() > 1 && unix_path.back() == '/') {
    unix_path.pop_back();
  }

  auto pos = unix_path.find_last_of('/');
  if (pos == std::string::npos) {
    return unix_path;
  }
  for (size_t i{}; i < pos; i++) {
    if (unix_path[i] != '/') {
      unix_path[i] = '*';
    }
  }
  return unix_path;
}