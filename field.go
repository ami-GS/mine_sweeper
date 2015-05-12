package main

import (
	"bytes"
	"fmt"
	"math/rand"
)

type Field struct {
	width  byte
	height byte
	state  [][]int
}

//Field.state == -2 or -1 or 0 ~ 8 or 10 ~ 18
//-2: opened with mine
//-1: not open with mine
//0 ~ 8: not open and the number of mine surrounding
//10 ~ 18: open and the number of mine surrounding

func NewField(width, height, mineNum byte) *Field {
	field := &Field{width, height, [][]int{}}
	field.state = make([][]int, height+2)

	var Combination [][2]byte
	Combination = make([][2]byte, width*height)
	for i := 0; i < int(height)+2; i++ {
		field.state[i] = make([]int, width+2)
	}
	for i := 0; i < int(height); i++ {
		for j := 0; j < int(width); j++ {
			Combination[i*int(height)+j][0] = byte(i + 1)
			Combination[i*int(height)+j][1] = byte(j + 1)
		}
	}

	// set mine
	var pos [][2]byte = make([][2]byte, mineNum)
	for i := 0; i < int(mineNum); i++ {
		idx := rand.Intn(int(width*height) - i)
		pos[i] = Combination[idx]
		Combination = append(Combination[:idx], Combination[idx+1:]...)
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
	for i := 0; i < int(mineNum); i++ {
		// put mine
		field.state[pos[i][0]][pos[i][1]] = -1
	}

	return field
}

func (self *Field) RefreshField() {

}

func (self *Field) Choose(row, column byte) {
	row += 1
	column += 1
	if 0 <= self.state[row][column] && self.state[row][column] <= 8 {
		self.state[row][column] += 10 //open
	} else if self.state[row][column] == -1 {
		self.state[row][column] += -1
	}
}

func (self *Field) FieldString() (out string) {
	header := "  "
	for c := 0; c < int(self.width); c++ {
		header += fmt.Sprintf(" %d  ", c+1)
	}

	field := fmt.Sprintf("%s\n", header)
	for r := 1; r < int(self.height)+1; r++ {
		field += fmt.Sprintf("%d ", r)
		for c := 1; c < int(self.width)+1; c++ {
			if -1 <= self.state[r][c] && self.state[r][c] <= 8 {
				field += "[ ]"
			} else if self.state[r][c] == 10 {
				field += "___"
			} else if 10 < self.state[r][c] {
				field += fmt.Sprintf("_%d_", self.state[r][c]-10)
			} else if self.state[r][c] == -2 {
				field += "_*_"
			}
			field += " "
		}
		if r < int(self.height) {
			field += "\n"
		}
	}
	return fmt.Sprintf("%s", field)
}

func InputLoop(field *Field) {
	var input string
	var pos [][]byte
	var ZERO byte = 48
	for {
		fmt.Scanln(&input)
		in := []byte(input)
		pos = bytes.Split(in, []byte(","))
		if len(pos) != 2 {
			fmt.Println("2 values should be input")
			continue
		}
		field.Choose(pos[0][0]-ZERO-1, pos[1][0]-ZERO-1)
		fmt.Printf("\r%s", field.FieldString())
	}
}

func main() {
	field := NewField(8, 8, 6)
	fmt.Printf("\r%s", field.FieldString())
	InputLoop(field)
}
