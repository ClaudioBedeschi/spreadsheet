#include <gtest/gtest.h>
#include "../src/Mean.h"
#include "../src/Cell.h"

class MeanTest : public ::testing::Test {
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

TEST_F(MeanTest, ComputeMean) {
	c0->setDependencies({c1.get(), c2.get(), c3.get()});
	Mean mean;
	mean.calculate(*c0);

	EXPECT_EQ(c0->getValue(), 2.0);
}

TEST_F(MeanTest, ThrowOnEmpty) {
	Mean mean;
	c0->setDependencies({});

	ASSERT_THROW(mean.calculate(*c0), std::logic_error);
}
