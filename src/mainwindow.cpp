#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QPushButton>
#include <QMessageBox>
#include <string>
#include <bitset>
#include <sstream>
#include "MIPS.h"

bool Flag_IsNew = false;
bool Flag_IsOpen = false;
QString Last_FileName;
QString Last_FileContent;

bool DEBUG_Start = false;
int DEBUG_Line = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->resize((QSize(1600,1200)));
    ui->setupUi(this);
    setWindowTitle("MIPS模拟器");
    setWindowIcon(QIcon("./favicon.ico"));
    ui->plainTextEdit->setMode(EDIT);
    ui->stackedWidget->setCurrentIndex(0);
    ui->regTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->memoryTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->regTable->setSelectionMode(QAbstractItemView::NoSelection);
//    ui->memoryTable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->regTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->memoryTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->memoryTable->setStyleSheet("selection-background-color:rgb(215,209,215)");

    ui->chooseNumber->setCurrentIndex(0);
    ui->chooseRadix->setCurrentIndex(0);
    ui->numberLabel_1->setText("Magnitude");
    ui->numberLabel_2->setText("Complement");
    ui->numberLabel_1->setAlignment(Qt::AlignCenter);
    ui->numberLabel_2->setAlignment(Qt::AlignCenter);

    for(int i=0; i < 8000; i++){
        btn[i] = nullptr;
    }
    showDisplay();

    this->on_actionNew_triggered();
//    MyHighLighter *highlighter = new MyHighLighter(configEditor->document());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_2_triggered(){
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,tr("Open File"),tr(""),tr("Assembly(*.asm);;Binary(*.bin))"));
    if(fileName == "")                  //如果用户直接关闭了文件浏览对话框，那么文件名就为空值，直接返回
    {
        return;
    }
    else
    {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,tr("错误"),tr("打开文件失败"));
            return;
        }
        else
        {
            if(!file.isReadable())
            {
                QMessageBox::warning(this,tr("错误"),tr("该文件不可读"));
            }
            else
            {
                QTextStream textStream(&file);       //读取文件，使用QTextStream
                while(!textStream.atEnd())
                {
                    ui->plainTextEdit->setPlainText(textStream.readAll());
                }
                ui->plainTextEdit->show();
                file.close();
                Flag_IsOpen = true;
                Last_FileName = fileName;
            }
        }
    }
}
void MainWindow::on_actionNew_triggered()
{
    ui->plainTextEdit->clear();
    ui->outputTest->clear();
    Flag_IsNew = true;
    Flag_IsOpen = true;
//    QFileDialog fileDialog;
//    QString filePath;
//    filePath = fileDialog.getSaveFileName(this,tr("New File"),"",tr("Assembly(*.asm);;Binary(*.bin))"));
//    if(filePath.isEmpty()){
//        QMessageBox::warning(this,"Failed!","文件路径不能为空！");
//        return;
//    }

//    QFile file(filePath);

//    // 文件不存在则自动创建，若存在则写入空值
//    if(!file.open(QIODevice::ReadWrite | QIODevice::Truncate)){
//        QMessageBox::warning(this,"ERROR","新建文件失败！");
//        return;
//    }
//    else{
//        QString str = "";
//             file.write(str.toLatin1());
//        file.close();
//             ui->outputTest->clear();             //清除原先文件内容
//        Flag_IsNew = true;
//        Flag_IsOpen = true;
//    }
}


