QML Desktop framework
=====================

The QML Desktop framework provides a plugin for use in desktop shells built using QML.

### How to use

First, compile and install the plugin:

    qmake
    make
    sudo make install

Then, to use in your desktop shell, simply import the framework like this:

    import Material.Desktop 0.1

### Features

Currently, there's only a plugin for MPRIS (Media Player Remote Interfacing Specification). You can use this to control most music plays on Linux.
