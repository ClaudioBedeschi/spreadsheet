#include <iostream>
#include <QApplication>

#include "SpreadsheetWindow.h"

int main(int argc, char *argv[])
{
	int rows, cols;
	std::cout << "Enter spreadsheet size (rows columns): \n";
	std::cin >> rows >> cols;

	if (rows>0 && cols>0) {
		QApplication app(argc, argv);

		SpreadsheetWindow window(rows, cols);
		window.show();

		return QApplication::exec();
	}
	std::cerr << "Invalid size";
}
