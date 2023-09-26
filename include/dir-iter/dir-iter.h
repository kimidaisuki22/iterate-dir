#pragma once
#include <filesystem>
#include <functional>
namespace dir_iter {
inline void
simple_iterate(std::filesystem::path root,
               std::function<void(std::filesystem::path dir)> callback) {
  std::filesystem::recursive_directory_iterator begin(root,std::filesystem::directory_options::skip_permission_denied), end;
  while (begin != end) {
    try {
      callback(*begin);
    } catch (std::exception &e) {
      (void)e;
    }

    try {
      ++begin;
    } catch (std::exception &e) {
      (void)e;
    }
  }
}
} // namespace dir_iter