import { runner } from './part_two';
import { expect } from 'chai';
import { day, results, year } from '.';
import { read } from "../../lib/index";

describe('2021 - Day 1 - Part Two', () => {
	it(`should resolve to ${5} when using the input`, async () => {
		expect(await runner((await read(year, day, "example.1.txt")()).input)).to.equal(5);
	});

})