import { NEWLINE } from './regex';
import { promises } from 'fs';

export interface PartResults<T = number> {
	input: T;
	example: T;
	[key: string]: T;
}

export interface DayResults<O = number, T = O> {
	one: Partial<PartResults<O>>;
	two: Partial<PartResults<T>>;
}

export interface Input<T, A = undefined> {
	input: T;
	args?: A | undefined;
}

export const split = (input: string, emptyLines = false): string[] => {
	const split = input.split(NEWLINE);
	if (emptyLines) {
		return split;
	} else {
		return split.filter((line) => !!line);
	}
};

/**
 * Factory function to create an input supplier
 *
 * @param year of the task
 * @param day of the task
 * @param file in the resources folder of the task
 */
export const read =
	<A>(year: number, day: number, file = 'input.txt') =>
	async (): Promise<Input<string, A>> => {
		const baseUrl = `../../resources/${year}/${day < 10 ? '0' + day : day}/`;

		const [input, args] = await Promise.all([
			promises.readFile(`${baseUrl}${file}`, {
				encoding: 'utf-8',
			}) as Promise<string>,
			promises
				.readFile(`${baseUrl}${file.split(/(.*)\..*/)[1]}.args.json`, {
					encoding: 'utf-8',
				})
				.catch(() => undefined) as Promise<string>,
		]);

		return { input, args: args && JSON.parse(args) };
	};