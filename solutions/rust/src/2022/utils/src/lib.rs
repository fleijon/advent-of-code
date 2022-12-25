use std::fs::read_to_string;

pub fn read_file(path: &str) -> String {
    let file_content_result = read_to_string(path);

    let file_content = match file_content_result {
        Ok(file) => file,
        Err(error) => panic!("Problem opening the file: {:?}", error),
    };

    return file_content;
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
    }
}
