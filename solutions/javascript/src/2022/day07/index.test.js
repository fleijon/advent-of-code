import { Directory, File, parseCommand, CommandTypes } from ".";

describe('Test support classes', () => {
    test('Directory size', () => {
        let dir = new Directory();

        let file1 = new File(10);
        let file2 = new File(20);

        dir.addFile(file1);
        dir.addFile(file2);

        expect(dir.size()).toEqual(30);
    })

    test('Should parse ls command', () => {
        const input = "$ ls";
        const command = parseCommand(input);

        expect(command.commandType).toEqual(CommandTypes.ls);
        expect(command.commandInput).toEqual('');
    })

    test('Should parse cd command', () => {
        const input = "$ cd ..";
        const command = parseCommand(input);

        expect(command.commandType).toEqual(CommandTypes.cd);
        expect(command.commandInput).toEqual("..");
    })

})