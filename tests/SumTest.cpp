#include <gtest/gtest.h>
#include "../src/Sum.h"
#include "../src/Cell.h"

class SumTest : public ::testing::Test {
protected:
	void SetUp() override {
		c1 = std::make_unique<Cell>(-1.0);
		c2 = std::make_unique<Cell>(0.0);
		c3 = std::make_unique<Cell>(7.0);

		c0 = std::make_unique<Cell>();
	}

	std::unique_ptr<Cell> c1;
	std::unique_ptr<Cell> c2;
	std::unique_ptr<Cell> c3;
	std::unique_ptr<Cell> c0;
};

TEST_F(SumTest, ComputeSum) {
	c0->setDependencies({c1.get(), c2.get(), c3.get()});
	Sum sum;
	sum.calculate(*c0);

	EXPECT_EQ(c0->getValue(), 6.0);
}

TEST_F(SumTest, ThrowOnEmpty) {
	Sum sum;
	c0->setDependencies({});

	ASSERT_THROW(sum.calculate(*c0), std::logic_error);
}
