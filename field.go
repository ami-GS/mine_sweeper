package mine_sweeper

import (
	"fmt"
	"math"
	"math/rand"
	"strconv"
	"strings"
	"time"
)

type Field struct {
	width  byte
	height byte
	state  [][]int
}

//Field.state == -1 ~ 18
//-1: not open with mine
//0 ~ 8: not open and the number of mine surrounding
//9: open with mine
//10 ~ 18: open and the number of mine surrounding

const ZERO byte = 48

func NewField(width, height, mineNum byte) *Field {
	field := &Field{width, height, [][]int{}}
	field.state = make([][]int, height+2)

	for i := 0; i < int(height)+2; i++ {
		field.state[i] = make([]int, width+2)
	}

	// set mine
	var pos [][2]byte = make([][2]byte, mineNum)
	rand.Seed(time.Now().UTC().UnixNano())
	idx := rand.Perm(int(width * height)) // [0,n)
	fmt.Println(idx)
	for i := 0; i < int(mineNum); i++ {
		pos[i] = [2]byte{(byte(idx[i]) / width) + 1, (byte(idx[i]) % width) + 1}
		// set surround
		field.state[pos[i][0]-1][pos[i][1]-1] += 1
		field.state[pos[i][0]-1][pos[i][1]] += 1
		field.state[pos[i][0]-1][pos[i][1]+1] += 1
		field.state[pos[i][0]][pos[i][1]-1] += 1
		field.state[pos[i][0]][pos[i][1]+1] += 1
		field.state[pos[i][0]+1][pos[i][1]-1] += 1
		field.state[pos[i][0]+1][pos[i][1]] += 1
		field.state[pos[i][0]+1][pos[i][1]+1] += 1
	}
	fmt.Println(pos)
	for i := 0; i < int(mineNum); i++ {
		// put mine
		field.state[pos[i][0]][pos[i][1]] = -1
	}

	return field
}

func (self *Field) Open(row, column byte) {
	self.state[row][column] += 10
}

func (self *Field) AllOpen() {
	var r, c byte
	for r = 1; r < self.height+1; r++ {
		for c = 1; c < self.width+1; c++ {
			if -1 <= self.state[r][c] && self.state[r][c] <= 8 {
				self.Open(r, c)
			}
		}
	}
}

func (self *Field) RecursiveOpen(row, column byte) {
	self.Open(row, column)
	if row == 0 || row == self.height+1 || column == 0 || column == self.width+1 {
		return
	}
	if 0 <= self.state[row-1][column-1] && self.state[row-1][column-1] <= 8 {
		if self.state[row-1][column-1] == 0 {
			self.RecursiveOpen(row-1, column-1)
		} else {
			self.Open(row-1, column-1)
		}
	}
	if 0 <= self.state[row-1][column] && self.state[row-1][column] <= 8 {
		if self.state[row-1][column] == 0 {
			self.RecursiveOpen(row-1, column)
		} else {
			self.Open(row-1, column)
		}
	}
	if 0 <= self.state[row-1][column+1] && self.state[row-1][column+1] <= 8 {
		if self.state[row-1][column+1] == 0 {
			self.RecursiveOpen(row-1, column+1)
		} else {
			self.Open(row-1, column+1)
		}
	}
	if 0 <= self.state[row][column-1] && self.state[row][column-1] <= 8 {
		if self.state[row][column-1] == 0 {
			self.RecursiveOpen(row, column-1)
		} else {
			self.Open(row, column-1)
		}
	}
	if 0 <= self.state[row][column+1] && self.state[row][column+1] <= 8 {
		if self.state[row][column+1] == 0 {
			self.RecursiveOpen(row, column+1)
		} else {
			self.Open(row, column+1)
		}
	}
	if 0 <= self.state[row+1][column-1] && self.state[row+1][column-1] <= 8 {
		if self.state[row+1][column-1] == 0 {
			self.RecursiveOpen(row+1, column-1)
		} else {
			self.Open(row+1, column-1)
		}
	}
	if 0 <= self.state[row+1][column] && self.state[row+1][column] <= 8 {
		if self.state[row+1][column] == 0 {
			self.RecursiveOpen(row+1, column)
		} else {
			self.Open(row+1, column)
		}
	}
	if 0 <= self.state[row+1][column+1] && self.state[row+1][column+1] <= 8 {
		if self.state[row+1][column+1] == 0 {
			self.RecursiveOpen(row+1, column+1)
		} else {
			self.Open(row+1, column+1)
		}
	}
}

