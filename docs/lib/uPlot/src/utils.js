import { domEnv, nav } from './dom';

// binary search for index of closest value
export function closestIdx(num, arr, lo, hi) {
	let mid;
	lo = lo || 0;
	hi = hi || arr.length - 1;
	let bitwise = hi <= 2147483647;

	while (hi - lo > 1) {
		mid = bitwise ? (lo + hi) >> 1 : floor((lo + hi) / 2);

		if (arr[mid] < num)
			lo = mid;
		else
			hi = mid;
	}

	if (num - arr[lo] <= arr[hi] - num)
		return lo;

	return hi;
}

export function nonNullIdx(data, _i0, _i1, dir) {
	for (let i = dir == 1 ? _i0 : _i1; i >= _i0 && i <= _i1; i += dir) {
		if (data[i] != null)
			return i;
	}

	return -1;
}

export function getMinMax(data, _i0, _i1, sorted) {
//	console.log("getMinMax()");

	let _min = inf;
	let _max = -inf;

	if (sorted == 1) {
		_min = data[_i0];
		_max = data[_i1];
	}
	else if (sorted == -1) {
		_min = data[_i1];
		_max = data[_i0];
	}
	else {
		for (let i = _i0; i <= _i1; i++) {
			if (data[i] != null) {
				_min = min(_min, data[i]);
				_max = max(_max, data[i]);
			}
		}
	}

	return [_min, _max];
}

export function getMinMaxLog(data, _i0, _i1) {
//	console.log("getMinMax()");

	let _min = inf;
	let _max = -inf;

	for (let i = _i0; i <= _i1; i++) {
		if (data[i] > 0) {
			_min = min(_min, data[i]);
			_max = max(_max, data[i]);
		}
	}

	return [
		_min ==  inf ?  1 : _min,
		_max == -inf ? 10 : _max,
	];
}

export function rangeLog(min, max, base, fullMags) {
	let minSign = sign(min);
	let maxSign = sign(max);

	let logFn = base == 10 ? log10 : log2;

	if (min == max) {
		if (minSign == -1) {
			min *= base;
			max /= base;
		}
		else {
			min /= base;
			max *= base;
		}
	}

	let growMinAbs = minSign == 1 ? floor : ceil;
	let growMaxAbs = maxSign == 1 ? ceil : floor;

	let minExp = growMinAbs(logFn(abs(min)));
	let maxExp = growMaxAbs(logFn(abs(max)));

	let minIncr = pow(base, minExp);
	let maxIncr = pow(base, maxExp);

	// fix values like Math.pow(10, -5) === 0.000009999999999999999
	if (minExp < 0)
		minIncr = roundDec(minIncr, -minExp);
	if (maxExp < 0)
		maxIncr = roundDec(maxIncr, -maxExp);

	if (fullMags) {
		min = minIncr * minSign;
		max = maxIncr * maxSign;
	}
	else {
		min = incrRoundDn(min, minIncr);
		max = incrRoundUp(max, maxIncr);
	}

	return [min, max];
}

export function rangeAsinh(min, max, base, fullMags) {
	let minMax = rangeLog(min, max, base, fullMags);

	if (min == 0)
		minMax[0] = 0;

	if (max == 0)
		minMax[1] = 0;

	return minMax;
}

export const rangePad = 0.1;

export const autoRangePart = {
	mode: 3,
	pad: rangePad,
};

const _eqRangePart = {
	pad:  0,
	soft: null,
	mode: 0,
};

const _eqRange = {
	min: _eqRangePart,
	max: _eqRangePart,
};

// this ensures that non-temporal/numeric y-axes get multiple-snapped padding added above/below
// TODO: also account for incrs when snapping to ensure top of axis gets a tick & value
export function rangeNum(_min, _max, mult, extra) {
	if (isObj(mult))
		return _rangeNum(_min, _max, mult);

	_eqRangePart.pad  = mult;
	_eqRangePart.soft = extra ? 0 : null;
	_eqRangePart.mode = extra ? 3 : 0;

	return _rangeNum(_min, _max, _eqRange);
}

// nullish coalesce
export function ifNull(lh, rh) {
	return lh == null ? rh : lh;
}

// checks if given index range in an array contains a non-null value
// aka a range-bounded Array.some()
export function hasData(data, idx0, idx1) {
	idx0 = ifNull(idx0, 0);
	idx1 = ifNull(idx1, data.length - 1);

	while (idx0 <= idx1) {
		if (data[idx0] != null)
			return true;
		idx0++;
	}

	return false;
}

