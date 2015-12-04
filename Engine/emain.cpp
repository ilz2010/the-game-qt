#include <time.h>
#include "Engine/emain.h"

int main(int argc, char *argv[]){
	QApplication a(argc, argv);
	QCoreApplication::setOrganizationName("IlzSoft");
	QCoreApplication::setOrganizationDomain("github.com/ilz2010");
	QCoreApplication::setApplicationName("The game");

	GV_LOGGER = new ELogger;
	GV_VARS = new EVars;

 EMain * gMain = new EMain();
	gMain->init();
 gMain->show();

	return a.exec();
}

EMain::EMain() {
 srand(unsigned(int(time(NULL))));

 varS(this, "eMain");
	varS(GV_LOGGER, "eLogger");

	mods = new EMods();

	varS(wgt, "eMainWindow");
	varS(wdev, "eDev");
	varS(mods, "eMods");
}

void EMain::init() {
	mods->coreInit();

	wgt = new EMWidget();
	wdev = new EDeveloper();

 mods->init();
}

void EMain::show() {
	//wdev->show();
	wgt->show();
}

void EMain::destroy() {

}