func (self *Field) Choose(row, column byte) (gameover bool) {
	gameover = false
	if 0 == self.state[row][column] {
		self.RecursiveOpen(row, column)
	} else if 0 < self.state[row][column] && self.state[row][column] <= 8 {
		self.Open(row, column)
	} else if self.state[row][column] == -1 {
		self.AllOpen() // game over
		return true
	}
	return
}

func (self *Field) FieldString() string {
	// make indices of first row
	header := " "
	for len(header) < int(math.Log10(float64(self.height)))+2 {
		header += " "
	}
	for c := 0; c < int(self.width); c++ {
		tmp := fmt.Sprintf(" %d", c+1)
		for len(tmp) < 4 {
			tmp += " " // TODO: here should be optimized
		}
		header += tmp
	}

	// make rows with index
	field := fmt.Sprintf("%s\n", header)
	for r := 1; r < int(self.height)+1; r++ {
		tmp := fmt.Sprintf("%d", r)
		for len(tmp) < int(math.Log10(float64(self.height)))+2 {
			tmp += " "
		}
		field += tmp

		for c := 1; c < int(self.width)+1; c++ {
			if -1 <= self.state[r][c] && self.state[r][c] <= 8 {
				field += CLOSED
			} else if self.state[r][c] == 10 {
				field += OPENED
			} else if 10 < self.state[r][c] {
				field += OPEN_NUM[self.state[r][c]-11]
			} else if self.state[r][c] == 9 {
				field += MINE
			}
			field += " "
		}
		if r < int(self.height) {
			field += "\n"
		}
	}
	return fmt.Sprintf("%s>> ", field)
}

func InputLoop(field *Field) {
	var input, header string
	var pos []string
	var r, c int
	for {
		fmt.Printf("%s\n%s", header, field.FieldString())
		fmt.Scanln(&input)
		pos = strings.Split(input, ",")
		if len(pos) != 2 {
			header = "\x1b[2J\n2 values should be input"
		} else {
			r, _ = strconv.Atoi(pos[0])
			c, _ = strconv.Atoi(pos[1])
			if 0 < byte(r) && byte(r) <= field.height && 0 < byte(c) && byte(c) <= field.width {
				gameover := field.Choose(byte(r), byte(c))
				if gameover {
					header = "\x1b[2J======== GAME OVER ========="
					fmt.Printf("%s\n%s", header, field.FieldString())
					break //messy!!
				} else {
					header = "\x1b[2J"
				}
			} else {
				header = fmt.Sprintf("\x1b[2J\n2 values should be input (1 <= height <= %d, 1 <= width <= %d)",
					field.height, field.width)
			}
		}
	}
}

func PlayGame() {
	var input string
	var field *Field
	//var err error
	var h, w, m int
set:
	fmt.Printf("Input height, width, (num of mine) (e.g : 8,8(,9))\n>> ")
	fmt.Scanln(&input)
	pos := strings.Split(input, ",")
	if len(pos) == 2 || len(pos) == 3 {
		w, _ = strconv.Atoi(pos[0])
		h, _ = strconv.Atoi(pos[1])
		if len(pos) == 2 {
			m = w * h / 4
		} else {
			m, _ = strconv.Atoi(pos[2])
		}
		// err is always nil (bug?), then value is 0
		//if err != nil {
		if w == 0 || h == 0 || m == 0 {
			fmt.Println("Please input 2 or 3 numerical values (value > 0)")
			goto set
		}
		field = NewField(byte(h), byte(w), byte(m))
	} else {
		fmt.Println("Please input 2 or 3 numerical values (value > 0)")
		goto set
	}
	InputLoop(field)
}
