const Log = require("./index.js");

const TAG = "NodeJS-Logger";

Log.d(TAG, "This is an example");

// $ logcat -s NodeJS-Logger:*
// --------- beginning of main
// 01-15 10:07:57.908 18431 18431 D NodeJS-Logger: This is an example
