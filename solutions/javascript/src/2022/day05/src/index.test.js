import { readAsLines, parseStacks, parseInstructions, Instruction, Stack, runInstructionsOnStacks, solve1Example, solve2Example } from ".";

describe('Test support functions', () => {
    test('Should read input as lines', () => {
        const input = [
            "    [D]    ",
            "[N] [C]    ",
            "[Z] [M] [P]",
            "1   2   3  "
        ];

        var lines = readAsLines(input);

        expect(lines.length).toEqual(3);
        expect(lines[0].length).toEqual(3);
        expect(lines[0][1]).toEqual('M');
    })

    test('Should parse input as stacks', () => {
        const input = [
            "    [D]    ",
            "[N] [C]    ",
            "[Z] [M] [P]",
            "1   2   3  "
        ];
        
        var stacks = parseStacks(input);

        expect(stacks.length).toEqual(3);
        expect(stacks[1].pop()).toEqual('D');
    });

    test('Should parse input as instructions', () => {
        const input = ["move 1 from 2 to 1",
        "move 3 from 1 to 3",
        "move 2 from 2 to 1",
        "move 1 from 1 to 2"];

        var instructions = parseInstructions(input);

        expect(instructions.length).toEqual(4);
        expect(instructions[0].move).toEqual(1);
        expect(instructions[0].from).toEqual(2);
        expect(instructions[0].to).toEqual(1);
    })

    test('Should run instructions on stacks', () => {
        const instructions = [
            new Instruction(1, 1, 2),
            new Instruction(2, 2, 3),
        ];
        const stack1 = new Stack();
        stack1.push('A');
        stack1.push('B');

        const stack2 = new Stack();
        stack2.push('C');
        stack2.push('D');

        const stack3 = new Stack();
        stack3.push('E');
        stack3.push('F');

        const stacks = [ stack1, stack2, stack3 ];

        runInstructionsOnStacks(instructions, stacks);

        expect(stacks[0].peek()).toEqual('A');
        expect(stacks[1].peek()).toEqual('C');
        expect(stacks[2].peek()).toEqual('D');
    })

    test('Should solve example 1', () => {
        const exampleResult = solve1Example();

        expect(exampleResult).toEqual("CMZ");
    })

    test('Should solve task with example input', () => {
        const exampleResult = solve2Example();

        expect(exampleResult).toEqual("MCD");
    })
}) 