#include <gtest/gtest.h>
#include "../src/FunctionFactory.h"
#include "../src/Cell.h"
#include "../src/Sum.h"
#include "../src/Min.h"
#include "../src/Max.h"
#include "../src/Mean.h"

TEST(FunctionFactoryTest, AssignSum) {
	const auto f = FunctionFactory::assignFunction("sum");
	ASSERT_NE(f, nullptr);
	EXPECT_NE(dynamic_cast<Sum*>(f.get()), nullptr);
}

TEST(FunctionFactoryTest, AssignMin) {
	const auto f = FunctionFactory::assignFunction("min");
	ASSERT_NE(f, nullptr);
	EXPECT_NE(dynamic_cast<Min*>(f.get()), nullptr);
}

TEST(FunctionFactoryTest, AssignMax) {
	const auto f = FunctionFactory::assignFunction("max");
	ASSERT_NE(f, nullptr);
	EXPECT_NE(dynamic_cast<Max*>(f.get()), nullptr);
}

TEST(FunctionFactoryTest, AssignMean) {
	const auto f = FunctionFactory::assignFunction("mean");
	ASSERT_NE(f, nullptr);
	EXPECT_NE(dynamic_cast<Mean*>(f.get()), nullptr);
}

TEST(FunctionFactoryTest, UnknownFunction) {
	EXPECT_THROW(FunctionFactory::assignFunction("unknown"), std::runtime_error);
}
