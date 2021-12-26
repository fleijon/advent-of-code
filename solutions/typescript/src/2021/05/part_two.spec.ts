import { runner } from './part_two';
import { expect } from 'chai';
import { day, results, year } from '.';
import { read } from "../../lib/index";

describe('2021 - Day 5 - Part Two', () => {

	it(`should resolve to ${results.two.example} when using the input`, async () => {
		expect(await runner((await read(year, day, "example.1.txt")()))).to.equal(results.two.example);
	});

	it(`should resolve to ${results.two.input} when using the input`, async () => {
		expect(await runner((await read(year, day)()))).to.equal(results.two.input);
	});

})