#include "dir_size.h"
#include <_types/_uint64_t.h>
#include <cstddef>
#include <filesystem>
#include <git2.h>
#include <git2/commit.h>
#include <git2/global.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <optional>
#include <vector>
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
struct Git_repo_state {};
std::optional<Git_repo_state> task_git_repo(std::filesystem::path path) {

  git_repository *repo = NULL;
  int error = git_repository_open(&repo, path.c_str());
  if (error) {
    return {};
  }

  git_object *head_commit;
  error = git_revparse_single(&head_commit, repo, "HEAD");
  if (error) {
    return {};
  }
  git_commit *commit = (git_commit *)head_commit;

  std::cout << "summary: " << git_commit_summary(commit) << "\n";
  std::cout << "message: " << git_commit_message(commit) << "\n";
  const git_signature *author = git_commit_author(commit);

  std::cout << "author: " << author->name << " " << author->email << "\n";
  const git_oid *tree_id = git_commit_tree_id(commit);

  char sha[256]{};
  git_oid_tostr(sha, sizeof(sha), tree_id);

  std::cout << "sha id: " << sha << "\n";

  git_commit_free(commit);
  git_repository_free(repo);
  return {};
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
    task_git_repo(p);
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