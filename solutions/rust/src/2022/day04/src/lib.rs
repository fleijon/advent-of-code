use std::{fs::read_to_string};

pub const SAMPLE_FILE: &str = "../../../../../resources/2022/04/example.1.txt";
pub const INPUT_FILE: &str = "../../../../../resources/2022/04/input.1.txt";

#[derive(Clone, Copy)]
pub struct Area {
    start: u32,
    end: u32
}

impl Area {
    fn create(start: u32, end: u32) -> Area {
        if start > end {
            panic!("start cannot be greated than end!")
        }
        Area {
            start: start,
            end: end
        }
    }

    fn contains(&self, target: &Area) -> bool {
        return self.start <= target.start && self.end >= target.end;
    }

    pub fn overlaps(&self, target: &Area) -> bool {
        let a = (self.start..self.end+1);
        let b: Vec<u32> = (target.start..target.end+1).collect();

        a.filter(|v| b.contains(v)).count() > 0
    }
}

pub fn pair_is_fully_overlapping(pair: (&Area, &Area)) -> bool {
    return pair.0.contains(&pair.1) || pair.1.contains(&pair.0);
}

pub fn read_file(path: &str) -> String {
    let file_content_result = read_to_string(path);

    let file_content = match file_content_result {
        Ok(file) => file,
        Err(error) => panic!("Problem opening the file: {:?}", error),
    };

    return file_content;
}

pub fn read_to_pairs(input: &str) -> Vec<(Area, Area)> {
    let mut pairs: Vec<(Area, Area)> = Vec::new();

    for line in input.lines() {

        let mut pair: [Option<Area>; 2] = [None, None];
        let mut i = 0;

        for sections in line.split(',') {
            let mut j = 0;
            let mut start: Option<u32> = None;
            let mut end: Option<u32> = None;

            for sectionStr in sections.split('-') {
                let section: u32 = sectionStr.parse().unwrap();
                if j == 0 {
                    start = Some(section);
                    j += 1;
                }
                else {
                    end = Some(section);
                    j = 0;
                }
            }
            let idx = (i+1) % 2;

            pair[idx] = Some(Area {
                start: start.expect(""),
                end: end.expect("")
            });

            i += 1;
        }

        let a = pair[0].expect("");
        let b = pair[1].expect("");
        pairs.push((a, b));
    }

    pairs
}

fn sample_1() -> u32 {
    let input = read_file(SAMPLE_FILE);
    let pairs = read_to_pairs(&input);
    
    pairs.iter()
         .filter(|&pair| pair_is_fully_overlapping((&pair.0, &pair.1)))
         .count() as u32
}

fn sample_2() -> u32 {
    let input = read_file(SAMPLE_FILE);
    let pairs = read_to_pairs(&input);

    pairs.iter()
            .filter(|pair| pair.0.overlaps(&pair.1))
            .count() as u32
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn overlaps_test() {
        let a1 = Area::create(2, 5);
        let a2 = Area::create(2, 3);

        let actual = a1.overlaps(&a2);

        assert_eq!(actual, true);
    }

    #[test]
    fn contains_test() {
        let a1 = Area::create(2, 5);
        let a2 = Area::create(2, 3);
        let actual = a1.contains(&a2);

        assert_eq!(actual, true);
    }

    #[test]
    fn pair_is_fully_overlapping_test() {
        let a1 = Area::create(2, 5);
        let a2 = Area::create(2, 3);
        let actual = pair_is_fully_overlapping((&a2, &a1));

        assert_eq!(actual, true);
    }

    #[test]
    fn read_to_pairs_test() {
        let input = "2-3,4-5\n1-2,3-4";
        let actual = read_to_pairs(input);

        assert_eq!(actual.len(), 2);
    }

    #[test]
    fn sample_1_test() {
        let result = sample_1();
        assert_eq!(result, 2);
    }

    #[test]
    fn sample_2_test() {
        let result = sample_2();
        assert_eq!(result, 4);
    }

}
