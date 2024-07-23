#include <ATen/core/interned_strings.h>
#include <c10/util/Optional.h>
#include <cstddef>
#include <torch/data.h>
#include <torch/data/datasets/base.h>
#include <torch/data/example.h>
#include <torch/torch.h>
#include <torch/types.h>
#include <vector>

class Corpus : torch::data::datasets::Dataset<Corpus> {

public:
  Corpus(std::vector<torch::Tensor> context, std::vector<torch::Tensor> center)
      : context_(context), center_(center){};

  torch::data::Example<> get(size_t index) override {
    return {context_[index], center_[index]};
  };
  torch::optional<size_t> size() const override { return center_.size(); };

private:
  std::vector<torch::Tensor> context_;
  std::vector<torch::Tensor> center_;
};
