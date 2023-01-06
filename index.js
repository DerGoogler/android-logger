const { __native_logger } = require('bindings')('__native_logger')

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
}


module.exports = Logger
