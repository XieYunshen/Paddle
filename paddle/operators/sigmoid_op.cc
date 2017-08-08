/* Copyright (c) 2016 PaddlePaddle Authors. All Rights Reserve.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */

#include "paddle/operators/sigmoid_op.h"
namespace paddle {
namespace operators {

class SigmoidOp : public OperatorWithKernel {
 protected:
  void InferShape(const InferShapeContext &ctx) const override {
    ctx.Output<Tensor>("Y")->Resize(ctx.Input<Tensor>("X")->dims());
  }
};

class SigmoidOpMaker : public OpProtoAndCheckerMaker {
 public:
  SigmoidOpMaker(OpProto *proto, OpAttrChecker *op_checker)
      : OpProtoAndCheckerMaker(proto, op_checker) {
    AddInput("X", "sigmoid input");
    AddOutput("Y", "sigmoid output");
    AddComment("Sigmoid function");
  }
};

class SigmoidOpGrad : public OperatorWithKernel {
 protected:
  void InferShape(const InferShapeContext &ctx) const override {
    ctx.Output<Tensor>(0)->Resize(ctx.Input<Tensor>(0)->dims());
  }
};

}  // namespace operators
}  // namespace paddle

REGISTER_OP(sigmoid, ops::SigmoidOp, ops::SigmoidOpMaker);
REGISTER_GRADIENT_OP(sigmoid, sigmoid_grad, ops::SigmoidOpGrad);

REGISTER_OP_CPU_KERNEL(sigmoid, ops::SigmoidKernel<ops::CPUPlace, float>);
REGISTER_OP_CPU_KERNEL(sigmoid_grad,
                       ops::SigmoidGradKernel<ops::CPUPlace, float>);
