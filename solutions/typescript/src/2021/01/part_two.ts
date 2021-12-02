import { read, split } from "./../../lib/";
import { day, year } from '.';

export const runner = (input: string): number => {
	const numbers = split(input).map((line: string) => parseInt(line, 10));
    const windows = numbers.flatMap((n, idx, arr) =>
        (idx > arr.length - 3) ? [] :
                                 [arr.slice(idx, idx + 3)]
    );
    console.log(windows);
    const sums = windows
        .map((v: number[]) => v.reduce((p, v) => p + v, 0));
    console.log(sums);
    return sums.map((v: number, idx : number, arr: number[]) : number =>
        (idx == 0)       ? 0 :
        (arr[idx-1] < v) ? 1 :
                           0
    )
    .reduce((p, v) => p + v, 0);
};

if (require.main === module) {
	(async () => {
		const input = await read(year, day)();
		const value = runner(input.input);
		console.log(`Result: ${value}.`);
	}
	)();
}