void MainWindow::on_actionSave_triggered()
{
    if(Flag_IsNew)                  //如果新文件标记位为1，则弹出保存文件对话框
    {
        if(ui->plainTextEdit->toPlainText() == "")
        {
            QMessageBox::warning(this,tr("警告"),tr("内容不能为空!"),QMessageBox::Ok);
        }
        else
        {
            QFileDialog fileDialog;
            QString str = fileDialog.getSaveFileName(this,tr("Open File"),"",tr("Assembly(*.asm);;Binary(*.bin))"));
            if(str == "")
            {
                return;
            }
            QFile filename(str);
            if(!filename.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QMessageBox::warning(this,tr("错误"),tr("打开文件失败"),QMessageBox::Ok);
                return;
            }
            else
            {
                QTextStream textStream(&filename);
                QString str = ui->plainTextEdit->toPlainText();
                textStream<<str;
                Last_FileContent = str;
            }
            QMessageBox::information(this,"保存文件","保存文件成功",QMessageBox::Ok);
            filename.close();
            Flag_IsNew = 0;     //新文件标记位记为0
            Last_FileName = str;//保存文件内容
        }
    }
    else                        //否则，新文件标记位是0，代表是旧文件，默认直接保存覆盖源文件
    {
        if(Flag_IsOpen)         //判断是否创建或打开了一个文件
        {
            QFile file(Last_FileName);
            if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QMessageBox::warning(this,tr("警告"),tr("打开文件失败"));
                return;
            }
            else
            {
                QTextStream textStream(&file);
                QString str = ui->plainTextEdit->toPlainText();
                textStream<<str;
                Last_FileContent = str;
                file.close();
            }
        }
        else
        {
            QMessageBox::warning(this,tr("警告"),tr("请先创建或者打开文件"));
            return;
        }
    }

}


void MainWindow::on_Code_Button_1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_Code_Button_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_Code_Button_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_Display_Button_1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::on_Display_Button_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::on_Display_Button_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_Number_Button_1_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::on_Number_Button_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::on_Number_Button_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->outputTest->clear();
    QString plainTextEditContents = ui->plainTextEdit->toPlainText();
    QStringList lines = plainTextEditContents.split("\n");

    if(ui->comboBox->currentIndex() == 0){
        try{
            vector<string> instr;
            for(int i=0; i < lines.length(); i++){
                string strtext = lines.at(i).toStdString();
                instr.push_back(strtext);
            }
            assembler.read(instr);
            int start = assembler.solve();
            if(start < 0){
                string s = "Error at loop " + to_string(-start);
                errorMsg(QString::fromStdString(s));
                return;
            }
            if(!ui->outputTest->isReadOnly())
                ui->outputTest->setReadOnly(true);
            for(auto &item: assembler.machine_code){
                ui->outputTest->appendPlainText(QString::fromStdString(item));
            }
            mips.load_and_execute(assembler.machine_code, start);
        }catch(const std::exception& e){
            errorMsg(e.what());
            return;
        }
    }
    else if(ui->comboBox->currentIndex() == 1){
        try{
            vector<string> instr;
            int type = 0;
            for(int i=0; i < lines.length(); i++){
                string strtext = lines.at(i).toStdString();
                if((strtext[0] == 'x' || strtext[0] == 'X') && type == 0){
                    type = 1;
                }
                instr.push_back(strtext);
            }
            disassembly.read(type, instr);
            int start = disassembly.solve();
            if(start < 0){
                string s = "Error at loop " + to_string(-start);
                errorMsg(QString::fromStdString(s));
                return;
            }
            if(!ui->outputTest->isReadOnly())
                ui->outputTest->setReadOnly(true);
            for(auto &item: disassembly.instruct){
                ui->outputTest->appendPlainText(QString::fromStdString(item));
            }
            mips.load_and_execute(disassembly.instruct_binary, 0);
        }catch(const std::exception& e){
            errorMsg(e.what());
            return;
        }
    }
    showDisplay();
}

void MainWindow::errorMsg(QString msg){
    QMessageBox::critical(this, tr("Error"), msg,
                          QMessageBox::Save | QMessageBox::Discard,  QMessageBox::Discard);
}

void MainWindow:: showDisplay(){
    ui->regTable->setColumnCount(2);
    ui->regTable->setRowCount(34);
    ui->regTable->setItem(0, 0, new QTableWidgetItem("PC"));
    ui->regTable->setItem(1, 0, new QTableWidgetItem("PC+4"));
    ostringstream ss;
    ss << "x" << setfill('0') << setw(8) << hex << mips.PC;
    ui->regTable->setItem(0, 1, new QTableWidgetItem(QString::fromStdString(ss.str())));
    ss.str("");
    ss << "x" << setfill('0') << setw(8) << hex << mips.PC+4;
    ui->regTable->setItem(1, 1, new QTableWidgetItem(QString::fromStdString(ss.str())));
    for(int i=0; i < 32; i++){
        bitset<5> bit(i);
        ss.str("");
        ss << "x" << setfill('0') << setw(8) << hex << mips.reg[i];
        string k = ss.str();
        ui->regTable->setItem(i+2, 0, new QTableWidgetItem(QString::fromStdString(disassembly.reg_binary[bit.to_string()])));
        ui->regTable->setItem(i+2, 1, new QTableWidgetItem(QString::fromStdString(ss.str())));
    }

    ui->memoryTable->setColumnCount(2);
    ui->memoryTable->setRowCount(65536);
    for(int i=0; i < 65536; i++){
        ss.str("");
        ss << "x" << setfill('0') << setw(4) << hex << i*4;
        ui->memoryTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(ss.str())));
        ss.str("");
        ss << "x" << setfill('0') << setw(8) << hex << mips.memo[i];
        ui->memoryTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(ss.str())));
    }
}

