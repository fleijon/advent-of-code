import { getExampleInput, getInput } from "../../utils/load.js";

export class Stack {
    constructor() {
        this.items = [];
    }

    push(item) {
        this.items.push(item);
    }

    pop() {
        if(!this.items.length)
        {
            return null;
        }
        return this.items.pop();
    }

    peek() {
        if(!this.items.length)
        {
            return null;
        }

        return this.items[this.items.length - 1];
    }

    isEmpty() {
        return this.items.length === 0;
    }

}

export class Instruction {
    constructor(move, from, to) {
        this.move = move;
        this.from = from;
        this.to = to;
    }
}

export function parseStacks(input) {
/* Example input represented in array
"    [D]    ",
"[N] [C]    ",
"[Z] [M] [P]",
"1   2   3"
*/

    var lines = readAsLines(input);
    const stacks = Array(lines[0].length)
                    .fill()
                    .map(() => new Stack());

    lines.forEach((line ) => {
        line.forEach((ele, j) => {
            if(ele)
            {
                stacks[j].push(ele);
            } 
        });
    });

    return stacks;
}

export function readAsLines(input) {
    return input.reverse()
                .slice(1)
                .map(takeIds)
}

function takeIds(line) {
    const groups = [];

    for (let i = 0; i < line.length; i += 4) {
        groups.push(line.slice(i, i + 4));
    }

    return groups.map((group) =>{ return group[1].replace(" ", "")});
}

export function parseInstructions(input) {
/*
["move 1 from 2 to 1",
"move 3 from 1 to 3",
"move 2 from 2 to 1",
"move 1 from 1 to 2"]
*/
    return input.map(line => {
        var splitted = line.split(" ")

        return new Instruction(parseInt(splitted[1]), parseInt(splitted[3]), parseInt(splitted[5]));
    })

}

export function runInstructionsOnStacks(instructions, stacks) {
    instructions.forEach((instruction) => {
        for(let i = 0; i < instruction.move; i++){
            var ele = stacks[instruction.from - 1].pop();

            if(ele){
                stacks[instruction.to - 1].push(ele)
            }
        }
    });
}

export function runInstructionsOnStacksWithCrateMover9001Operations(instructions, stacks) {
    instructions.forEach((instruction) => {
        let cratesInTransit = [];

        for(let i = 0; i < instruction.move; i++){
            var ele = stacks[instruction.from - 1].pop();

            if(ele){
                cratesInTransit.push(ele); 
            }
        }

        cratesInTransit.reverse().forEach((crate) => {
            stacks[instruction.to - 1].push(crate)
        });

    });
}

function solve(dayInput, moveInstructions) {
    let sepRow = 0;

    dayInput.forEach((line, i) => {
        if(line.length === 0){
            sepRow = i;
        }
    });

    const stacks = parseStacks(dayInput.slice(0, sepRow));
    const instructions = parseInstructions(dayInput.slice(sepRow + 1));

    moveInstructions(instructions, stacks);
    
    const top = stacks.map((stack) => { return stack.pop()}).join("");
    return top;
}

export function solve1Example() {
    const sampleInput = getExampleInput("05", 1);
    return solve(sampleInput, runInstructionsOnStacks);
}

export function solve2Example() {
    const sampleInput = getExampleInput("05", 1);
    return solve(sampleInput, runInstructionsOnStacksWithCrateMover9001Operations);
}

function solveCrateMover9000() {
    const input = getInput("05", 1);

    return solve(input, runInstructionsOnStacks);
}

function solveCrateMover9001() {
    const input = getInput("05", 1);

    return solve(input, runInstructionsOnStacksWithCrateMover9001Operations);
}

if (process.env.NODE_ENV !== 'test') {
    const answer1 = solveCrateMover9000();
    const answer2 = solveCrateMover9001();

    console.log(`
        Solution part1: ${answer1}
        Solution part2: ${answer2}
    `);
}