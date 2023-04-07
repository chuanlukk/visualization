#include "mysort.h"

MySort::MySort(int radius, QString name, QString desc, int _type, QWidget *parent) :
    QWidget(parent),
    sortName(name),
    sortDescription(desc),
    type(_type)
{
    mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(mainLayout);
    sortCanvas = new MainCanvas();
    mainLayout->addWidget(sortCanvas);

    this->setFocusPolicy(Qt::ClickFocus);

    CreateSettings(radius);
}

MySort::MySort(QTextStream &ts, int radius, QWidget *parent) :
    QWidget(parent)
{
    sortName = ts.readLine();
    sortDescription = ts.readLine();
    ts >> type;

    mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(mainLayout);
    sortCanvas = new MainCanvas();
    mainLayout->addWidget(sortCanvas);

    this->setFocusPolicy(Qt::ClickFocus);

    CreateSettings(radius);
}

void MySort::CreateSettings(int r)
{
    //侧页-单击排序页面设置
    settings = new SlidePage(r, "SETTINGS", this->parentWidget());

    textInputItem * rename = new textInputItem("Name", this);
    rename->setValue(sortName);
    connect(rename, &textInputItem::textEdited, this, [=](QString text){
        sortName = text;
        emit nameChanged(text);
    });

    textInputItem * redesc = new textInputItem("Detail", this);
    redesc->setValue(sortDescription);
    connect(redesc, &textInputItem::textEdited, this, [=](QString text){
        sortDescription = text;
        emit descChanged(text);
    });

    QWidget * whiteSpace = new QWidget(this);
    whiteSpace->setFixedHeight(30);

//    textButton * saveBtn = new textButton("Save to file", this);
//    connect(saveBtn, &textButton::clicked, this, [=](){
//        QString savePath = QFileDialog::getSaveFileName(this, tr("Save Visualizetion"), " ", tr("Map file(*.map)"));
//        if(!savePath.isEmpty()) SaveToFile
//    })

    textButton * delBtn = new textButton("Delete", "#0acb1b45", "#1acbab45", "#2acbab45", this);
    connect(delBtn, &textButton::clicked, this, [=](){emit setDel(this);});
    settings->AddContent(delBtn);
    settings->AddContent(whiteSpace);
    settings->AddContent(redesc);
    settings->AddContent(rename);
    settings->show();

    QTimer *delay = new QTimer(this);
    connect(delay, &QTimer::timeout, this, [=](){Init();});
    delay->setSingleShot(true);
    delay->start(10);
}

void MySort::Init()
{
    cntlWidget = new QWidget(this);
    mainLayout->addWidget(cntlWidget);
    mainLayout->setStretch(0, 7);
    mainLayout->setStretch(1, 3);
    cntlWidget->setFixedWidth(250);
//    cntlWidget->setFixedWidth(500);

    QVBoxLayout *cntlLayout = new QVBoxLayout(cntlWidget);
    cntlWidget->setLayout((cntlLayout));
    cntlLayout->setContentsMargins(10, 0, 0, 0);
    cntlLayout->setAlignment(Qt::AlignTop);

    contentContainer * control = new contentContainer("CONTROL", cntlWidget);
    textInputItem *num = new textInputItem("Amount", control);
    horizontalValueAdjuster *aniSpeed = new horizontalValueAdjuster("Animation speed", 1, 199, 1, control);
    textButton *strtBtn = new textButton("Start", cntlWidget);
    textButton *stopBtn = new textButton("END", "#0acb1b45","#1acb1b45","#2acb1b45", cntlWidget);

    control->AddContent(num);
    control->AddContent(aniSpeed);
    control->AddContent(strtBtn);
    control->AddContent(stopBtn);
    cntlLayout->addWidget(control);
//    cntlWidget->show();

//    QVBoxLayout * cntlLayout = new QVBoxLayout(cntlWidget);
//    cntlWidget->setLayout(cntlLayout);
//    cntlLayout->setContentsMargins(10, 0, 0, 0);
//    cntlLayout->setAlignment(Qt::AlignTop);
}





