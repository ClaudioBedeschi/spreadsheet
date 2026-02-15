#include <gtest/gtest.h>
#include "../src/Spreadsheet.h"
#include "../src/FunctionFactory.h"
#include "../src/Sum.h"
#include "../src/Cell.h"

class SpreadsheetTest : public ::testing::Test {
protected:
	void SetUp() override {
		sheet = std::make_unique<Spreadsheet>(3, 3);
	}
	std::unique_ptr<Spreadsheet> sheet;
};

TEST_F(SpreadsheetTest, Constructor) {
	ASSERT_EQ(sheet->getSizeR(), 3);
	ASSERT_EQ(sheet->getSizeC(), 3);
	EXPECT_EQ(sheet->getCellValue(0,0), 0.0);
}

TEST_F(SpreadsheetTest, CellValidity) {
	EXPECT_TRUE(sheet->isValidCell(0,0));
	EXPECT_TRUE(sheet->isValidCell(2,2));
	EXPECT_FALSE(sheet->isValidCell(-1,0));
	EXPECT_FALSE(sheet->isValidCell(3,0));
	EXPECT_FALSE(sheet->isValidCell(0,3));
}

TEST_F(SpreadsheetTest, SetGetValue) {
	sheet->setCellValueFromUser(1,1,5.0);
	EXPECT_EQ(sheet->getCellValue(1,1), 5.0);

	ASSERT_THROW(sheet->setCellValueFromUser(3,3,5.0), std::runtime_error);
	ASSERT_THROW(sheet->getCellValue(3,0), std::logic_error);
}

TEST_F(SpreadsheetTest, DependenciesAndCalc) {
	sheet->setCellValueFromUser(0,0,10);
	sheet->setCellValueFromUser(0,1,20);
	sheet->setCellDependencies(1,1,0,0,0,1);
	sheet->setCellFunction(1,1,"max");

	sheet->makeCellComputation(1,1);
	ASSERT_EQ(sheet->getCellValue(1,1), 20.0);
}
