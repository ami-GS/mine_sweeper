#include <iostream>
#include <sstream>
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
    std::stringstream out, tmp;
    std::string header;
    while (header.length() < (int)log10((double)height)+2) {header += " ";}
    for (int c = 0; c < width; c++) {
        tmp << " " << c+1;
        while (tmp.str().length() < 4) {tmp << " ";}
        header += tmp.str();
        tmp.str("");
    }
    out << header + "\n";
    for (int r = 1; r < height+1; r++) {
        tmp << r;
        while (tmp.str().length() < (int)log10((double)height)+2) {tmp << " ";}
        out << tmp.str();
        tmp.str("");
        for (int c = 1; c < width+1; c++) {
            if (-1 <= ww[r][c] && ww[r][c] <= 8) {
                out << CLOSED;
            } else if (ww[r][c] == 10) {
                out << OPENED;
            } else if (10 < ww[r][c]) {
                out << "_" << ww[r][c]-10 << "_";
            } else if (ww[r][c] == 9) {
                out << MINE;
            }
            out << " ";
        }
        if (r < height) {
            out << "\n";
        }
    }

    return out.str() + ">> ";
}

void InputLoop(Field* f) {
    std::string input, header;
    std::vector<std::string> strVec;
    int r, c;
    while (1) {
        std::cout << header << "\n" << f->FieldString() << std::flush;
        std::cin >> input; // need split
        strVec = Split(input, ",");
        for (int i = 0; i < 2; i++) {
            std::cout << strVec[i] << std::endl;
        }
        if (strVec.size() != 2) {
            std::cout << "\x1b[2J\n2 values should be input" << std::endl;            
        } else {
            r = std::stoi(strVec[0]);
            c = std::stoi(strVec[1]);
            if (0 < r && r <= f->height && 0 < c && c <= f->width) {
                
            }
        }
        //for (int i = 0; i < 2; i++) {
        //std::cout << ans[i] << std::endl;
        //}
        //delete [] ans;
        
        }
}

int main() {
    Field *f1;
    f1 = new Field(10,10,10);
    InputLoop(f1);
    return 0;
}
