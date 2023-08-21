from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(998, 616)
        Form.setMinimumSize(QtCore.QSize(998, 616))
        Form.setMaximumSize(QtCore.QSize(998, 616))
        self.pushButton = QtWidgets.QPushButton(Form)
        self.pushButton.setGeometry(QtCore.QRect(70, 40, 411, 311))
        self.pushButton.setStyleSheet("border:1px")
        self.pushButton.setText("")
        # icon = QtGui.QIcon()
        # icon.addPixmap(QtGui.QPixmap("image001.jpg"),
                    #    QtGui.QIcon.Normal, QtGui.QIcon.Off)
        # self.pushButton.setIcon(icon)
        self.pushButton.setIconSize(QtCore.QSize(300, 300))
        self.pushButton.setFlat(True)
        self.pushButton.setObjectName("pushButton")
        self.pushButton_2 = QtWidgets.QPushButton(Form)
        self.pushButton_2.setEnabled(True)
        self.pushButton_2.setGeometry(QtCore.QRect(530, 40, 411, 311))
        self.pushButton_2.setStyleSheet("border:1px")
        self.pushButton_2.setText("")
        # self.pushButton_2.setIcon(icon)
        self.pushButton_2.setIconSize(QtCore.QSize(300, 300))
        self.pushButton_2.setFlat(True)
        self.pushButton_2.setObjectName("pushButton_2")
        self.lineEdit = QtWidgets.QLineEdit(Form)
        self.lineEdit.setGeometry(QtCore.QRect(50, 530, 891, 31))
        self.lineEdit.setText("")
        self.lineEdit.setObjectName("lineEdit")
        self.radioButton = QtWidgets.QRadioButton(Form)
        self.radioButton.setGeometry(QtCore.QRect(60, 570, 83, 18))
        self.radioButton.setObjectName("radioButton")
        self.radioButton_2 = QtWidgets.QRadioButton(Form)
        self.radioButton_2.setGeometry(QtCore.QRect(190, 570, 83, 18))
        self.radioButton_2.setObjectName("radioButton_2")
        self.radioButton_3 = QtWidgets.QRadioButton(Form)
        self.radioButton_3.setGeometry(QtCore.QRect(330, 570, 83, 18))
        self.radioButton_3.setObjectName("radioButton_3")
        self.textBrowser = QtWidgets.QTextBrowser(Form)
        self.textBrowser.setEnabled(False)
        self.textBrowser.setGeometry(QtCore.QRect(50, 400, 256, 111))
        self.textBrowser.setStyleSheet("")
        self.textBrowser.setObjectName("textBrowser")
        self.pushButton_3 = QtWidgets.QPushButton(Form)
        self.pushButton_3.setGeometry(QtCore.QRect(860, 570, 75, 23))
        self.pushButton_3.setObjectName("pushButton_3")
        self.checkBox = QtWidgets.QCheckBox(Form)
        self.checkBox.setGeometry(QtCore.QRect(360, 400, 70, 18))
        self.checkBox.setObjectName("checkBox")
        self.checkBox_2 = QtWidgets.QCheckBox(Form)
        self.checkBox_2.setGeometry(QtCore.QRect(470, 400, 70, 18))
        self.checkBox_2.setObjectName("checkBox_2")
        self.checkBox_3 = QtWidgets.QCheckBox(Form)
        self.checkBox_3.setGeometry(QtCore.QRect(580, 400, 70, 18))
        self.checkBox_3.setObjectName("checkBox_3")
        self.checkBox_4 = QtWidgets.QCheckBox(Form)
        self.checkBox_4.setGeometry(QtCore.QRect(670, 400, 70, 18))
        self.checkBox_4.setObjectName("checkBox_4")
        self.checkBox_5 = QtWidgets.QCheckBox(Form)
        self.checkBox_5.setGeometry(QtCore.QRect(770, 400, 70, 18))
        self.checkBox_5.setObjectName("checkBox_5")
        self.checkBox_6 = QtWidgets.QCheckBox(Form)
        self.checkBox_6.setGeometry(QtCore.QRect(870, 400, 70, 18))
        self.checkBox_6.setObjectName("checkBox_6")
        self.checkBox_7 = QtWidgets.QCheckBox(Form)
        self.checkBox_7.setGeometry(QtCore.QRect(360, 430, 70, 18))
        self.checkBox_7.setObjectName("checkBox_7")
        self.checkBox_8 = QtWidgets.QCheckBox(Form)
        self.checkBox_8.setGeometry(QtCore.QRect(470, 430, 70, 18))
        self.checkBox_8.setObjectName("checkBox_8")
        self.checkBox_9 = QtWidgets.QCheckBox(Form)
        self.checkBox_9.setGeometry(QtCore.QRect(580, 430, 70, 18))
        self.checkBox_9.setObjectName("checkBox_9")
        self.checkBox_10 = QtWidgets.QCheckBox(Form)
        self.checkBox_10.setGeometry(QtCore.QRect(670, 430, 70, 18))
        self.checkBox_10.setObjectName("checkBox_10")
        self.checkBox_11 = QtWidgets.QCheckBox(Form)
        self.checkBox_11.setGeometry(QtCore.QRect(770, 430, 70, 18))
        self.checkBox_11.setObjectName("checkBox_11")
        self.checkBox_12 = QtWidgets.QCheckBox(Form)
        self.checkBox_12.setGeometry(QtCore.QRect(870, 430, 70, 18))
        self.checkBox_12.setObjectName("checkBox_12")
        self.checkBox_13 = QtWidgets.QCheckBox(Form)
        self.checkBox_13.setGeometry(QtCore.QRect(770, 460, 70, 18))
        self.checkBox_13.setObjectName("checkBox_13")
        self.checkBox_15 = QtWidgets.QCheckBox(Form)
        self.checkBox_15.setGeometry(QtCore.QRect(580, 460, 70, 18))
        self.checkBox_15.setObjectName("checkBox_15")
        self.checkBox_16 = QtWidgets.QCheckBox(Form)
        self.checkBox_16.setGeometry(QtCore.QRect(470, 460, 70, 18))
        self.checkBox_16.setObjectName("checkBox_16")
        self.checkBox_17 = QtWidgets.QCheckBox(Form)
        self.checkBox_17.setGeometry(QtCore.QRect(670, 460, 70, 18))
        self.checkBox_17.setObjectName("checkBox_17")
        self.checkBox_18 = QtWidgets.QCheckBox(Form)
        self.checkBox_18.setGeometry(QtCore.QRect(360, 490, 70, 18))
        self.checkBox_18.setObjectName("checkBox_18")
        self.checkBox_19 = QtWidgets.QCheckBox(Form)
        self.checkBox_19.setGeometry(QtCore.QRect(870, 460, 70, 18))
        self.checkBox_19.setObjectName("checkBox_19")
        self.checkBox_21 = QtWidgets.QCheckBox(Form)
        self.checkBox_21.setGeometry(QtCore.QRect(360, 460, 70, 18))
        self.checkBox_21.setObjectName("checkBox_21")
        self.radioButton_4 = QtWidgets.QRadioButton(Form)
        self.radioButton_4.setGeometry(QtCore.QRect(460, 570, 82, 17))
        self.radioButton_4.setObjectName("radioButton_4")

        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def main_job(self):
        self.checkBox.isChecked
        self.checkBox_2.isChecked
        self.checkBox_3.isChecked
        self.checkBox_4.isChecked
        self.checkBox_5.isChecked
        self.checkBox_6.isChecked
        self.checkBox_7.isChecked
        self.checkBox_8.isChecked
        self.checkBox_9.isChecked
        self.checkBox_10.isChecked
        self.checkBox_11.isChecked
        self.checkBox_12.isChecked
        self.checkBox_13.isChecked
        self.checkBox_21.isChecked
        self.checkBox_15.isChecked
        self.checkBox_16.isChecked
        self.checkBox_16.isChecked
        self.checkBox_17.isChecked
        self.checkBox_18.isChecked
        self.checkBox_19.isChecked

        a=self.lineEdit.text()
        self.radioButton.isChecked
        self.radioButton_2.isChecked
        self.radioButton_3.isChecked
        self.radioButton_4.isChecked
        # run cpp


        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap("image001.jpg"),
                       QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.pushButton.setIcon(icon)

        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap("image001.jpg"),
                       QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.pushButton_2.setIcon(icon)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "Form"))
        self.radioButton.setText(_translate("Form", "E-MAIL"))
        self.radioButton_2.setText(_translate("Form", "URL-SOCKET"))
        self.radioButton_3.setText(_translate("Form", "URL-CURL"))
        self.textBrowser.setHtml(_translate("Form", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
                                            "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
                                            "p, li { white-space: pre-wrap; }\n"
                                            "</style></head><body style=\" font-family:\'MS Shell Dlg 2\'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
                                            "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:7.875pt;\">1.if you want select your picture from system choose local path  </span></p>\n"
                                            "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:7.875pt;\">2.if you want downlaod your picture from url write your url</span></p>\n"
                                            "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:7.875pt;\">3. if you want use email send your picture to parsaali0002@gmail.com </span></p></body></html>"))
        self.pushButton_3.setText(_translate("Form", "go"))
        self.checkBox.setText(_translate("Form", "hue"))
        self.checkBox_2.setText(_translate("Form", ""))
        self.checkBox_3.setText(_translate("Form", "solarize"))
        self.checkBox_4.setText(_translate("Form", "revert"))
        self.checkBox_5.setText(_translate("Form", "grayscale"))
        self.checkBox_6.setText(_translate("Form", "sepia"))
        self.checkBox_7.setText(_translate("Form", "brn"))
        self.checkBox_8.setText(_translate("Form", "offgrid"))
        self.checkBox_9.setText(_translate("Form", "cybr"))
        self.checkBox_10.setText(_translate("Form", "sharpen"))
        self.checkBox_11.setText(_translate("Form", "noise"))
        self.checkBox_12.setText(_translate("Form", "vin4"))
        self.checkBox_13.setText(_translate("Form", "warmcolor"))
        self.checkBox_15.setText(_translate("Form", "ooipainting"))
        self.checkBox_16.setText(_translate("Form", "motion blur"))
        self.checkBox_17.setText(_translate("Form", "cross"))
        self.checkBox_18.setText(_translate("Form", "neon"))
        self.checkBox_19.setText(_translate("Form", "comic"))
        self.checkBox_21.setText(_translate("Form", "watercolor"))
        self.radioButton_4.setText(_translate("Form", "LOCAL-PATH"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Form = QtWidgets.QWidget()
    ui = Ui_Form()
    ui.setupUi(Form)
    ui.pushButton_3.clicked.connect(lambda:ui.main_job())
    Form.show()
    sys.exit(app.exec_())
