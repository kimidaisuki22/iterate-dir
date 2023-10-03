#pragma once
#include <filesystem>

inline bool is_sub_dir(std::filesystem::path parent,
                       std::filesystem::path child) {
  // auto result = !child.lexically_relative(parent).empty();
  auto bp = parent.begin();
  auto ep = parent.end();

  auto bc = child.begin();
  auto ec = child.end();

  while (bp != ep) {
    if (ep == ec) {
      return false;
    }
    if (*bp != *bc) {
      return false;
    }
    bp++;
    bc++;
  }
  return true;
}