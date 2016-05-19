#include <hilbert/hilbert.h>
#include <test/test_helper.h>
#include <gtest/gtest.h>
#include <memory>

namespace {

template <typename T>
struct Vals {
    T n, idx, x, y;
};

class HilbertTest : public ::testing::TestWithParam<Vals<uint64_t> > {
public:
    virtual void SetUp() {
        vals_ = std::make_unique<Vals<uint64_t> >(GetParam());
    }
protected:
    std::unique_ptr<Vals<uint64_t> > vals_;
};

TEST_P(HilbertTest, XYToIndex)
{
    uint64_t idx = hilbertXYToIndex(vals_->n, vals_->x, vals_->y);
    EXPECT_EQ(vals_->idx, idx);
}

TEST_P(HilbertTest, IndexToXY)
{
    uint64_t x, y;
    hilbertIndexToXY(vals_->n, vals_->idx, x, y);
    EXPECT_EQ(vals_->x, x);
    EXPECT_EQ(vals_->y, y);
}

INSTANTIATE_TEST_CASE_P(HilbertTestInst, HilbertTest, ::testing::Values(
    Vals<uint64_t> {3, 43, 7, 6},
    Vals<uint64_t> {4, 11, 3, 2},
    Vals<uint64_t> {7, 3221, 16, 55},
    Vals<uint64_t> {12, 14817202, 2718, 746},
    Vals<uint64_t> {17, 16300445320, 108506, 12538},
    Vals<uint64_t> {20, 356498311480, 62302, 916810},
    Vals<uint64_t> {22, 13551291030207, 4154631, 1203392},
    Vals<uint64_t> {24, 74487931704934, 1530880, 8395626},
    Vals<uint64_t> {26, 1780052725245042, 17935846, 64840650},
    Vals<uint64_t> {30, 749591077725015621, 905608972, 1049443111},
    Vals<uint64_t> {32, 6392537371738903748, 712335866, 3971717520}
));

class HilbertInverseTest : public ::testing::TestWithParam<int> {
    virtual void SetUp() {
    }
};

TEST_P(HilbertInverseTest, IndexXYIndex)
{
    uint64_t n = static_cast<uint64_t>(GetParam());
    uint64_t idx = random_idx(n);
    uint64_t x, y;
    hilbertIndexToXY(n, idx, x, y);
    EXPECT_EQ(idx, hilbertXYToIndex(n, x, y));
};

TEST_P(HilbertInverseTest, XYIndexXY)
{
    uint64_t n = static_cast<uint64_t>(GetParam());
    auto xy = random_xy(n);
    uint64_t idx = hilbertXYToIndex(n, xy.first, xy.second);
    uint64_t x, y;
    hilbertIndexToXY(n, idx, x, y);
    EXPECT_EQ(xy.first, x);
    EXPECT_EQ(xy.second, y);
};

INSTANTIATE_TEST_CASE_P(HilbertInverseTestInst, HilbertInverseTest, ::testing::Range(1, 33));

} // namespace {}
