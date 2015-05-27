#include <iostream>
#include <string.h>
#include <math.h>
#include "field.h"

void Field::Open(int row, int column) {
  ww[row][column] += 10;
}
void Field::AllOpen() {
  for (int r = 1; r < height+1; r++) {
    for (int c = 1; c < width+1; c++) {
      Open(r, c);
    }
  }
}

void Field::RecursiveOpen(int row, int column) {
  Open(row, column);
  if (row == 0 || row == height+1 || column == 0 || column == width+1) {
    return;
  }
  if (0 <= ww[row-1][column-1] && ww[row-1][column-1] <= 8) {
    if (ww[row-1][column-1] == 0) {
      RecursiveOpen(row-1, column-1);
    } else {
      Open(row-1, column-1);
    }
  }
  if (0 <= ww[row-1][column] && ww[row-1][column] <= 8) {
    if (ww[row-1][column] == 0) {
      RecursiveOpen(row-1, column);
    } else {
      Open(row-1, column);
    }
  }
  if (0 <= ww[row-1][column+1] && ww[row-1][column+1] <= 8) {
    if (ww[row-1][column+1] == 0) {
      RecursiveOpen(row-1, column+1);
    } else {
      Open(row-1, column+1);
    }
  }
  if (0 <= ww[row][column-1] && ww[row][column-1] <= 8) {
    if (ww[row][column-1] == 0) {
      RecursiveOpen(row, column-1);
    } else {
      Open(row, column-1);
    }
  }
  if (0 <= ww[row][column+1] && ww[row][column+1] <= 8) {
    if (ww[row][column+1] == 0) {
      RecursiveOpen(row, column+1);
    } else {
      Open(row, column+1);
    }
  }
  if (0 <= ww[row+1][column-1] && ww[row+1][column-1] <= 8) {
    if (ww[row+1][column-1] == 0) {
      RecursiveOpen(row+1, column-1);
    } else {
      Open(row+1, column-1);
    }
  }
  if (0 <= ww[row+1][column] && ww[row+1][column] <= 8) {
    if (ww[row+1][column] == 0) {
      RecursiveOpen(row+1, column);
    } else {
      Open(row+1, column);
    }
  }
  if (0 <= ww[row+1][column+1] && ww[row+1][column+1] <= 8) {
    if (ww[row+1][column+1] == 0) {
      RecursiveOpen(row+1, column+1);
    } else {
      Open(row+1, column+1);
    }
  }
}

int Field::Choose(int row, int column) {
  row += 1;
  column += 1;
  if (ww[row][column] == 0) {
    RecursiveOpen(row, column);
  } else if (0 < ww[row][column] && ww[row][column] <= 8) {
    Open(row, column);
  } else if (ww[row][column] == -1){
    AllOpen();
    return 1;
  }
  return -1;
}

std::string Field::FieldString() {
  std::string out;
  std::string header;
  std::string tmp;
  while (header.length() < (int)log10((double)height)+2) {header += " ";}
  std::cout << "1" << std::endl;
  for (int c = 0; c < width; c++) {
    tmp = " %s", c+1;
    while (tmp.length() < 4) {tmp += " ";}
    header += tmp;
  }
  out = header + "\n";
  for (int r = 1; r < height+1; r++) {
    tmp = "%d", r;
    while (tmp.length() < (int)log10((double)height)+2) {tmp += " ";}
    out += tmp;
    for (int c = 1; c < width+1; c++) {
      if (-1 <= ww[r][c] && ww[r][c] <= 8) {
	out += "[ ]";
      } else if (ww[r][c] == 10) {
	out += "___";
      } else if (10 < ww[r][c]) {
	out += "_%d_", ww[r][c]-10;
      } else if (ww[r][c] == 9) {
	out += "_*_";
      }
      out += " ";
    }
    if (r < height) {
      out += "\n";
    }
  }
  
  return "%s>> ", out;
}

int main() {
  Field *f1;
  f1 = new Field(10,10,10);
  for (int i = 1; i < 11; i++) {
    for (int j = 1; j < 11; j++) {
      std::cout << f1->ww[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << f1->FieldString() << std::endl;
  std::cout << "aiueo\n" << std::endl;
  return 0;
}
