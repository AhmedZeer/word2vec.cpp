/*#include "dataloader.h"*/
#include "vectorizer.h"
#include <iostream>

#define WINDOW_SIZE 1

using ::std::string;
using ::std::vector;

// Init Embeds.
vector<vector<int>> init_embeds(int vocab_size, int dim, int seed);

int main(int argc, char *argv[]) {

  string corpus = "This is a corpus. That contains a bunch of words !!!!!"
                  "and stuff 2 be deleted.";

  auto vec = Vectorizer(corpus);

  for (auto elem : vec.train_int) {
    std::cout << vec.vocab[elem.first] << std::endl;
    std::cout << vec.vocab[elem.second[0]] << std::endl;
    std::cout << vec.vocab[elem.second[1]] << std::endl << std::endl;
  }

  return 0;
}