void MainWindow::on_chooseNumber_currentIndexChanged(int index)
{
    if(index == 0){
        ui->numberLabel_1->setText("Magnitude");
        ui->numberLabel_2->setText("Complement");
        ui->chooseRadix->clear();
        ui->chooseRadix->addItem("Decimal");
        ui->chooseRadix->addItem("Binary");
        ui->chooseRadix->addItem("Hexadecimal");
        ui->chooseRadix->setCurrentIndex(0);
    }
    else{
        ui->numberLabel_1->setText("Binary");
        ui->numberLabel_2->setText("Hexadecimal");
        ui->chooseRadix->clear();
        ui->chooseRadix->addItem("Decimal");
        ui->chooseRadix->addItem("Binary");
        ui->chooseRadix->setCurrentIndex(0);
    }
}

void MainWindow::on_chooseRadix_currentIndexChanged(int index)
{
    if(ui->chooseNumber->currentIndex() == 0){
        if(index == 0){
            ui->numberLabel_1->setText("Magnitude");
        }
        else{
            ui->numberLabel_1->setText("Decimal");
        }
    }
    else if(ui->chooseNumber->currentIndex() == 1){
        if(index == 0){
            ui->numberLabel_1->setText("Binary");
        }
        else{
            ui->numberLabel_1->setText("Float");
        }
    }
    else if(ui->chooseNumber->currentIndex() == 2){
        if(index == 0){
            ui->numberLabel_1->setText("Binary");
        }
        else{
            ui->numberLabel_1->setText("Double");
        }
    }
}

