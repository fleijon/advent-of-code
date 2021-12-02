import { runner } from './part_one';
import { expect } from 'chai';
import { day, results, year } from '.';
import { read } from "../../lib/index";

describe('2021 - Day 1 - Part One', () => {
	it(`should resolve to ${7} when using the input`, async () => {
		expect(await runner((await read(year, day, "example.1.txt")()).input)).to.equal(7);
	});

	it(`should resolve to ${results.one.input} when using the input`, async () => {
		expect(await runner((await read(year, day)()).input)).to.equal(results.one.input);
	});

})