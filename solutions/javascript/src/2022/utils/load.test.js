import { readFileToString, getInput, getExampleInput } from './load.js'

describe('Tests for loading input data', () => {
    test('Should load file', () => {
        const content = readFileToString('./utils/testfile.txt');
        expect(content).not.toBeNull();
    })

    test('Should load day 01 input', () => {
        var day01Input = getInput('01', 1);

        expect(day01Input).not.toBeNull();
    })

    test('Should load day 01 example', () => {
        var day01example = getExampleInput('01', 1);

        expect(day01example.length).toEqual(14);
    })
})