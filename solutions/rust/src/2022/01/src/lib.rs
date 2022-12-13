mod main;


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_read_sample_file() {
        let sample_content = main::read_sample_file();
        assert!(sample_content.is_empty() == false);
    }

    #[test]
    fn test_parse_elfs() {
        let sample_content = main::read_sample_file();
        let elfs = main::parse_elfs(sample_content);

        assert!(elfs.len() == 5);
    }

    #[test]
    fn test_get_most_calories_of_elfs() {
        let sample_content = main::read_sample_file();
        let elfs = main::parse_elfs(sample_content);
        let max = main::get_most_calories_of_elf(elfs);
        
        assert!(max == 24000);
    }

    #[test]
    fn test_get_total_calories_of_top_3() {
        let sample_content = main::read_sample_file();
        let elfs = main::parse_elfs(sample_content);
        let total = main::get_total_calories_of_top_3(elfs);

        assert!(total == 45000);
    }

}
