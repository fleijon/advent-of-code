import os

INPUT_BASE = "../../../../../resources/2022"

def load_example_input(day: str, inputNumber: int) -> str:
    curr = os.path.dirname(__file__)
    filename = f"example.{inputNumber}.txt"
    filepath = os.path.join(curr, INPUT_BASE, day, filename)
    
    return load_file(filepath)
    
def load_input(day: str, inputNumber: int) -> str:
    curr = os.path.dirname(__file__)
    filename = f"input.{inputNumber}.txt"
    filepath = os.path.join(curr, INPUT_BASE, day, filename)
    
    return load_file(filepath)
    
def load_file(filepath: str) -> str:
    
    with open(filepath, 'r') as f:
        data = f.read()
        
    return data

def as_rows(file_content: str) -> list[str]:
    
    return file_content.split("\n")
