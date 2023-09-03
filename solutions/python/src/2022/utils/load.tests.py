import os
import unittest
from load import load_file, load_example_input, load_input, as_rows

class TestLoadMethods(unittest.TestCase):

    def test_load_test_file(self):
        curr = os.path.dirname(__file__)
        file = "./test.txt"
        filepath = os.path.join(curr, file)
        file_content = load_file(filepath)
        self.assertEqual(file_content.upper(), 'TEST')
    
    def test_load_example_input_day1(self):
        content = load_example_input("01", 1)
        
        self.assertIsNotNone(content)
        self.assertGreater(len(content), 0)
        
    def test_load_input_day1(self):
        content = load_input("01", 1)
        
        self.assertIsNotNone(content)
        self.assertGreater(len(content), 0)
    
    def test_load_and_split_example_input_day1(self):
        content = load_example_input("01", 1)
        splitted = as_rows(content)
        
        self.assertEqual(len(splitted), 14)
        

if __name__ == '__main__':
    unittest.main()