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
            if (-1 <= ww[r][c] && ww[r][c] <= 8) {
                Open(r, c);
            }
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
    if (ww[row][column] == 0) {
        RecursiveOpen(row, column);
    } else if (0 < ww[row][column] && ww[row][column] <= 8) {
        Open(row, column);
    } else if (ww[row][column] == -1){
        AllOpen();
        return -1;
    }
    return 1;
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
    std::string input;
    std::stringstream header;
    std::vector<std::string> strVec;
    int r, c;
    while (1) {
        std::cout << header.str() << "\n" << f->FieldString() << std::flush;
        header.str("");
        std::cin >> input; // need split
        strVec = Split(input, ",");
        if (strVec.size() != 2) {
            header << "\x1b[2J\n2 values should be input";
        } else {
            r = std::stoi(strVec[0]);
            c = std::stoi(strVec[1]);
            if (0 < r && r <= f->height && 0 < c && c <= f->width) {
                if (f->Choose(r, c)) {
                    header << "\x1b[2J";
                } else {
                    std::cout << "\x1b[2J========== GAME OVER ==========" << std::endl;
                    std::cout << header.str() << "\n" << f->FieldString() << std::flush;
                    break;
                }
            } else {
                header << "\x1b[2J2 values should be input (1 <= height <= " << f->height << ", 1 <= width <= " << f->width << ")";
            }
        }
    }
}

void PlayGame() {
    std::string input;
    Field *f;
    int h, w, m;
    std::vector<std::string> strVec;

    std::cout << "Input height, width, (num of mine) (e.g : 8,8,(,9))\n>> " << std::flush;
    while (1) {
        std::cin >> input;
        strVec = Split(input, ",");
        if (strVec.size() == 2 || strVec.size() == 3) {
            w = std::stoi(strVec[0]);
            h = std::stoi(strVec[1]);
            if (strVec.size() == 2) {
                m = w * h / 4;
            } else {
                m = std::stoi(strVec[2]);
            }

            if (w == 0 || h == 0 || m == 0) {
                std::cout << "Please input 2 or 3 numerical values (value > 0)";
            }
            f = new Field(h, w, m);
            break;
        } else {
            std::cout << "Please input 2 or 3 numerical values (value > 0)";
        }
    }
    InputLoop(f);
}

int main() {
    PlayGame();
    return 0;
}
