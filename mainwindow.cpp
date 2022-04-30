#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include "qmessagebox.h"
#include "qlogging.h"
#include "qvalidator.h"
#include "Work.h"
#include "qtimer.h"
#include <QThreadPool>
#include "gamecontext.h"

// 声明函数
//读取阳光值
//DWORD readSunnyValue(HANDLE *handle);
void findSunnyValueTask(HANDLE hprocess,QLabel &sunnyLabel);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // 设置IU
    ui->setupUi(this);


    timer = new QTimer(this);
    timer->setInterval(std::chrono::seconds(1));


    // 设置文本框可输入内容
    ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("\\d{0,10}"),ui->lineEdit));

   // 启动线程检查窗口
    qRegisterMetaType<HWND>("HWND");
    Work *w = new Work(this);
    connect(w,&Work::gameRuning,this,&MainWindow::setupComponentEnable);
    connect(w,SIGNAL(gameNoRun()),this, SLOT(setupComponentDisable()));
    w->start();


    //初始化无限阳光
     wuxiangSunnyTimer = new QTimer(this);
     connect(wuxiangSunnyTimer,&QTimer::timeout,[=](){
           this->setSunnyOf(999999);
     });


     // 无限冷却
     wulengqueTimer = new QTimer(this);
     wulengqueTimer->setInterval(200);
     connect(wulengqueTimer,&QTimer::timeout,[=](){
           this->resetCooling();
     });

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setupComponentDisable(){
    this->ui->gameStatusLabel->setStyleSheet("color:red;");
    this->ui->gameStatusLabel->setText("游戏未运行");

    this->ui->groupBox->setDisabled(true);

    // 将checkbox设置为未选中
    this->ui->checkBox->setChecked(false);
    this->ui->checkBox_2->setChecked(false);
    this->ui->checkBox_3->setChecked(false);
    this->ui->checkBox_4->setChecked(false);

    timer->stop();
    disconnect(timer,&QTimer::timeout,this,&MainWindow::findSunnyValueTask);
}

void MainWindow::setupComponentEnable(HWND hwnd){
    this->ui->gameStatusLabel->setStyleSheet("color:green;");
    this->ui->gameStatusLabel->setText("游戏运行中");

    // 调用WindowAPI加载进程
    // 获取窗口进程
    DWORD processId;
    GetWindowThreadProcessId(hwnd,&processId);

    // 打开进程
    hprocess = OpenProcess(PROCESS_ALL_ACCESS,false,processId);

    if(hprocess == 0){
        QMessageBox::information(this,"异常","打开进程失败");
        return ;
    }


    //打开周期任务 定时查询阳光数量
    connect(timer,&QTimer::timeout,this,&MainWindow::findSunnyValueTask);
    timer->start();

    this->ui->groupBox->setEnabled(true);
}

void MainWindow::findSunnyValueTask(){
         DWORD value ;

         this->show();
         if(!ReadProcessMemory(this->hprocess,(LPCVOID)GameContext::BASE_ADDRESS,&value,4,nullptr)){
             qWarning() << "读取内存失败";
             return ;
         }

         if(!ReadProcessMemory(this->hprocess,(LPCVOID)(value+GameContext::SUNNY_OFFSET1),&value,4,nullptr)){
             qWarning() << "读取内存失败";
             return ;
         }

         if(!ReadProcessMemory(this->hprocess,(LPCVOID)(value+GameContext::SUNNY_OFFSET2),&value,4,nullptr)){
             qWarning() << "读取内存失败";
             return ;
         }

         ui->label_3->setText(QString::number((long)value));

}


void MainWindow::on_pushButton_clicked()
{

     QString text = this->ui->lineEdit->text();
     qDebug() << text;
     int  v = text.toInt();

     this->setSunnyOf(v);

}

void MainWindow::setSunnyOf(int sunnyValue){
    DWORD value ;

    this->show();
    if(!ReadProcessMemory(this->hprocess,(LPCVOID)GameContext::BASE_ADDRESS,&value,4,nullptr)){
        qWarning() << "读取内存失败";
        return ;
    }

    if(!ReadProcessMemory(this->hprocess,(LPCVOID)(value+GameContext::SUNNY_OFFSET1),&value,4,nullptr)){
        qWarning() << "读取内存失败";
        return ;
    }


     WriteProcessMemory(this->hprocess,(LPVOID)(value+GameContext::SUNNY_OFFSET2),(LPCVOID)(&sunnyValue),4,nullptr);
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{



    if(this->ui->checkBox->isChecked()){
        // 开启无限阳光
         wuxiangSunnyTimer->start(300);
    }else{
        // 关闭无限阳光
        wuxiangSunnyTimer->stop();

    }
}


void MainWindow::on_checkBox_2_stateChanged(int arg1)
{

    if(ui->checkBox_2->isChecked()){
        wulengqueTimer->start();
    }else{
        wulengqueTimer->stop();
    }
}

void MainWindow::resetCooling(){


    DWORD value ;

    this->show();
    if(!ReadProcessMemory(this->hprocess,(LPCVOID)GameContext::BASE_ADDRESS,&value,4,nullptr)){
        qWarning() << "读取内存失败";
        return ;
    }

    if(!ReadProcessMemory(this->hprocess,(LPCVOID)(value+GameContext::cooling_offset1),&value,4,nullptr)){
        qWarning() << "读取内存失败";
        return ;
    }

    if(!ReadProcessMemory(this->hprocess,(LPCVOID)(value+GameContext::cooling_offset2),&value,4,nullptr)){
        qWarning() << "读取内存失败";
        return ;
    }



    int len = sizeof(GameContext::cooling_offset3)/sizeof(int);


    for(int i = 0;i<len ;i++){
        int offset = GameContext::cooling_offset3[i];

        // qDebug() << QString::number(value,16) << "=="<<len<<"=="<<QString::number(offset,16);
        WriteProcessMemory(this->hprocess,(LPVOID)(value+offset),(LPCVOID)&GameContext::cooling_ok,1,nullptr);
    }


}