function _rangeNum(_min, _max, cfg) {
	let cmin = cfg.min;
	let cmax = cfg.max;

	let padMin = ifNull(cmin.pad, 0);
	let padMax = ifNull(cmax.pad, 0);

	let hardMin = ifNull(cmin.hard, -inf);
	let hardMax = ifNull(cmax.hard,  inf);

	let softMin = ifNull(cmin.soft,  inf);
	let softMax = ifNull(cmax.soft, -inf);

	let softMinMode = ifNull(cmin.mode, 0);
	let softMaxMode = ifNull(cmax.mode, 0);

	let delta = _max - _min;
	let deltaMag = log10(delta);

	let scalarMax = max(abs(_min), abs(_max));
	let scalarMag = log10(scalarMax);

	let scalarMagDelta = abs(scalarMag - deltaMag);

	// this handles situations like 89.7, 89.69999999999999
	// by assuming 0.001x deltas are precision errors
//	if (delta > 0 && delta < abs(_max) / 1e3)
//		delta = 0;

	// treat data as flat if delta is less than 1 billionth
	// or range is 11+ orders of magnitude below raw values, e.g. 99999999.99999996 - 100000000.00000004
	if (delta < 1e-9 || scalarMagDelta > 10) {
		delta = 0;

		// if soft mode is 2 and all vals are flat at 0, avoid the 0.1 * 1e3 fallback
		// this prevents 0,0,0 from ranging to -100,100 when softMin/softMax are -1,1
		if (_min == 0 || _max == 0) {
			delta = 1e-9;

			if (softMinMode == 2 && softMin != inf)
				padMin = 0;

			if (softMaxMode == 2 && softMax != -inf)
				padMax = 0;
		}
	}

	let nonZeroDelta = delta || scalarMax || 1e3;
	let mag          = log10(nonZeroDelta);
	let base         = pow(10, floor(mag));

	let _padMin  = nonZeroDelta * (delta == 0 ? (_min == 0 ? .1 : 1) : padMin);
	let _newMin  = roundDec(incrRoundDn(_min - _padMin, base/10), 9);
	let _softMin = _min >= softMin && (softMinMode == 1 || softMinMode == 3 && _newMin <= softMin || softMinMode == 2 && _newMin >= softMin) ? softMin : inf;
	let minLim   = max(hardMin, _newMin < _softMin && _min >= _softMin ? _softMin : min(_softMin, _newMin));

	let _padMax  = nonZeroDelta * (delta == 0 ? (_max == 0 ? .1 : 1) : padMax);
	let _newMax  = roundDec(incrRoundUp(_max + _padMax, base/10), 9);
	let _softMax = _max <= softMax && (softMaxMode == 1 || softMaxMode == 3 && _newMax >= softMax || softMaxMode == 2 && _newMax <= softMax) ? softMax : -inf;
	let maxLim   = min(hardMax, _newMax > _softMax && _max <= _softMax ? _softMax : max(_softMax, _newMax));

	if (minLim == maxLim && minLim == 0)
		maxLim = 100;

	return [minLim, maxLim];
}

// alternative: https://stackoverflow.com/a/2254896
const numFormatter = new Intl.NumberFormat(domEnv ? nav.language : 'en-US');
export const fmtNum = val => numFormatter.format(val);

const M = Math;

export const PI = M.PI;
export const abs = M.abs;
export const floor = M.floor;
export const round = M.round;
export const ceil = M.ceil;
export const min = M.min;
export const max = M.max;
export const pow = M.pow;
export const sqrt = M.sqrt;
export const sign = M.sign;
export const log10 = M.log10;
export const log2 = M.log2;
// TODO: seems like this needs to match asinh impl if the passed v is tweaked?
export const sinh =  (v, linthresh = 1) => M.sinh(v) * linthresh;
export const asinh = (v, linthresh = 1) => M.asinh(v / linthresh);

export const inf = Infinity;

export function numIntDigits(x) {
	return (log10((x ^ (x >> 31)) - (x >> 31)) | 0) + 1;
}

export function clamp(num, _min, _max) {
	return min(max(num, _min), _max);
}

export function fnOrSelf(v) {
	return typeof v == "function" ? v : () => v;
}

export const noop = () => {};

export const retArg0 = _0 => _0;

export const retArg1 = (_0, _1) => _1;

export const retNull = _ => null;

export const retTrue = _ => true;

export const retEq = (a, b) => a == b;

// this will probably prevent tick incrs > 14 decimal places
// (we generate up to 17 dec, see fixedDec const)
const fixFloat = v => roundDec(v, 14);

export function incrRound(num, incr) {
	return fixFloat(roundDec(fixFloat(num/incr))*incr);
}

export function incrRoundUp(num, incr) {
	return fixFloat(ceil(fixFloat(num/incr))*incr);
}

export function incrRoundDn(num, incr) {
	return fixFloat(floor(fixFloat(num/incr))*incr);
}

// https://stackoverflow.com/a/48764436
// rounds half away from zero
export function roundDec(val, dec = 0) {
	if (isInt(val))
		return val;
//	else if (dec == 0)
//		return round(val);

	let p = 10 ** dec;
	let n = (val * p) * (1 + Number.EPSILON);
	return round(n) / p;
}

// https://stackoverflow.com/questions/14879691/get-number-of-digits-with-javascript/28203456#28203456
export function numDigits(x) {
	return (log10((x ^ (x >> 31)) - (x >> 31)) | 0) + 1;
}

