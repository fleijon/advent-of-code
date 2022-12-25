extern crate utils;

pub const MOVE_IDX: usize = 5;
pub const FROM_IDX: usize = 12;
pub const TO_IDX: usize = 17;

pub const SAMPLE_FILE: &str = "../../../../../resources/2022/05/example.1.txt";
pub const INPUT_FILE: &str = "../../../../../resources/2022/05/input.1.txt";

pub struct Stack {
    content: Vec<Box>
}

pub struct Box {
    value: char
}

pub struct Move {
    amount: u32,
    from: usize,
    to: usize
}

fn read_stacks(stack_content: &str, stacks: &mut Vec<Stack>) {

    for line in stack_content.lines(){
        let chars: Vec<char> = line.chars().collect();
        let len = chars.len();
        let mut i = 0;

        while i < len {
            if chars[i] == '[' {
                let new_box = Box {
                    value: chars[i+1]
                };
                let stack_number = i/4;
                let stack_number_i32: i32 = stack_number.try_into().unwrap();

                let stacks_to_create = 1 + stack_number_i32 - stacks.len() as i32;
                if stacks_to_create > 0 {
                    for _ in 0..stacks_to_create {
                        let content : Vec<Box> = Vec::new();
                        let new_stack = Stack {
                            content: content
                        };

                        stacks.push(new_stack)
                    }
                }

                let stack = stacks.get_mut(stack_number)
                                                .unwrap();
                stack.content.push(new_box);

                i += 1;
            }

            i += 1;
        }
    }

    for stack in stacks {
        stack.content.reverse();
    }
}

pub fn read_moves(moves_content: &str, moves: &mut Vec<Move>) {
     for line in moves_content.lines() {
        let chars: Vec<char> = line.chars().collect();
        let amount = chars[MOVE_IDX].to_string().parse::<u32>().unwrap();
        let from_result = chars[FROM_IDX].to_string().parse::<usize>();
        let from = match from_result {
            Ok(from) => from,
            Err(err) => panic!("Problem parsing the char '{:?}'", chars[FROM_IDX])
        };
        let to = chars[TO_IDX].to_string().parse::<usize>().unwrap();
        
        let new_move = Move {
            amount: amount,
            from: from,
            to: to
        };

        moves.push(new_move);
     }
}

pub fn apply_moves(moves: Vec<Move>, stacks: &mut Vec<Stack>) {
    for action in moves {
        for _ in 0..action.amount {
            let from = stacks.get_mut(action.from - 1).unwrap();
            let b = from.content.pop();

            if b.is_some() {
                let to = stacks.get_mut(action.to - 1).unwrap();
                to.content.push(b.unwrap());
            }
        }
    }
}

pub fn get_top_boxes(stacks: &Vec<Stack>) -> String {
    let a: String = stacks.iter()
            .map(|s| s.content.last().unwrap_or(&Box { value: '\0' }).value)
            .collect();

    a.replace("\0", "")
}

pub fn split_content(full_content: &str, stacks: &mut Vec<String>, moves: &mut Vec<String>) {
    let mut s = true;
    for line in full_content.lines() {
        if line == "" {
            s = false;
        }
        else if s {
            stacks.push(line.to_string());
        }else {
            moves.push(line.to_string());
        }
    }
}

pub fn solve_a(file_path: &str) -> String {
    let content = utils::read_file(file_path);
    let mut stacks_rows: Vec<String> = Vec::new();
    let mut moves_rows: Vec<String> = Vec::new();
    split_content(&content, &mut stacks_rows, &mut moves_rows);

    let stack_content = stacks_rows.join("\n");
    let mut stacks: Vec<Stack> = Vec::new();
    read_stacks(&stack_content, &mut stacks);

    let move_content = moves_rows.join("\n");
    let mut moves: Vec<Move> = Vec::new();
    read_moves(&move_content, &mut moves);

    apply_moves(moves, &mut stacks);

    get_top_boxes(&stacks)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn sample_1() {
        let result = solve_a(SAMPLE_FILE);

        assert_eq!(result, "CMZ");
    }

    #[test]
    fn split_content_test() {
        let content = "    [D]    
[N] [C]    
[Z] [M] [P]
 1   2   3 

move 1 from 2 to 1
move 3 from 1 to 3
move 2 from 2 to 1
move 1 from 1 to 2";

        let mut stacks :Vec<String> = Vec::new();
        let mut moves: Vec<String> = Vec::new();

        split_content(content, &mut stacks, &mut moves);

        assert_eq!(stacks.len(), 4);
        assert_eq!(moves.len(), 4);
    }

    #[test]
    fn read_stacks_test(){
        let content =
"    [D]    
[N] [C]    
[Z] [M] [P]
 1   2   3 ";
        let mut stacks: Vec<Stack> = Vec::new();
        read_stacks(content, &mut stacks);

        assert_eq!(stacks.len(), 3);
        assert_eq!(stacks[0].content.len(), 2);
        assert_eq!(stacks[1].content.len(), 3);
        assert_eq!(stacks[2].content.len(), 1);
        assert_eq!(stacks[1].content[0].value, 'M');
        assert_eq!(stacks[1].content[1].value, 'C');
        assert_eq!(stacks[1].content[2].value, 'D');
    }

    #[test]
    fn read_moves_test() {
        let content = "move 1 from 2 to 1
move 3 from 1 to 3
move 2 from 2 to 1
move 1 from 1 to 2";
        let mut moves: Vec<Move> = Vec::new();
        read_moves(content, &mut moves);
        assert_eq!(moves.len(), 4);
        assert_eq!(moves[0].amount, 1);
        assert_eq!(moves[1].from, 1);
        assert_eq!(moves[2].to, 1);
    }

    #[test]
    fn apply_moves_test() {
        let moves: Vec<Move> = vec![
            Move { amount: 1, from: 1, to: 2},
            Move { amount: 2, from: 2, to: 3},
        ];
        let mut stacks: Vec<Stack> = vec![
            Stack {
                content: vec![ Box { value: 'A' }]
            },
            Stack {
                content: vec![ Box { value: 'B' }]
            },
            Stack {
                content: vec![]
            }
        ];

        apply_moves(moves, &mut stacks);

        assert_eq!(stacks[0].content.len(), 0);
        assert_eq!(stacks[1].content.len(), 0);
        assert_eq!(stacks[2].content.len(), 2);
    }

    #[test]
    fn get_top_boxes_test() {
        let stacks: Vec<Stack> = vec![
            Stack {
                content: vec![ Box { value: 'A' }]
            },
            Stack {
                content: vec![ Box { value: 'B' }]
            },
            Stack {
                content: vec![]
            }
        ];

        let result = get_top_boxes(&stacks);

        assert_eq!(result, "AB");
    }

}
