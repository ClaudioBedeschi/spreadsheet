#include <QHeaderView>
#include <QLineEdit>
#include <QLabel>

#include "SpreadsheetWindow.h"


SpreadsheetWindow::SpreadsheetWindow(const int rows, const int cols, QWidget* parent)
	: QWidget(parent), rows {rows}, cols {cols}, sheet(rows, cols)
{
	setupWindow();
	setupTopBar();
	setupTable();
	refreshTable();
	handleCellChanges();
	setupLayout();
}

void SpreadsheetWindow::setupWindow() {
	setWindowTitle("Spreadsheet");
	resize(600, 400);
	setMinimumSize(400, 300);
}

void SpreadsheetWindow::setupTopBar() {
	topBar = new QWidget();
	topBar->setStyleSheet("background-color: lightgreen;");
	topBar->setFixedHeight(30);

	quitButton = new QPushButton("X", topBar);
	quitButton->setFixedSize(20, 20);
	quitButton->move(560, 5);
	connect(quitButton, &QPushButton::clicked, this, &QWidget::close);
}

void SpreadsheetWindow::setupTable() {
	table = new QTableWidget(rows, cols, this);
	QStringList rowLabels, colLabels;	// Change labels to start from 0
	for (int i=0; i<rows; i++)
		rowLabels << QString::number(i);
	for (int i=0; i<cols; i++)
		colLabels << QString::number(i);
	table->setVerticalHeaderLabels(rowLabels);
	table->setHorizontalHeaderLabels(colLabels);
	table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	table->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::AnyKeyPressed);
}

void SpreadsheetWindow::refreshTable() {
	for(int r=0; r<rows; r++) {
		for(int c=0; c<cols; c++) {
			const double val = sheet.getCellValue(r,c);
			QString text = (val==0) ? "" : QString::number(val);	// Cells are empty when 0

			item = table->item(r,c);
			if(!item) {	// Table contains no items at startup
				item = new QTableWidgetItem;
				table->setItem(r,c,item);
			}

			table->blockSignals(true);	// Avoid triggering signal loops
			item->setText(text);
			table->blockSignals(false);
		}
	}
}

void SpreadsheetWindow::handleCellChanges() {
	connect(table, &QTableWidget::cellChanged, [=] (const int thisR, const int thisC) {	// Lambda as a slot
		item = table->item(thisR, thisC);
		if(!item) return;

		QString text = item->text();

		if(text.startsWith("=")) {
			const ParsedExpr parsedExpr = parseExpr(text);
			if(parsedExpr.valid) {
				sheet.setCellDependencies(thisR, thisC, parsedExpr.startR, parsedExpr.endR, parsedExpr.startC, parsedExpr.endC);
				sheet.setCellFunction(thisR,thisC,parsedExpr.function.toStdString());
			}
			else
				item->setText("Err: NoExpr");
		}
		else {
			bool ok;
			const double value = text.toDouble(&ok);
			if(ok)
				sheet.setCellValueFromUser(thisR, thisC, value);
			else
				item->setText("Err: Value");
		}

		refreshTable();
	});
}

SpreadsheetWindow::ParsedExpr SpreadsheetWindow::parseExpr(const QString& text) {
	ParsedExpr parsedExpr;
	QString expr = text.mid(1);	// Ditch "="

	const auto leftParen = expr.indexOf('(');
	const auto rightParen = expr.indexOf(')');

	if(leftParen!=-1 && rightParen!=-1 && rightParen>leftParen) {
		const QString args = expr.mid(leftParen+1, rightParen-leftParen-1);	// Ditch "()", extract arguments
		QStringList parts = args.split(separators, Qt::SkipEmptyParts);	// Separate them with regex
		if(parts.size() == 4) {
			bool ok1, ok2, ok3, ok4;	// Check index validity
			parsedExpr.startR = parts[0].toInt(&ok1);
			parsedExpr.endR = parts[1].toInt(&ok2);
			parsedExpr.startC = parts[2].toInt(&ok3);
			parsedExpr.endC = parts[3].toInt(&ok4);
			if(ok1 && ok2 && ok3 && ok4)
				parsedExpr.valid = true;
		}
		expr = expr.left(leftParen).toLower();	// Get function name and make it case-insensitive
		parsedExpr.function = expr;
	}
	return parsedExpr;
}

void SpreadsheetWindow::setupLayout() {
	vLayout = new QVBoxLayout(this);
	vLayout->addWidget(topBar);
	vLayout->addWidget(table);
	setLayout(vLayout);
}

const QRegularExpression SpreadsheetWindow::separators("[,:]");
