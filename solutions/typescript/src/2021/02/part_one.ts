import { read, split } from "./../../lib/";
import { day, year } from '.';


export const runner = (input: string): number => {
	const commands = split(input)
						.map((line: string) => line.split(" "));
	var forward = commands.filter((v)=>v[0].startsWith("f"))
					  .reduce((p, v) => p+ parseInt(v[1]), 0);
	var up = commands.filter((v)=>v[0].startsWith("u"))
					  .reduce((p,v)=> p + parseInt(v[1]), 0);
	var down = commands.filter((v)=>v[0].startsWith("d"))
					  .reduce((p,v)=> p + parseInt(v[1]), 0);
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