void MainWindow::on_inputNumber_editingFinished()
{
    QString text = ui->inputNumber->text();
    if(text == ""){
        errorMsg("Text is empty!");
        return;
    }
    if(ui->chooseNumber->currentIndex() == 0){// 整数的原码与补码表示
        if(ui->chooseRadix->currentIndex() == 0){//输入十进制数
            try{
                int number = stoi(text.toStdString());
                ui->numberConvert_1->setText(QString::fromStdString(Binary_change.Int2Binary(number, 32)));
                ui->numberConvert_2->setText(QString::fromStdString(Binary_change.Int2Complement(number, 32)));
            }catch(const std::exception& e){
                errorMsg("Error Format");
                return;
            }
        }
        else if(ui->chooseRadix->currentIndex() == 1){//输入二进制数
            try{
                int number = stoi(text.toStdString(), 0, 2);
                ui->numberConvert_1->setText(QString::fromStdString(to_string(number)));
                ui->numberConvert_2->setText(QString::fromStdString(Binary_change.Int2Complement(number, 32)));
            }catch(const std::exception& e){
                errorMsg("Error Format");
                return;
            }

        }
        else if(ui->chooseRadix->currentIndex() == 2){//输入十六进制数
            try{
                int number = stoi(text.toStdString(), 0, 16);
                ui->numberConvert_1->setText(QString::fromStdString(to_string(number)));
                ui->numberConvert_2->setText(QString::fromStdString(Binary_change.Int2Complement(number, 32)));
            }catch(const std::exception& e){
                errorMsg("Error Format");
                return;
            }

        }
    }
    else if(ui->chooseNumber->currentIndex() == 1){//float的表示
        if(ui->chooseRadix->currentIndex() == 0){
            try{
                float number = stof(text.toStdString());
                ui->numberConvert_1->setText(QString::fromStdString(Float_change.float2binary(number)));
                ostringstream ss;
                ss << disassembly.binary2hex(Float_change.float2binary(number));
                ui->numberConvert_2->setText(QString::fromStdString(ss.str()));
            }catch(const std::exception& e){
                errorMsg("Error Format");
                return;
            }
        }
        else if(ui->chooseRadix->currentIndex() == 1){
            string s = text.toStdString();
            if(s.length() != 32){
                errorMsg("Format Error");
                return;
            }
            try{
                ui->numberConvert_1->setText(QString::fromStdString(to_string(Float_change.binary2float(s))));
                ostringstream ss;
                ss << disassembly.binary2hex(s);
                ui->numberConvert_2->setText(QString::fromStdString(ss.str()));
            }catch(const std::exception& e){
                errorMsg("Error Format");
                return;
            }
        }
    }
    else if(ui->chooseNumber->currentIndex() == 2){//double的表示
        if(ui->chooseRadix->currentIndex() == 0){
            try{
                QString text = ui->inputNumber->text();
                double number = stod(text.toStdString());
                ui->numberConvert_1->setText(QString::fromStdString(Double_change.double2binary(number)));
                ostringstream ss;
                ss << disassembly.binary2hex(Double_change.double2binary(number).substr(0,32));
                ss << disassembly.binary2hex(Double_change.double2binary(number).substr(32,32));
                ui->numberConvert_2->setText(QString::fromStdString(ss.str()));
            }catch(const std::exception& e){
                errorMsg("Error Format");
                return;
            }
        }
        else if(ui->chooseRadix->currentIndex() == 1){
            QString text = ui->inputNumber->text();
            string s = text.toStdString();
            if(s.length() != 64){
                errorMsg("Format Error");
                return;
            }
            try{
                ui->numberConvert_1->setText(QString::fromStdString(to_string(Double_change.binary2double(s))));
                ostringstream ss;
                ss << disassembly.binary2hex(s.substr(0,32));
                ss << disassembly.binary2hex(s.substr(32,32));
                ui->numberConvert_2->setText(QString::fromStdString(ss.str()));
            }catch(const std::exception& e){
                errorMsg("Error Format");
                return;
            }
        }
    }
}


