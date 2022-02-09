[![Build status](https://ci.appveyor.com/api/projects/status/2n6fgm5hbwv3ntsn?svg=true)](https://ci.appveyor.com/project/DominikCebula/npp-java-plugin)
[![GitHub release](https://img.shields.io/github/release/dominikcebula/npp-java-plugin.svg)](https://github.com/dominikcebula/npp-java-plugin/releases)

# Introduction

## What is NppJavaPlugin?

NppJavaPlugin is a Java Plugin for Notepad++, which allows you to compile and run Java code directly from Notepad++.

![npp-java-plugin-screenshot](/npp-java-plugin/npp-java-plugin-screenshot.png)

## Why would I want to use NppJavaPlugin?

NppJavaPlugin was created with following use cases in mind:
* Simple Code Experiments
* Simple Code Creation for Education Purposes
* Preparing for a Coding Interview (Amazon, Facebook, Google, Netflix, …)
* Preparing for a Java Certification
   * Oracle Certified Professional: Java SE 17 Developer (1Z0-829)
   * Oracle Certified Professional: Java SE 11 Developer (1Z0-819)
   * Oracle Certified Associate Java SE 8 Programmer (1Z0-808)
   * Oracle Certified Professional Java SE 8 Programmer (1Z0-809)

Whenever preparing for a Coding Interview or a Java Certification, you should create a practice environment that does **not** provide you with Integrated Development Environment (IDE) features like Code Completion, Syntax Highlight, Code Generation, Early Error Checking. During regular development IDE does a very good job of making developers more productive through those features, however during a Coding Interview or a Java Certification Exam, an environment under which you will take the exam, will not include those features. This is why it is important to practice without those features to make sure that you can write code accurately and fluently without having to rely on mentioned IDE features.

In other cases I recommend using a full IDE like IntelliJ, Eclipse, NetBeans.

## What functionalities are provided by NppJavaPlugin?

After installing NppJavaPlugin following options will be available under Plugins -> Java Plugin menu:
* Compile
* Run
* Compile and Run

On top of it, NppJavaPlugin also includes Java Console which will output compilation issues if those are found. Java Console can be manually shown with usage of “Show/Hide Java Console” option.

## Does NppJavaPlugin include any default keyboard shortcuts?

Yes, by default following keyboard shortcuts are configured:
* Compile - Shift + F8
* Run - Shift + F9
* Compile and Run - Shift + F10
* Clear Java Console - Shift + F11
* Show/Hide Java Console - Shift + F12

Those can be changed using Settings -> Shortcut Mapper -> Plugin commands option. If you need more information, more precise instructions can be found here: [https://npp-user-manual.org/docs/preferences/#shortcut-mapper](https://npp-user-manual.org/docs/preferences/#shortcut-mapper)

# Installation

## Prerequisites

* Java Development Kit (JDK) is installed
   * Plugin should work with any version
   * Plugin should work with any Java distribution
   * Here are some links on where you can download JDK:
      * [https://adoptium.net/](https://adoptium.net/)
      * [https://www.oracle.com/java/technologies/downloads/](https://www.oracle.com/java/technologies/downloads/)
* JAVA_HOME system property is set
   * [https://www.baeldung.com/java-home-on-windows-7-8-10-mac-os-x-linux#windows](https://www.baeldung.com/java-home-on-windows-7-8-10-mac-os-x-linux#windows)

## Automatic

1. Go to Plugins -> Plugins Admin
2. Search for "Java Plugin"
3. Check "Java Plugin"
4. Click Install

If you need more information, more precise instructions can be found here: [https://npp-user-manual.org/docs/plugins/#install-using-plugins-admin](https://npp-user-manual.org/docs/plugins/#install-using-plugins-admin)

## Manual

1. Download ZIP file from [https://github.com/dominikcebula/npp-java-plugin/releases](https://github.com/dominikcebula/npp-java-plugin/releases)
2. Unpack ZIP file to your Notepad++ installation folder, for example “C:\Program Files\Notepad++\plugins\NppJavaPlugin”

If you need more information, more precise instructions can be found here: [https://npp-user-manual.org/docs/plugins/#install-plugin-manually](https://npp-user-manual.org/docs/plugins/#install-plugin-manually)

# Ideas for future versions

* Tech:
   * Automated Test Coverage and Full CI - Unit and Integration Tests (Testing Pyramid)
   * Automated Code Quality Scans
   * Automated Security Scans (SAST)
   * Support for ARM64
* Features:
   * Compilation Feedback - after compilation is executed, if errors are detected, lines that contains issues are marked as red
   * Run Dialog - user can set program arguments for program execution
   * Run Dialog - user can set input for stdin from file
   * Run Dialog - user can redirect stdout and/or stderr to file
   * JDK autodetection - if JAVA_HOME is not set, plugin should automatically detect and find JDK
   * Clean Action - plugin deletes all created “.class” files when user clicks “Clean” option from menu
   * Configuration Dialog - user can define JDK that should be used, without plugin having to rely on JAVA_HOME system variable or autodetection
   * Configuration Dialog - user can set flags for code compilation
   * Configuration Dialog - user can set additional classpath elements for compilation and execution
   * Run Dialog - user can set environment variables for program execution
   * Java Console - ability to configure font, font size, colors for info, warnings, errors
   * Configuration Dialog - user can decide if application should execute in a separate command prompt or if it should execute under Plugin Java Console

# Contribution Rules

You are more than welcome to contribute, but please keep in mind few rules:
* Use Modern C++ (C++11, C++17, …)
* Use Clean Code
* Use SOLID
* Use GoF Design Patterns (when applicable)
* Use KISS, DRY, YAGNI
* Use Component Coupling and Cohesion Principles (REP, CRP, CCP, ADP, SDP, SAP)
* Don't overdesign

# Author

Dominik Cebula <br/>
[dominikcebula@gmail.com](mailto:dominikcebula@gmail.com) <br/>
[http://dominikcebula.com/](http://dominikcebula.com/) <br/>
