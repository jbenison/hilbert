#include <hilbert/hilbert.h>
#include <test/test_helper.h>
#include <gtest/gtest.h>
#include <cstdint>
#include <memory>
#include <utility>

namespace {

template <typename T>
struct Vals {
    T n, idx, x, y;
};

class HilbertTest : public ::testing::TestWithParam<Vals<std::uint64_t>> {
public:
    virtual void SetUp() {
        vals_ = std::make_unique<Vals<std::uint64_t>>(GetParam());
    }
protected:
    std::unique_ptr<Vals<std::uint64_t>> vals_;
};

TEST_P(HilbertTest, XYToIndex)
{
    std::uint64_t idx = hilbert::xy_to_index(vals_->n, vals_->x, vals_->y);
    EXPECT_EQ(vals_->idx, idx);
}

TEST_P(HilbertTest, IndexToXY)
{
    std::pair<std::uint64_t, std::uint64_t> xy_res = hilbert::index_to_xy(vals_->n, vals_->idx);
    EXPECT_EQ(vals_->x, xy_res.first);
    EXPECT_EQ(vals_->y, xy_res.second);
}

INSTANTIATE_TEST_CASE_P(HilbertTestInst, HilbertTest, ::testing::Values(
    Vals<std::uint64_t> {3, 43, 7, 6},
    Vals<std::uint64_t> {4, 11, 3, 2},
    Vals<std::uint64_t> {7, 3221, 16, 55},
    Vals<std::uint64_t> {12, 14817202, 2718, 746},
    Vals<std::uint64_t> {17, 16300445320, 108506, 12538},
    Vals<std::uint64_t> {20, 356498311480, 62302, 916810},
    Vals<std::uint64_t> {22, 13551291030207, 4154631, 1203392},
    Vals<std::uint64_t> {24, 74487931704934, 1530880, 8395626},
    Vals<std::uint64_t> {26, 1780052725245042, 17935846, 64840650},
    Vals<std::uint64_t> {30, 749591077725015621, 905608972, 1049443111},
    Vals<std::uint64_t> {32, 6392537371738903748, 712335866, 3971717520}
));

class HilbertInverseTest : public ::testing::TestWithParam<int> {
    virtual void SetUp() {
    }
};

TEST_P(HilbertInverseTest, IndexXYIndex)
{
    std::uint64_t n = static_cast<std::uint64_t>(GetParam());
    std::uint64_t idx = random_idx(n);
    std::pair<std::uint64_t, std::uint64_t> xy_res = hilbert::index_to_xy(n, idx);
    EXPECT_EQ(idx, hilbert::xy_to_index(n, xy_res.first, xy_res.second));
};

TEST_P(HilbertInverseTest, XYIndexXY)
{
    std::uint64_t n = static_cast<std::uint64_t>(GetParam());
    std::pair<std::uint64_t, std::uint64_t> xy = random_xy(n);
    std::uint64_t idx = hilbert::xy_to_index(n, xy.first, xy.second);
    std::pair<std::uint64_t, std::uint64_t> xy_res = hilbert::index_to_xy(n, idx);
    EXPECT_EQ(xy.first, xy_res.first);
    EXPECT_EQ(xy.second, xy_res.second);
};

INSTANTIATE_TEST_CASE_P(HilbertInverseTestInst, HilbertInverseTest, ::testing::Range(1, 33));

} // namespace {}
