import { read, split } from '../../lib';
import { day, year } from '.';

export const runner = (input: string): number => {
	const numbers = split(input).map((line: string) => parseInt(line, 10));
	for (let i = 0; i < numbers.length; i++) {
		const ni = numbers[i];
		for (let j = i + 1; j < numbers.length; j++) {
			const nj = numbers[j];
			if (ni + nj === 2020) {
				return ni * nj;
			}
		}
	}
	return 0;
};