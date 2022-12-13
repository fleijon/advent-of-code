
fn first() {
    let content = day02::read_file(day02::INPUT_FILE);
    let pairs = day02::parse_to_sign_pairs(&content);
    let score = day02::calculate_score(&pairs);
    print!("Answer A: {}\n", score);
}

fn second() {
    let content = day02::read_file(day02::INPUT_FILE);
    let pairs = day02::parse_to_sign_and_outcome(&content);
    let mapped_pairs = day02::map_to_sign_pairs(&pairs);
    let score = day02::calculate_score(&mapped_pairs);

    print!("Answer B: {}\n", score);
}

fn main() {
    first();
    second();
}