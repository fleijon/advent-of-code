import exp from 'constants';
import * as fs from 'fs'
import path from 'path';

const resources2022BasePath = "../../../../resources/2022";

export function getInput(dayStr, sampleNumber) {
    const filename = `input.${sampleNumber}.txt`;
    const relativePath = `${resources2022BasePath}/${dayStr}/${filename}`;

    const fileStringContent = readFileToString(relativePath);

    return parseFileContent(fileStringContent);
}

export function getExampleInput(dayStr, sampleNumber) {
    const filename = `example.${sampleNumber}.txt`;
    const relativePath = `${resources2022BasePath}/${dayStr}/${filename}`;

    const fileStringContent = readFileToString(relativePath);

    return parseFileContent(fileStringContent);
}

export function parseFileContent(fileContent) {
    const rows = fileContent.split("\r\n");

    return rows;
}

export function readFileToString(relativeFilePath) {
    let absolutePath = path.resolve(relativeFilePath);
    return fs.readFileSync(absolutePath).toString();
}