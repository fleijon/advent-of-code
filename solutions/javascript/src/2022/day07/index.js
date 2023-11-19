
class Command {
    constructor(commandType, commandInput) {
        this.commandType = commandType;
        this.commandInput = commandInput;
    }

}

export const CommandTypes = {
	cd: 0,
	ls: 1,
}

export class Directory {

    constructor() {
        this.files = []
    }

    addFile(file) {
        this.files.push(file);
    }

    size() {
        let size = 0;

        this.files.forEach(f => size+=f.size);

        return size;
    }

}

export class File {

    constructor(size) {
        this.size = size;
    }

}

export function parseCommand(command) {
    let splitted = command.split(" ");
    let type = CommandTypes.cd;
    let commandInput = '';

    switch(splitted[1]) {
        case "cd":
            type = CommandTypes.cd;
            break;
        case "ls":
            type = CommandTypes.ls;
            break;
        default:
            throw new Error(`Could not parse command: ${splitted[0]}.`);
    }

    if(splitted.length > 2){
        commandInput = splitted[2];
    }

    return new Command(type, commandInput);
}

function isCommand(arg) {
    return arg.startsWith("$");
}

export function parseConsoleArguments(console) {
    let command = [];
    for (let i = 0; i < console.length; i++) {
        const line = console[i];

        if(isCommand(line))
        {
            command.push()
        }
    }
}