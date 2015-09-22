#include "mmodloader.h"

QString ModLoader::getName(){
	return "BaseModLoader";
}

void ModLoader::setVars(GVars *v) {
 this->vars = v;
	this->log = reinterpret_cast<GLogger*>(vars->get("logger"));

	log->log(GLogLevel::INFO, "Main", "ModLoader Inited");
}

void ModLoader::corePreInit(){
	this->log->log(GLogLevel::FINE, "Main", "corePreInit finished");
}
void ModLoader::coreInit(){
	this->log->log(GLogLevel::FINE, "Main", "coreInit finished");
}
void ModLoader::corePostInit(){
	this->log->log(GLogLevel::FINE, "Main", "corePostInit finished");
}

void ModLoader::preInit(){
	this->log->log(GLogLevel::FINE, "Main", "preInit finished");
}
void ModLoader::init(){
	this->log->log(GLogLevel::FINE, "Main", "init finished");
}
void ModLoader::postInit(){
	this->log->log(GLogLevel::FINE, "Main", "postInit finished");
}


