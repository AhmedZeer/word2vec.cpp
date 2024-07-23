#include <torch/nn/module.h>
#include <torch/nn/modules/embedding.h>
#include <torch/nn/modules/linear.h>
#include <torch/nn/options/embedding.h>
#include <torch/nn/options/linear.h>
#include <torch/torch.h>

class CBOW : torch::nn::Module {

public:
  CBOW(int vocab_size, int embed_size = 256)
      : vocab_size_(vocab_size), embed_size_(embed_size) {
    embed = torch::nn::Embedding(
        torch::nn::EmbeddingOptions(vocab_size_, embed_size_).max_norm(1));
    ln = torch::nn::Linear(torch::nn::LinearOptions(embed_size_, 1));
  };
  void train(size_t n_epochs);
  void eval();

private:
  torch::nn::Embedding embed;
  torch::nn::Linear ln;
  torch::Tensor forward(torch::Tensor x);
  size_t vocab_size_;
  size_t embed_size_;
};

torch::Tensor CBOW::forward(torch::Tensor x) {
  x = embed->forward(x);
  x = ln->forward(x);
  return x;
}

int main(int argc, char *argv[]) {

  auto cbow = CBOW(3, 3);

  return 0;
}
