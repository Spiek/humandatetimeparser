QT += core
QT -= gui

CONFIG += c++11

TARGET = HumanDateTimeParserExample
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

include(../HumanDateTimeParser.pri)
