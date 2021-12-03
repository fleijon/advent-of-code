import { read, split } from "./../../lib/";
import { day, year } from '.';

export const runner = (input: string): number => {
	const c = split(input);
	var bitSize = c[0].length;
    var d =	c
				.flatMap(v => v.split(''))
				.reduce<number[]>((p, v, idx) => {
					const pos = idx%bitSize;
					let curr = [...p];
					curr[pos] += (v==="1") ? 1 : -1;
					return curr;
				}, new Array(bitSize).fill(0))
				.map((v) => {
					if(v > 0) return 1;
					return 0;
				}
				);
	const value = parseInt(d.join(''), 2);
	const valueNot = parseInt(d.map(v => (v == 0) ? 1 : 0).join(''), 2);
	return value * valueNot;
}

if (require.main === module) {
	(async () => {
		const input = await read(year, day)();
		const value = runner(input.input);
		console.log(`Result: ${value}.`);
	}
	)();
}