void MainWindow::on_numberCalculateButton_clicked()
{
    string text = ui->numberCalculate->text().toStdString();
    if(text == ""){
        errorMsg("Text is empty!");
        return;
    }

    regex pattern("\\s*([\\da-fA-F]+\\.?[\\da-fA-F]*)\\s*([\\+\\-\\*/])\\s*([\\da-fA-F]+\\.?[\\da-fA-F]*)\\s*");
    smatch result;
    if(ui->chooseNumber->currentIndex() == 0){// 整数的原码与补码表示
        if(ui->chooseRadix->currentIndex() == 0){//输入十进制数
            if(regex_match(text, result, pattern)){
                try{
                    int number_1 = stoi(result[1].str());
                    char op = result[2].str().at(0);
                    int number_2 = stoi(result[3].str());
                    int number = 0;
                    switch(op){
                    case '+':{
                        number = number_1 + number_2;
                        break;
                    }
                    case '-':{
                        number = number_1- number_2;
                        break;
                    }
                    case '*':{
                        number = number_1* number_2;
                        break;
                    }
                    case '/':{
                        if(number_2 == 0){
                            errorMsg("Denominator can't be 0");
                            return;
                        }
                        number = number_1/ number_2;
                        break;
                    }
                    default:{
                        errorMsg("Error Format");
                        return;
                    }
                    }
                    ui->inputNumber->setText(QString::fromStdString(to_string(number)));
                    ui->numberConvert_1->setText(QString::fromStdString(Binary_change.Int2Binary(number, 32)));
                    ui->numberConvert_2->setText(QString::fromStdString(Binary_change.Int2Complement(number, 32)));
                }catch (const std::exception& e){
                    errorMsg("Error Format");
                    return;
                }
            }else{
                errorMsg("Error Format");
                return;
            }
        }
        else if(ui->chooseRadix->currentIndex() == 1){//输入二进制数
            if(regex_match(text, result, pattern)){
                try{
                    int number_1 = stoi(result[1].str(), 0, 2);
                    char op = result[2].str()[0];
                    int number_2 = stoi(result[3].str(), 0, 2);
                    int number = 0;
                    switch(op){
                    case '+':{
                        number = number_1 + number_2;
                        break;
                    }
                    case '-':{
                        number = number_1- number_2;
                        break;
                    }
                    case '*':{
                        number = number_1* number_2;
                        break;
                    }
                    case '/':{
                        if(number_2 == 0){
                            errorMsg("Denominator can't be 0");
                            return;
                        }
                        number = number_1/ number_2;
                        break;
                    }
                    default:{
                        errorMsg("Error Format");
                        return;
                    }
                    }
                    ui->inputNumber->setText(QString::fromStdString(Binary_change.Int2Binary(number, 32)));
                    ui->numberConvert_1->setText(QString::fromStdString(to_string(number)));
                    ui->numberConvert_2->setText(QString::fromStdString(Binary_change.Int2Complement(number, 32)));
                }catch(const std::exception& e){
                    errorMsg("Error Format");
                    return;
                }
            }else{
                errorMsg("Error Format");
                return;
            }
        }
        else if(ui->chooseRadix->currentIndex() == 2){//输入十六进制数
            if(regex_match(text, result, pattern)){
                try{
                    int number_1 = stoi(result[1].str(), 0, 16);
                    char op = result[2].str()[0];
                    int number_2 = stoi(result[3].str(), 0, 16);
                    int number = 0;
                    switch(op){
                    case '+':{
                        number = number_1 + number_2;
                        break;
                    }
                    case '-':{
                        number = number_1- number_2;
                        break;
                    }
                    case '*':{
                        number = number_1* number_2;
                        break;
                    }
                    case '/':{
                        if(number_2 == 0){
                            errorMsg("Denominator can't be 0");
                            return;
                        }
                        number = number_1/ number_2;
                        break;
                    }
                    default:{
                        errorMsg("Error Format");
                        return;
                    }
                    }
                    ui->inputNumber->setText(QString::fromStdString(disassembly.binary2hex(Binary_change.Int2Binary(number, 32))));
                    ui->numberConvert_1->setText(QString::fromStdString(to_string(number)));
                    ui->numberConvert_2->setText(QString::fromStdString(Binary_change.Int2Complement(number, 32)));
                }catch(const std::exception& e){
                    errorMsg("Error Format");
                    return;
                }
            }else{
                errorMsg("Error Format");
                return;
            }
        }
    }
    else if(ui->chooseNumber->currentIndex() == 1){//float的表示
        if(ui->chooseRadix->currentIndex() == 0){
            if(regex_match(text, result, pattern)){
                try{
                    float number_1 = stof(result[1].str());
                    char op = result[2].str()[0];
                    float number_2 = stof(result[3].str());
                    float number = 0;
                    switch(op){
                    case '+':{
                        number = number_1 + number_2;
                        break;
                    }
                    case '-':{
                        number = number_1- number_2;
                        break;
                    }
                    case '*':{
                        number = number_1* number_2;
                        break;
                    }
                    case '/':{
                        if(number_2 == 0){
                            errorMsg("Denominator can't be 0");
                            return;
                        }
                        number = number_1/ number_2;
                        break;
                    }
                    default:{
                        errorMsg("Error Format");
                        return;
                    }
                    }
                    ui->inputNumber->setText(QString::fromStdString(to_string(number)));
                    if(number == 0){
                        string _s(32, '0');
                        ui->numberConvert_1->setText(QString::fromStdString(_s));
                        ui->numberConvert_2->setText(QString::fromStdString(_s.substr(0,8)));
                        return;
                    }
                    ui->numberConvert_1->setText(QString::fromStdString(Float_change.float2binary(number)));
                    ostringstream ss;
                    ss << disassembly.binary2hex(Float_change.float2binary(number));
                    ui->numberConvert_2->setText(QString::fromStdString(ss.str()));
                }catch(const std::exception& e){
                    errorMsg("Error Format");
                    return;
                }
            }else{
                errorMsg("Error Format");
                return;
            }
        }
        else if(ui->chooseRadix->currentIndex() == 1){
            if(regex_match(text, result, pattern)){
                try{
                    if(result[1].str().length() != 32){
                        errorMsg("Format Error");
                        return;
                    }
                    Float number_1(result[1].str());
                    char op = result[2].str()[0];
                    string number = "";
                    switch(op){
                    case '+':{
                        number = number_1 + result[3].str();
                        break;
                    }
                    case '-':{
                        number = number_1 - result[3].str();
                        break;
                    }
                    case '*':{
                        number = number_1 * result[3].str();
                        break;
                    }
                    case '/':{
                        if(stoi(result[3].str(), 0, 2) == 0){
                            errorMsg("Denominator can't be 0");
                            return;
                        }
                        number = number_1 / result[3].str();
                        break;
                    }
                    default:{
                        errorMsg("Error Format");
                        return;
                    }
                    }

                    ui->inputNumber->setText(QString::fromStdString(number));
                    ui->numberConvert_1->setText(QString::fromStdString(to_string(Float_change.binary2float(number))));
                    ostringstream ss;
                    ss << disassembly.binary2hex(number);
                    ui->numberConvert_2->setText(QString::fromStdString(ss.str()));
                }catch(const std::exception& e){
                    errorMsg("Error Format");
                    return;
                }
            }else{
                errorMsg("Error Format");
                return;
            }
        }
    }
    else if(ui->chooseNumber->currentIndex() == 2){//double的表示
        if(ui->chooseRadix->currentIndex() == 0){//输入double
            if(regex_match(text, result, pattern)){
                try{
                    double number_1 = stod(result[1].str());
                    char op = result[2].str()[0];
                    double number_2 = stod(result[3].str());
                    double number = 0;
                    switch(op){
                    case '+':{
                        number = number_1 + number_2;
                        break;
                    }
                    case '-':{
                        number = number_1 - number_2;
                        break;
                    }
                    case '*':{
                        number = number_1 * number_2;
                        break;
                    }
                    case '/':{
                        if(number_2 == 0){
                            errorMsg("Denominator can't be 0");
                            return;
                        }
                        number = number_1 / number_2;
                        break;
                    }
                    default:{
                        errorMsg("Error Format");
                        return;
                    }
                    }
                    ui->inputNumber->setText(QString::fromStdString(to_string(number)));
                    if(number == 0){
                        string _s(64, '0');
                        ui->numberConvert_1->setText(QString::fromStdString(_s));
                        ui->numberConvert_2->setText(QString::fromStdString(_s.substr(0,16)));
                        return;
                    }
                    ui->numberConvert_1->setText(QString::fromStdString(Double_change.double2binary(number)));
                    ostringstream ss;
                    ss << disassembly.binary2hex(Double_change.double2binary(number).substr(0,32));
                    ss << disassembly.binary2hex(Double_change.double2binary(number).substr(32,32));
                    ui->numberConvert_2->setText(QString::fromStdString(ss.str()));
                }catch(const std::exception& e){
                    errorMsg("Error Format");
                    return;
                }
            }else{
                errorMsg("Error Format");
                return;
            }
        }
        else if(ui->chooseRadix->currentIndex() == 1){
            if(regex_match(text, result, pattern)){
                if(result[1].str().length() != 64){
                    errorMsg("Format Error");
                    return;
                }
                try{
                    Double number_1(result[1].str());
                    char op = result[2].str()[0];
                    string number = "";
                    switch(op){
                    case '+':{
                        number = number_1 + result[3].str();
                        break;
                    }
                    case '-':{
                        number = number_1 - result[3].str();
                        break;
                    }
                    case '*':{
                        number = number_1 * result[3].str();
                        break;
                    }
                    case '/':{
                        if(stoi(result[3].str(), 0, 2) == 0){
                            errorMsg("Denominator can't be 0");
                            return;
                        }
                        number = number_1 / result[3].str();
                        break;
                    }
                    default:{
                        errorMsg("Error Format");
                        return;
                    }
                    }
                    ui->inputNumber->setText(QString::fromStdString(number));
                    ui->numberConvert_1->setText(QString::fromStdString(to_string(Double_change.binary2double(number))));
                    ostringstream ss;
                    ss << disassembly.binary2hex(number.substr(0,32));
                    ss << disassembly.binary2hex(number.substr(32,32));
                    ui->numberConvert_2->setText(QString::fromStdString(ss.str()));
                }catch(const std::exception& e){
                    errorMsg("Error Format");
                    return;
                }
            }else{
                errorMsg("Error Format");
                return;
            }
        }
    }
}


