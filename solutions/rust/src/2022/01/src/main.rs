use std::fs::read_to_string;
use std::str;

pub struct Elf {
    food_calories: Vec<i32>
}

const SAMPLE_FILE: &str = "../../../../../resources/2022/01/example.1.txt";
const INPUT_FILE: &str = "../../../../../resources/2022/01/input.1.txt";

pub fn read_sample_file() -> String{
    let sample_content_result = read_to_string(SAMPLE_FILE);

    let sample_content_result = match sample_content_result {
        Ok(file) => file,
        Err(error) => panic!("Problem opening the file: {:?}", error),
    };

    return sample_content_result;
}

pub fn parse_elfs(content: String) -> Vec<Elf>{
    let mut elfs = Vec::new();
    let mut calories = Vec::new();
    for content in content.lines(){
        if content.is_empty() {
            elfs.push(Elf{
                food_calories: calories.to_owned(),
            });

            calories = Vec::new();
        } else {
            calories.push(content.parse::<i32>().unwrap());
        }
    }

    elfs.push(Elf{
        food_calories: calories,
    });
    
    return elfs;
}

pub fn get_most_calories_of_elf(elf: Vec<Elf>) -> i32 {

    let mut max = 0;
    for elf in elf{
        let sum_elf = elf.food_calories.iter().sum();
        if sum_elf > max {
            max = sum_elf;
        }
    }

    return max;
}

pub fn get_total_calories_of_top_3(elfs: Vec<Elf>) -> i32 {
    let mut top_n: [i32; 3]= [0; 3];

    for elf in elfs{
        let sum_elf: i32 = elf.food_calories.iter().sum();

        let mut i = 0;
        let mut curr = sum_elf;
        while i < 3 {
           if curr > top_n[i] {
                let temp = top_n[i];
                top_n[i] = curr;
                curr = temp;
           } 

           i += 1;
        }
    }

    return top_n.iter().sum();
}

pub fn first() {
    let input_content = read_to_string(INPUT_FILE);

    let content = match input_content {
        Ok(file) => file,
        Err(error) => panic!("Problem opening the file: {:?}", error),
    };

    let elfs = parse_elfs(content);

    let max = get_most_calories_of_elf(elfs);

    print!("Answer A: {}\n", max);
}

pub fn second() {
    let input_content = read_to_string(INPUT_FILE);

    let content = match input_content {
        Ok(file) => file,
        Err(error) => panic!("Problem opening the file: {:?}", error),
    };

    let elfs = parse_elfs(content);
    let total_calories = get_total_calories_of_top_3(elfs);

    print!("Answer B: {}\n", total_calories);
}

pub fn main() {
    first();
    second();
}
