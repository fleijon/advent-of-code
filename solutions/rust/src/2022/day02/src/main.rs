
fn first() {
    let content = day02::read_file(day02::INPUT_FILE);
    let pairs = day02::parse_to_sign_pairs(&content);
    let score = day02::calculate_score(&pairs);
    print!("Answer A: {}\n", score);
}

fn main() {
    first();
}