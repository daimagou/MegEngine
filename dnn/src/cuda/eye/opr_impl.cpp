/**
 * \file dnn/src/cuda/eye/opr_impl.cpp
 * MegEngine is Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Copyright (c) 2014-2020 Megvii Inc. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT ARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */
#include "src/cuda/eye/opr_impl.h"

#include "src/cuda/eye/eye.cuh"
#include "src/cuda/utils.h"

namespace megdnn {
namespace cuda {

void EyeImpl::exec(_megdnn_tensor_out dst, _megdnn_workspace workspace)
{
    check_exec(dst.layout, workspace.size);
#define cb(DType) \
    if (dst.layout.dtype.enumv() == DTypeTrait<DType>::enumv) { \
        using ctype = typename DTypeTrait<DType>::ctype; \
        eye::exec_internal<ctype>(dst.ptr<ctype>(), \
                dst.layout.shape[0], dst.layout.shape[1], \
                param().k, \
                cuda_stream(handle())); \
    }
    MEGDNN_FOREACH_COMPUTING_DTYPE(cb)
#undef cb
}

} // namespace cuda
} // namespace megdnn
// vim: syntax=cpp.doxygen foldmethod=marker foldmarker=f{{{,f}}}
