/**
 * \file dnn/test/cuda/fixture.h
 * MegEngine is Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Copyright (c) 2014-2020 Megvii Inc. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT ARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */
#pragma once
#include <gtest/gtest.h>
#include "test/common/fix_gtest_on_platforms_without_exception.inl"

#include "megdnn/handle.h"
#include "megcore_cdefs.h"

#include <memory>

namespace megdnn {
namespace test {

class CUDA : public ::testing::Test {
public:
    void SetUp() override;
    void TearDown() override;

    Handle* handle_cuda() { return m_handle_cuda.get(); }
    Handle* handle_naive();

private:
    std::unique_ptr<Handle> m_handle_naive;
    std::unique_ptr<Handle> m_handle_cuda;
};

//! cuda test fixture with AsyncErrorInfo
class CUDA_ERROR_INFO : public ::testing::Test {
public:
    void SetUp() override;
    void TearDown() override;

    Handle* handle_cuda() { return m_handle_cuda.get(); }

    megcore::AsyncErrorInfo get_error_info();

private:
    megcore::AsyncErrorInfo* m_error_info_dev;
    std::unique_ptr<Handle> m_handle_cuda;
};

}  // namespace test
}  // namespace megdnn

// vim: syntax=cpp.doxygen
