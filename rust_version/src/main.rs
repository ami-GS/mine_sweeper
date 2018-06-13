extern crate rand;
use rand::prelude::*;
use std::io;
use std::io::prelude::*;

// can be map?
const OPENED_STR: &'static str = "___";
const CLOSED_STR: &'static str = "[ ]";
const MINE_STR:   &'static str = "[ ]";
const MINEOPENED_STR: &'static str = "_*_";

const OPENED: i8 = 0;
const CLOSED: i8 = -1;
const MINE: i8 = -2;
const MINEOPENED: i8 = -3;


struct Field {
    row: usize,
    column: usize,
    world: Vec<Vec<i8>>,
}

impl Field {
    fn new(r: usize, c: usize, percent: usize) -> Field {
        let mut world = vec![vec![CLOSED; c+2]; r+2];
        // set random mine
        let mut rng = thread_rng();

        let all_mine_num = r*c*percent/100;
        let mut mine_num = 0;
        while mine_num < all_mine_num {
            let row = rng.gen_range(1, r+1);
            let col = rng.gen_range(1, c+1);
            if world[row][col] == MINE {
                continue;
            }
            world[row][col] = MINE;
            mine_num += 1;
        }
        println!("row: {}, col:{}, mines:{}", r, c, all_mine_num);
        return Field{
            row: r,
            column: c,
            world: world,
        }
    }

    fn all_open(&mut self) {
        for r in 1..self.row+1 {
            for c in 1..self.column+1 {
                let around_num = self.count_around(r, c);
                if self.world[r][c] == MINE {
                    self.world[r][c] = MINEOPENED;
                } else {
                    self.world[r][c] = around_num;
                }
            }
        }
    }
    /*
    fn At(w: usize, h: usize) -> u8 { }
    */
    fn count_around(&self, row: usize, col: usize) -> i8 {
        // comes 0 origin, increase 1
        let mut ans: i8 = 0;

        for r in row-1..row+2 {
            for c in col-1..col+2 {
                if r == row && c == col {
                    continue;
                }

                if self.world[r][c] == MINE || self.world[r][c] == MINEOPENED {
                    ans += 1;
                }
            }
        }
        return ans;
    }

    fn show_field(&self) {
        let print_one = |sign: &str| {print!(" {}", sign)};

        for r in 1..self.row+1 {
            for c in 1..self.column+1 {
                match self.world[r][c] {
                    OPENED => print_one(OPENED_STR),
                    CLOSED => print_one(CLOSED_STR),
                    MINE   => print_one(MINE_STR),
                    MINEOPENED => print_one(MINEOPENED_STR),
                    _n if self.world[r][c] >= 1 => print!(" _{}_", self.world[r][c]),
                    _ => continue,
                }
            }
            print!("\n")
        }
    }

    pub fn choose(&mut self, mut r: usize, mut c: usize) -> bool {
        // will be replaced by At()
        r+=1;
        c+=1;

        if self.world[r][c] == MINE {
            self.all_open();
            return false;
        }
        let around_num = self.count_around(r, c);
        self.world[r][c] = around_num;

        return true;
    }
}

fn read<T: std::str::FromStr>() -> Vec<T> {
    let mut s = String::new();
    io::stdin().read_line(&mut s).ok();
    s.trim().split_whitespace().map(|e| e.parse().ok().unwrap()).collect()
}

fn stoi(val: &String) -> usize {
    return match val.parse::<usize>() {
        Ok(i) => i,
        Err(_e) => {
            0
        }
    }
}

fn main() {
    print!("input [row column mine_percentage] => ");
    io::stdout().flush().unwrap();

    let row_col_percent = read::<String>();
    let mut field = Field::new(stoi(&row_col_percent[0]), stoi(&row_col_percent[1]), stoi(&row_col_percent[2]));
    let mut flag = true;
    print!("\x1b[0;0H");
    field.show_field();
    while flag {
        let out = read::<String>();
        flag = field.choose(stoi(&out[0]), stoi(&out[1]));
        print!("\x1b[0;0H");
        field.show_field();
    }
}
