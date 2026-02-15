#include <gtest/gtest.h>
#include <QApplication>
#include "../src/SpreadsheetWindow.h"

class SpreadsheetWindowTest : public ::testing::Test {
public:
	static void SetUpTestSuite() {
		int argc = 0;
		char** argv = nullptr;
		app = std::make_unique<QApplication>(argc, argv);
	}
	static void TearDownTestSuite() {
		app.reset();
	}
protected:
	static std::unique_ptr<QApplication> app;

	void SetUp() override {
		window = std::make_unique<SpreadsheetWindow>(3, 3);
	}

	std::unique_ptr<SpreadsheetWindow> window;
};

std::unique_ptr<QApplication> SpreadsheetWindowTest::app = nullptr;

TEST_F(SpreadsheetWindowTest, ValidExpr) {
	SpreadsheetWindow::ParsedExpr parsedExpr = SpreadsheetWindow::parseExpr("=sum(0,1,0,1)");
	ASSERT_TRUE(parsedExpr.valid);
	EXPECT_EQ(parsedExpr.function, "sum");
	EXPECT_EQ(parsedExpr.startR, 0);
	EXPECT_EQ(parsedExpr.endR, 1);
	EXPECT_EQ(parsedExpr.startC, 0);
	EXPECT_EQ(parsedExpr.endC, 1);
}

TEST_F(SpreadsheetWindowTest, InvalidExpr) {
	SpreadsheetWindow::ParsedExpr parsedExpr = SpreadsheetWindow::parseExpr("=sum0,1,0,1");
	EXPECT_FALSE(parsedExpr.valid);

	parsedExpr = SpreadsheetWindow::parseExpr("=sum(0,1,2)");
	EXPECT_FALSE(parsedExpr.valid);

	parsedExpr = SpreadsheetWindow::parseExpr("=sum(a,b,c,d)");
	EXPECT_FALSE(parsedExpr.valid);
}

TEST_F(SpreadsheetWindowTest, QuitButton) {
	auto quitButton = window->findChild<QPushButton*>();
	ASSERT_NE(quitButton, nullptr);
	EXPECT_EQ(quitButton->text(), "X");
}

TEST_F(SpreadsheetWindowTest, RefreshTable) {
	EXPECT_NO_THROW(window->findChild<QTableWidget*>()->blockSignals(true));
}
