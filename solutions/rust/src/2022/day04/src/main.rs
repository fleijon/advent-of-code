fn first() {
    let input = day04::read_file(day04::INPUT_FILE);
    let pairs = day04::read_to_pairs(&input);
    
    let count = pairs.iter()
                        .filter(|&pair| day04::pair_is_fully_overlapping((&pair.0, &pair.1)))
                        .count() as u32;
    print!("Answer A: {}\n", count);
}

fn second() {
    let input = day04::read_file(day04::INPUT_FILE);
    let pairs = day04::read_to_pairs(&input);

    let count = pairs.iter()
                    .filter(|pair| pair.0.overlaps(&pair.1))
                    .count() as u32;

    print!("Answer B: {}\n", count);
}

fn main() {
    first();
    second();
}