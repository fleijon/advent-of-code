import { read, split } from "./../../lib/";
import { day, year } from '.';

interface cord{
    x: number,
    y: number,
    aim: number
}

const move = (command:string[], curr: cord): cord =>{
    let newCord = {...curr};
    if(command[0].startsWith("d")){
        newCord.aim += parseInt(command[1]);
    }else if(command[0].startsWith("u")){
        newCord.aim -= parseInt(command[1]);
    }else{
        // forward
        newCord.x += parseInt(command[1]);
        newCord.y += curr.aim * parseInt(command[1]);
    }
    return newCord;
}

export const runner = (input: string): number => {
    const commands = split(input)
                        .map((line: string) => line.split(" "));
    const cord =  commands.reduce<cord>((p, v) => move(v, p), {x:0, y:0, aim:0} as cord)
    return cord.x * cord.y;
};

if (require.main === module) {
	(async () => {
		const input = await read(year, day)();
		const value = runner(input.input);
		console.log(`Result: ${value}.`);
	}
	)();
}