#include <gtest/gtest.h>
#include "../src/Max.h"
#include "../src/Cell.h"

class MaxTest : public ::testing::Test {
protected:
	void SetUp() override {
		c1 = std::make_unique<Cell>(-1.0);
		c2 = std::make_unique<Cell>(0.0);
		c3 = std::make_unique<Cell>(6.0);

		c0 = std::make_unique<Cell>();
	}

	std::unique_ptr<Cell> c1;
	std::unique_ptr<Cell> c2;
	std::unique_ptr<Cell> c3;
	std::unique_ptr<Cell> c0;
};

TEST_F(MaxTest, ComputeMax) {
	c0->setDependencies({c1.get(), c2.get(), c3.get()});
	Max max;
	max.calculate(*c0);

	EXPECT_EQ(c0->getValue(), 6.0);
}

TEST_F(MaxTest, ThrowOnEmpty) {
	Max max;
	c0->setDependencies({});

	ASSERT_THROW(max.calculate(*c0), std::logic_error);
}
