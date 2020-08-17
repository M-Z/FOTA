# -*- coding: utf-8 -*-
# Form implementation generated from reading ui file 'kk.ui'
#
# Created by: PyQt5 UI code generator 5.5
#
# WARNING! All changes made in this file will be lost!
import img_rc
from PyQt5 import QtCore
from PyQt5 import QtGui
from PyQt5 import QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(640, 440)
        MainWindow.setMinimumSize(QtCore.QSize(640, 440))
        MainWindow.setMaximumSize(QtCore.QSize(640, 440))
        MainWindow.setStyleSheet(
            "QWidget {\n"
            "  background-color: #19232D;\n"
            "  border: 0px solid #32414B;\n"
            "  padding: 0px;\n"
            "  color: #F0F0F0;\n"
            "  selection-background-color: #1464A0;\n"
            "  selection-color: #F0F0F0;\n"
            "}\n"
            "\n"
            "QWidget:disabled {\n"
            "  background-color: #19232D;\n"
            "  color: #787878;\n"
            "  selection-background-color: #14506E;\n"
            "  selection-color: #787878;\n"
            "}\n"
            "\n"
            "QWidget::item:selected {\n"
            "  background-color: #1464A0;\n"
            "}\n"
            "\n"
            "QWidget::item:hover {\n"
            "  background-color: #148CD2;\n"
            "  color: #32414B;\n"
            "}\n"
            "\n"
            "/* QMainWindow ------------------------------------------------------------\n"
            "\n"
            "This adjusts the splitter in the dock widget, not qsplitter\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qmainwindow\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QMainWindow::separator {\n"
            "  background-color: #32414B;\n"
            "  border: 0px solid #19232D;\n"
            "  spacing: 0px;\n"
            "  padding: 2px;\n"
            "}\n"
            "\n"
            "QMainWindow::separator:hover {\n"
            "  background-color: #505F69;\n"
            "  border: 0px solid #148CD2;\n"
            "}\n"
            "\n"
            "QMainWindow::separator:horizontal {\n"
            "  width: 5px;\n"
            "  margin-top: 2px;\n"
            "  margin-bottom: 2px;\n"
            '  image: url(":/qss_icons/rc/toolbar_separator_vertical.png");\n'
            "}\n"
            "\n"
            "QMainWindow::separator:vertical {\n"
            "  height: 5px;\n"
            "  margin-left: 2px;\n"
            "  margin-right: 2px;\n"
            '  image: url(":/qss_icons/rc/toolbar_separator_horizontal.png");\n'
            "}\n"
            "\n"
            "/* QToolTip ---------------------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qtooltip\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QToolTip {\n"
            "  background-color: #148CD2;\n"
            "  border: 1px solid #19232D;\n"
            "  color: #19232D;\n"
            "  /* Remove padding, for fix combo box tooltip */\n"
            "  padding: 0px;\n"
            "  /* Remove opacity, fix #174 - may need to use RGBA */\n"
            "}\n"
            "\n"
            "/* QStatusBar -------------------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qstatusbar\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QStatusBar {\n"
            "  border: 1px solid #32414B;\n"
            "  /* Fixes Spyder #9120, #9121 */\n"
            "  background: #32414B;\n"
            "  /* Fixes #205, white vertical borders separating items */\n"
            "}\n"
            "\n"
            "QStatusBar::item {\n"
            "  border: none;\n"
            "}\n"
            "\n"
            "QStatusBar QToolTip {\n"
            "  background-color: #148CD2;\n"
            "  border: 1px solid #19232D;\n"
            "  color: #19232D;\n"
            "  /* Remove padding, for fix combo box tooltip */\n"
            "  padding: 0px;\n"
            "  /* Reducing transparency to read better */\n"
            "  opacity: 230;\n"
            "}\n"
            "\n"
            "QStatusBar QLabel {\n"
            "  /* Fixes Spyder #9120, #9121 */\n"
            "  background: transparent;\n"
            "}\n"
            "\n"
            "/* QCheckBox --------------------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qcheckbox\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QCheckBox {\n"
            "  background-color: #19232D;\n"
            "  color: #F0F0F0;\n"
            "  spacing: 4px;\n"
            "  outline: none;\n"
            "  padding-top: 4px;\n"
            "  padding-bottom: 4px;\n"
            "}\n"
            "\n"
            "QCheckBox:focus {\n"
            "  border: none;\n"
            "}\n"
            "\n"
            "QCheckBox QWidget:disabled {\n"
            "  background-color: #19232D;\n"
            "  color: #787878;\n"
            "}\n"
            "\n"
            "QCheckBox::indicator {\n"
            "  margin-left: 4px;\n"
            "  height: 16px;\n"
            "  width: 16px;\n"
            "}\n"
            "\n"
            "QCheckBox::indicator:unchecked {\n"
            '  image: url(":/qss_icons/rc/checkbox_unchecked.png");\n'
            "}\n"
            "\n"
            "QCheckBox::indicator:unchecked:hover, QCheckBox::indicator:unchecked:focus, QCheckBox::indicator:unchecked:pressed {\n"
            "  border: none;\n"
            '  image: url(":/qss_icons/rc/checkbox_unchecked_focus.png");\n'
            "}\n"
            "\n"
            "QCheckBox::indicator:unchecked:disabled {\n"
            '  image: url(":/qss_icons/rc/checkbox_unchecked_disabled.png");\n'
            "}\n"
            "\n"
            "QCheckBox::indicator:checked {\n"
            '  image: url(":/qss_icons/rc/checkbox_checked.png");\n'
            "}\n"
            "\n"
            "QCheckBox::indicator:checked:hover, QCheckBox::indicator:checked:focus, QCheckBox::indicator:checked:pressed {\n"
            "  border: none;\n"
            '  image: url(":/qss_icons/rc/checkbox_checked_focus.png");\n'
            "}\n"
            "\n"
            "QCheckBox::indicator:checked:disabled {\n"
            '  image: url(":/qss_icons/rc/checkbox_checked_disabled.png");\n'
            "}\n"
            "\n"
            "QCheckBox::indicator:indeterminate {\n"
            '  image: url(":/qss_icons/rc/checkbox_indeterminate.png");\n'
            "}\n"
            "\n"
            "QCheckBox::indicator:indeterminate:disabled {\n"
            '  image: url(":/qss_icons/rc/checkbox_indeterminate_disabled.png");\n'
            "}\n"
            "\n"
            "QCheckBox::indicator:indeterminate:focus, QCheckBox::indicator:indeterminate:hover, QCheckBox::indicator:indeterminate:pressed {\n"
            '  image: url(":/qss_icons/rc/checkbox_indeterminate_focus.png");\n'
            "}\n"
            "\n"
            "/* QGroupBox --------------------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qgroupbox\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QGroupBox {\n"
            "  font-weight: bold;\n"
            "  border: 1px solid #32414B;\n"
            "  border-radius: 4px;\n"
            "  padding: 4px;\n"
            "  margin-top: 16px;\n"
            "}\n"
            "\n"
            "QGroupBox::title {\n"
            "  subcontrol-origin: margin;\n"
            "  subcontrol-position: top left;\n"
            "  left: 3px;\n"
            "  padding-left: 3px;\n"
            "  padding-right: 5px;\n"
            "  padding-top: 8px;\n"
            "  padding-bottom: 16px;\n"
            "}\n"
            "\n"
            "QGroupBox::indicator {\n"
            "  margin-left: 2px;\n"
            "  height: 12px;\n"
            "  width: 12px;\n"
            "}\n"
            "\n"
            "QGroupBox::indicator:unchecked:hover, QGroupBox::indicator:unchecked:focus, QGroupBox::indicator:unchecked:pressed {\n"
            "  border: none;\n"
            '  image: url(":/qss_icons/rc/checkbox_unchecked_focus.png");\n'
            "}\n"
            "\n"
            "QGroupBox::indicator:unchecked:disabled {\n"
            '  image: url(":/qss_icons/rc/checkbox_unchecked_disabled.png");\n'
            "}\n"
            "\n"
            "QGroupBox::indicator:checked:hover, QGroupBox::indicator:checked:focus, QGroupBox::indicator:checked:pressed {\n"
            "  border: none;\n"
            '  image: url(":/qss_icons/rc/checkbox_checked_focus.png");\n'
            "}\n"
            "\n"
            "QGroupBox::indicator:checked:disabled {\n"
            '  image: url(":/qss_icons/rc/checkbox_checked_disabled.png");\n'
            "}\n"
            "\n"
            "/* QRadioButton -----------------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qradiobutton\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QRadioButton {\n"
            "  background-color: #19232D;\n"
            "  color: #F0F0F0;\n"
            "  spacing: 4px;\n"
            "  padding: 0px;\n"
            "  border: none;\n"
            "  outline: none;\n"
            "}\n"
            "\n"
            "QRadioButton:focus {\n"
            "  border: none;\n"
            "}\n"
            "\n"
            "QRadioButton:disabled {\n"
            "  background-color: #19232D;\n"
            "  color: #787878;\n"
            "  border: none;\n"
            "  outline: none;\n"
            "}\n"
            "\n"
            "QRadioButton QWidget {\n"
            "  background-color: #19232D;\n"
            "  color: #F0F0F0;\n"
            "  spacing: 0px;\n"
            "  padding: 0px;\n"
            "  outline: none;\n"
            "  border: none;\n"
            "}\n"
            "\n"
            "QRadioButton::indicator {\n"
            "  border: none;\n"
            "  outline: none;\n"
            "  margin-left: 4px;\n"
            "  height: 16px;\n"
            "  width: 16px;\n"
            "}\n"
            "\n"
            "QRadioButton::indicator:unchecked {\n"
            '  image: url(":/qss_icons/rc/radio_unchecked.png");\n'
            "}\n"
            "\n"
            "QRadioButton::indicator:unchecked:hover, QRadioButton::indicator:unchecked:focus, QRadioButton::indicator:unchecked:pressed {\n"
            "  border: none;\n"
            "  outline: none;\n"
            '  image: url(":/qss_icons/rc/radio_unchecked_focus.png");\n'
            "}\n"
            "\n"
            "QRadioButton::indicator:unchecked:disabled {\n"
            '  image: url(":/qss_icons/rc/radio_unchecked_disabled.png");\n'
            "}\n"
            "\n"
            "QRadioButton::indicator:checked {\n"
            "  border: none;\n"
            "  outline: none;\n"
            '  image: url(":/qss_icons/rc/radio_checked.png");\n'
            "}\n"
            "\n"
            "QRadioButton::indicator:checked:hover, QRadioButton::indicator:checked:focus, QRadioButton::indicator:checked:pressed {\n"
            "  border: none;\n"
            "  outline: none;\n"
            '  image: url(":/qss_icons/rc/radio_checked_focus.png");\n'
            "}\n"
            "\n"
            "QRadioButton::indicator:checked:disabled {\n"
            "  outline: none;\n"
            '  image: url(":/qss_icons/rc/radio_checked_disabled.png");\n'
            "}\n"
            "\n"
            "/* QMenuBar ---------------------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qmenubar\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QMenuBar {\n"
            "  background-color: #32414B;\n"
            "  padding: 2px;\n"
            "  border: 1px solid #19232D;\n"
            "  color: #F0F0F0;\n"
            "}\n"
            "\n"
            "QMenuBar:focus {\n"
            "  border: 1px solid #148CD2;\n"
            "}\n"
            "\n"
            "QMenuBar::item {\n"
            "  background: transparent;\n"
            "  padding: 4px;\n"
            "}\n"
            "\n"
            "QMenuBar::item:selected {\n"
            "  padding: 4px;\n"
            "  background: transparent;\n"
            "  border: 0px solid #32414B;\n"
            "}\n"
            "\n"
            "QMenuBar::item:pressed {\n"
            "  padding: 4px;\n"
            "  border: 0px solid #32414B;\n"
            "  background-color: #148CD2;\n"
            "  color: #F0F0F0;\n"
            "  margin-bottom: 0px;\n"
            "  padding-bottom: 0px;\n"
            "}\n"
            "\n"
            "/* QMenu ------------------------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qmenu\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QMenu {\n"
            "  border: 0px solid #32414B;\n"
            "  color: #F0F0F0;\n"
            "  margin: 0px;\n"
            "}\n"
            "\n"
            "QMenu::separator {\n"
            "  height: 1px;\n"
            "  background-color: #505F69;\n"
            "  color: #F0F0F0;\n"
            "}\n"
            "\n"
            "QMenu::icon {\n"
            "  margin: 0px;\n"
            "  padding-left: 8px;\n"
            "}\n"
            "\n"
            "QMenu::item {\n"
            "  background-color: #32414B;\n"
            "  padding: 4px 24px 4px 24px;\n"
            "  /* Reserve space for selection border */\n"
            "  border: 1px transparent #32414B;\n"
            "}\n"
            "\n"
            "QMenu::item:selected {\n"
            "  color: #F0F0F0;\n"
            "}\n"
            "\n"
            "QMenu::indicator {\n"
            "  width: 12px;\n"
            "  height: 12px;\n"
            "  padding-left: 6px;\n"
            "  /* non-exclusive indicator = check box style indicator (see QActionGroup::setExclusive) */\n"
            "  /* exclusive indicator = radio button style indicator (see QActionGroup::setExclusive) */\n"
            "}\n"
            "\n"
            "QMenu::indicator:non-exclusive:unchecked {\n"
            '  image: url(":/qss_icons/rc/checkbox_unchecked.png");\n'
            "}\n"
            "\n"
            "QMenu::indicator:non-exclusive:unchecked:selected {\n"
            '  image: url(":/qss_icons/rc/checkbox_unchecked_disabled.png");\n'
            "}\n"
            "\n"
            "QMenu::indicator:non-exclusive:checked {\n"
            '  image: url(":/qss_icons/rc/checkbox_checked.png");\n'
            "}\n"
            "\n"
            "QMenu::indicator:non-exclusive:checked:selected {\n"
            '  image: url(":/qss_icons/rc/checkbox_checked_disabled.png");\n'
            "}\n"
            "\n"
            "QMenu::indicator:exclusive:unchecked {\n"
            '  image: url(":/qss_icons/rc/radio_unchecked.png");\n'
            "}\n"
            "\n"
            "QMenu::indicator:exclusive:unchecked:selected {\n"
            '  image: url(":/qss_icons/rc/radio_unchecked_disabled.png");\n'
            "}\n"
            "\n"
            "QMenu::indicator:exclusive:checked {\n"
            '  image: url(":/qss_icons/rc/radio_checked.png");\n'
            "}\n"
            "\n"
            "QMenu::indicator:exclusive:checked:selected {\n"
            '  image: url(":/qss_icons/rc/radio_checked_disabled.png");\n'
            "}\n"
            "\n"
            "QMenu::right-arrow {\n"
            "  margin: 5px;\n"
            '  image: url(":/qss_icons/rc/arrow_right.png");\n'
            "  height: 12px;\n"
            "  width: 12px;\n"
            "}\n"
            "\n"
            "/* QAbstractItemView ------------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qcombobox\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QAbstractItemView {\n"
            "  alternate-background-color: #19232D;\n"
            "  color: #F0F0F0;\n"
            "  border: 1px solid #32414B;\n"
            "  border-radius: 4px;\n"
            "}\n"
            "\n"
            "QAbstractItemView QLineEdit {\n"
            "  padding: 2px;\n"
            "}\n"
            "\n"
            "/* QAbstractScrollArea ----------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qabstractscrollarea\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QAbstractScrollArea {\n"
            "  background-color: #19232D;\n"
            "  border: 1px solid #32414B;\n"
            "  border-radius: 4px;\n"
            "  padding: 2px;\n"
            "  /* fix #159 */\n"
            "  min-height: 1.25em;\n"
            "  /* fix #159 */\n"
            "  color: #F0F0F0;\n"
            "}\n"
            "\n"
            "QAbstractScrollArea:disabled {\n"
            "  color: #787878;\n"
            "}\n"
            "\n"
            "/* QScrollArea ------------------------------------------------------------\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QScrollArea QWidget QWidget:disabled {\n"
            "  background-color: #19232D;\n"
            "}\n"
            "\n"
            "/* QScrollBar -------------------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qscrollbar\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QScrollBar:horizontal {\n"
            "  height: 16px;\n"
            "  margin: 2px 16px 2px 16px;\n"
            "  border: 1px solid #32414B;\n"
            "  border-radius: 4px;\n"
            "  background-color: #19232D;\n"
            "}\n"
            "\n"
            "QScrollBar:vertical {\n"
            "  background-color: #19232D;\n"
            "  width: 16px;\n"
            "  margin: 16px 2px 16px 2px;\n"
            "  border: 1px solid #32414B;\n"
            "  border-radius: 4px;\n"
            "}\n"
            "\n"
            "QScrollBar::handle:horizontal {\n"
            "  background-color: #787878;\n"
            "  border: 1px solid #32414B;\n"
            "  border-radius: 4px;\n"
            "  min-width: 8px;\n"
            "}\n"
            "\n"
            "QScrollBar::handle:horizontal:hover {\n"
            "  background-color: #148CD2;\n"
            "  border: 1px solid #148CD2;\n"
            "  border-radius: 4px;\n"
            "  min-width: 8px;\n"
            "}\n"
            "\n"
            "QScrollBar::handle:horizontal:focus {\n"
            "  border: 1px solid #1464A0;\n"
            "}\n"
            "\n"
            "QScrollBar::handle:vertical {\n"
            "  background-color: #787878;\n"
            "  border: 1px solid #32414B;\n"
            "  min-height: 8px;\n"
            "  border-radius: 4px;\n"
            "}\n"
            "\n"
            "QScrollBar::handle:vertical:hover {\n"
            "  background-color: #148CD2;\n"
            "  border: 1px solid #148CD2;\n"
            "  border-radius: 4px;\n"
            "  min-height: 8px;\n"
            "}\n"
            "\n"
            "QScrollBar::handle:vertical:focus {\n"
            "  border: 1px solid #1464A0;\n"
            "}\n"
            "\n"
            "QScrollBar::add-line:horizontal {\n"
            "  margin: 0px 0px 0px 0px;\n"
            '  border-image: url(":/qss_icons/rc/arrow_right_disabled.png");\n'
            "  height: 12px;\n"
            "  width: 12px;\n"
            "  subcontrol-position: right;\n"
            "  subcontrol-origin: margin;\n"
            "}\n"
            "\n"
            "QScrollBar::add-line:horizontal:hover, QScrollBar::add-line:horizontal:on {\n"
            '  border-image: url(":/qss_icons/rc/arrow_right.png");\n'
            "  height: 12px;\n"
            "  width: 12px;\n"
            "  subcontrol-position: right;\n"
            "  subcontrol-origin: margin;\n"
            "}\n"
            "\n"
            "QScrollBar::add-line:vertical {\n"
            "  margin: 3px 0px 3px 0px;\n"
            '  border-image: url(":/qss_icons/rc/arrow_down_disabled.png");\n'
            "  height: 12px;\n"
            "  width: 12px;\n"
            "  subcontrol-position: bottom;\n"
            "  subcontrol-origin: margin;\n"
            "}\n"
            "\n"
            "QScrollBar::add-line:vertical:hover, QScrollBar::add-line:vertical:on {\n"
            '  border-image: url(":/qss_icons/rc/arrow_down.png");\n'
            "  height: 12px;\n"
            "  width: 12px;\n"
            "  subcontrol-position: bottom;\n"
            "  subcontrol-origin: margin;\n"
            "}\n"
            "\n"
            "QScrollBar::sub-line:horizontal {\n"
            "  margin: 0px 3px 0px 3px;\n"
            '  border-image: url(":/qss_icons/rc/arrow_left_disabled.png");\n'
            "  height: 12px;\n"
            "  width: 12px;\n"
            "  subcontrol-position: left;\n"
            "  subcontrol-origin: margin;\n"
            "}\n"
            "\n"
            "QScrollBar::sub-line:horizontal:hover, QScrollBar::sub-line:horizontal:on {\n"
            '  border-image: url(":/qss_icons/rc/arrow_left.png");\n'
            "  height: 12px;\n"
            "  width: 12px;\n"
            "  subcontrol-position: left;\n"
            "  subcontrol-origin: margin;\n"
            "}\n"
            "\n"
            "QScrollBar::sub-line:vertical {\n"
            "  margin: 3px 0px 3px 0px;\n"
            '  border-image: url(":/qss_icons/rc/arrow_up_disabled.png");\n'
            "  height: 12px;\n"
            "  width: 12px;\n"
            "  subcontrol-position: top;\n"
            "  subcontrol-origin: margin;\n"
            "}\n"
            "\n"
            "QScrollBar::sub-line:vertical:hover, QScrollBar::sub-line:vertical:on {\n"
            '  border-image: url(":/qss_icons/rc/arrow_up.png");\n'
            "  height: 12px;\n"
            "  width: 12px;\n"
            "  subcontrol-position: top;\n"
            "  subcontrol-origin: margin;\n"
            "}\n"
            "\n"
            "QScrollBar::up-arrow:horizontal, QScrollBar::down-arrow:horizontal {\n"
            "  background: none;\n"
            "}\n"
            "\n"
            "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {\n"
            "  background: none;\n"
            "}\n"
            "\n"
            "QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {\n"
            "  background: none;\n"
            "}\n"
            "\n"
            "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {\n"
            "  background: none;\n"
            "}\n"
            "\n"
            "/* QTextEdit --------------------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-specific-widgets\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QTextEdit {\n"
            "  background-color: #19232D;\n"
            "  color: #F0F0F0;\n"
            "  border-radius: 4px;\n"
            "  border: 1px solid #32414B;\n"
            "}\n"
            "\n"
            "QTextEdit:hover {\n"
            "  border: 1px solid #148CD2;\n"
            "  color: #F0F0F0;\n"
            "}\n"
            "\n"
            "QTextEdit:focus {\n"
            "  border: 1px solid #1464A0;\n"
            "}\n"
            "\n"
            "QTextEdit:selected {\n"
            "  background: #1464A0;\n"
            "  color: #32414B;\n"
            "}\n"
            "\n"
            "/* QPlainTextEdit ---------------------------------------------------------\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QPlainTextEdit {\n"
            "  background-color: #19232D;\n"
            "  color: #F0F0F0;\n"
            "  border-radius: 4px;\n"
            "  border: 1px solid #32414B;\n"
            "}\n"
            "\n"
            "QPlainTextEdit:hover {\n"
            "  border: 1px solid #148CD2;\n"
            "  color: #F0F0F0;\n"
            "}\n"
            "\n"
            "QPlainTextEdit:focus {\n"
            "  border: 1px solid #1464A0;\n"
            "}\n"
            "\n"
            "QPlainTextEdit:selected {\n"
            "  background: #1464A0;\n"
            "  color: #32414B;\n"
            "}\n"
            "\n"
            "/* QSizeGrip --------------------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qsizegrip\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QSizeGrip {\n"
            "  background: transparent;\n"
            "  width: 12px;\n"
            "  height: 12px;\n"
            '  image: url(":/qss_icons/rc/window_grip.png");\n'
            "}\n"
            "\n"
            "/* QStackedWidget ---------------------------------------------------------\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QStackedWidget {\n"
            "  padding: 2px;\n"
            "  border: 1px solid #32414B;\n"
            "  border: 1px solid #19232D;\n"
            "}\n"
            "\n"
            "/* QToolBar ---------------------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qtoolbar\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QToolBar {\n"
            "  background-color: #32414B;\n"
            "  border-bottom: 1px solid #19232D;\n"
            "  padding: 2px;\n"
            "  font-weight: bold;\n"
            "  spacing: 2px;\n"
            "}\n"
            "\n"
            "QToolBar QToolButton {\n"
            "  background-color: #32414B;\n"
            "  border: 1px solid #32414B;\n"
            "}\n"
            "\n"
            "QToolBar QToolButton:hover {\n"
            "  border: 1px solid #148CD2;\n"
            "}\n"
            "\n"
            "QToolBar QToolButton:checked {\n"
            "  border: 1px solid #19232D;\n"
            "  background-color: #19232D;\n"
            "}\n"
            "\n"
            "QToolBar QToolButton:checked:hover {\n"
            "  border: 1px solid #148CD2;\n"
            "}\n"
            "\n"
            "QToolBar::handle:horizontal {\n"
            "  width: 16px;\n"
            '  image: url(":/qss_icons/rc/toolbar_move_horizontal.png");\n'
            "}\n"
            "\n"
            "QToolBar::handle:vertical {\n"
            "  height: 16px;\n"
            '  image: url(":/qss_icons/rc/toolbar_move_vertical.png");\n'
            "}\n"
            "\n"
            "QToolBar::separator:horizontal {\n"
            "  width: 16px;\n"
            '  image: url(":/qss_icons/rc/toolbar_separator_horizontal.png");\n'
            "}\n"
            "\n"
            "QToolBar::separator:vertical {\n"
            "  height: 16px;\n"
            '  image: url(":/qss_icons/rc/toolbar_separator_vertical.png");\n'
            "}\n"
            "\n"
            "QToolButton#qt_toolbar_ext_button {\n"
            "  background: #32414B;\n"
            "  border: 0px;\n"
            "  color: #F0F0F0;\n"
            '  image: url(":/qss_icons/rc/arrow_right.png");\n'
            "}\n"
            "\n"
            "/* QAbstractSpinBox -------------------------------------------------------\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QAbstractSpinBox {\n"
            "  background-color: #19232D;\n"
            "  border: 1px solid #32414B;\n"
            "  color: #F0F0F0;\n"
            "  /* This fixes 103, 111 */\n"
            "  padding-top: 2px;\n"
            "  /* This fixes 103, 111 */\n"
            "  padding-bottom: 2px;\n"
            "  padding-left: 4px;\n"
            "  padding-right: 4px;\n"
            "  border-radius: 4px;\n"
            "  /* min-width: 5px; removed to fix 109 */\n"
            "}\n"
            "\n"
            "QAbstractSpinBox:up-button {\n"
            "  background-color: transparent #19232D;\n"
            "  subcontrol-origin: border;\n"
            "  subcontrol-position: top right;\n"
            "  border-left: 1px solid #32414B;\n"
            "  border-bottom: 1px solid #32414B;\n"
            "  border-top-left-radius: 0;\n"
            "  border-bottom-left-radius: 0;\n"
            "  margin: 1px;\n"
            "  width: 12px;\n"
            "  margin-bottom: -1px;\n"
            "}\n"
            "\n"
            "QAbstractSpinBox::up-arrow, QAbstractSpinBox::up-arrow:disabled, QAbstractSpinBox::up-arrow:off {\n"
            '  image: url(":/qss_icons/rc/arrow_up_disabled.png");\n'
            "  height: 8px;\n"
            "  width: 8px;\n"
            "}\n"
            "\n"
            "QAbstractSpinBox::up-arrow:hover {\n"
            '  image: url(":/qss_icons/rc/arrow_up.png");\n'
            "}\n"
            "\n"
            "QAbstractSpinBox:down-button {\n"
            "  background-color: transparent #19232D;\n"
            "  subcontrol-origin: border;\n"
            "  subcontrol-position: bottom right;\n"
            "  border-left: 1px solid #32414B;\n"
            "  border-top: 1px solid #32414B;\n"
            "  border-top-left-radius: 0;\n"
            "  border-bottom-left-radius: 0;\n"
            "  margin: 1px;\n"
            "  width: 12px;\n"
            "  margin-top: -1px;\n"
            "}\n"
            "\n"
            "QAbstractSpinBox::down-arrow, QAbstractSpinBox::down-arrow:disabled, QAbstractSpinBox::down-arrow:off {\n"
            '  image: url(":/qss_icons/rc/arrow_down_disabled.png");\n'
            "  height: 8px;\n"
            "  width: 8px;\n"
            "}\n"
            "\n"
            "QAbstractSpinBox::down-arrow:hover {\n"
            '  image: url(":/qss_icons/rc/arrow_down.png");\n'
            "}\n"
            "\n"
            "QAbstractSpinBox:hover {\n"
            "  border: 1px solid #148CD2;\n"
            "  color: #F0F0F0;\n"
            "}\n"
            "\n"
            "QAbstractSpinBox:focus {\n"
            "  border: 1px solid #1464A0;\n"
            "}\n"
            "\n"
            "QAbstractSpinBox:selected {\n"
            "  background: #1464A0;\n"
            "  color: #32414B;\n"
            "}\n"
            "\n"
            "/* ------------------------------------------------------------------------ */\n"
            "/* DISPLAYS --------------------------------------------------------------- */\n"
            "/* ------------------------------------------------------------------------ */\n"
            "/* QLabel -----------------------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qframe\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QLabel {\n"
            "  background-color: #19232D;\n"
            "  border: 0px solid #32414B;\n"
            "  padding: 2px;\n"
            "  margin: 0px;\n"
            "  color: #F0F0F0;\n"
            "}\n"
            "\n"
            "QLabel:disabled {\n"
            "  background-color: #19232D;\n"
            "  border: 0px solid #32414B;\n"
            "  color: #787878;\n"
            "}\n"
            "\n"
            "/* QTextBrowser -----------------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qabstractscrollarea\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QTextBrowser {\n"
            "  background-color: #19232D;\n"
            "  border: 1px solid #32414B;\n"
            "  color: #F0F0F0;\n"
            "  border-radius: 4px;\n"
            "}\n"
            "\n"
            "QTextBrowser:disabled {\n"
            "  background-color: #19232D;\n"
            "  border: 1px solid #32414B;\n"
            "  color: #787878;\n"
            "  border-radius: 4px;\n"
            "}\n"
            "\n"
            "QTextBrowser:hover, QTextBrowser:!hover, QTextBrowser:selected, QTextBrowser:pressed {\n"
            "  border: 1px solid #32414B;\n"
            "}\n"
            "\n"
            "/* QGraphicsView ----------------------------------------------------------\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QGraphicsView {\n"
            "  background-color: #19232D;\n"
            "  border: 1px solid #32414B;\n"
            "  color: #F0F0F0;\n"
            "  border-radius: 4px;\n"
            "}\n"
            "\n"
            "QGraphicsView:disabled {\n"
            "  background-color: #19232D;\n"
            "  border: 1px solid #32414B;\n"
            "  color: #787878;\n"
            "  border-radius: 4px;\n"
            "}\n"
            "\n"
            "QGraphicsView:hover, QGraphicsView:!hover, QGraphicsView:selected, QGraphicsView:pressed {\n"
            "  border: 1px solid #32414B;\n"
            "}\n"
            "\n"
            "/* QCalendarWidget --------------------------------------------------------\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QCalendarWidget {\n"
            "  border: 1px solid #32414B;\n"
            "  border-radius: 4px;\n"
            "}\n"
            "\n"
            "QCalendarWidget:disabled {\n"
            "  background-color: #19232D;\n"
            "  color: #787878;\n"
            "}\n"
            "\n"
            "/* QLCDNumber -------------------------------------------------------------\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QLCDNumber {\n"
            "  background-color: #19232D;\n"
            "  color: #F0F0F0;\n"
            "}\n"
            "\n"
            "QLCDNumber:disabled {\n"
            "  background-color: #19232D;\n"
            "  color: #787878;\n"
            "}\n"
            "\n"
            "/* QProgressBar -----------------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qprogressbar\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QProgressBar {\n"
            "  background-color: #19232D;\n"
            "  border: 1px solid #32414B;\n"
            "  color: #F0F0F0;\n"
            "  border-radius: 4px;\n"
            "  text-align: center;\n"
            "}\n"
            "\n"
            "QProgressBar:disabled {\n"
            "  background-color: #19232D;\n"
            "  border: 1px solid #32414B;\n"
            "  color: #787878;\n"
            "  border-radius: 4px;\n"
            "  text-align: center;\n"
            "}\n"
            "\n"
            "QProgressBar::chunk {\n"
            "  background-color: #1464A0;\n"
            "  color: #19232D;\n"
            "  border-radius: 4px;\n"
            "}\n"
            "\n"
            "QProgressBar::chunk:disabled {\n"
            "  background-color: #14506E;\n"
            "  color: #787878;\n"
            "  border-radius: 4px;\n"
            "}\n"
            "\n"
            "/* ------------------------------------------------------------------------ */\n"
            "/* BUTTONS ---------------------------------------------------------------- */\n"
            "/* ------------------------------------------------------------------------ */\n"
            "/* QPushButton ------------------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qpushbutton\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QPushButton {\n"
            "  background-color: #505F69;\n"
            "  border: 1px solid #32414B;\n"
            "  color: #F0F0F0;\n"
            "  border-radius: 4px;\n"
            "  padding: 3px;\n"
            "  outline: none;\n"
            "  /* Issue #194 - Special case of QPushButton inside dialogs, for better UI */\n"
            "  min-width: 80px;\n"
            "}\n"
            "\n"
            "QPushButton:disabled {\n"
            "  background-color: #32414B;\n"
            "  border: 1px solid #32414B;\n"
            "  color: #787878;\n"
            "  border-radius: 4px;\n"
            "  padding: 3px;\n"
            "}\n"
            "\n"
            "QPushButton:checked {\n"
            "  background-color: #32414B;\n"
            "  border: 1px solid #32414B;\n"
            "  border-radius: 4px;\n"
            "  padding: 3px;\n"
            "  outline: none;\n"
            "}\n"
            "\n"
            "QPushButton:checked:disabled {\n"
            "  background-color: #19232D;\n"
            "  border: 1px solid #32414B;\n"
            "  color: #787878;\n"
            "  border-radius: 4px;\n"
            "  padding: 3px;\n"
            "  outline: none;\n"
            "}\n"
            "\n"
            "QPushButton:checked:selected {\n"
            "  background: #1464A0;\n"
            "  color: #32414B;\n"
            "}\n"
            "\n"
            "QPushButton::menu-indicator {\n"
            "  subcontrol-origin: padding;\n"
            "  subcontrol-position: bottom right;\n"
            "  bottom: 4px;\n"
            "}\n"
            "\n"
            "QPushButton:pressed {\n"
            "  background-color: #19232D;\n"
            "  border: 1px solid #19232D;\n"
            "}\n"
            "\n"
            "QPushButton:pressed:hover {\n"
            "  border: 1px solid #148CD2;\n"
            "}\n"
            "\n"
            "QPushButton:hover {\n"
            "  border: 1px solid #148CD2;\n"
            "  color: #F0F0F0;\n"
            "}\n"
            "\n"
            "QPushButton:selected {\n"
            "  background: #1464A0;\n"
            "  color: #32414B;\n"
            "}\n"
            "\n"
            "QPushButton:hover {\n"
            "  border: 1px solid #148CD2;\n"
            "  color: #F0F0F0;\n"
            "}\n"
            "\n"
            "QPushButton:focus {\n"
            "  border: 1px solid #1464A0;\n"
            "}\n"
            "\n"
            "/* QToolButton ------------------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qtoolbutton\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QToolButton {\n"
            "  background-color: transparent;\n"
            "  border: 1px solid transparent;\n"
            "  border-radius: 4px;\n"
            "  margin: 0px;\n"
            "  padding: 2px;\n"
            "  /* The subcontrols below are used only in the DelayedPopup mode */\n"
            "  /* The subcontrols below are used only in the MenuButtonPopup mode */\n"
            "  /* The subcontrol below is used only in the InstantPopup or DelayedPopup mode */\n"
            "}\n"
            "\n"
            "QToolButton:checked {\n"
            "  background-color: transparent;\n"
            "  border: 1px solid #1464A0;\n"
            "}\n"
            "\n"
            "QToolButton:checked:disabled {\n"
            "  border: 1px solid #14506E;\n"
            "}\n"
            "\n"
            "QToolButton:pressed {\n"
            "  margin: 1px;\n"
            "  background-color: transparent;\n"
            "  border: 1px solid #1464A0;\n"
            "}\n"
            "\n"
            "QToolButton:disabled {\n"
            "  border: none;\n"
            "}\n"
            "\n"
            "QToolButton:hover {\n"
            "  border: 1px solid #148CD2;\n"
            "}\n"
            "\n"
            'QToolButton[popupMode="0"] {\n'
            "  /* Only for DelayedPopup */\n"
            "  padding-right: 2px;\n"
            "}\n"
            "\n"
            'QToolButton[popupMode="1"] {\n'
            "  /* Only for MenuButtonPopup */\n"
            "  padding-right: 20px;\n"
            "}\n"
            "\n"
            'QToolButton[popupMode="1"]::menu-button {\n'
            "  border: none;\n"
            "}\n"
            "\n"
            'QToolButton[popupMode="1"]::menu-button:hover {\n'
            "  border: none;\n"
            "  border-left: 1px solid #148CD2;\n"
            "  border-radius: 0;\n"
            "}\n"
            "\n"
            'QToolButton[popupMode="2"] {\n'
            "  /* Only for InstantPopup */\n"
            "  padding-right: 2px;\n"
            "}\n"
            "\n"
            "QToolButton::menu-button {\n"
            "  padding: 2px;\n"
            "  border-radius: 4px;\n"
            "  border: 1px solid #32414B;\n"
            "  width: 12px;\n"
            "  outline: none;\n"
            "}\n"
            "\n"
            "QToolButton::menu-button:hover {\n"
            "  border: 1px solid #148CD2;\n"
            "}\n"
            "\n"
            "QToolButton::menu-button:checked:hover {\n"
            "  border: 1px solid #148CD2;\n"
            "}\n"
            "\n"
            "QToolButton::menu-indicator {\n"
            '  image: url(":/qss_icons/rc/arrow_down.png");\n'
            "  height: 8px;\n"
            "  width: 8px;\n"
            "  top: 0;\n"
            "  /* Exclude a shift for better image */\n"
            "  left: -2px;\n"
            "  /* Shift it a bit */\n"
            "}\n"
            "\n"
            "QToolButton::menu-arrow {\n"
            '  image: url(":/qss_icons/rc/arrow_down.png");\n'
            "  height: 8px;\n"
            "  width: 8px;\n"
            "}\n"
            "\n"
            "QToolButton::menu-arrow:hover {\n"
            '  image: url(":/qss_icons/rc/arrow_down_focus.png");\n'
            "}\n"
            "\n"
            "/* QCommandLinkButton -----------------------------------------------------\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QCommandLinkButton {\n"
            "  background-color: transparent;\n"
            "  border: 1px solid #32414B;\n"
            "  color: #F0F0F0;\n"
            "  border-radius: 4px;\n"
            "  padding: 0px;\n"
            "  margin: 0px;\n"
            "}\n"
            "\n"
            "QCommandLinkButton:disabled {\n"
            "  background-color: transparent;\n"
            "  color: #787878;\n"
            "}\n"
            "\n"
            "/* ------------------------------------------------------------------------ */\n"
            "/* INPUTS - NO FIELDS ----------------------------------------------------- */\n"
            "/* ------------------------------------------------------------------------ */\n"
            "/* QComboBox --------------------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qcombobox\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QComboBox {\n"
            "  border: 1px solid #32414B;\n"
            "  border-radius: 4px;\n"
            "  selection-background-color: #1464A0;\n"
            "  padding-left: 4px;\n"
            "  padding-right: 36px;\n"
            "  /* 4 + 16*2 See scrollbar size */\n"
            "  /* Fixes #103, #111 */\n"
            "  min-height: 1.5em;\n"
            "  /* padding-top: 2px;     removed to fix #132 */\n"
            "  /* padding-bottom: 2px;  removed to fix #132 */\n"
            "  /* min-width: 75px;      removed to fix #109 */\n"
            "  /* Needed to remove indicator - fix #132 */\n"
            "}\n"
            "\n"
            "QComboBox QAbstractItemView {\n"
            "  border: 1px solid #32414B;\n"
            "  border-radius: 0;\n"
            "  background-color: #19232D;\n"
            "  selection-background-color: #1464A0;\n"
            "}\n"
            "\n"
            "QComboBox QAbstractItemView:hover {\n"
            "  background-color: #19232D;\n"
            "  color: #F0F0F0;\n"
            "}\n"
            "\n"
            "QComboBox QAbstractItemView:selected {\n"
            "  background: #1464A0;\n"
            "  color: #32414B;\n"
            "}\n"
            "\n"
            "QComboBox QAbstractItemView:alternate {\n"
            "  background: #19232D;\n"
            "}\n"
            "\n"
            "QComboBox:disabled {\n"
            "  background-color: #19232D;\n"
            "  color: #787878;\n"
            "}\n"
            "\n"
            "QComboBox:hover {\n"
            "  border: 1px solid #148CD2;\n"
            "}\n"
            "\n"
            "QComboBox:focus {\n"
            "  border: 1px solid #1464A0;\n"
            "}\n"
            "\n"
            "QComboBox:on {\n"
            "  selection-background-color: #1464A0;\n"
            "}\n"
            "\n"
            "QComboBox::indicator {\n"
            "  border: none;\n"
            "  border-radius: 0;\n"
            "  background-color: transparent;\n"
            "  selection-background-color: transparent;\n"
            "  color: transparent;\n"
            "  selection-color: transparent;\n"
            "  /* Needed to remove indicator - fix #132 */\n"
            "}\n"
            "\n"
            "QComboBox::indicator:alternate {\n"
            "  background: #19232D;\n"
            "}\n"
            "\n"
            "QComboBox::item:alternate {\n"
            "  background: #19232D;\n"
            "}\n"
            "\n"
            "QComboBox::item:checked {\n"
            "  font-weight: bold;\n"
            "}\n"
            "\n"
            "QComboBox::item:selected {\n"
            "  border: 0px solid transparent;\n"
            "}\n"
            "\n"
            "QComboBox::drop-down {\n"
            "  subcontrol-origin: padding;\n"
            "  subcontrol-position: top right;\n"
            "  width: 12px;\n"
            "  border-left: 1px solid #32414B;\n"
            "}\n"
            "\n"
            "QComboBox::down-arrow {\n"
            '  image: url(":/qss_icons/rc/arrow_down_disabled.png");\n'
            "  height: 8px;\n"
            "  width: 8px;\n"
            "}\n"
            "\n"
            "QComboBox::down-arrow:on, QComboBox::down-arrow:hover, QComboBox::down-arrow:focus {\n"
            '  image: url(":/qss_icons/rc/arrow_down.png");\n'
            "}\n"
            "\n"
            "/* QSlider ----------------------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qslider\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QSlider:disabled {\n"
            "  background: #19232D;\n"
            "}\n"
            "\n"
            "QSlider:focus {\n"
            "  border: none;\n"
            "}\n"
            "\n"
            "QSlider::groove:horizontal {\n"
            "  background: #32414B;\n"
            "  border: 1px solid #32414B;\n"
            "  height: 4px;\n"
            "  margin: 0px;\n"
            "  border-radius: 4px;\n"
            "}\n"
            "\n"
            "QSlider::groove:vertical {\n"
            "  background: #32414B;\n"
            "  border: 1px solid #32414B;\n"
            "  width: 4px;\n"
            "  margin: 0px;\n"
            "  border-radius: 4px;\n"
            "}\n"
            "\n"
            "QSlider::add-page:vertical {\n"
            "  background: #1464A0;\n"
            "  border: 1px solid #32414B;\n"
            "  width: 4px;\n"
            "  margin: 0px;\n"
            "  border-radius: 4px;\n"
            "}\n"
            "\n"
            "QSlider::add-page:vertical :disabled {\n"
            "  background: #14506E;\n"
            "}\n"
            "\n"
            "QSlider::sub-page:horizontal {\n"
            "  background: #1464A0;\n"
            "  border: 1px solid #32414B;\n"
            "  height: 4px;\n"
            "  margin: 0px;\n"
            "  border-radius: 4px;\n"
            "}\n"
            "\n"
            "QSlider::sub-page:horizontal:disabled {\n"
            "  background: #14506E;\n"
            "}\n"
            "\n"
            "QSlider::handle:horizontal {\n"
            "  background: #787878;\n"
            "  border: 1px solid #32414B;\n"
            "  width: 8px;\n"
            "  height: 8px;\n"
            "  margin: -8px 0px;\n"
            "  border-radius: 4px;\n"
            "}\n"
            "\n"
            "QSlider::handle:horizontal:hover {\n"
            "  background: #148CD2;\n"
            "  border: 1px solid #148CD2;\n"
            "}\n"
            "\n"
            "QSlider::handle:horizontal:focus {\n"
            "  border: 1px solid #1464A0;\n"
            "}\n"
            "\n"
            "QSlider::handle:vertical {\n"
            "  background: #787878;\n"
            "  border: 1px solid #32414B;\n"
            "  width: 8px;\n"
            "  height: 8px;\n"
            "  margin: 0 -8px;\n"
            "  border-radius: 4px;\n"
            "}\n"
            "\n"
            "QSlider::handle:vertical:hover {\n"
            "  background: #148CD2;\n"
            "  border: 1px solid #148CD2;\n"
            "}\n"
            "\n"
            "QSlider::handle:vertical:focus {\n"
            "  border: 1px solid #1464A0;\n"
            "}\n"
            "\n"
            "/* QLineEdit --------------------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qlineedit\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QLineEdit {\n"
            "  background-color: #19232D;\n"
            "  padding-top: 2px;\n"
            "  /* This QLineEdit fix  103, 111 */\n"
            "  padding-bottom: 2px;\n"
            "  /* This QLineEdit fix  103, 111 */\n"
            "  padding-left: 4px;\n"
            "  padding-right: 4px;\n"
            "  border-style: solid;\n"
            "  border: 1px solid #32414B;\n"
            "  border-radius: 4px;\n"
            "  color: #F0F0F0;\n"
            "}\n"
            "\n"
            "QLineEdit:disabled {\n"
            "  background-color: #19232D;\n"
            "  color: #787878;\n"
            "}\n"
            "\n"
            "QLineEdit:hover {\n"
            "  border: 1px solid #148CD2;\n"
            "  color: #F0F0F0;\n"
            "}\n"
            "\n"
            "QLineEdit:focus {\n"
            "  border: 1px solid #1464A0;\n"
            "}\n"
            "\n"
            "QLineEdit:selected {\n"
            "  background-color: #1464A0;\n"
            "  color: #32414B;\n"
            "}\n"
            "\n"
            "/* QTabWiget --------------------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qtabwidget-and-qtabbar\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QTabWidget {\n"
            "  padding: 2px;\n"
            "  selection-background-color: #32414B;\n"
            "}\n"
            "\n"
            "QTabWidget QWidget {\n"
            "  /* Fixes #189 */\n"
            "  border-radius: 4px;\n"
            "}\n"
            "\n"
            "QTabWidget::pane {\n"
            "  border: 1px solid #32414B;\n"
            "  border-radius: 4px;\n"
            "  margin: 0px;\n"
            "  /* Fixes double border inside pane with pyqt5 */\n"
            "  padding: 0px;\n"
            "}\n"
            "\n"
            "QTabWidget::pane:selected {\n"
            "  background-color: #32414B;\n"
            "  border: 1px solid #1464A0;\n"
            "}\n"
            "\n"
            "/* QTabBar ----------------------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qtabwidget-and-qtabbar\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QTabBar {\n"
            "  qproperty-drawBase: 0;\n"
            "  border-radius: 4px;\n"
            "  margin: 0px;\n"
            "  padding: 2px;\n"
            "  border: 0;\n"
            "  /* left: 5px; move to the right by 5px - removed for fix */\n"
            "}\n"
            "\n"
            "QTabBar::close-button {\n"
            "  border: 0;\n"
            "  margin: 2px;\n"
            "  padding: 2px;\n"
            '  image: url(":/qss_icons/rc/window_close.png");\n'
            "}\n"
            "\n"
            "QTabBar::close-button:hover {\n"
            '  image: url(":/qss_icons/rc/window_close_focus.png");\n'
            "}\n"
            "\n"
            "QTabBar::close-button:pressed {\n"
            '  image: url(":/qss_icons/rc/window_close_pressed.png");\n'
            "}\n"
            "\n"
            "/* QTabBar::tab - selected ------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qtabwidget-and-qtabbar\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QTabBar::tab {\n"
            "  /* !selected and disabled ----------------------------------------- */\n"
            "  /* selected ------------------------------------------------------- */\n"
            "}\n"
            "\n"
            "QTabBar::tab:top:selected:disabled {\n"
            "  border-bottom: 3px solid #14506E;\n"
            "  color: #787878;\n"
            "  background-color: #32414B;\n"
            "}\n"
            "\n"
            "QTabBar::tab:bottom:selected:disabled {\n"
            "  border-top: 3px solid #14506E;\n"
            "  color: #787878;\n"
            "  background-color: #32414B;\n"
            "}\n"
            "\n"
            "QTabBar::tab:left:selected:disabled {\n"
            "  border-right: 3px solid #14506E;\n"
            "  color: #787878;\n"
            "  background-color: #32414B;\n"
            "}\n"
            "\n"
            "QTabBar::tab:right:selected:disabled {\n"
            "  border-left: 3px solid #14506E;\n"
            "  color: #787878;\n"
            "  background-color: #32414B;\n"
            "}\n"
            "\n"
            "QTabBar::tab:top:!selected:disabled {\n"
            "  border-bottom: 3px solid #19232D;\n"
            "  color: #787878;\n"
            "  background-color: #19232D;\n"
            "}\n"
            "\n"
            "QTabBar::tab:bottom:!selected:disabled {\n"
            "  border-top: 3px solid #19232D;\n"
            "  color: #787878;\n"
            "  background-color: #19232D;\n"
            "}\n"
            "\n"
            "QTabBar::tab:left:!selected:disabled {\n"
            "  border-right: 3px solid #19232D;\n"
            "  color: #787878;\n"
            "  background-color: #19232D;\n"
            "}\n"
            "\n"
            "QTabBar::tab:right:!selected:disabled {\n"
            "  border-left: 3px solid #19232D;\n"
            "  color: #787878;\n"
            "  background-color: #19232D;\n"
            "}\n"
            "\n"
            "QTabBar::tab:top:!selected {\n"
            "  border-bottom: 2px solid #19232D;\n"
            "  margin-top: 2px;\n"
            "}\n"
            "\n"
            "QTabBar::tab:bottom:!selected {\n"
            "  border-top: 2px solid #19232D;\n"
            "  margin-bottom: 3px;\n"
            "}\n"
            "\n"
            "QTabBar::tab:left:!selected {\n"
            "  border-left: 2px solid #19232D;\n"
            "  margin-right: 2px;\n"
            "}\n"
            "\n"
            "QTabBar::tab:right:!selected {\n"
            "  border-right: 2px solid #19232D;\n"
            "  margin-left: 2px;\n"
            "}\n"
            "\n"
            "QTabBar::tab:top {\n"
            "  background-color: #32414B;\n"
            "  color: #F0F0F0;\n"
            "  margin-left: 2px;\n"
            "  padding-left: 4px;\n"
            "  padding-right: 4px;\n"
            "  padding-top: 2px;\n"
            "  padding-bottom: 2px;\n"
            "  min-width: 5px;\n"
            "  border-bottom: 3px solid #32414B;\n"
            "  border-top-left-radius: 3px;\n"
            "  border-top-right-radius: 3px;\n"
            "}\n"
            "\n"
            "QTabBar::tab:top:selected {\n"
            "  background-color: #505F69;\n"
            "  color: #F0F0F0;\n"
            "  border-bottom: 3px solid #1464A0;\n"
            "  border-top-left-radius: 3px;\n"
            "  border-top-right-radius: 3px;\n"
            "}\n"
            "\n"
            "QTabBar::tab:top:!selected:hover {\n"
            "  border: 1px solid #148CD2;\n"
            "  border-bottom: 3px solid #148CD2;\n"
            "  /* Fixes spyder-ide/spyder#9766 */\n"
            "  padding-left: 4px;\n"
            "  padding-right: 4px;\n"
            "}\n"
            "\n"
            "QTabBar::tab:bottom {\n"
            "  color: #F0F0F0;\n"
            "  border-top: 3px solid #32414B;\n"
            "  background-color: #32414B;\n"
            "  margin-left: 2px;\n"
            "  padding-left: 4px;\n"
            "  padding-right: 4px;\n"
            "  padding-top: 2px;\n"
            "  padding-bottom: 2px;\n"
            "  border-bottom-left-radius: 3px;\n"
            "  border-bottom-right-radius: 3px;\n"
            "  min-width: 5px;\n"
            "}\n"
            "\n"
            "QTabBar::tab:bottom:selected {\n"
            "  color: #F0F0F0;\n"
            "  background-color: #505F69;\n"
            "  border-top: 3px solid #1464A0;\n"
            "  border-bottom-left-radius: 3px;\n"
            "  border-bottom-right-radius: 3px;\n"
            "}\n"
            "\n"
            "QTabBar::tab:bottom:!selected:hover {\n"
            "  border: 1px solid #148CD2;\n"
            "  border-top: 3px solid #148CD2;\n"
            "  /* Fixes spyder-ide/spyder#9766 */\n"
            "  padding-left: 4px;\n"
            "  padding-right: 4px;\n"
            "}\n"
            "\n"
            "QTabBar::tab:left {\n"
            "  color: #F0F0F0;\n"
            "  background-color: #32414B;\n"
            "  margin-top: 2px;\n"
            "  padding-left: 2px;\n"
            "  padding-right: 2px;\n"
            "  padding-top: 4px;\n"
            "  padding-bottom: 4px;\n"
            "  border-top-left-radius: 3px;\n"
            "  border-bottom-left-radius: 3px;\n"
            "  min-height: 5px;\n"
            "}\n"
            "\n"
            "QTabBar::tab:left:selected {\n"
            "  color: #F0F0F0;\n"
            "  background-color: #505F69;\n"
            "  border-right: 3px solid #1464A0;\n"
            "}\n"
            "\n"
            "QTabBar::tab:left:!selected:hover {\n"
            "  border: 1px solid #148CD2;\n"
            "  border-right: 3px solid #148CD2;\n"
            "  padding: 0px;\n"
            "}\n"
            "\n"
            "QTabBar::tab:right {\n"
            "  color: #F0F0F0;\n"
            "  background-color: #32414B;\n"
            "  margin-top: 2px;\n"
            "  padding-left: 2px;\n"
            "  padding-right: 2px;\n"
            "  padding-top: 4px;\n"
            "  padding-bottom: 4px;\n"
            "  border-top-right-radius: 3px;\n"
            "  border-bottom-right-radius: 3px;\n"
            "  min-height: 5px;\n"
            "}\n"
            "\n"
            "QTabBar::tab:right:selected {\n"
            "  color: #F0F0F0;\n"
            "  background-color: #505F69;\n"
            "  border-left: 3px solid #1464A0;\n"
            "}\n"
            "\n"
            "QTabBar::tab:right:!selected:hover {\n"
            "  border: 1px solid #148CD2;\n"
            "  border-left: 3px solid #148CD2;\n"
            "  padding: 0px;\n"
            "}\n"
            "\n"
            "QTabBar QToolButton {\n"
            "  /* Fixes #136 */\n"
            "  background-color: #32414B;\n"
            "  height: 12px;\n"
            "  width: 12px;\n"
            "}\n"
            "\n"
            "QTabBar QToolButton:pressed {\n"
            "  background-color: #32414B;\n"
            "}\n"
            "\n"
            "QTabBar QToolButton:pressed:hover {\n"
            "  border: 1px solid #148CD2;\n"
            "}\n"
            "\n"
            "QTabBar QToolButton::left-arrow:enabled {\n"
            '  image: url(":/qss_icons/rc/arrow_left.png");\n'
            "}\n"
            "\n"
            "QTabBar QToolButton::left-arrow:disabled {\n"
            '  image: url(":/qss_icons/rc/arrow_left_disabled.png");\n'
            "}\n"
            "\n"
            "QTabBar QToolButton::right-arrow:enabled {\n"
            '  image: url(":/qss_icons/rc/arrow_right.png");\n'
            "}\n"
            "\n"
            "QTabBar QToolButton::right-arrow:disabled {\n"
            '  image: url(":/qss_icons/rc/arrow_right_disabled.png");\n'
            "}\n"
            "\n"
            "/* QDockWiget -------------------------------------------------------------\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QDockWidget {\n"
            "  outline: 1px solid #32414B;\n"
            "  background-color: #19232D;\n"
            "  border: 1px solid #32414B;\n"
            "  border-radius: 4px;\n"
            '  titlebar-close-icon: url(":/qss_icons/rc/window_close.png");\n'
            '  titlebar-normal-icon: url(":/qss_icons/rc/window_undock.png");\n'
            "}\n"
            "\n"
            "QDockWidget::title {\n"
            "  /* Better size for title bar */\n"
            "  padding: 6px;\n"
            "  spacing: 4px;\n"
            "  border: none;\n"
            "  background-color: #32414B;\n"
            "}\n"
            "\n"
            "QDockWidget::close-button {\n"
            "  background-color: #32414B;\n"
            "  border-radius: 4px;\n"
            "  border: none;\n"
            "}\n"
            "\n"
            "QDockWidget::close-button:hover {\n"
            '  image: url(":/qss_icons/rc/window_close_focus.png");\n'
            "}\n"
            "\n"
            "QDockWidget::close-button:pressed {\n"
            '  image: url(":/qss_icons/rc/window_close_pressed.png");\n'
            "}\n"
            "\n"
            "QDockWidget::float-button {\n"
            "  background-color: #32414B;\n"
            "  border-radius: 4px;\n"
            "  border: none;\n"
            "}\n"
            "\n"
            "QDockWidget::float-button:hover {\n"
            '  image: url(":/qss_icons/rc/window_undock_focus.png");\n'
            "}\n"
            "\n"
            "QDockWidget::float-button:pressed {\n"
            '  image: url(":/qss_icons/rc/window_undock_pressed.png");\n'
            "}\n"
            "\n"
            "/* QTreeView QListView QTableView -----------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qtreeview\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qlistview\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qtableview\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QTreeView:branch:selected, QTreeView:branch:hover {\n"
            '  background: url(":/qss_icons/rc/transparent.png");\n'
            "}\n"
            "\n"
            "QTreeView:branch:has-siblings:!adjoins-item {\n"
            '  border-image: url(":/qss_icons/rc/branch_line.png") 0;\n'
            "}\n"
            "\n"
            "QTreeView:branch:has-siblings:adjoins-item {\n"
            '  border-image: url(":/qss_icons/rc/branch_more.png") 0;\n'
            "}\n"
            "\n"
            "QTreeView:branch:!has-children:!has-siblings:adjoins-item {\n"
            '  border-image: url(":/qss_icons/rc/branch_end.png") 0;\n'
            "}\n"
            "\n"
            "QTreeView:branch:has-children:!has-siblings:closed, QTreeView:branch:closed:has-children:has-siblings {\n"
            "  border-image: none;\n"
            '  image: url(":/qss_icons/rc/branch_closed.png");\n'
            "}\n"
            "\n"
            "QTreeView:branch:open:has-children:!has-siblings, QTreeView:branch:open:has-children:has-siblings {\n"
            "  border-image: none;\n"
            '  image: url(":/qss_icons/rc/branch_open.png");\n'
            "}\n"
            "\n"
            "QTreeView:branch:has-children:!has-siblings:closed:hover, QTreeView:branch:closed:has-children:has-siblings:hover {\n"
            '  image: url(":/qss_icons/rc/branch_closed_focus.png");\n'
            "}\n"
            "\n"
            "QTreeView:branch:open:has-children:!has-siblings:hover, QTreeView:branch:open:has-children:has-siblings:hover {\n"
            '  image: url(":/qss_icons/rc/branch_open_focus.png");\n'
            "}\n"
            "\n"
            "QTreeView::indicator:checked,\n"
            "QListView::indicator:checked {\n"
            '  image: url(":/qss_icons/rc/checkbox_checked.png");\n'
            "}\n"
            "\n"
            "QTreeView::indicator:checked:hover, QTreeView::indicator:checked:focus, QTreeView::indicator:checked:pressed,\n"
            "QListView::indicator:checked:hover,\n"
            "QListView::indicator:checked:focus,\n"
            "QListView::indicator:checked:pressed {\n"
            '  image: url(":/qss_icons/rc/checkbox_checked_focus.png");\n'
            "}\n"
            "\n"
            "QTreeView::indicator:unchecked,\n"
            "QListView::indicator:unchecked {\n"
            '  image: url(":/qss_icons/rc/checkbox_unchecked.png");\n'
            "}\n"
            "\n"
            "QTreeView::indicator:unchecked:hover, QTreeView::indicator:unchecked:focus, QTreeView::indicator:unchecked:pressed,\n"
            "QListView::indicator:unchecked:hover,\n"
            "QListView::indicator:unchecked:focus,\n"
            "QListView::indicator:unchecked:pressed {\n"
            '  image: url(":/qss_icons/rc/checkbox_unchecked_focus.png");\n'
            "}\n"
            "\n"
            "QTreeView::indicator:indeterminate,\n"
            "QListView::indicator:indeterminate {\n"
            '  image: url(":/qss_icons/rc/checkbox_indeterminate.png");\n'
            "}\n"
            "\n"
            "QTreeView::indicator:indeterminate:hover, QTreeView::indicator:indeterminate:focus, QTreeView::indicator:indeterminate:pressed,\n"
            "QListView::indicator:indeterminate:hover,\n"
            "QListView::indicator:indeterminate:focus,\n"
            "QListView::indicator:indeterminate:pressed {\n"
            '  image: url(":/qss_icons/rc/checkbox_indeterminate_focus.png");\n'
            "}\n"
            "\n"
            "QTreeView,\n"
            "QListView,\n"
            "QTableView,\n"
            "QColumnView {\n"
            "  background-color: #19232D;\n"
            "  border: 1px solid #32414B;\n"
            "  color: #F0F0F0;\n"
            "  gridline-color: #32414B;\n"
            "  border-radius: 4px;\n"
            "}\n"
            "\n"
            "QTreeView:disabled,\n"
            "QListView:disabled,\n"
            "QTableView:disabled,\n"
            "QColumnView:disabled {\n"
            "  background-color: #19232D;\n"
            "  color: #787878;\n"
            "}\n"
            "\n"
            "QTreeView:selected,\n"
            "QListView:selected,\n"
            "QTableView:selected,\n"
            "QColumnView:selected {\n"
            "  background-color: #1464A0;\n"
            "  color: #32414B;\n"
            "}\n"
            "\n"
            "QTreeView:hover,\n"
            "QListView:hover,\n"
            "QTableView:hover,\n"
            "QColumnView:hover {\n"
            "  background-color: #19232D;\n"
            "  border: 1px solid #148CD2;\n"
            "}\n"
            "\n"
            "QTreeView::item:pressed,\n"
            "QListView::item:pressed,\n"
            "QTableView::item:pressed,\n"
            "QColumnView::item:pressed {\n"
            "  background-color: #1464A0;\n"
            "}\n"
            "\n"
            "QTreeView::item:selected:hover,\n"
            "QListView::item:selected:hover,\n"
            "QTableView::item:selected:hover,\n"
            "QColumnView::item:selected:hover {\n"
            "  background: #1464A0;\n"
            "  color: #19232D;\n"
            "}\n"
            "\n"
            "QTreeView::item:selected:active,\n"
            "QListView::item:selected:active,\n"
            "QTableView::item:selected:active,\n"
            "QColumnView::item:selected:active {\n"
            "  background-color: #1464A0;\n"
            "}\n"
            "\n"
            "QTreeView::item:!selected:hover,\n"
            "QListView::item:!selected:hover,\n"
            "QTableView::item:!selected:hover,\n"
            "QColumnView::item:!selected:hover {\n"
            "  outline: 0;\n"
            "  color: #148CD2;\n"
            "  background-color: #32414B;\n"
            "}\n"
            "\n"
            "QTableCornerButton::section {\n"
            "  background-color: #19232D;\n"
            "  border: 1px transparent #32414B;\n"
            "  border-radius: 0px;\n"
            "}\n"
            "\n"
            "/* QHeaderView ------------------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qheaderview\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QHeaderView {\n"
            "  background-color: #32414B;\n"
            "  border: 0px transparent #32414B;\n"
            "  padding: 0px;\n"
            "  margin: 0px;\n"
            "  border-radius: 0px;\n"
            "}\n"
            "\n"
            "QHeaderView:disabled {\n"
            "  background-color: #32414B;\n"
            "  border: 1px transparent #32414B;\n"
            "  padding: 2px;\n"
            "}\n"
            "\n"
            "QHeaderView::section {\n"
            "  background-color: #32414B;\n"
            "  color: #F0F0F0;\n"
            "  padding: 2px;\n"
            "  border-radius: 0px;\n"
            "  text-align: left;\n"
            "}\n"
            "\n"
            "QHeaderView::section:checked {\n"
            "  color: #F0F0F0;\n"
            "  background-color: #1464A0;\n"
            "}\n"
            "\n"
            "QHeaderView::section:checked:disabled {\n"
            "  color: #787878;\n"
            "  background-color: #14506E;\n"
            "}\n"
            "\n"
            "QHeaderView::section::horizontal {\n"
            "  padding-left: 4px;\n"
            "  padding-right: 4px;\n"
            "  border-left: 1px solid #19232D;\n"
            "}\n"
            "\n"
            "QHeaderView::section::horizontal::first, QHeaderView::section::horizontal::only-one {\n"
            "  border-left: 1px solid #32414B;\n"
            "}\n"
            "\n"
            "QHeaderView::section::horizontal:disabled {\n"
            "  color: #787878;\n"
            "}\n"
            "\n"
            "QHeaderView::section::vertical {\n"
            "  padding-left: 4px;\n"
            "  padding-right: 4px;\n"
            "  border-top: 1px solid #19232D;\n"
            "}\n"
            "\n"
            "QHeaderView::section::vertical::first, QHeaderView::section::vertical::only-one {\n"
            "  border-top: 1px solid #32414B;\n"
            "}\n"
            "\n"
            "QHeaderView::section::vertical:disabled {\n"
            "  color: #787878;\n"
            "}\n"
            "\n"
            "QHeaderView::down-arrow {\n"
            "  /* Those settings (border/width/height/background-color) solve bug */\n"
            "  /* transparent arrow background and size */\n"
            "  background-color: #32414B;\n"
            "  border: none;\n"
            "  height: 12px;\n"
            "  width: 12px;\n"
            "  padding-left: 2px;\n"
            "  padding-right: 2px;\n"
            '  image: url(":/qss_icons/rc/arrow_down.png");\n'
            "}\n"
            "\n"
            "QHeaderView::up-arrow {\n"
            "  background-color: #32414B;\n"
            "  border: none;\n"
            "  height: 12px;\n"
            "  width: 12px;\n"
            "  padding-left: 2px;\n"
            "  padding-right: 2px;\n"
            '  image: url(":/qss_icons/rc/arrow_up.png");\n'
            "}\n"
            "\n"
            "/* QToolBox --------------------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qtoolbox\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QToolBox {\n"
            "  padding: 0px;\n"
            "  border: 0px;\n"
            "  border: 1px solid #32414B;\n"
            "}\n"
            "\n"
            "QToolBox:selected {\n"
            "  padding: 0px;\n"
            "  border: 2px solid #1464A0;\n"
            "}\n"
            "\n"
            "QToolBox::tab {\n"
            "  background-color: #19232D;\n"
            "  border: 1px solid #32414B;\n"
            "  color: #F0F0F0;\n"
            "  border-top-left-radius: 4px;\n"
            "  border-top-right-radius: 4px;\n"
            "}\n"
            "\n"
            "QToolBox::tab:disabled {\n"
            "  color: #787878;\n"
            "}\n"
            "\n"
            "QToolBox::tab:selected {\n"
            "  background-color: #505F69;\n"
            "  border-bottom: 2px solid #1464A0;\n"
            "}\n"
            "\n"
            "QToolBox::tab:selected:disabled {\n"
            "  background-color: #32414B;\n"
            "  border-bottom: 2px solid #14506E;\n"
            "}\n"
            "\n"
            "QToolBox::tab:!selected {\n"
            "  background-color: #32414B;\n"
            "  border-bottom: 2px solid #32414B;\n"
            "}\n"
            "\n"
            "QToolBox::tab:!selected:disabled {\n"
            "  background-color: #19232D;\n"
            "}\n"
            "\n"
            "QToolBox::tab:hover {\n"
            "  border-color: #148CD2;\n"
            "  border-bottom: 2px solid #148CD2;\n"
            "}\n"
            "\n"
            "QToolBox QScrollArea QWidget QWidget {\n"
            "  padding: 0px;\n"
            "  border: 0px;\n"
            "  background-color: #19232D;\n"
            "}\n"
            "\n"
            "/* QFrame -----------------------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qframe\n"
            "https://doc.qt.io/qt-5/qframe.html#-prop\n"
            "https://doc.qt.io/qt-5/qframe.html#details\n"
            "https://stackoverflow.com/questions/14581498/qt-stylesheet-for-hline-vline-color\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "/* (dot) .QFrame  fix #141, #126, #123 */\n"
            ".QFrame {\n"
            "  border-radius: 4px;\n"
            "  border: 1px solid #32414B;\n"
            "  /* No frame */\n"
            "  /* HLine */\n"
            "  /* HLine */\n"
            "}\n"
            "\n"
            '.QFrame[frameShape="0"] {\n'
            "  border-radius: 4px;\n"
            "  border: 1px transparent #32414B;\n"
            "}\n"
            "\n"
            '.QFrame[frameShape="4"] {\n'
            "  max-height: 2px;\n"
            "  border: none;\n"
            "  background-color: #32414B;\n"
            "}\n"
            "\n"
            '.QFrame[frameShape="5"] {\n'
            "  max-width: 2px;\n"
            "  border: none;\n"
            "  background-color: #32414B;\n"
            "}\n"
            "\n"
            "/* QSplitter --------------------------------------------------------------\n"
            "\n"
            "https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qsplitter\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QSplitter {\n"
            "  background-color: #32414B;\n"
            "  spacing: 0px;\n"
            "  padding: 0px;\n"
            "  margin: 0px;\n"
            "}\n"
            "\n"
            "QSplitter::handle {\n"
            "  background-color: #32414B;\n"
            "  border: 0px solid #19232D;\n"
            "  spacing: 0px;\n"
            "  padding: 1px;\n"
            "  margin: 0px;\n"
            "}\n"
            "\n"
            "QSplitter::handle:hover {\n"
            "  background-color: #787878;\n"
            "}\n"
            "\n"
            "QSplitter::handle:horizontal {\n"
            "  width: 5px;\n"
            '  image: url(":/qss_icons/rc/line_vertical.png");\n'
            "}\n"
            "\n"
            "QSplitter::handle:vertical {\n"
            "  height: 5px;\n"
            '  image: url(":/qss_icons/rc/line_horizontal.png");\n'
            "}\n"
            "\n"
            "/* QDateEdit --------------------------------------------------------------\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QDateEdit {\n"
            "  selection-background-color: #1464A0;\n"
            "  border-style: solid;\n"
            "  border: 1px solid #32414B;\n"
            "  border-radius: 4px;\n"
            "  /* This fixes 103, 111 */\n"
            "  padding-top: 2px;\n"
            "  /* This fixes 103, 111 */\n"
            "  padding-bottom: 2px;\n"
            "  padding-left: 4px;\n"
            "  padding-right: 4px;\n"
            "  min-width: 10px;\n"
            "}\n"
            "\n"
            "QDateEdit:on {\n"
            "  selection-background-color: #1464A0;\n"
            "}\n"
            "\n"
            "QDateEdit::drop-down {\n"
            "  subcontrol-origin: padding;\n"
            "  subcontrol-position: top right;\n"
            "  width: 12px;\n"
            "  border-left: 1px solid #32414B;\n"
            "}\n"
            "\n"
            "QDateEdit::down-arrow {\n"
            '  image: url(":/qss_icons/rc/arrow_down_disabled.png");\n'
            "  height: 8px;\n"
            "  width: 8px;\n"
            "}\n"
            "\n"
            "QDateEdit::down-arrow:on, QDateEdit::down-arrow:hover, QDateEdit::down-arrow:focus {\n"
            '  image: url(":/qss_icons/rc/arrow_down.png");\n'
            "}\n"
            "\n"
            "QDateEdit QAbstractItemView {\n"
            "  background-color: #19232D;\n"
            "  border-radius: 4px;\n"
            "  border: 1px solid #32414B;\n"
            "  selection-background-color: #1464A0;\n"
            "}\n"
            "\n"
            "/* QAbstractView ----------------------------------------------------------\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "QAbstractView:hover {\n"
            "  border: 1px solid #148CD2;\n"
            "  color: #F0F0F0;\n"
            "}\n"
            "\n"
            "QAbstractView:selected {\n"
            "  background: #1464A0;\n"
            "  color: #32414B;\n"
            "}\n"
            "\n"
            "/* PlotWidget -------------------------------------------------------------\n"
            "\n"
            "--------------------------------------------------------------------------- */\n"
            "PlotWidget {\n"
            "  /* Fix cut labels in plots #134 */\n"
            "  padding: 0px;\n"
            "}"
        )
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.tabWidget = QtWidgets.QTabWidget(self.centralwidget)
        self.tabWidget.setGeometry(QtCore.QRect(140, 10, 481, 361))
        self.tabWidget.setTabPosition(QtWidgets.QTabWidget.North)
        self.tabWidget.setObjectName("tabWidget")
        self.tab_6 = QtWidgets.QWidget()
        self.tab_6.setObjectName("tab_6")
        self.tabWidget.addTab(self.tab_6, "")
        self.tab_2 = QtWidgets.QWidget()
        self.tab_2.setObjectName("tab_2")
        self.tabWidget.addTab(self.tab_2, "")
        self.tab = QtWidgets.QWidget()
        self.tab.setObjectName("tab")
        self.tabWidget.addTab(self.tab, "")
        self.tab_4 = QtWidgets.QWidget()
        self.tab_4.setObjectName("tab_4")
        self.tabWidget.addTab(self.tab_4, "")
        self.tab_5 = QtWidgets.QWidget()
        self.tab_5.setObjectName("tab_5")
        self.pushButton_14 = QtWidgets.QPushButton(self.tab_5)
        self.pushButton_14.setGeometry(QtCore.QRect(0, 50, 121, 51))
        font = QtGui.QFont()
        font.setFamily("Microsoft Tai Le")
        font.setPointSize(8)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_14.setFont(font)
        icon = QtGui.QIcon()
        icon.addPixmap(
            QtGui.QPixmap(":/img/brakes.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off
        )
        self.pushButton_14.setIcon(icon)
        self.pushButton_14.setIconSize(QtCore.QSize(61, 61))
        self.pushButton_14.setFlat(True)
        self.pushButton_14.setObjectName("pushButton_14")
        self.pushButton_15 = QtWidgets.QPushButton(self.tab_5)
        self.pushButton_15.setGeometry(QtCore.QRect(0, 260, 121, 51))
        font = QtGui.QFont()
        font.setFamily("Microsoft Tai Le")
        font.setPointSize(8)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_15.setFont(font)
        icon1 = QtGui.QIcon()
        icon1.addPixmap(
            QtGui.QPixmap(":/img/water-pump.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off
        )
        self.pushButton_15.setIcon(icon1)
        self.pushButton_15.setIconSize(QtCore.QSize(61, 61))
        self.pushButton_15.setFlat(True)
        self.pushButton_15.setObjectName("pushButton_15")
        self.pushButton_16 = QtWidgets.QPushButton(self.tab_5)
        self.pushButton_16.setGeometry(QtCore.QRect(0, 190, 121, 51))
        font = QtGui.QFont()
        font.setFamily("Microsoft Tai Le")
        font.setPointSize(8)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_16.setFont(font)
        icon2 = QtGui.QIcon()
        icon2.addPixmap(
            QtGui.QPixmap(":/img/ignition-cap.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off
        )
        self.pushButton_16.setIcon(icon2)
        self.pushButton_16.setIconSize(QtCore.QSize(61, 61))
        self.pushButton_16.setFlat(True)
        self.pushButton_16.setObjectName("pushButton_16")
        self.pushButton_17 = QtWidgets.QPushButton(self.tab_5)
        self.pushButton_17.setGeometry(QtCore.QRect(0, 120, 121, 51))
        font = QtGui.QFont()
        font.setFamily("Microsoft Tai Le")
        font.setPointSize(8)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_17.setFont(font)
        icon3 = QtGui.QIcon()
        icon3.addPixmap(
            QtGui.QPixmap(":/img/airbag.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off
        )
        self.pushButton_17.setIcon(icon3)
        self.pushButton_17.setIconSize(QtCore.QSize(61, 61))
        self.pushButton_17.setFlat(True)
        self.pushButton_17.setObjectName("pushButton_17")
        self.tabWidget_3 = QtWidgets.QTabWidget(self.tab_5)
        self.tabWidget_3.setGeometry(QtCore.QRect(130, 0, 351, 331))
        self.tabWidget_3.setObjectName("tabWidget_3")
        self.tab_3 = QtWidgets.QWidget()
        self.tab_3.setObjectName("tab_3")
        self.tabWidget_4 = QtWidgets.QTabWidget(self.tab_3)
        self.tabWidget_4.setGeometry(QtCore.QRect(0, 0, 331, 301))
        font = QtGui.QFont()
        font.setFamily("Microsoft JhengHei")
        font.setPointSize(8)
        font.setBold(True)
        font.setWeight(75)
        self.tabWidget_4.setFont(font)
        self.tabWidget_4.setObjectName("tabWidget_4")
        self.tab_15 = QtWidgets.QWidget()
        self.tab_15.setObjectName("tab_15")
        self.textBrowser = QtWidgets.QTextBrowser(self.tab_15)
        self.textBrowser.setGeometry(QtCore.QRect(40, 20, 251, 71))
        self.textBrowser.setObjectName("textBrowser")
        self.label_3 = QtWidgets.QLabel(self.tab_15)
        self.label_3.setGeometry(QtCore.QRect(70, 100, 191, 21))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.label_3.setFont(font)
        self.label_3.setObjectName("label_3")
        self.pushButton_18 = QtWidgets.QPushButton(self.tab_15)
        self.pushButton_18.setGeometry(QtCore.QRect(10, 140, 121, 31))
        self.pushButton_18.setObjectName("pushButton_18")
        self.pushButton_19 = QtWidgets.QPushButton(self.tab_15)
        self.pushButton_19.setGeometry(QtCore.QRect(200, 140, 121, 31))
        self.pushButton_19.setObjectName("pushButton_19")
        self.progressBar = QtWidgets.QProgressBar(self.tab_15)
        self.progressBar.setGeometry(QtCore.QRect(20, 240, 281, 23))
        self.progressBar.setProperty("value", 24)
        self.progressBar.setObjectName("progressBar")
        self.label_4 = QtWidgets.QLabel(self.tab_15)
        self.label_4.setGeometry(QtCore.QRect(20, 210, 171, 20))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.label_4.setFont(font)
        self.label_4.setObjectName("label_4")
        self.tabWidget_4.addTab(self.tab_15, "")
        self.tab_16 = QtWidgets.QWidget()
        self.tab_16.setObjectName("tab_16")
        self.tableWidget = QtWidgets.QTableWidget(self.tab_16)
        self.tableWidget.setGeometry(QtCore.QRect(0, 0, 321, 261))
        self.tableWidget.setObjectName("tableWidget")
        self.tableWidget.setColumnCount(3)
        self.tableWidget.setRowCount(7)
        item = QtWidgets.QTableWidgetItem()
        self.tableWidget.setVerticalHeaderItem(0, item)
        item = QtWidgets.QTableWidgetItem()
        self.tableWidget.setVerticalHeaderItem(1, item)
        item = QtWidgets.QTableWidgetItem()
        self.tableWidget.setVerticalHeaderItem(2, item)
        item = QtWidgets.QTableWidgetItem()
        self.tableWidget.setVerticalHeaderItem(3, item)
        item = QtWidgets.QTableWidgetItem()
        self.tableWidget.setVerticalHeaderItem(4, item)
        item = QtWidgets.QTableWidgetItem()
        self.tableWidget.setVerticalHeaderItem(5, item)
        item = QtWidgets.QTableWidgetItem()
        self.tableWidget.setVerticalHeaderItem(6, item)
        item = QtWidgets.QTableWidgetItem()
        self.tableWidget.setHorizontalHeaderItem(0, item)
        item = QtWidgets.QTableWidgetItem()
        self.tableWidget.setHorizontalHeaderItem(1, item)
        item = QtWidgets.QTableWidgetItem()
        self.tableWidget.setHorizontalHeaderItem(2, item)
        item = QtWidgets.QTableWidgetItem()
        font = QtGui.QFont()
        font.setPointSize(48)
        item.setFont(font)
        self.tableWidget.setItem(0, 0, item)
        item = QtWidgets.QTableWidgetItem()
        font = QtGui.QFont()
        font.setPointSize(17)
        item.setFont(font)
        self.tableWidget.setItem(3, 0, item)
        self.tableWidget.horizontalHeader().setDefaultSectionSize(153)
        self.tableWidget.verticalHeader().setDefaultSectionSize(56)
        self.tableWidget.verticalHeader().setMinimumSectionSize(33)
        self.tabWidget_4.addTab(self.tab_16, "")
        self.tabWidget_3.addTab(self.tab_3, "")
        self.tab_13 = QtWidgets.QWidget()
        self.tab_13.setObjectName("tab_13")
        self.tabWidget_5 = QtWidgets.QTabWidget(self.tab_13)
        self.tabWidget_5.setGeometry(QtCore.QRect(0, 0, 501, 451))
        font = QtGui.QFont()
        font.setFamily("Microsoft JhengHei")
        font.setPointSize(10)
        font.setBold(True)
        font.setWeight(75)
        self.tabWidget_5.setFont(font)
        self.tabWidget_5.setObjectName("tabWidget_5")
        self.tab_17 = QtWidgets.QWidget()
        self.tab_17.setObjectName("tab_17")
        self.tabWidget_5.addTab(self.tab_17, "")
        self.tab_18 = QtWidgets.QWidget()
        self.tab_18.setObjectName("tab_18")
        self.tabWidget_5.addTab(self.tab_18, "")
        self.tabWidget_3.addTab(self.tab_13, "")
        self.tab_14 = QtWidgets.QWidget()
        self.tab_14.setObjectName("tab_14")
        self.tabWidget_6 = QtWidgets.QTabWidget(self.tab_14)
        self.tabWidget_6.setGeometry(QtCore.QRect(0, 0, 501, 451))
        font = QtGui.QFont()
        font.setFamily("Microsoft JhengHei")
        font.setPointSize(10)
        font.setBold(True)
        font.setWeight(75)
        self.tabWidget_6.setFont(font)
        self.tabWidget_6.setObjectName("tabWidget_6")
        self.tab_19 = QtWidgets.QWidget()
        self.tab_19.setObjectName("tab_19")
        self.tabWidget_6.addTab(self.tab_19, "")
        self.tab_20 = QtWidgets.QWidget()
        self.tab_20.setObjectName("tab_20")
        self.tabWidget_6.addTab(self.tab_20, "")
        self.tabWidget_3.addTab(self.tab_14, "")
        self.tab_12 = QtWidgets.QWidget()
        self.tab_12.setObjectName("tab_12")
        self.tabWidget_7 = QtWidgets.QTabWidget(self.tab_12)
        self.tabWidget_7.setGeometry(QtCore.QRect(0, 0, 491, 371))
        font = QtGui.QFont()
        font.setFamily("Microsoft JhengHei")
        font.setPointSize(10)
        font.setBold(True)
        font.setWeight(75)
        self.tabWidget_7.setFont(font)
        self.tabWidget_7.setObjectName("tabWidget_7")
        self.tab_21 = QtWidgets.QWidget()
        self.tab_21.setObjectName("tab_21")
        self.tabWidget_7.addTab(self.tab_21, "")
        self.tab_22 = QtWidgets.QWidget()
        self.tab_22.setObjectName("tab_22")
        self.tabWidget_7.addTab(self.tab_22, "")
        self.tabWidget_3.addTab(self.tab_12, "")
        self.tabWidget.addTab(self.tab_5, "")
        self.tab_8 = QtWidgets.QWidget()
        self.tab_8.setObjectName("tab_8")
        self.textBrowser_2 = QtWidgets.QTextBrowser(self.tab_8)
        self.textBrowser_2.setGeometry(QtCore.QRect(30, 30, 411, 141))
        self.textBrowser_2.setObjectName("textBrowser_2")
        self.pushButton_21 = QtWidgets.QPushButton(self.tab_8)
        self.pushButton_21.setGeometry(QtCore.QRect(150, 220, 141, 31))
        self.pushButton_21.setObjectName("pushButton_21")
        self.tabWidget.addTab(self.tab_8, "")
        self.tab_7 = QtWidgets.QWidget()
        self.tab_7.setObjectName("tab_7")
        self.tabWidget_2 = QtWidgets.QTabWidget(self.tab_7)
        self.tabWidget_2.setGeometry(QtCore.QRect(0, 0, 471, 341))
        font = QtGui.QFont()
        font.setFamily("Microsoft JhengHei")
        font.setPointSize(8)
        font.setBold(True)
        font.setWeight(75)
        self.tabWidget_2.setFont(font)
        self.tabWidget_2.setDocumentMode(False)
        self.tabWidget_2.setObjectName("tabWidget_2")
        self.tab_9 = QtWidgets.QWidget()
        self.tab_9.setObjectName("tab_9")
        self.lineEdit = QtWidgets.QLineEdit(self.tab_9)
        self.lineEdit.setGeometry(QtCore.QRect(60, 20, 341, 31))
        font = QtGui.QFont()
        font.setPointSize(10)
        font.setBold(True)
        font.setWeight(75)
        self.lineEdit.setFont(font)
        self.lineEdit.setObjectName("lineEdit")
        self.lineEdit_2 = QtWidgets.QLineEdit(self.tab_9)
        self.lineEdit_2.setGeometry(QtCore.QRect(60, 100, 341, 31))
        font = QtGui.QFont()
        font.setPointSize(10)
        font.setBold(True)
        font.setWeight(75)
        self.lineEdit_2.setFont(font)
        self.lineEdit_2.setEchoMode(QtWidgets.QLineEdit.Password)
        self.lineEdit_2.setObjectName("lineEdit_2")
        self.pushButton_8 = QtWidgets.QPushButton(self.tab_9)
        self.pushButton_8.setGeometry(QtCore.QRect(150, 250, 121, 31))
        self.pushButton_8.setObjectName("pushButton_8")
        self.groupBox = QtWidgets.QGroupBox(self.tab_9)
        self.groupBox.setGeometry(QtCore.QRect(0, 170, 461, 61))
        self.groupBox.setTitle("")
        self.groupBox.setObjectName("groupBox")
        self.label = QtWidgets.QLabel(self.groupBox)
        self.label.setGeometry(QtCore.QRect(0, 20, 331, 31))
        self.label.setObjectName("label")
        self.pushButton_10 = QtWidgets.QPushButton(self.groupBox)
        self.pushButton_10.setGeometry(QtCore.QRect(330, 20, 121, 31))
        self.pushButton_10.setObjectName("pushButton_10")
        self.tabWidget_2.addTab(self.tab_9, "")
        self.tab_10 = QtWidgets.QWidget()
        self.tab_10.setObjectName("tab_10")
        self.lineEdit_3 = QtWidgets.QLineEdit(self.tab_10)
        self.lineEdit_3.setGeometry(QtCore.QRect(70, 10, 341, 31))
        font = QtGui.QFont()
        font.setFamily("MS Shell Dlg 2")
        font.setPointSize(10)
        font.setBold(True)
        font.setWeight(75)
        self.lineEdit_3.setFont(font)
        self.lineEdit_3.setObjectName("lineEdit_3")
        self.lineEdit_4 = QtWidgets.QLineEdit(self.tab_10)
        self.lineEdit_4.setGeometry(QtCore.QRect(70, 80, 341, 31))
        font = QtGui.QFont()
        font.setPointSize(10)
        font.setBold(True)
        font.setWeight(75)
        self.lineEdit_4.setFont(font)
        self.lineEdit_4.setObjectName("lineEdit_4")
        self.lineEdit_5 = QtWidgets.QLineEdit(self.tab_10)
        self.lineEdit_5.setGeometry(QtCore.QRect(70, 150, 341, 31))
        font = QtGui.QFont()
        font.setPointSize(10)
        font.setBold(True)
        font.setWeight(75)
        self.lineEdit_5.setFont(font)
        self.lineEdit_5.setEchoMode(QtWidgets.QLineEdit.Password)
        self.lineEdit_5.setObjectName("lineEdit_5")
        self.lineEdit_6 = QtWidgets.QLineEdit(self.tab_10)
        self.lineEdit_6.setGeometry(QtCore.QRect(70, 220, 341, 31))
        font = QtGui.QFont()
        font.setPointSize(10)
        font.setBold(True)
        font.setWeight(75)
        self.lineEdit_6.setFont(font)
        self.lineEdit_6.setEchoMode(QtWidgets.QLineEdit.Password)
        self.lineEdit_6.setObjectName("lineEdit_6")
        self.pushButton_9 = QtWidgets.QPushButton(self.tab_10)
        self.pushButton_9.setGeometry(QtCore.QRect(170, 270, 121, 31))
        self.pushButton_9.setObjectName("pushButton_9")
        self.tabWidget_2.addTab(self.tab_10, "")
        self.tab_11 = QtWidgets.QWidget()
        self.tab_11.setObjectName("tab_11")
        self.lineEdit_7 = QtWidgets.QLineEdit(self.tab_11)
        self.lineEdit_7.setGeometry(QtCore.QRect(50, 40, 341, 31))
        font = QtGui.QFont()
        font.setPointSize(10)
        font.setBold(True)
        font.setWeight(75)
        self.lineEdit_7.setFont(font)
        self.lineEdit_7.setObjectName("lineEdit_7")
        self.groupBox_2 = QtWidgets.QGroupBox(self.tab_11)
        self.groupBox_2.setGeometry(QtCore.QRect(10, 120, 451, 51))
        self.groupBox_2.setTitle("")
        self.groupBox_2.setObjectName("groupBox_2")
        self.label_2 = QtWidgets.QLabel(self.groupBox_2)
        self.label_2.setGeometry(QtCore.QRect(20, 19, 151, 31))
        self.label_2.setObjectName("label_2")
        self.pushButton_11 = QtWidgets.QPushButton(self.groupBox_2)
        self.pushButton_11.setGeometry(QtCore.QRect(320, 20, 111, 21))
        self.pushButton_11.setObjectName("pushButton_11")
        self.pushButton_13 = QtWidgets.QPushButton(self.groupBox_2)
        self.pushButton_13.setGeometry(QtCore.QRect(180, 20, 111, 21))
        self.pushButton_13.setObjectName("pushButton_13")
        self.pushButton_12 = QtWidgets.QPushButton(self.tab_11)
        self.pushButton_12.setGeometry(QtCore.QRect(80, 200, 281, 31))
        self.pushButton_12.setObjectName("pushButton_12")
        self.tabWidget_2.addTab(self.tab_11, "")
        self.tabWidget.addTab(self.tab_7, "")
        self.tab_23 = QtWidgets.QWidget()
        self.tab_23.setObjectName("tab_23")
        self.tabWidget.addTab(self.tab_23, "")
        self.pushButton = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton.setGeometry(QtCore.QRect(10, -10, 121, 41))
        font = QtGui.QFont()
        font.setFamily("Microsoft Tai Le")
        font.setPointSize(8)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton.setFont(font)
        icon4 = QtGui.QIcon()
        icon4.addPixmap(
            QtGui.QPixmap(":/img/camera.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off
        )
        self.pushButton.setIcon(icon4)
        self.pushButton.setIconSize(QtCore.QSize(61, 61))
        self.pushButton.setFlat(True)
        self.pushButton.setObjectName("pushButton")
        self.pushButton_2 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_2.setGeometry(QtCore.QRect(10, 190, 121, 41))
        font = QtGui.QFont()
        font.setFamily("Microsoft Tai Le")
        font.setPointSize(8)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_2.setFont(font)
        icon5 = QtGui.QIcon()
        icon5.addPixmap(
            QtGui.QPixmap(":/img/updates.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off
        )
        self.pushButton_2.setIcon(icon5)
        self.pushButton_2.setIconSize(QtCore.QSize(61, 61))
        self.pushButton_2.setFlat(True)
        self.pushButton_2.setObjectName("pushButton_2")
        self.pushButton_3 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_3.setGeometry(QtCore.QRect(10, 140, 121, 41))
        font = QtGui.QFont()
        font.setFamily("Microsoft Tai Le")
        font.setPointSize(8)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_3.setFont(font)
        icon6 = QtGui.QIcon()
        icon6.addPixmap(
            QtGui.QPixmap(":/img/ga.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off
        )
        self.pushButton_3.setIcon(icon6)
        self.pushButton_3.setIconSize(QtCore.QSize(61, 61))
        self.pushButton_3.setFlat(True)
        self.pushButton_3.setObjectName("pushButton_3")
        self.pushButton_5 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_5.setGeometry(QtCore.QRect(10, 40, 121, 41))
        font = QtGui.QFont()
        font.setFamily("Microsoft Tai Le")
        font.setPointSize(8)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_5.setFont(font)
        icon7 = QtGui.QIcon()
        icon7.addPixmap(
            QtGui.QPixmap(":/img/head1.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off
        )
        self.pushButton_5.setIcon(icon7)
        self.pushButton_5.setIconSize(QtCore.QSize(61, 61))
        self.pushButton_5.setFlat(True)
        self.pushButton_5.setObjectName("pushButton_5")
        self.pushButton_7 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_7.setGeometry(QtCore.QRect(10, 290, 121, 41))
        font = QtGui.QFont()
        font.setFamily("Microsoft Tai Le")
        font.setPointSize(8)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_7.setFont(font)
        icon8 = QtGui.QIcon()
        icon8.addPixmap(
            QtGui.QPixmap(":/img/login.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off
        )
        self.pushButton_7.setIcon(icon8)
        self.pushButton_7.setIconSize(QtCore.QSize(61, 61))
        self.pushButton_7.setFlat(True)
        self.pushButton_7.setObjectName("pushButton_7")
        self.pushButton_20 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_20.setGeometry(QtCore.QRect(10, 240, 121, 41))
        font = QtGui.QFont()
        font.setFamily("Microsoft Tai Le")
        font.setPointSize(8)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_20.setFont(font)
        icon9 = QtGui.QIcon()
        icon9.addPixmap(
            QtGui.QPixmap(":/img/diag.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off
        )
        self.pushButton_20.setIcon(icon9)
        self.pushButton_20.setIconSize(QtCore.QSize(61, 61))
        self.pushButton_20.setFlat(True)
        self.pushButton_20.setObjectName("pushButton_20")
        self.pushButton_6 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_6.setGeometry(QtCore.QRect(10, 90, 121, 41))
        font = QtGui.QFont()
        font.setFamily("Microsoft Tai Le")
        font.setPointSize(8)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_6.setFont(font)
        icon10 = QtGui.QIcon()
        icon10.addPixmap(
            QtGui.QPixmap(":/img/not1.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off
        )
        self.pushButton_6.setIcon(icon10)
        self.pushButton_6.setIconSize(QtCore.QSize(61, 61))
        self.pushButton_6.setFlat(True)
        self.pushButton_6.setObjectName("pushButton_6")
        self.pushButton_4 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_4.setGeometry(QtCore.QRect(10, 340, 121, 41))
        font = QtGui.QFont()
        font.setFamily("Microsoft Tai Le")
        font.setPointSize(8)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_4.setFont(font)
        icon11 = QtGui.QIcon()
        icon11.addPixmap(
            QtGui.QPixmap(":/img/schedule.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off
        )
        self.pushButton_4.setIcon(icon11)
        self.pushButton_4.setIconSize(QtCore.QSize(61, 61))
        self.pushButton_4.setFlat(True)
        self.pushButton_4.setObjectName("pushButton_4")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 640, 30))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.toolBar = QtWidgets.QToolBar(MainWindow)
        self.toolBar.setObjectName("toolBar")
        MainWindow.addToolBar(QtCore.Qt.TopToolBarArea, self.toolBar)

        self.retranslateUi(MainWindow)
        self.tabWidget.setCurrentIndex(6)
        self.tabWidget_3.setCurrentIndex(0)
        self.tabWidget_4.setCurrentIndex(0)
        self.tabWidget_5.setCurrentIndex(0)
        self.tabWidget_6.setCurrentIndex(0)
        self.tabWidget_7.setCurrentIndex(1)
        self.tabWidget_2.setCurrentIndex(0)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.tabWidget.setTabText(
            self.tabWidget.indexOf(self.tab_6), _translate("MainWindow", "Page")
        )
        self.tabWidget.setTabText(
            self.tabWidget.indexOf(self.tab_2), _translate("MainWindow", "page")
        )
        self.tabWidget.setTabText(
            self.tabWidget.indexOf(self.tab), _translate("MainWindow", "Page")
        )
        self.tabWidget.setTabText(
            self.tabWidget.indexOf(self.tab_4), _translate("MainWindow", "Page")
        )
        self.pushButton_14.setText(_translate("MainWindow", "Brakes"))
        self.pushButton_15.setText(_translate("MainWindow", "Engine"))
        self.pushButton_16.setText(_translate("MainWindow", "Ignition"))
        self.pushButton_17.setText(_translate("MainWindow", "Airbags"))
        self.label_3.setText(_translate("MainWindow", "Do you want to update it now ?"))
        self.pushButton_18.setText(_translate("MainWindow", "Update"))
        self.pushButton_19.setText(_translate("MainWindow", "Later"))
        self.label_4.setText(_translate("MainWindow", "Update Progress"))
        self.tabWidget_4.setTabText(
            self.tabWidget_4.indexOf(self.tab_15),
            _translate("MainWindow", "Notifications"),
        )
        item = self.tableWidget.verticalHeaderItem(0)
        item.setText(_translate("MainWindow", "NO1"))
        item = self.tableWidget.verticalHeaderItem(1)
        item.setText(_translate("MainWindow", "NO2"))
        item = self.tableWidget.verticalHeaderItem(2)
        item.setText(_translate("MainWindow", "NO3"))
        item = self.tableWidget.verticalHeaderItem(3)
        item.setText(_translate("MainWindow", "NO4"))
        item = self.tableWidget.verticalHeaderItem(4)
        item.setText(_translate("MainWindow", "NO5"))
        item = self.tableWidget.verticalHeaderItem(5)
        item.setText(_translate("MainWindow", "NO6"))
        item = self.tableWidget.verticalHeaderItem(6)
        item.setText(_translate("MainWindow", "NO7"))
        item = self.tableWidget.horizontalHeaderItem(0)
        item.setText(_translate("MainWindow", "Date"))
        item = self.tableWidget.horizontalHeaderItem(1)
        item.setText(_translate("MainWindow", "Update Details"))
        item = self.tableWidget.horizontalHeaderItem(2)
        item.setText(_translate("MainWindow", "Status"))
        __sortingEnabled = self.tableWidget.isSortingEnabled()
        self.tableWidget.setSortingEnabled(False)
        self.tableWidget.setSortingEnabled(__sortingEnabled)
        self.tabWidget_4.setTabText(
            self.tabWidget_4.indexOf(self.tab_16),
            _translate("MainWindow", "Updates History"),
        )
        self.tabWidget_3.setTabText(
            self.tabWidget_3.indexOf(self.tab_3), _translate("MainWindow", "Page")
        )
        self.tabWidget_5.setTabText(
            self.tabWidget_5.indexOf(self.tab_17),
            _translate("MainWindow", "Notifications"),
        )
        self.tabWidget_5.setTabText(
            self.tabWidget_5.indexOf(self.tab_18),
            _translate("MainWindow", "Updates History"),
        )
        self.tabWidget_3.setTabText(
            self.tabWidget_3.indexOf(self.tab_13), _translate("MainWindow", "Page")
        )
        self.tabWidget_6.setTabText(
            self.tabWidget_6.indexOf(self.tab_19),
            _translate("MainWindow", "Notifications"),
        )
        self.tabWidget_6.setTabText(
            self.tabWidget_6.indexOf(self.tab_20),
            _translate("MainWindow", "Updates History"),
        )
        self.tabWidget_3.setTabText(
            self.tabWidget_3.indexOf(self.tab_14), _translate("MainWindow", "Page")
        )
        self.tabWidget_7.setTabText(
            self.tabWidget_7.indexOf(self.tab_21),
            _translate("MainWindow", "Notifications"),
        )
        self.tabWidget_7.setTabText(
            self.tabWidget_7.indexOf(self.tab_22),
            _translate("MainWindow", "Updates History"),
        )
        self.tabWidget_3.setTabText(
            self.tabWidget_3.indexOf(self.tab_12), _translate("MainWindow", "Page")
        )
        self.tabWidget.setTabText(
            self.tabWidget.indexOf(self.tab_5), _translate("MainWindow", "Page")
        )
        self.pushButton_21.setText(_translate("MainWindow", "Send Diagnostics"))
        self.tabWidget.setTabText(
            self.tabWidget.indexOf(self.tab_8), _translate("MainWindow", "Page")
        )
        self.lineEdit.setPlaceholderText(
            _translate("MainWindow", "Enter Your Username")
        )
        self.lineEdit_2.setPlaceholderText(
            _translate("MainWindow", "Enter Your Password")
        )
        self.pushButton_8.setText(_translate("MainWindow", "Login"))
        self.label.setText(
            _translate(
                "MainWindow",
                "Your Password is Incorrect, click resend if you forgot your pssword",
            )
        )
        self.pushButton_10.setText(_translate("MainWindow", "Resend Password"))
        self.tabWidget_2.setTabText(
            self.tabWidget_2.indexOf(self.tab_9), _translate("MainWindow", "Login")
        )
        self.lineEdit_3.setPlaceholderText(
            _translate("MainWindow", "Enter Your Username")
        )
        self.lineEdit_4.setPlaceholderText(_translate("MainWindow", "Enter Your Email"))
        self.lineEdit_5.setPlaceholderText(
            _translate("MainWindow", "Enter Your Password")
        )
        self.lineEdit_6.setPlaceholderText(
            _translate("MainWindow", "Confirm Your Password")
        )
        self.pushButton_9.setText(_translate("MainWindow", "Sign up"))
        self.tabWidget_2.setTabText(
            self.tabWidget_2.indexOf(self.tab_10), _translate("MainWindow", "Sign up")
        )
        self.lineEdit_7.setPlaceholderText(_translate("MainWindow", "Enter Your Email"))
        self.label_2.setText(_translate("MainWindow", "You can login from here"))
        self.pushButton_11.setText(_translate("MainWindow", "Login"))
        self.pushButton_13.setText(_translate("MainWindow", "Resend Password"))
        self.pushButton_12.setText(_translate("MainWindow", "Send me on Email"))
        self.tabWidget_2.setTabText(
            self.tabWidget_2.indexOf(self.tab_11), _translate("MainWindow", "Resend")
        )
        self.tabWidget.setTabText(
            self.tabWidget.indexOf(self.tab_7), _translate("MainWindow", "Page")
        )
        self.tabWidget.setTabText(
            self.tabWidget.indexOf(self.tab_23), _translate("MainWindow", "Page")
        )
        self.pushButton.setText(_translate("MainWindow", "Gallery"))
        self.pushButton_2.setText(_translate("MainWindow", "FOTA"))
        self.pushButton_3.setText(_translate("MainWindow", "Games"))
        self.pushButton_5.setText(_translate("MainWindow", "Music"))
        self.pushButton_7.setText(_translate("MainWindow", "Users"))
        self.pushButton_20.setText(_translate("MainWindow", "DIAGS"))
        self.pushButton_6.setText(_translate("MainWindow", "Notify"))
        self.pushButton_4.setText(_translate("MainWindow", "Calendar"))
        self.toolBar.setWindowTitle(_translate("MainWindow", "toolBar"))


if __name__ == "__main__":
    import sys

    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())
