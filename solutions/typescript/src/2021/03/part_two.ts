import { read, split } from "./../../lib/";
import { day, year } from '.';

interface stacks{
    one:string[],
    zero:string[]
}

const findRemainder = (initState: string[], reducer: (v: string[], pos: number) => string[]) : string => {
    let curr: string[] = [...initState];
    let pos = 0;
    const max = initState.length;
    while(curr.length > 1 && pos < max){
        curr = reducer(curr, pos);
        pos++;
    }

    return curr[0];
}

const reducePos = (values: string[], pos: number, selector: (stacks: stacks) => string[]): string[]  => {
    const val = values.reduce<stacks>((p, v, idx) => {
        if(v[pos] === "1"){
            p.one.push(v);
        }
        else
        {
            p.zero.push(v);
        }
        return p;
    },
    {one:[], zero:[]} as stacks);
    return selector(val);
}

export const runner = (input: string): number => {
    const values = split(input);
    let oxygen = findRemainder(values, (v:string[], pos: number) => reducePos(v, pos, (stack: stacks)=> (stack.one.length < stack.zero.length) ? stack.zero : stack.one ));
    let co2 = findRemainder(values, (v:string[], pos: number) => reducePos(v, pos, (stack: stacks)=> (stack.one.length < stack.zero.length) ? stack.one : stack.zero ));

    return parseInt(oxygen, 2) * parseInt(co2, 2);
};

if (require.main === module) {
	(async () => {
		const input = await read(year, day)();
		const value = runner(input.input);
		console.log(`Result: ${value}.`);
	}
	)();
}