"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
var __generator = (this && this.__generator) || function (thisArg, body) {
    var _ = { label: 0, sent: function() { if (t[0] & 1) throw t[1]; return t[1]; }, trys: [], ops: [] }, f, y, t, g;
    return g = { next: verb(0), "throw": verb(1), "return": verb(2) }, typeof Symbol === "function" && (g[Symbol.iterator] = function() { return this; }), g;
    function verb(n) { return function (v) { return step([n, v]); }; }
    function step(op) {
        if (f) throw new TypeError("Generator is already executing.");
        while (_) try {
            if (f = 1, y && (t = op[0] & 2 ? y["return"] : op[0] ? y["throw"] || ((t = y["return"]) && t.call(y), 0) : y.next) && !(t = t.call(y, op[1])).done) return t;
            if (y = 0, t) op = [op[0] & 2, t.value];
            switch (op[0]) {
                case 0: case 1: t = op; break;
                case 4: _.label++; return { value: op[1], done: false };
                case 5: _.label++; y = op[1]; op = [0]; continue;
                case 7: op = _.ops.pop(); _.trys.pop(); continue;
                default:
                    if (!(t = _.trys, t = t.length > 0 && t[t.length - 1]) && (op[0] === 6 || op[0] === 2)) { _ = 0; continue; }
                    if (op[0] === 3 && (!t || (op[1] > t[0] && op[1] < t[3]))) { _.label = op[1]; break; }
                    if (op[0] === 6 && _.label < t[1]) { _.label = t[1]; t = op; break; }
                    if (t && _.label < t[2]) { _.label = t[2]; _.ops.push(op); break; }
                    if (t[2]) _.ops.pop();
                    _.trys.pop(); continue;
            }
            op = body.call(thisArg, _);
        } catch (e) { op = [6, e]; y = 0; } finally { f = t = 0; }
        if (op[0] & 5) throw op[1]; return { value: op[0] ? op[1] : void 0, done: true };
    }
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.read = exports.split = void 0;
var regex_1 = require("./regex");
var fs_1 = require("fs");
var split = function (input, emptyLines) {
    if (emptyLines === void 0) { emptyLines = false; }
    var split = input.split(regex_1.NEWLINE);
    if (emptyLines) {
        return split;
    }
    else {
        return split.filter(function (line) { return !!line; });
    }
};
exports.split = split;
/**
 * Factory function to create an input supplier
 *
 * @param year of the task
 * @param day of the task
 * @param file in the resources folder of the task
 */
var read = function (year, day, file) {
    if (file === void 0) { file = 'input.txt'; }
    return function () { return __awaiter(void 0, void 0, void 0, function () {
        var baseUrl, _a, input, args;
        return __generator(this, function (_b) {
            switch (_b.label) {
                case 0:
                    baseUrl = "../../resources/" + year + "/" + (day < 10 ? '0' + day : day) + "/";
                    return [4 /*yield*/, Promise.all([
                            fs_1.promises.readFile("" + baseUrl + file, {
                                encoding: 'utf-8',
                            }),
                            fs_1.promises
                                .readFile("" + baseUrl + file.split(/(.*)\..*/)[1] + ".args.json", {
                                encoding: 'utf-8',
                            })
                                .catch(function () { return undefined; }),
                        ])];
                case 1:
                    _a = _b.sent(), input = _a[0], args = _a[1];
                    return [2 /*return*/, { input: input, args: args && JSON.parse(args) }];
            }
        });
    }); };
};
exports.read = read;
