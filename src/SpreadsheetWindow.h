#ifndef SPREADSHEETWINDOW_H
#define SPREADSHEETWINDOW_H
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "Spreadsheet.h"

class SpreadsheetWindow : public QWidget {
public:
	SpreadsheetWindow(int rows, int cols, QWidget* parent = nullptr);

	struct ParsedExpr {
		QString function {};
		int startR {}, endR {}, startC {}, endC {};
		bool valid = false;
	};
private:

	void setupWindow();
	void setupTopBar();
	void setupTable();
	void setupLayout();

	void refreshTable();
	void handleCellChanges();
	static ParsedExpr parseExpr(const QString& text);


	int rows, cols;
	Spreadsheet sheet;

	QTableWidget* table {};
	QTableWidgetItem* item {};

	QVBoxLayout* vLayout {};
	QWidget* topBar {};
	QPushButton* quitButton {};

	static const QRegularExpression separators;
};
#endif // SPREADSHEETWINDOW_H
