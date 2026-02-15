#include <gtest/gtest.h>
#include "../src/Min.h"
#include "../src/Cell.h"

class MinTest : public ::testing::Test {
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

TEST_F(MinTest, ComputeMin) {
	c0->setDependencies({c1.get(), c2.get(), c3.get()});
	Min min;
	min.calculate(*c0);

	EXPECT_EQ(c0->getValue(), -1.0);
}

TEST_F(MinTest, ThrowOnEmpty) {
	Min min;
	c0->setDependencies({});

	ASSERT_THROW(min.calculate(*c0), std::logic_error);
}
