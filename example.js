const Logger = require('./index.js')

const console = new Logger({ debug: true })

const TAG = 'NodeJS-Logger'

console.debug(TAG, 'This is an example')

// $ logcat -s NodeJS-Logger:*
// --------- beginning of main
// 01-15 10:07:57.908 18431 18431 D NodeJS-Logger: This is an example

console.table(TAG, [
		{
			Query: "Package",
			Detail: 'com.googler',
		},
		{
			Query: "V. Name",
			Detail: '48.34.4',
		},
		{
			Query: "V. Code",
			Detail: '843939',
		}
	]
)