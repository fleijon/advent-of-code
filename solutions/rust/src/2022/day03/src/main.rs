
fn first() {
    let input = day03::read_file(day03::INPUT_FILE);
    let bags = day03::get_bags(&input);
    let score: u32 = bags.iter()
                    .map(|b| day03::get_compartments(b))
                    .map(|comps| day03::get_unique_item_score(comps))
                    .sum();
    print!("Answer A: {}\n", score);
}

fn second() {
    let input = day03::read_file(day03::INPUT_FILE);
    let groups = day03::create_groups_by(&input, 3);
    let score: u32 = groups.iter()
                        .map(|b| b.badge())
                        .map(|c| day03::get_letter_score(c))
                        .sum();

    print!("Answer B: {}\n", score);
}


fn main(){
    first();
    second();
}