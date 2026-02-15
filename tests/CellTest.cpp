#include "gtest/gtest.h"
#include "../src/Cell.h"
#include "../src/FunctionFactory.h"

class CellTest : public ::testing::Test {
protected:
	void SetUp() override {
		c1 = std::make_unique<Cell>();
		c2 = std::make_unique<Cell>(5.0);
	}
	std::unique_ptr<Cell> c1;
	std::unique_ptr<Cell> c2;
};

TEST_F(CellTest, DefaultConstructor) {
	EXPECT_EQ(c1->getValue(), 0);
}

TEST_F(CellTest, ValueConstructor) {
	EXPECT_EQ(c2->getValue(), 5.0);
}

TEST_F(CellTest, SetRawValueFromUser) {
	c1->setRawValueFromUser(5.0);
	EXPECT_EQ(c1->getValue(), 5.0);
}

TEST_F(CellTest, SetMathComputedValue) {
	c1->setMathComputedValue(5.0);
	EXPECT_EQ(c1->getValue(), 5.0);
}

TEST_F(CellTest, TestDependenciesNotification) {
	c1->setDependencies({c2.get()});
	c1->setFunction("sum");
	bool notified = false;
	class TestObserver : public Cell {
	public:
		std::shared_ptr<Function> function = FunctionFactory::assignFunction("sum");
		bool* flag;
		explicit TestObserver(bool* f) : flag(f) {}
		void update(Subject*) override {
			*flag = true;
		}
	} observer(&notified);

	c1->subscribe(&observer);

	c2->setRawValueFromUser(5.0);

	ASSERT_TRUE(notified);

	notified = false;
	c1->unsubscribe(&observer);
	c1->notify(nullptr);
	EXPECT_FALSE(notified);
}

TEST_F(CellTest, ComputeAndNotify) {
	c2->setRawValueFromUser(2);
	c1->setFunction("sum");
	c1->setDependencies({c2.get()});
	c1->computeAndNotify();
	EXPECT_EQ(c1->getValue(), 2.0);
}

TEST_F(CellTest, UpdateCycleDetection) {
	c1->setDependencies({c2.get()});
	c1->setFunction("max");
	c2->setDependencies({c1.get()});
	c2->setFunction("min");

	EXPECT_THROW(c1->update(c1.get()), std::runtime_error);
}
