import { Input, read, split } from "./../../lib/";
import { day, year, toLine, getAllLineCoords, Coordinate } from '.';


export const runner = (input: Input<string, unknown>): number => {
	const lines = split(input.input).map(v => toLine(v));
	const allCoord =  lines.flatMap((line) => getAllLineCoords(line, true));
	const maxX =  allCoord.reduce<number>((prev: number, curr, idx): number => 
		prev < curr.x ? curr.x :
		prev
	, 0);
	const maxY =  allCoord.reduce<number>((prev: number, curr, idx): number => 
		prev < curr.y ? curr.y :
		prev
	, 0);
	const boardSize = [maxY+1, maxX+1];
	const board = new Array<number>(boardSize[0])
						.fill(0)
						.map(() => 
							new Array<number>(boardSize[1]).fill(0)
						);
	const popBoard = allCoord.reduce<number[][]>( (prev, curr, idx)=> {
		prev[curr.y][curr.x] ++;
		return prev;
	}, board );
	return popBoard.flat().filter(v => v > 1).length;
}

if (require.main === module) {
	(async () => {
		const input = await read(year, day)();
		const value = runner(input as Input<string, unknown>);
		console.log(`Result: ${value}.`);
	}
	)().catch((r)=>console.log(r));
}