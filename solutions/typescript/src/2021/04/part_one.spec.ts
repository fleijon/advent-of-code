import { runner, args } from './part_one';
import { expect } from 'chai';
import { day, results, year } from '.';
import { read } from "../../lib/index";

describe('2021 - Day 4 - Part One', () => {
	it(`should resolve to ${results.one.example} when using the input`, async () => {
		expect(await runner((await read<args>(year, day, "example.1.txt")()))).to.equal(results.one.example);
	});

	it(`should resolve to ${results.one.input} when using the input`, async () => {
		expect(await runner((await read<args>(year, day)()))).to.equal(results.one.input);
	});
})