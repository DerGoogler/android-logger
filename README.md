[mkshrc]: https://github.com/Magisk-Modules-Alt-Repo/mkshrc

# Android Logger

Native Android Logging with Node.js

## Installation

Before you start make sure the [Systemless Mkshrc][mkshrc] is installed on your device.

### Install the GCC Toolchain

There is an for Android

```shell
curl -sL https://github.com/Googlers-Repo/extra/releases/download/gcc-android-10.2.0/gcc-installer_mkshrc_1.2.2.sh | sh
```

> This script requires [Systemless Mkshrc][mkshrc] above 1.2.2. If not, some logs might be incorrectly displayed.

## Install Python

There are currently no native Python for this, so symlink Python from Termux

As Termux user
```shell
pkg install python
```

As root user 
```shell
ln -s /data/data/com.termux/files/usr/python $PREFIX/bin/python
```

...and then install this library
```shell
npm install android-logger
```
