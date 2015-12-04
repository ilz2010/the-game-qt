#undef CLASS_NAME
#define CLASS_NAME "GMWidget"
#include "Engine/ewidgets.h"

EMWidget::EMWidget():QOpenGLWidget(){
	setAutoFillBackground(false);
	this->render = varG(IRender*, "mRender");
}

void EMWidget::animate(){
	update();
}

void EMWidget::paintEvent(QPaintEvent *event){
	if(render)
		render->render(this);



	event->accept();
}


EDeveloper::EDeveloper(){
	lay = new QVBoxLayout();

	bsett = new QPushButton("Settings Editor");
	blevl = new QPushButton("Level Editor");
	bmods = new QPushButton("Mods Editor");
	bmodl = new QPushButton("Model Editor");
	bpack = new QPushButton("Resource Packer");
	bresm = new QPushButton("Resource Manager");

	lay->addWidget(bsett);
	lay->addWidget(blevl);
	lay->addWidget(bmods);
	lay->addWidget(bmodl);
	lay->addWidget(bpack);
	lay->addWidget(bresm);

	this->setLayout(lay);

	connect(bsett, SIGNAL(clicked()), this, SLOT(showSett()));
	connect(blevl, SIGNAL(clicked()), this, SLOT(showLevl()));
	connect(bmods, SIGNAL(clicked()), this, SLOT(showMods()));
	connect(bmodl, SIGNAL(clicked()), this, SLOT(showModl()));
	connect(bpack, SIGNAL(clicked()), this, SLOT(showPack()));
	connect(bresm, SIGNAL(clicked()), this, SLOT(showResm()));
}

void EDeveloper::showSett(){

}

void EDeveloper::showLevl(){

}

void EDeveloper::showMods(){

}

void EDeveloper::showModl(){

}

void EDeveloper::showPack(){

}

void EDeveloper::showResm(){

}

void EMWidget::closeEvent(QCloseEvent *event) {
	varG(EMain*, "eMain")->destroy();
}