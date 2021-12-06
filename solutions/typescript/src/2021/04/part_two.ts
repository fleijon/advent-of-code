import { read, split } from "./../../lib/";
import { day, year } from '.';

export const runner = (input: string): number => {
    const values = split(input);
};

if (require.main === module) {
	(async () => {
		const input = await read(year, day)();
		const value = runner(input.input);
		console.log(`Result: ${value}.`);
	}
	)();
}