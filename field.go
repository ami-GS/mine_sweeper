package main

import (
	"bytes"
	"fmt"
)

type Field struct {
	width  byte
	height byte
	state  [][]int
}

//Field.state == -2 or -1 or 0 or 1 or 2 or 3
//-1: not open with mine
//0 ~ 8: not open and the number of mine surrounding
//10 ~ 18: open and the number of mine surrounding

func NewField(width, height byte) *Field {
	field := &Field{width, height, [][]int{}}
	field.state = make([][]int, height)
	for i := 0; i < int(height); i++ {
		field.state[i] = make([]int, width)
	}
	field.state[5][3] = 4
	field.state[2][1] = 1
	/*for r := 0; r < int(height); r++ {
		for c := 0; c < int(width); c++ {
			field.state[r][c] = 10
		}
	}*/

	return field
}

func (self *Field) RefreshField() {

}

func (self *Field) Choose(row, column byte) {
	if 0 <= self.state[row][column] && self.state[row][column] <= 8 {
		self.state[row][column] += 10 //open
	} if self.state[row][column] == -1 {
		// game over
	}

}

func (self *Field) FieldString() (out string) {
	header := "  "
	for c := 0; c < int(self.width); c++ {
		header += fmt.Sprintf(" %d  ", c+1)
	}

	field := fmt.Sprintf("%s\n", header)
	for r := 0; r < int(self.height); r++ {
		field += fmt.Sprintf("%d ", r+1)
		for c := 0; c < int(self.width); c++ {
			if 0 <= self.state[r][c] && self.state[r][c] <= 8 {
				field += "[ ]"
			} else if self.state[r][c] == 10 {
				field += "___"
			} else if 10 < self.state[r][c] {
				field += fmt.Sprintf(" %d ", self.state[r][c]-10)
			}
			field += " "
		}
		if r < int(self.height)-1 {
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
	field := NewField(8, 8)
	fmt.Printf("\r%s", field.FieldString())
	InputLoop(field)
}