export const fixedDec = new Map();

export function guessDec(num) {
	return ((""+num).split(".")[1] || "").length;
}

export function genIncrs(base, minExp, maxExp, mults) {
	let incrs = [];

	let multDec = mults.map(guessDec);

	for (let exp = minExp; exp < maxExp; exp++) {
		let expa = abs(exp);
		let mag = roundDec(pow(base, exp), expa);

		for (let i = 0; i < mults.length; i++) {
			let _incr = mults[i] * mag;
			let dec = (_incr >= 0 && exp >= 0 ? 0 : expa) + (exp >= multDec[i] ? 0 : multDec[i]);
			let incr = roundDec(_incr, dec);
			incrs.push(incr);
			fixedDec.set(incr, dec);
		}
	}

	return incrs;
}

//export const assign = Object.assign;

export const EMPTY_OBJ = {};
export const EMPTY_ARR = [];

export const nullNullTuple = [null, null];

export const isArr = Array.isArray;
export const isInt = Number.isInteger;

export function isStr(v) {
	return typeof v == 'string';
}

export function isObj(v) {
	let is = false;

	if (v != null) {
		let c = v.constructor;
		is = c == null || c == Object;
	}

	return is;
}

export function fastIsObj(v) {
	return v != null && typeof v == 'object';
}

const TypedArray = Object.getPrototypeOf(Uint8Array);

export function copy(o, _isObj = isObj) {
	let out;

	if (isArr(o)) {
		let val = o.find(v => v != null);

		if (isArr(val) || _isObj(val)) {
			out = Array(o.length);
			for (let i = 0; i < o.length; i++)
				out[i] = copy(o[i], _isObj);
		}
		else
			out = o.slice();
	}
	else if (o instanceof TypedArray) // also (ArrayBuffer.isView(o) && !(o instanceof DataView))
		out = o.slice();
	else if (_isObj(o)) {
		out = {};
		for (let k in o)
			out[k] = copy(o[k], _isObj);
	}
	else
		out = o;

	return out;
}

export function assign(targ) {
	let args = arguments;

	for (let i = 1; i < args.length; i++) {
		let src = args[i];

		for (let key in src) {
			if (isObj(targ[key]))
				assign(targ[key], copy(src[key]));
			else
				targ[key] = copy(src[key]);
		}
	}

	return targ;
}

// nullModes
const NULL_REMOVE = 0;  // nulls are converted to undefined (e.g. for spanGaps: true)
const NULL_RETAIN = 1;  // nulls are retained, with alignment artifacts set to undefined (default)
const NULL_EXPAND = 2;  // nulls are expanded to include any adjacent alignment artifacts

// sets undefined values to nulls when adjacent to existing nulls (minesweeper)
function nullExpand(yVals, nullIdxs, alignedLen) {
	for (let i = 0, xi, lastNullIdx = -1; i < nullIdxs.length; i++) {
		let nullIdx = nullIdxs[i];

		if (nullIdx > lastNullIdx) {
			xi = nullIdx - 1;
			while (xi >= 0 && yVals[xi] == null)
				yVals[xi--] = null;

			xi = nullIdx + 1;
			while (xi < alignedLen && yVals[xi] == null)
				yVals[lastNullIdx = xi++] = null;
		}
	}
}

// nullModes is a tables-matched array indicating how to treat nulls in each series
// output is sorted ASC on the joined field (table[0]) and duplicate join values are collapsed
export function join(tables, nullModes) {
	let xVals = new Set();

	for (let ti = 0; ti < tables.length; ti++) {
		let t = tables[ti];
		let xs = t[0];
		let len = xs.length;

		for (let i = 0; i < len; i++)
			xVals.add(xs[i]);
	}

	let data = [Array.from(xVals).sort((a, b) => a - b)];

	let alignedLen = data[0].length;

	let xIdxs = new Map();

	for (let i = 0; i < alignedLen; i++)
		xIdxs.set(data[0][i], i);

	for (let ti = 0; ti < tables.length; ti++) {
		let t = tables[ti];
		let xs = t[0];

		for (let si = 1; si < t.length; si++) {
			let ys = t[si];

			let yVals = Array(alignedLen).fill(undefined);

			let nullMode = nullModes ? nullModes[ti][si] : NULL_RETAIN;

			let nullIdxs = [];

			for (let i = 0; i < ys.length; i++) {
				let yVal = ys[i];
				let alignedIdx = xIdxs.get(xs[i]);

				if (yVal === null) {
					if (nullMode != NULL_REMOVE) {
						yVals[alignedIdx] = yVal;

						if (nullMode == NULL_EXPAND)
							nullIdxs.push(alignedIdx);
					}
				}
				else
					yVals[alignedIdx] = yVal;
			}

			nullExpand(yVals, nullIdxs, alignedLen);

			data.push(yVals);
		}
	}

	return data;
}

export const microTask = typeof queueMicrotask == "undefined" ? fn => Promise.resolve().then(fn) : queueMicrotask;