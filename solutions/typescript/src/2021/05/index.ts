import { DayResults } from "src/lib";

export const year = 2021;
export const day = 5;

export const results: DayResults = {
	one: {
		input: 4745,
        example: 5
	},
    two: {
        input: 18442,
        example: 12
    }
};

export interface Coordinate {
    x: number;
    y: number;
}

export interface Line {
    start: Coordinate;
    end: Coordinate
}

export const getAllLineCoords = (line: Line, useDiagonal: Boolean): Coordinate[] => {

    if(isDiagonal(line)){
        if(useDiagonal){
            var toX = Math.max(line.end.x, line.start.x);
            var fromX= Math.min(line.end.x, line.start.x);
            const x = createCoordsFromTo(fromX, toX + 1, (val): Coordinate => { return { x: val, y: line.end.y} as Coordinate  });
            const toY = Math.max(line.end.y, line.start.y);
            const fromY = Math.min(line.end.y, line.start.y);
            const xOrdered = line.end.x < line.start.x ? x.reverse() : x;
            const y = createCoordsFromTo(fromY, toY + 1, (val): Coordinate => { return { x: line.start.x, y: val} as Coordinate  });
            const yOrdered = line.end.y < line.start.y ? y.reverse() : y;
            const vals = xOrdered.map((val, indx): Coordinate => { return { x:val.x, y:yOrdered[indx].y } as Coordinate });
            return vals;
        }
        else{
            return [];
        }
    }
    else if(isHorizontal(line)){
        const to = Math.max(line.end.x, line.start.x);
        const from = Math.min(line.end.x, line.start.x);
        return createCoordsFromTo(from, to + 1, (val): Coordinate => { return { x: val, y: line.end.y} as Coordinate  });
    }
    else if(isVertical(line)){
        const to = Math.max(line.end.y, line.start.y);
        const from = Math.min(line.end.y, line.start.y);
        return createCoordsFromTo(from, to + 1, (val): Coordinate => { return { x: line.start.x, y: val} as Coordinate  });
    }
    else{
        return [];
    }
}

export const isDiagonal = (line: Line) => {
    return line.end.x != line.start.x && line.end.y != line.start.y
}

export const isHorizontal = (line: Line) => {
    return line.end.x != line.start.x;
}

export const isVertical = (line: Line) => {
    return line.end.y != line.start.y;
}

function createCoordsFromTo(from: number, to: number, factory: (x:number) => Coordinate ): Coordinate[]{
    return [...Array(to-from)].map((_, i) => factory(i+from));
}

export const toLine = (stringCoord: string): Line => {
    return stringCoord
            .split(" -> ")
            .map( v => v.split(",").reduce<Coordinate>((p, v, idx) => 
                (idx == 0) ? {...p, x: parseInt(v)} :
                            {...p, y: parseInt(v)}, {} as Coordinate))
            .reduce<Line>((p, v, idx) => 
                (idx == 0) ? {...p, start: v} : 
                            {...p, end: v}, {} as Line
            );
}