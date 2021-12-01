import { read, split } from "./../../lib/";
import { day, year } from '.';

export const runner = (input: string): number => {
	const numbers = split(input).map((line: string) => parseInt(line, 10));
	let current = numbers[0];
	let counter = 0;
	for (let index = 1; index < numbers.length; index++) {
		const number = numbers[index];
		if(current < number){
			counter++;
		}
		current = number;
	}
	return counter;
};

if (require.main === module) {
	(async () => {
		const input = await read(year, day)();
		const value = runner(input.input);
		console.log(`Result: ${value}.`);
	}
	)();
}