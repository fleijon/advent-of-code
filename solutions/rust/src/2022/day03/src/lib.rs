use std::{fs::read_to_string};

const ascii_cap_start: u32 = 65;
const ascii_lower_start: u32 = 97;
const cap_score_start: u32 = 27;

pub const SAMPLE_FILE: &str = "../../../../../resources/2022/03/example.1.txt";
pub const INPUT_FILE: &str = "../../../../../resources/2022/03/input.1.txt";

pub struct Bag<'a> {
    items: &'a str,
}

pub struct Compartment<'a> {
    items: &'a str
}

pub struct Group<'a, const N: usize> {
    bags: [Bag<'a>; N]
}

impl Group<'_, 3> {
    pub fn badge(&self) -> char{
        // brute force search
        for first in self.bags[0].items.chars() {
            for second in self.bags[1].items.chars() {
                if first == second {
                    for third in self.bags[2].items.chars() {
                       if third == first  {
                            return first;
                       }
                    }
                }
            }
        }
        panic!("Could not find badge");
    }
}

pub fn read_file(path: &str) -> String {
    let file_content_result = read_to_string(path);

    let file_content = match file_content_result {
        Ok(file) => file,
        Err(error) => panic!("Problem opening the file: {:?}", error),
    };

    return file_content;
}

fn to_array<T, const N: usize>(v: Vec<T>) -> [T; N] {
    v.try_into()
        .unwrap_or_else(|v: Vec<T>| panic!("Expected a Vec of length {} but it was {}", N, v.len()))
}

pub fn create_groups_by(content: &str, size: usize) -> Vec<Group<3>> {

    let mut groups: Vec<Group<3>> = Vec::new();
    let mut c = 0;
    let mut bags: Vec<Bag> = Vec::new();

    for line in content.lines() {
        let bag = Bag {
            items: line
        };

        bags.push(bag);
        c+=1;

        if c == size {
            let group = Group {
                bags: to_array(bags)
            };

            groups.push(group);
            bags = Vec::new();
            c = 0;
        }
    }

    return groups;
}

pub fn get_bags(input: &str) -> Vec<Bag> {
    let a = input.lines()
        .map(|line| Bag { items: line.clone() })
        .collect();
    return a;
}

pub fn get_compartments<'a>(bag: &'a Bag) -> (Compartment<'a>, Compartment<'a>) {
    let compartment_size = bag.items.len() / 2 as usize;
    (Compartment {
        items: &bag.items[..compartment_size]
    },
    Compartment {
        items: &bag.items[compartment_size..],
    })
}

pub fn get_unique_item_score(compartments: (Compartment, Compartment)) -> u32 {
    for item in compartments.0.items.chars() {
        for item2 in compartments.1.items.chars() {
            if item == item2 {
                return get_letter_score(item);
            }
        }
    }

    return 0 as u32;
}

pub fn get_letter_score(c: char) -> u32 {
    let ascii_value = get_ascii(c);
    if ascii_value < ascii_cap_start {
        panic!("not a valic character")
    } else if ascii_value >= ascii_cap_start && ascii_value < ascii_lower_start {
        return ascii_value - ascii_cap_start + cap_score_start;
    } else {
        return ascii_value - ascii_lower_start + 1;
    }
}

fn get_ascii(c: char) -> u32 {
    c as u32
}

fn sample_1() -> u32{
    let input = read_file(SAMPLE_FILE);
    let bags = get_bags(&input);
    bags.iter()
        .map(|b| get_compartments(b))
        .map(|comps| get_unique_item_score(comps))
        .sum()
}

fn sample_2() -> u32 {
    let input = read_file(SAMPLE_FILE);
    let groups = create_groups_by(&input, 3);
    return groups.iter()
                 .map(|b| b.badge())
                 .map(|c| get_letter_score(c))
                 .sum();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn sample_2_test() {
        let score = sample_2();

        assert_eq!(score, 70);
    }

    #[test]
    fn Group_badge_test() {
        let bags = [
            Bag{
                items: "ad"
            },
            Bag{
                items: "bd"
            },
            Bag{
                items: "cd"
            },
        ];

        let group:Group<3> = Group {
            bags: bags,
        };
        let badge = group.badge();

        assert_eq!(badge, 'd');
    }

    #[test]
    fn create_groups_by_test(){

        let content = "A\nB\nC\na\nb\nc";
        let groups = create_groups_by(content, 3);

        assert_eq!(groups.len(), 2);
    }

    #[test]
    fn sample_1_test() {
        let score = sample_1();
        assert_eq!(score, 157);
    }

    #[test]
    fn get_unique_item_score_test() {
        let compartments = (Compartment {
                items: "abcd"
            },
            Compartment {
                items: "efgd"
            }
        );

        let score = get_unique_item_score(compartments);

        assert_eq!(score, 4);
    }

    #[test]
    fn get_compartments_test() {
        let bag = Bag {
            items: "abcABC",
        };

        let compartments = get_compartments(&bag);

        assert_eq!(compartments.0.items, "abc");
        assert_eq!(compartments.1.items, "ABC");
    }

    #[test]
    fn get_letter_score_test() {
        let a = get_letter_score('a');
        let A = get_letter_score('A');
        assert_eq!(a, 1 as u32);
        assert_eq!(A, 27 as u32);
    }
}
