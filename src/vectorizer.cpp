#include "vectorizer.h"

using ::std::map;
using ::std::set;
using ::std::string;
using ::std::vector;

// Remove Puncts, Decaptialize.
void Vectorizer::normalize_str(string &str) {
  str.erase(std::remove_if(str.begin(), str.end(), ispunct), str.end());
}

vector<string> Vectorizer::tokenizer(const string &str) {

  vector<string> ret;
  string::const_iterator b = str.begin();
  string::const_iterator e = str.begin();

  while (b != str.end()) {

    while (isalnum(*e)) {
      ++e;
    }

    while (!isalnum(*b)) {
      ++b;
    }

    if (*e == ' ' || e == str.end()) {

      string temp = string(b, e);

      if (!Vectorizer::is_stopword(temp)) {
        // std::cout << temp << std::endl;
        ret.push_back(temp);
      }
      b = e++;
    }
  }

  return ret;
}

set<string> Vectorizer::word_set(const string &str) {

  set<string> ret;

  string::const_iterator b = str.begin();
  string::const_iterator e = str.begin();

  vector<string> splitted_str = Vectorizer::tokenizer(str);

  for (auto elem : splitted_str) {
    ret.insert(elem);
  }

  return ret;
}

bool Vectorizer::is_stopword(const string &str) {

  auto exists = std::find(stopwords.begin(), stopwords.end(), str);

  if (exists == stopwords.end()) {
    return false;
  }

  return true;
}

map<int, string> Vectorizer::create_vocab(set<string> word_set) {

  map<int, string> ret;
  int idx = 0;

  for (auto elm : word_set) {
    ret[idx] = elm;
    idx++;
  }

  return ret;
}

map<int, vector<int>> Vectorizer::gen_train(const map<int, string> &vocab,
                                            const string &corpus) {

  map<int, vector<int>> ret;
  map<string, int> stoi_vocab;

  for (auto pair : vocab) {
    stoi_vocab[pair.second] = pair.first;
  }

  vector<string> splitted_corpus = tokenizer(corpus);
  for (int i = WINDOW_SIZE; i < splitted_corpus.size() - WINDOW_SIZE; i++) {

    string center_w = splitted_corpus[i];
    int center_ = stoi_vocab[center_w];
    vector<int> context_vec;

    for (int j = WINDOW_SIZE; j != 0; j--) {

      string context1_ = splitted_corpus[i - j];
      string context2_ = splitted_corpus[i + j];
      context_vec.push_back(stoi_vocab[context1_]);
      context_vec.push_back(stoi_vocab[context2_]);
    }

    ret[center_] = context_vec;
  }

  return ret;
}
