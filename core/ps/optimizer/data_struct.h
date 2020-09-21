// Copyright (c) 2020, Qihoo, Inc.  All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef TENSORNET_OPTIMIZER_DATA_STRUCT_H_
#define TENSORNET_OPTIMIZER_DATA_STRUCT_H_

#include <stdint.h>

namespace tensornet {

union UnionWeight {
    float* p = nullptr;
    float v[2];
};

struct SparseGradInfo {
    SparseGradInfo()
        : sign(0)
        , batch_show(0)
        , grad(nullptr) {
    }
    uint64_t sign;
    int batch_show;
    float* grad;
};

} // namespace tensornet {

#endif // !TENSORNET_OPTIMIZER_DATA_STRUCT_H_