void MainWindow::on_debugButton_clicked()
{
    if(DEBUG_Start == false){
        if(DEBUG_Line != 0){
            DEBUG_Line = 0;
        }
//        QString str = ui->memoryTable->item(0, 1)->text();
//        string hs = str.toStdString();
//        hs = hs.substr(1, hs.length()-1);
//        string bs = disassembly.hex2binary(hs);
//        vector<string> bsArray;
//        bsArray.push_back(bs);
//        mips.load(bsArray, 0);

//        DEBUG_Start = true;

//        mips.debug[DEBUG_Line] = true;


        mips.initial();
        ui->memoryTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        //设置选中行的背景色，必须要显示设置，即代码设置或者在ui文件的控件中设置，用系统默认的是无法代码选中高亮某行
        ui->memoryTable->setStyleSheet("selection-background-color:rgb(215,209,215)");
        //设置要选中高亮的行，这里会触发QTableWidget::itemClicked的信号


        DEBUG_Start = true;

        mips.load(mips.machine_code, assembler.labels["main"]);
        ui->memoryTable->selectRow(assembler.labels["main"]/4);
    }
    else if(DEBUG_Start == true){
        if(mips.execute()){
            ui->memoryTable->selectRow(mips.PC/4);
        }
        else{
            DEBUG_Start = false;
            ui->memoryTable->clearSelection();
            ui->memoryTable->setSelectionBehavior(QAbstractItemView::SelectItems);
        }
    }

    ostringstream ss;
    ss << "x" << setfill('0') << setw(8) << hex << mips.PC;
    ui->regTable->setItem(0, 1, new QTableWidgetItem(QString::fromStdString(ss.str())));
    ss.str("");
    ss << "x" << setfill('0') << setw(8) << hex << mips.PC+4;
    ui->regTable->setItem(1, 1, new QTableWidgetItem(QString::fromStdString(ss.str())));
    for(int i=0; i < 32; i++){
        ss.str("");
        ss << "x" << setfill('0') << setw(8) << hex << mips.reg[i];
        ui->regTable->setItem(i+2, 1, new QTableWidgetItem(QString::fromStdString(ss.str())));
    }
    for(int i=0; i < 65536; i++){
        ss.str("");
        ss << "x" << setfill('0') << setw(8) << hex << mips.memo[i];
        ui->memoryTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(ss.str())));
    }
}


