#include <random>

class Field {
public:
    int width;
    int height;
    int **ww;
    Field(int width, int height, int mineNum) : width(width), height(height) {
        ww = new int*[height];
        for (int i = 0; i < height+2; i++) {
            ww[i] = new int[width+2];
            for (int j = 0; j < width+2; j++) {
                ww[i][j] = 0; // zero init
            }
        }
        int *tmp = new int[width*height];
        for (int i = 0; i < width*height; i++) {
            tmp[i] = i;
        }
        std::random_shuffle(&tmp[0], &tmp[width*height]); //end must be width * height, not width * height - 1
        //std::random_shuffle(std::begin(a), std::end(a)); // c++11
        int **pos;
        pos = new int*[mineNum];

        for (int i = 0; i < mineNum; i++) {
            pos[i] = new int[2];
            pos[i][0] = tmp[i]/width+1;
            pos[i][1] = tmp[i]%width+1;
            ww[pos[i][0]-1][pos[i][1]-1] += 1;
            ww[pos[i][0]-1][pos[i][1]] += 1;
            ww[pos[i][0]-1][pos[i][1]+1] += 1;
            ww[pos[i][0]][pos[i][1]-1] += 1;
            ww[pos[i][0]][pos[i][1]+1] += 1;
            ww[pos[i][0]+1][pos[i][1]-1] += 1;
            ww[pos[i][0]+1][pos[i][1]] += 1;
            ww[pos[i][0]+1][pos[i][1]+1] += 1;
        }
        for (int i = 0; i < mineNum; i++) {
            ww[pos[i][0]][pos[i][1]] = -1;
        }

        delete [] tmp;
        for (int i = 0; i < mineNum; i++) {
            delete [] pos[i];
        }
        delete [] pos;
    }
    void Open(int row, int column);
    void AllOpen();
    void RecursiveOpen(int row, int column);
    int Choose(int row, int column);
    std::string FieldString();
    ~Field() {
        for (int i = 0; i < height; i++) {
            delete [] ww[i];
        }
        delete [] ww;
    }
};

const std::string CLOSED = "[ ]";
const std::string OPENED = "___";
const std::string MINE = "_*_";

std::string* Split(std::string str, std::string substr) {
    std::string*  ans = new std::string[3]; // ?
    std::string tmp;
    int num, loc;
    num = 0;
    while (1) {
        loc = str.find(substr, 0);
        if (loc == std::string::npos) {
            break;
        }
        for (int i = 0; i < loc+1; i++) {
            tmp += str.at(i);
        }
        ans[num] = tmp;
    }
    return ans;
}
