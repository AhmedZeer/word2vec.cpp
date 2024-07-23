#include <algorithm>
#include <cctype>
#include <map>
#include <ostream>
#include <set>
#include <string>
#include <vector>

#define WINDOW_SIZE 1

class Vectorizer {

public:
  Vectorizer(){};

  Vectorizer(std::string corpus) {
    normalize_str(corpus);
    apply_char(corpus, &Vectorizer::to_lowercase_inplace);
    vocab = create_vocab(word_set(corpus));
    train_int = gen_train(vocab, corpus);
  }

  std::map<int, std::string> vocab;
  std::map<int, std::vector<int>> train_int;
  std::map<std::string, std::vector<std::string>> train_str();
  std::map<int, std::string> create_vocab(std::set<std::string> word_set);

private:
  void normalize_str(std::string &str);

  void apply_char(std::string &str, void (Vectorizer::*foo)(char &c)) {
    for (auto &c : str) {
      (this->*foo)(c); // Call the member function on the current instance
    }
  }

  bool is_stopword(const std::string &str);
  std::set<std::string> word_set(const std::string &str);
  std::map<int, std::vector<int>>
  gen_train(const std::map<int, std::string> &vocab, const std::string &corpus);

  std::vector<std::string> tokenizer(const std::string &str);

  // Char Manipu. Funcs.
  char to_lowercase(char &c) { return (tolower(c)); }

  void to_lowercase_inplace(char &c) { c = to_lowercase(c); }
};

const std::vector<std::string> stopwords = {
    "i",          "me",        "my",      "myself", "we",         "our",
    "ours",       "ourselves", "you",     "your",   "yours",      "yourself",
    "yourselves", "he",        "him",     "his",    "himself",    "she",
    "her",        "hers",      "herself", "it",     "its",        "itself",
    "they",       "them",      "their",   "theirs", "themselves", "what",
    "which",      "who",       "whom",    "this",   "that",       "these",
    "those",      "am",        "is",      "are",    "was",        "were",
    "be",         "been",      "being",   "have",   "has",        "had",
    "having",     "do",        "does",    "did",    "doing",      "a",
    "an",         "the",       "and",     "but",    "if",         "or",
    "because",    "as",        "until",   "while",  "of",         "at",
    "by",         "for",       "with",    "about",  "against",    "between",
    "into",       "through",   "during",  "before", "after",      "above",
    "below",      "to",        "from",    "up",     "down",       "in",
    "out",        "on",        "off",     "over",   "under",      "again",
    "further",    "then",      "once",    "here",   "there",      "when",
    "where",      "why",       "how",     "all",    "any",        "both",
    "each",       "few",       "more",    "most",   "other",      "some",
    "such",       "no",        "nor",     "not",    "only",       "own",
    "same",       "so",        "than",    "too",    "very",       "s",
    "t",          "can",       "will",    "just",   "don",        "should",
    "now"};
