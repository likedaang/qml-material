QML Desktop
=====================

[![GitHub release](https://img.shields.io/github/release/papyros/qml-desktop.svg)](https://github.com/papyros/qml-desktop)
[![Build Status](https://travis-ci.org/papyros/qml-desktop.svg?branch=master)](https://travis-ci.org/papyros/qml-desktop)
[![GitHub issues](https://img.shields.io/github/issues/papyros/qml-desktop.svg)](https://github.com/papyros/qml-desktop/issues)
[![Bountysource](https://www.bountysource.com/badge/team?team_id=48685&style=bounties_received)](https://www.bountysource.com/teams/papyros/issues?utm_source=Papyros&utm_medium=shield&utm_campaign=bounties_received)

The QML Desktop framework provides a plugin for QML that exposes different system-integrated DBus "components" that are useful for desktop shells as well as apps that would like to get access to notifications or music players, for example.

### How to use

First, compile and install the plugin:

    qmake
    make
    sudo make install

Then, to use in your desktop shell, simply import the framework like this:

    import Material.Desktop 0.1

### Components
 - MprisConnection
 - NotificationServer
 - UPower
 - DesktopFile + Scrobbler
 - Sound + Mixer
 - KeyEventFilter
 
### To Do
 - Add documentation
 - Port other components to qquicklist for animations
 - Add tests
