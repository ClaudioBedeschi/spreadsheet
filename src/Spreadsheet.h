#ifndef SPREADSHEET_H
#define SPREADSHEET_H
#include <string>
#include <vector>
#include <memory>

#include "Cell.h"

class Spreadsheet {
public:
	Spreadsheet(int r, int c);

	// Resizing does not make sense for now

	int getSizeR() const {
		return sizeR;
	}

	int getSizeC() const {
		return sizeC;
	}

	bool isValidCell(int r, int c) const;

	void setCellValueFromUser(int r, int c, double v) const;

	void setCellFunction(int r, int c, const std::string& functionName) const;

	void makeCellComputation(int r, int c) const;

	double getCellValue(int r, int c) const;

	void setCellDependencies(int resultR, int resultC, int startR, int endR, int startC, int endC) const;

	~Spreadsheet() = default;
private:
	int sizeR, sizeC;
	std::vector<std::vector<std::unique_ptr<Cell>>> sheet;
};
#endif // SPREADSHEET_H
