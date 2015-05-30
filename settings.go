package mine_sweeper

import (
	"github.com/ami-GS/soac"
	"strconv"
)

var (
	CLOSED   string = "[ ]"
	OPENED   string = "___"
	OPEN_NUM [8]string
	MINE     string = "_*_"
)

var C *soac.Changer

func init() {
	C = soac.NewChanger()
	C.Red()
	MINE = "_" + C.Apply("*") + "_"

	for i := 0; i < 7; i++ {
		C.Set(soac.White - soac.Color(i))
		OPEN_NUM[i] = "_" + C.Apply(strconv.Itoa(i+1)) + "_"
	}
	C.Set(soac.White)
	OPEN_NUM[7] = "_" + C.Apply(strconv.Itoa(8)) + "_"
}
