import { read, split } from "./../../lib/";
import { day, year } from '.';


export const runner = (input: string): number => {
	const commands = split(input)
						.map((line: string) => line.split(" "));
	console.log(commands);
	var forward = commands.filter((v)=>v[0].startsWith("f"))
					  .reduce((p, v) => p+ parseInt(v[1]), 0);
	console.log(forward);
	var up = commands.filter((v)=>v[0].startsWith("u"))
					  .reduce((p,v)=> p + parseInt(v[1]), 0);
	console.log(up);
	var down = commands.filter((v)=>v[0].startsWith("d"))
					  .reduce((p,v)=> p + parseInt(v[1]), 0);
	console.log(down);
	return (down-up)*forward;
};

if (require.main === module) {
	(async () => {
		const input = await read(year, day)();
		const value = runner(input.input);
		console.log(`Result: ${value}.`);
	}
	)();
}