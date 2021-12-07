import { Input, read, split } from "./../../lib/";
import { day, year } from '.';

export interface args{
	draws: number[]
}

interface board{
	isBingo: boolean
	squares: square[]
}

interface square{
	value: number,
	isMarked: boolean,
}

const mark = (board: board, number: number): board => {
	let newBoard: board = {...board, squares: [...board.squares]}
	newBoard.squares.forEach(square => {
		if(square.value === number){
			square.isMarked = true;
		}
	});

	return newBoard;
}

const colIsBingo = (board: board, colIndex: number) : boolean => {
	const size = board.squares.length;
	for (let index = colIndex + Math.sqrt(size); index < size; index+=Math.sqrt(size)) {
		const element = board.squares[index];
		if(!element.isMarked){
			return false;
		}
	}
	return true;
}

const rowIsBingo = (board: board, rowIdx : number) : boolean => {
	const size = board.squares.length;
	for (let index = rowIdx + 1; index < rowIdx+Math.sqrt(size); index++) {
		const element = board.squares[index];
		if(!element.isMarked){
			return false;
		}
	}
	return true;
}

const isBingo = (board: board) : boolean => {
	// check each col
	const size = board.squares.length;
	for (let index = 0; index < Math.sqrt(size); index++) {
		const element = board.squares[index];
		if(element.isMarked){
			if(colIsBingo(board, index)){
				return true;
			}
		}
	}

	// check row bingo
	for (let index = 0; index < size; index+=Math.sqrt(size)) {
		const element = board.squares[index];
		if(element.isMarked){
			if(rowIsBingo(board, index)){
				return true;
			}
		}
	}

	return false;
}

const prepareBoards = (input: string) : board[] =>  {
	const c = split(input);
	const boardSize = 5;
	const nMarkers = boardSize*boardSize;
	const inputValues = c.map( v => v.split(' ').map( r => parseInt(r))).flat().filter(v => !Number.isNaN(v));
	const boards: board[] = [];
	const iterations = Math.floor(inputValues.length/nMarkers);
	for (let index = 0; index < iterations; index++) {
		boards.push({ 
			isBingo : false,
			squares: inputValues.slice(index * (nMarkers), ((index + 1) * (nMarkers))).map(v => ({ value:v, isMarked: false } as square))
		} as board);
	}

	return boards;
}

export const runner = (input: Input<string, args>): number => {
	let nonBingoBoards = prepareBoards(input.input);
	let drawIndex = 0;
	while(nonBingoBoards.length > 0 && drawIndex < input.args!.draws.length){
		const drawnNumber = input.args!.draws[drawIndex];

		for (let index = 0; index < nonBingoBoards.length; index++) {
				let board = nonBingoBoards[index];
				board = mark(board, drawnNumber);
				nonBingoBoards[index] = board;

				if(isBingo(board)){
					board.isBingo = true;
					if(nonBingoBoards.length === 1){
						return drawnNumber  * nonBingoBoards[0].squares.filter(v => !v.isMarked).reduce((p, v) => p+v.value, 0)
					}
				}
		}

		nonBingoBoards = nonBingoBoards.filter(v => !v.isBingo);
		drawIndex++;
	}

	return 0;
};

if (require.main === module) {
	(async () => {
		const input = await read<args>(year, day)();
		const value = runner(input);
		console.log(`Result: ${value}.`);
	}
	)();
}