import unittest
from main import process_signal
import sys
from pathlib import Path

path_to_utils = Path(__file__).parent.parent
sys.path.insert(0, str(path_to_utils))

from utils.load import load_example_input, as_rows

class TestLoadMethods(unittest.TestCase):
    
    def test_process_signal(self):
        example_signal = as_rows(load_example_input("06", 1))[0]
        index = process_signal(example_signal)
        
        self.assertEqual(index, 7)

if __name__ == '__main__':
    unittest.main()