void MainWindow::on_exitButton_clicked()
{
    if(DEBUG_Start == true){
        DEBUG_Start = false;
        ui->memoryTable->clearSelection();
        ui->memoryTable->setSelectionBehavior(QAbstractItemView::SelectItems);
    }
}


void MainWindow::on_nextStepButton_clicked()
{
    if(DEBUG_Start == true){
        if(mips.execute()){
            ui->memoryTable->selectRow(mips.PC/4);
        }
        else{
            DEBUG_Start = false;
            ui->memoryTable->clearSelection();
            ui->memoryTable->setSelectionBehavior(QAbstractItemView::SelectItems);
        }

        ostringstream ss;
        ss << "x" << setfill('0') << setw(8) << hex << mips.PC;
        ui->regTable->setItem(0, 1, new QTableWidgetItem(QString::fromStdString(ss.str())));
        ss.str("");
        ss << "x" << setfill('0') << setw(8) << hex << mips.PC+4;
        ui->regTable->setItem(1, 1, new QTableWidgetItem(QString::fromStdString(ss.str())));
        for(int i=0; i < 32; i++){
            ss.str("");
            ss << "x" << setfill('0') << setw(8) << hex << mips.reg[i];
            ui->regTable->setItem(i+2, 1, new QTableWidgetItem(QString::fromStdString(ss.str())));
        }
        for(int i=0; i < 65536; i++){
            ss.str("");
            ss << "x" << setfill('0') << setw(8) << hex << mips.memo[i];
            ui->memoryTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(ss.str())));
        }
    }
}

