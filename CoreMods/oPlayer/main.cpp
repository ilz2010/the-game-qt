#include "main.h"

QStringList CM_O_PLAYER::getOwList() {
	return {"mPlayer"};
}

QStringList CM_O_PLAYER::getDpList() {
	return {};
}

void CM_O_PLAYER::setVars(IVars *v) {
	IV_VARS = v;
	IV_LOGGER = reinterpret_cast<ILogger*>(v->get("eLogger"));
}

void CM_O_PLAYER::preInit() {}

void CM_O_PLAYER::init() {}

void CM_O_PLAYER::postInit() {}


void *CM_O_PLAYER::get(QString name) {
	logI("Get " + name);

	if(name == "mPlayer"){
		if(p == nullptr)	p = new MPlayer;
		return p;
	}else{
		return nullptr;
	}
}

void *CM_O_PLAYER::getO(QString name) { Q_UNUSED(name)	return nullptr;}

QStringList CM_O_PLAYER::getVarsList() {
	return {"mPlayer"};
}

ILogger* IV_LOGGER;
IVars*   IV_VARS;