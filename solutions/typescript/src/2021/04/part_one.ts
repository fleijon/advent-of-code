import { Input, read, split } from "./../../lib/";
import { day, year } from '.';

export interface args{
	draws: number[]
}

interface board{
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
		boards.push( {
			squares: inputValues.slice(index *(nMarkers), ((index+1)*(nMarkers))).map(v => ({ value:v, isMarked: false } as square))
		} as board);
	}

	return boards;
}

export const runner = (input: Input<string, args>): number => {
	const boards = prepareBoards(input.input);
	for (let index = 0; index < input.args!.draws.length; index++) {
		const drawnNumber = input.args!.draws[index];
		for (let index = 0; index < boards.length; index++) {
			let board = boards[index];
			board = mark(board, drawnNumber);
			
			if(isBingo(board)){
				const boardScore = board.squares.reduce((p, v) => 
					(v.isMarked) ? p :
								   p+v.value
				, 0);

				return drawnNumber * boardScore;
			}
		}
	}

	return 0;
}

if (require.main === module) {
	(async () => {
		const input = await read<args>(year, day)();
		const value = runner(input);
		console.log(`Result: ${value}.`);
	}
	)();
}