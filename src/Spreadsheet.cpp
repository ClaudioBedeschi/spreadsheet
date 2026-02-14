#include "Spreadsheet.h"

/* Using rows and columns instead of ys and xs because
 * - avoids confusion between the two
 * - they go in the order one expects,
 *   both in accessing elements of containers and in cycles
 *
 * Whereas you would have (y, x), which is correct but confusing;
 * or you could use x for rows and y for columns, which feels wrong;
 * or you could have a vector of vertical vectors, which is not how you read.
 */

Spreadsheet::Spreadsheet(const int r, const int c) : sizeR {r}, sizeC {c} {	// Creates an empty spreadsheet
	std::vector<std::unique_ptr<Cell>> tmpRow;
	for(int row=0; row<sizeR; row++) {
		for(int col=0; col<sizeC; col++)
			tmpRow.emplace_back(new Cell());
		sheet.push_back(std::move(tmpRow));
		tmpRow.clear();
	}
}

bool Spreadsheet::isValidCell(const int r, const int c) const {
	if(0<=r && r<sizeR && 0<=c && c<=sizeC)
		return true;
}

void Spreadsheet::setCellValueFromUser(const int r, const int c, const double v) const {
	if(isValidCell(r,c))
		sheet[r][c]->setRawValueFromUser(v);
}

void Spreadsheet::setCellFunction(const int r, const int c, const std::string& functionName) const {
	if(isValidCell(r,c))
		sheet[r][c]->setFunction(functionName);
}

double Spreadsheet::getCellValue(const int r, const int c) {
	if(isValidCell(r,c))
		return sheet[r][c]->getValue();
}

void Spreadsheet::setCellDependencies(const int resultR, const int resultC, int startR, int endR, int startC, int endC) const
{
	if(isValidCell(resultR,resultC) && isValidCell(startR,startC) && isValidCell(endR,endC)) {
		int tmp;	// Making sure we can iterate
		if(startR>endR) {
			tmp = startR;
			startR = endR;
			endR = tmp;
		}
		if(startC>endC) {
			tmp = startC;
			startC = endC;
			endC = tmp;
		}

		std::list<Cell*> dependencies;
		for(int row=startR; row<=endR; row++) {
			for(int col=startC; col<=endC; col++)
				dependencies.push_back(sheet[row][col].get());
		}
		sheet[resultR][resultC]->setDependencies(dependencies);
	}
}
