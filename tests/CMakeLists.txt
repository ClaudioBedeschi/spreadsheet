add_subdirectory(lib/googletest-main)

set(TEST_SOURCE_FILES
		runAllTests.cpp
		CellTest.cpp
		FunctionFactoryTest.cpp
		MaxTest.cpp
		MeanTest.cpp
		MinTest.cpp
		SumTest.cpp
		SpreadsheetTest.cpp
		SpreadsheetWindowTest.cpp
)

add_executable(runSpreadsheetTests
		${TEST_SOURCE_FILES}
)

target_link_libraries(runSpreadsheetTests
		PRIVATE
		GTest::gtest
		core
)

add_test(NAME runSpreadsheetTests COMMAND runSpreadsheetTests)
