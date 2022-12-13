use std::fs::read_to_string;
use std::str;

pub const SAMPLE_FILE: &str = "../../../../../resources/2022/02/example.1.txt";
pub const INPUT_FILE: &str = "../../../../../resources/2022/02/input.1.txt";

pub struct Sign {
    pub value: i32
}

pub const DRAW: i32 = 3;
pub const WIN: i32 = 6;
pub const LOSS: i32 = 0;

pub const ROCK: i32 = 1;
pub const PAPER: i32 = 2;
pub const SCISSOR: i32 = 3;

pub fn read_file(path: &str) -> String {
    let file_content_result = read_to_string(path);

    let file_content = match file_content_result {
        Ok(file) => file,
        Err(error) => panic!("Problem opening the file: {:?}", error),
    };

    return file_content;
}

fn get_scores(pairs: &Vec<(Sign, Sign)>) -> impl Iterator<Item=i32> + '_{
    return pairs.iter()
                .map(|v| (result(&v.0,&v.1) + v.1.value));
}

pub fn calculate_score(pairs: &Vec<(Sign, Sign)>) -> i32 {
    return get_scores(pairs).sum();
}

pub fn parse_to_sign_pairs(content: &String) -> Vec<(Sign, Sign)> {
    return content.lines()
                    .map(|v| parse_row(v))
                    .collect();
}

fn parse_row(row: &str) -> (Sign, Sign) {
    let mut splitted: Vec<Sign> = row.split(' ')
                                    .map(|v| parse_to_sign(v))
                                    .collect();

    return (splitted.remove(0),
            splitted.remove(0));
}

pub fn parse_to_sign(sign: &str) -> Sign {
    match sign {
        "A" => Sign { value: ROCK},
        "B" => Sign { value: PAPER},
        "C" => Sign { value: SCISSOR},
        "X" => Sign { value: ROCK},
        "Y" => Sign { value: PAPER },
        "Z" => Sign { value: SCISSOR },
        &_ => todo!(),
    }
}

pub fn result(opponent: &Sign, user: &Sign) -> i32 {
    let diff = opponent.value - user.value;

    if diff == 0 {
        return DRAW;
    } else if diff == -2 {
        return LOSS;
    } else if diff == -1 {
        return WIN;
    } else if diff == 2 {
        return WIN;
    }
    else {
        return LOSS;
    }
}

pub fn test_get_scores() {
    let content = read_file(INPUT_FILE);
    let pairs = parse_to_sign_pairs(&content);
    let results = get_scores(&pairs);
    for result in results.take(20) {
        print!("{}\n", result);
    }
}


#[cfg(test)]
mod tests {

    use super::*;

    #[test]
    fn test_parse_input_file(){
        let content = read_file(INPUT_FILE);
        let result = parse_to_sign_pairs(&content);

        assert_eq!(result.len(), 2500);
    }

    #[test]
    fn test_parse_to_sing() {
        let result = parse_to_sign("X");

        assert_eq!(result.value, ROCK);

        let result = parse_to_sign("Y");

        assert_eq!(result.value, PAPER);

        let result = parse_to_sign("Z");

        assert_eq!(result.value, SCISSOR);
    }

    #[test]
    fn test_result() {
        let a = Sign { value: ROCK };
        let b = Sign { value: PAPER };

        let result = result(&a, &b);

        assert_eq!(result, WIN);
    }

    #[test]
    fn test_result_loss() {
        let a = Sign { value: ROCK };
        let b = Sign { value: SCISSOR };

        let result = result(&a, &b);

        assert_eq!(result, LOSS);
    }

    #[test]
    fn test_parse_row() {
        let a = parse_row("A X");

        assert_eq!(a.0.value, ROCK);
        assert_eq!(a.1.value, ROCK);
    }

    #[test]
    fn test_parse_to_sign_pairs() {
        let content = read_file(SAMPLE_FILE);
        let pairs = parse_to_sign_pairs(&content);
        assert_eq!(pairs.len(), 3);
    }

    #[test]
    fn test_calculate_score() {
        let content = read_file(SAMPLE_FILE);
        let pairs = parse_to_sign_pairs(&content);
        let score = calculate_score(&pairs);

        assert_eq!(score, 15);
    }

}