const { __native_logger } = require('bindings')('__native_logger')
const { Transform } = require('stream')
const { Console } = require('console')

class Logger extends __native_logger {
	_opt = undefined

	constructor(opt) {
		super(0)
		this._opt = opt || {
			debug: false
		}
	}

	d(tag, data) {
		if (!tag || !data) throw new Error('Tag or message is undefined')
		// Log only if debug has been enabled
		if (this._opt.debug) {
			super.d(tag, data)
		}
	}

	e(tag, data) {
		if (!tag || !data) throw new Error('Tag or message is undefined')
		super.e(tag, data)
	}

	i(tag, data) {
		if (!tag || !data) throw new Error('Tag or message is undefined')
		super.i(tag, data)
	}

	v(tag, data) {
		if (!tag || !data) throw new Error('Tag or message is undefined')
		super.v(tag, data)
	}

	w(tag, data) {
		if (!tag || !data) throw new Error('Tag or message is undefined')
		super.w(tag, data)
	}

	debug(tag, data) {
		if (!tag || !data) throw new Error('Tag or message is undefined')
		// Log only if debug has been enabled
		if (this._opt.debug) {
			super.d(tag, data)
		}
	}

	error(tag, data) {
		if (!tag || !data) throw new Error('Tag or message is undefined')
		super.e(tag, data)
	}

	info(tag, data) {
		if (!tag || !data) throw new Error('Tag or message is undefined')
		super.i(tag, data)
	}

	verbose(tag, data) {
		if (!tag || !data) throw new Error('Tag or message is undefined')
		super.v(tag, data)
	}

	warn(tag, data) {
		if (!tag || !data) throw new Error('Tag or message is undefined')
		super.w(tag, data)
	}

	table(tag, data) {
		if (!tag || !data) throw new Error('Tag or message is undefined')
		const ts = new Transform({
			transform(chunk, enc, cb) {
				cb(null, chunk);
			},
		});
		const logger = new Console({ stdout: ts });
		logger.table(data);
		const table = (ts.read() || "").toString();
		let result = "";
		for (let row of table.split(/[\r\n]+/)) {
			let r = row.replace(/[^┬]*┬/, "┌");
			r = r.replace(/^├─*┼/, "├");
			r = r.replace(/│[^│]*/, "");
			r = r.replace(/^└─*┴/, "└");
			r = r.replace(/'/g, " ");
			result += `${r}\n`;
		}
		super.i(tag, result)
	}

}

module.exports = Logger