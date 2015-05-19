# mine_sweeper
mine sweeper on CUI


### Usage
```
>> go run example/play.go
>> Input width, height, (num of mine) (e.g : 8,8(,9))
>> 4,4,3
   1   2   3   4
1 [ ] [ ] [ ] [ ]
2 [ ] [ ] [ ] [ ]
3 [ ] [ ] [ ] [ ]
4 [ ] [ ] [ ] [ ] 3,3

# screen will be refreshed
   1   2   3   4
1 [ ] [ ] [ ] [ ]
2 [ ] [ ] [ ] [ ]
3 [ ] [ ] _1_ [ ]
4 [ ] [ ] [ ] [ ]

# game over
   1   2   3   4
1 _1_ _*_ _*_ _1_
2 _1_ _2_ _2_ _1_
3 _1_ _1_ _1_ ___
4 _1_ _*_ _1_ ___
```


### License
The MIT License (MIT) Copyright (c) 2015 ami-GS