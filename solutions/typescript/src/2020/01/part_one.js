"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.runner = void 0;
var lib_1 = require("../../lib");
var runner = function (input) {
    var numbers = (0, lib_1.split)(input).map(function (line) { return parseInt(line, 10); });
    for (var i = 0; i < numbers.length; i++) {
        var ni = numbers[i];
        for (var j = i + 1; j < numbers.length; j++) {
            var nj = numbers[j];
            if (ni + nj === 2020) {
                return ni * nj;
            }
        }
    }
    return 0;
};
exports.runner = runner;
