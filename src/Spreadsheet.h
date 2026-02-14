#ifndef SPREADSHEET_H
#define SPREADSHEET_H
#include <string>
#include <vector>
#include <memory>

#include "Cell.h"

class Spreadsheet {
public:
	Spreadsheet(int r, int c);
	/* Resizing would not make sense
	void setSizeR(const int r) {
		sizeR = r;
	} */
	int getSizeR() const {
		return sizeR;
	}
	/* Resizing would not make sense
	void setSizeC(const int c) {
		sizeC = c;
	} */
	int getSizeC() const {
		return sizeC;
	}

	bool isValidCell(int r, int c) const;

	void setCellValueFromUser(int r, int c, double v) const;

	void setCellFunction(int r, int c, const std::string& functionName) const;

	double getCellValue(int r, int c);

	void setCellDependencies(int resultR, int resultC, int startR, int endR, int startC, int endC) const;

	~Spreadsheet() = default;
private:
	int sizeR, sizeC;
	std::vector<std::vector<std::unique_ptr<Cell>>> sheet;
};
#endif // SPREADSHEET_H
