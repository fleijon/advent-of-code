
import sys
from pathlib import Path

path_to_utils = Path(__file__).parent.parent
sys.path.insert(0, str(path_to_utils))

from utils.load import load_input, as_rows

def process_signal(signal: str, u_len: int) -> int:
    
    for c in range(u_len, len(signal)):
        current = signal[c-(u_len-1):c+1:1]
        uniques = set([*current])
        if(len(uniques) == u_len):
            return c+1
    
    raise NotImplementedError("No solution was found")

        
def contains(string: str, char: str) -> bool:
    for c in string:
        if(c == char):
            return True
    
    return False


if __name__ == "__main__":
    input_data = as_rows(load_input("06", 1))[0]
    answer1 = process_signal(input_data, 4)
    print(f"Solution to part 1: {answer1}")
    
    answer2 = process_signal(input_data, 14)
    print(f"Solution to part 2: {answer2}")